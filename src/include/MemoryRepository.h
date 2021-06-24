#pragma once

#include <map>
#include <string>

enum MemoryKey {
    MEMORY_M,
    MEMORY_A,
    MEMORY_B,
    MEMORY_C,
    MEMORY_D,
    MEMORY_X,
    MEMORY_Y,
    MEMORY_ANS
};

class MemoryRepository final {
public:
    static MemoryRepository& getInstance(void);

    MemoryRepository(const MemoryRepository&) = delete;

    void set(const MemoryKey& key, const std::string& value);
    const std::string get(const MemoryKey& key);

private:
    MemoryRepository(void);

    std::map<MemoryKey, std::string> m_storage;
};
