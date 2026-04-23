#include <postgresql/libpq-fe.h>

class PostgresResult {
public:
    PostgresResult(PGresult* result);

    PostgresResult(const PostgresResult& obj) = delete;
    PostgresResult& operator=(const PostgresResult& obj)  = delete;
    PostgresResult(PostgresResult&& obj) noexcept;
    PostgresResult& operator=(PostgresResult&& obj) noexcept;

    ~PostgresResult();

private:
    PGresult* result_ = nullptr;
};