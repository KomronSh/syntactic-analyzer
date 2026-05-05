#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <cctype>
#include <string>
#include <regex>
using namespace std;

map<string, string> lexemes{
    {"keyStart",       "Var"},
    {"keyStartVars",   "Begin"},
    {"keyEndVars",     "Boolean"},
    {"constTrue",      "1"},
    {"constFalse",     "0"},
    {"unaryOperand",   "XOR"},
    {"binaryNot",      "NOT"},
    {"binaryOR",       "OR"},
    {"binaryAND",      "AND"},
    {"parenthLeft",    "("},
    {"parenthRight",   ")"},
    {"terminalComma",  ","},
    {"terminalPeriod", "."},
    {"colon",          ":"},
    {"equal",          "="},
    {"lineEnd",        ";"},
    {"keyStop",        "End"}
};

regex identifier("[a-zA-Z_]+");

bool lexical_analiz()
{
    ifstream in("source_code.txt");
    ofstream out("lexem.txt");

    if (!in) {
        cerr << "Error opening file" << endl;
		return false;
    }

    char ch{};
    string strLex{};
    int lineNumber = 1;

    auto printLex = [&](string value) {
        bool found = false;
        for (auto pair : lexemes) {
            if (pair.second == value) {
                out << lineNumber << " " << value << " " << pair.first << "\n";
                found = true;
                break;
            }
        }
        if (!found && regex_match(value, identifier)) {
            out << lineNumber << " " << value << " Identifier" << "\n";
            found = true;
        }

        strLex = "";
    };

    while (in.get(ch)) {
        if (ch == '\n') lineNumber++;

        if (isalpha(ch) || isdigit(ch) || ch == '_') {
            strLex += ch;
        }
        else if (ch == '=' || ch == ',' || ch == ';' || ch == '(' || ch == ')') {
            if (strLex != "") printLex(strLex);
            printLex(string(1, ch));
        }
        else if (ch == '.' || ch == ':') {
            if (strLex != "") printLex(strLex);
            printLex(string(1, ch));
        }
        else if (strLex != "") {
            printLex(strLex);
        }
        else if (isspace(ch)) {
            continue;
        }
        else {
            cout << lineNumber << " " << ch << " Not found!" << "\n";
            out << lineNumber << " " << ch << " Not found!" << "\n";
			return false;
        }
    }

    in.close();
    out.close();
	return true;
}