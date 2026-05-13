#pragma once

namespace SqlQueries {
    inline constexpr const char* CreateOperationsTable = 
        "CREATE TABLE IF NOT EXISTS operations ("
        "id SERIAL PRIMARY KEY, "
        "operation TEXT NOT NULL, "
        "arg1 INTEGER NOT NULL, "
        "arg2 INTEGER, "
        "result INTEGER, "
        "status INTEGER NOT NULL"
        ")";

    inline constexpr const char* InsertOperation = 
        "INSERT INTO operations (operation, arg1, arg2, result, status) "
        "VALUES ($1, $2, $3, $4, $5)";

    inline constexpr const char* SelectAllOperations = 
        "SELECT operation, "
        "arg1, "
        "arg2, "
        "result, "
        "status FROM operations WHERE status = 0";
}

namespace SqlColumns {
    inline constexpr int Operation = 0;
    inline constexpr int Arg1      = 1;
    inline constexpr int Arg2      = 2;
    inline constexpr int Result    = 3;
    inline constexpr int Status    = 4;
}
