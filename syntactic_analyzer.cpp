#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "lexical_analizer.h"
using namespace std;

struct Lexem {
    int    line;
    string value;
    string type;
};

Lexem lex;
int errorCount = 0;

ifstream in("lexem.txt");
ofstream logFile("errors.log");


bool S();
bool A();
bool B();
bool C();
bool C1();
bool D();
bool D1();
bool E();
bool F();
bool G();
bool G1();
bool H();
bool O();
bool readNext();
void error(const string& msg);
bool isIdent();
bool isConst();
bool isBinaryOp();

int main() {
    if (!lexical_analiz()) {
        cout << "Ошибка: не удалось провести лексический анализ\n";
        return 1;
    }
    if (!readNext()) {
        cout << "Ошибка: не удалось прочитать файл лексем\n";
        return 1;
    }
    if (S()) {
        cout << "\nСинтаксический анализ завершён успешно\n";
        logFile << "\nСинтаксический анализ завершён успешно\n";
    }
    else {
        cout << "\nСинтаксический анализ завершён с ошибками\n";
        logFile << "\nСинтаксический анализ завершён с ошибками\n";
    }

    cout << "Всего ошибок: " << errorCount << "\n";
    logFile << "Всего ошибок: " << errorCount << "\n";

    if (logFile.is_open()) logFile.close();
    return (errorCount > 0) ? 1 : 0;
}

bool readNext() {
    if (!in.is_open()) return false;
    if (in.eof())      return false;
    in >> lex.line >> lex.value >> lex.type;
    return !in.fail();
}

void error(const string& msg) {
    errorCount++;
    string errorMsg = "Ошибка " + to_string(errorCount) 
        + ": " + msg
        + " строки " + to_string(lex.line)
        + " лексемы: '" + lex.value + "'"
        + " тип: " + lex.type;
    cout << errorMsg << "\n";

    if (logFile.is_open()) {
        logFile << errorMsg << "\n";
    }
}

bool isIdent() {
    return lex.type == "Identifier";
}

bool isConst() {
    return lex.type == "constFalse" || lex.type == "constTrue";
}

bool isBinaryOp() {
    return lex.type == "binaryAND" ||
        lex.type == "binaryOR" ||
        lex.type == "unaryOperand";
}

bool S() {
    if (!A()) return false;
    if (!B()) return false;
    if (lex.type != "terminalPeriod") {
        error("Ожидалась точка '.' в конце программы");
        return false;
    }
    readNext();
    return true;
}

bool A() {
    if (lex.type != "keyStart") {
        error("Ожидалось ключевое слово 'Var'");
        return false;
    }
    readNext();
    if (!C()) return false;
    if (lex.type != "colon") {
        error("Ожидалось двоеточие ':'");
        return false;
    }
    readNext();
    if (lex.type != "keyEndVars") {
        error("Ожидалось ключевое слово 'Boolean'");
        return false;
    }
    readNext();
    if (lex.type != "lineEnd") {
        error("Ожидалась ';' после Boolean");
        return false;
    }
    readNext();
    return true;
}

bool B() {
    if (lex.type != "keyStartVars") {
        error("Ожидалось ключевое слово 'Begin'");
        return false;
    }
    readNext();
    if (!D()) return false;
    if (lex.type != "keyStop") {
        error("Ожидалось ключевое слово 'End'");
        return false;
    }
    readNext();
    return true;
}

bool C() {
    if (!isIdent()) {
        error("Ожидался идентификатор в списке переменных");
        return false;
    }
    readNext();
    return C1();
}

bool C1() {
    if (lex.type == "terminalComma") {
        readNext();
        if (!isIdent()) {
            error("Ожидался идентификатор после запятой");
            return false;
        }
        readNext();
        return C1();
    }
    return true;
}

bool D() {
    if (isIdent()) {
        if (!E())  return false;
        if (!D1()) return false;
    }
    return true;
}

bool D1() {
    if (isIdent()) {
        if (!E())  return false;
        if (!D1()) return false;
    }
    return true;
}

bool E() {
    if (!isIdent()) {
        error("Ожидался идентификатор в левой части присваивания");
        return false;
    }
    readNext();
    if (lex.type != "equal") {
        error("Ожидался знак '='");
        return false;
    }
    readNext();
    if (!F()) return false;
    if (lex.type != "lineEnd") {
        error("Ожидалась ';' в конце присваивания");
        return false;
    }
    readNext();
    return true;
}

bool F() {
    if (lex.type == "terminalPeriod") {
        readNext();
        if (lex.type != "binaryNot") {
            error("Ожидался оператор 'NOT' после '.'");
            return false;
        }
        readNext();
        if (lex.type != "terminalPeriod") {
            error("Ожидалась '.' после 'NOT'");
            return false;
        }
        readNext();
        return F();
    }
    return G();
}

bool G() {
    if (lex.type == "parenthLeft") {
        readNext();
        if (!F()) return false;
        if (lex.type != "parenthRight") {
            error("Ожидалась закрывающая скобка ')'");
            return false;
        }
        readNext();
        return G1();
    }
    if (!O())  return false;
    if (!G1()) return false;
    return true;
}

bool G1() {
    if (lex.type == "terminalPeriod") {
        if (!H()) return false;
        if (!G()) return false;
        return G1();
    }
    return true;
}

bool H() {
    readNext();
    if (!isBinaryOp()) {
        error("Ожидался бинарный оператор AND, OR или XOR");
        return false;
    }
    readNext();
    if (lex.type != "terminalPeriod") {
        error("Ожидалась '.' после оператора AND/OR/XOR");
        return false;
    }
    readNext();
    return true;
}

bool O() {
    if (isIdent()) {
        readNext();
        return true;
    }
    if (isConst()) {
        readNext();
        return true;
    }
    error("Ожидался идентификатор или константа (0 или 1)");
    return false;
}
