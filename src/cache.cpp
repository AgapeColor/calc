#include "cache.h"

void Cache::load(const std::vector<OperationRecord>& operationHistory) {
    for (const auto& record : operationHistory) {
        std::string key = makeCacheKey(record);
        cache_.insert({key, record});
    }
}

bool Cache::contains(const OperationRecord& record) const {
    std::string key = makeCacheKey(record);
    return cache_.find(key) != cache_.end();
}

OperationRecord Cache::get(const OperationRecord& record) const {
    std::string key = makeCacheKey(record);
    auto found = cache_.find(key);
    if (found == cache_.end()) {
        throw std::logic_error("Operation not found in cache: " + key);
    }
    return found->second;
}

void Cache::insert(const OperationRecord& record) {
    if (record.status_ != 0) return;
    std::string key = makeCacheKey(record);
    cache_.insert({key, record});
}

std::string Cache::makeCacheKey(const OperationRecord& record) {
    if (record.operation_ != "fact" && !record.arg2_.has_value()) {
        throw std::logic_error("arg2 is missing for binary operation: " + record.operation_);
    }
    return record.operation_ + ":" + std::to_string(record.arg1_) + ":" 
            + ((record.arg2_.has_value()) ? std::to_string(*record.arg2_) : "");
}