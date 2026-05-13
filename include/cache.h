#pragma once

#include "operation_record.h"

#include <unordered_map>
#include <string>
#include <vector>
#include <stdexcept>

class Cache {
public:
    void load(const std::vector<OperationRecord>& operationHistory);
    bool contains(const OperationRecord& record) const;
    OperationRecord get(const OperationRecord& record) const;
    void insert(const OperationRecord& record);
private:
    std::unordered_map<std::string, OperationRecord> cache_;
    static std::string makeCacheKey(const OperationRecord& record);
};