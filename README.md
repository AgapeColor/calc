# calc

CLI-калькулятор для целых чисел (`long long`) с обработкой ошибок (overflow / деление на 0 / неверный ввод).

## Зависимость

Математика вынесена в отдельную header-only библиотеку **calc-math** (подключается через **CMake FetchContent**).
Repo: `https://github.com/AgapeColor/calc-math.git`

## Операции

`add`, `sub`, `mul`, `div`, `pow` (итеративно), `fact` (рекурсивно). 

## Сборка / установка

```bash
cmake -B build
cmake --build build
sudo cmake --build build --target install
```

## Использование

Парсинг аргументов: `getopt_long`.

```bash
./build/calc -h
./build/calc -o add  -a 2 -b 3
./build/calc -o div  -a 10 -b 2
./build/calc -o pow  -a 2 -b 10
./build/calc -o fact -a 5
```

Опции: 

* `-o, --op   add|sub|mul|div|pow|fact`
* `-a, --a    first integer`
* `-b, --b    second integer (not for fact)`
* `-h, --help show help`

## Архитектура

Поток выполнения: `main -> run -> parse -> check -> calculate -> print`.  
Сущности: Runner / Parser / Checker / Calculator / Printer.     

## Code style / static analysis

В корне проекта: `.clang-format`, `.clang-tidy`.

Форматирование кода:
```bash
cmake --build build --target format
```
