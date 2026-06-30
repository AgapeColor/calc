# calc

TCP-сервис калькулятора для целых чисел (`int`), принимающий JSON-запросы по сети и возвращающий JSON-ответы с результатом или ошибкой.

## Зависимости

Системные зависимости:

* **PostgreSQL** (`libpq-dev`) — хранение истории операций
* **Boost.System / Boost.Asio** — сетевое взаимодействие TCP-сервера

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

## DEB-пакет и systemd

### Сборка deb-пакета:

```bash
cmake --build --preset debug
cd build/debug
cpack -G DEB
```

### Установка deb-пакета:

```bash
sudo apt install ./calc-1.0.0-Linux.deb
```

### Управление сервисом:
```bash
sudo systemctl start calc
sudo systemctl restart calc
sudo systemctl stop calc
sudo systemctl status calc
```

## Использование

Сервис запускается без аргументов и начинает слушать TCP-порт `8080`.

### Справка:

```bash
calc --help
calc -h
```

### Ручной запуск после установки:

```bash
calc
```

### Или без установки (из директории сборки):

```bash
./build/debug/calc
```

### Примеры запросов через `nc`:

```bash
printf '{"op":"add","a":2,"b":3}\n' | nc localhost 8080
printf '{"op":"div","a":10,"b":2}\n' | nc localhost 8080
printf '{"op":"pow","a":2,"b":10}\n' | nc localhost 8080
printf '{"op":"fact","a":5}\n' | nc localhost 8080
```

## TCP API

### Формат запроса:

* `op` — операция: `add`, `sub`, `mul`, `div`, `pow`, `fact`
* `a`  — первый операнд
* `b`  — второй операнд (не требуется для `fact`)

### Успешный ответ:

```json
{"result":5}
```

### Ошибка запроса:

```json
{"error":{"type":"request","code":"JSON_PARSE_ERROR"}}
```

### Ошибка вычисления:

```json
{"error":{"type":"math","code":"DIV_BY_ZERO"}}
```

### Внутренняя ошибка сервиса:

```json
{"error":{"type":"internal","code":"INTERNAL_ERROR"}}
```

Важно оставить `\n`, потому что сервер читает запрос через `read_until(..., '\n')`.

## Архитектура

### Сущности:

* `Application` — запускает TCP-сервер и отдельный поток обработки сигналов завершения.
* `TcpServer` — принимает TCP-подключения, читает JSON-запросы и отправляет JSON-ответы.
* `RequestHandler` — связывает парсинг, проверку, кэш, вычисление и сохранение операции.
* `Parser` — преобразует JSON-строку в `Context`.
* `Checker` — проверяет корректность операции и аргументов.
* `Calculator` — выполняет математическое вычисление.
* `ResponseSerializer` — преобразует результат или ошибку в JSON-ответ.
* `PostgresConnection` — работает с PostgreSQL: создаёт таблицу, сохраняет и загружает операции.
* `Cache` — хранит успешные операции и возвращает ранее вычисленный результат.

### Поток выполнения:

**Cache hit:**

```text
main -> Application -> TcpServer -> RequestHandler -> Parser -> Checker -> [cache] -> ResponseSerializer
```

**Cache miss:**

```text
main -> Application -> TcpServer -> RequestHandler -> Parser -> Checker -> Calculator -> save DB -> [cache] -> ResponseSerializer
```

При запуске `main` подключается к PostgreSQL, создаёт таблицу операций и загружает историю успешных операций в `Cache`. `Application` запускает TCP-сервер и обрабатывает завершение по сигналам `SIGINT` / `SIGTERM`.

## Code style / static analysis

В корне проекта: `.clang-format`, `.clang-tidy`.

### Форматирование кода:
```bash
cmake --build build --target format
```

## Анализ памяти и производительности

### Valgrind:
```bash
cmake --build build --target valgrind
cmake --build build --target valgrind_tests
```

### ThreadSanitizer:

```bash
cmake --preset tsan
cmake --build --preset tsan
setarch $(uname -m) -R ctest --test-dir build/tsan --output-on-failure
```
