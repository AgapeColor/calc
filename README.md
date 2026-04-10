# calc

CLI-калькулятор для целых чисел (`int`) с обработкой ошибок (overflow / деление на 0 / неверный ввод).

## Зависимости

Подключаются через **CMake FetchContent**:

* **calc-math** — header-only библиотека с математическими операциями.
    Repo: `https://github.com/AgapeColor/calc-math.git`
* **nlohmann/json** — парсинг JSON-аргументов
* **spdlog** — логирование
* **googletest** — юнит-тесты

## Операции

`add`, `sub`, `mul`, `div`, `pow` (итеративно), `fact` (рекурсивно). 

## Сборка / установка

```bash
cmake -B build
cmake --build build
sudo cmake --build build --target install
```

## Использование

Программа принимает один аргумент — JSON-строку.

После установки:

```bash
calc --help
calc '{"op":"add","a":2,"b":3}'
calc '{"op":"div","a":10,"b":2}'
calc '{"op":"pow","a":2,"b":10}'
calc '{"op":"fact","a":5}'
```

Или без установки (из директории сборки):

```bash
./build/calc --help
./build/calc '{"op":"add","a":2,"b":3}'
./build/calc '{"op":"div","a":10,"b":2}'
./build/calc '{"op":"pow","a":2,"b":10}'
./build/calc '{"op":"fact","a":5}'

```

JSON-формат:

* `op — операция: add|sub|mul|div|pow|fact`
* `a — первый операнд`
* `b — второй операнд (не требуется для fact)`

## Архитектура

Поток выполнения: `main -> run -> parse -> check -> calculate -> print`.  
Сущности: Runner / Parser / Checker / Calculator / Printer.     

## Code style / static analysis

В корне проекта: `.clang-format`, `.clang-tidy`.

Форматирование кода:
```bash
cmake --build build --target format
```
