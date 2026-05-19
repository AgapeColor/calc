# calc

CLI-калькулятор для целых чисел (`int`) с обработкой ошибок (overflow / деление на 0 / неверный ввод).

## Зависимости

Системные зависимости:

* **PostgreSQL** (`libpq-dev`) — хранение истории операций

Подключаются через **CMake FetchContent**:

* **calc-math** — header-only библиотека с математическими операциями.
    Repo: `https://github.com/AgapeColor/calc-math.git`
* **nlohmann/json** — парсинг JSON-аргументов
* **spdlog** — логирование
* **googletest** — юнит-тесты

## Операции

`add`, `sub`, `mul`, `div`, `pow` (итеративно), `fact` (рекурсивно). 

## Настройка PostgreSQL

```bash
sudo -u postgres psql
CREATE USER calc_user WITH PASSWORD 'calc';
CREATE DATABASE calc_db OWNER calc_user;
\q
```

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

Поток выполнения:

* Cache hit: `main -> run -> parse -> check -> [cache] -> print`
* Cache miss: `main -> run -> parse -> check -> calculate -> save DB -> [cache] -> print`

Сущности: Runner / Parser / Checker / Calculator / Printer / PostgresConnection / Cache.

При запуске Runner подключается к PostgreSQL, загружает историю успешных операций в кэш (`std::unordered_map`). Повторные запросы с теми же аргументами возвращают результат из кэша без обращения к БД.

## Code style / static analysis

В корне проекта: `.clang-format`, `.clang-tidy`.

Форматирование кода:
```bash
cmake --build build --target format
```

## Анализ памяти и производительности

Valgrind:
```bash
cmake --build build --target valgrind
cmake --build build --target valgrind_tests
```

Профилирование (perf):
```bash
perf stat ./build/debug/calc '{"op":"add","a":2,"b":3}'
perf stat -r 5 ./build/debug/calc '{"op":"add","a":2,"b":3}'
```
