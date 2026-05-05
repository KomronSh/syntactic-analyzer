# Syntax Analyzer

Этот проект реализует лексический и синтаксический анализатор для простого языка с булевыми выражениями.

## Структура проекта
- `lexical_analizer.h` — лексический анализатор, который разбивает исходный код на лексемы и сохраняет их в файл `lexem.txt`.
- `syntactic_analyzer.cpp` — синтаксический анализатор, который читает лексемы из файла и проверяет их на соответствие грамматике.
- `source_code.txt` — пример исходного кода для анализа.

## Как использовать
1. Скомпилируйте оба файла:
   - Включите `lexical_analizer.h` в проект.
   - Соберите и запустите `syntactic_analyzer.cpp`.
2. Поместите исходный код для анализа в файл `source_code.txt`.
3. Запустите программу. Результаты лексического анализа будут в `lexem.txt`, ошибки синтаксиса — в `errors.log`.

## Пример запуска
```
g++ syntactic_analyzer.cpp -o analyzer
./analyzer
```

## Загрузка на GitHub
1. Инициализируйте репозиторий:
   ```
   git init
   git add .
   git commit -m "Initial commit: syntax analyzer"
   git branch -M main
   git remote add origin https://github.com/ВАШ_ЛОГИН/ВАШ_РЕПОЗИТОРИЙ.git
   git push -u origin main
   ```
2. Проверьте, что все файлы (`syntactic_analyzer.cpp`, `lexical_analizer.h`, `source_code.txt`, `README.md`) добавлены в репозиторий.

---

Если потребуется, добавьте инструкции по сборке для вашей IDE или платформы.
