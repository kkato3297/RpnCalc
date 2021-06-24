#include <MemoryRepository.h>

MemoryRepository& MemoryRepository::getInstance(void)
{
    static MemoryRepository instance;
    return instance;
};

MemoryRepository::MemoryRepository(void) : m_storage()
{}

void MemoryRepository::set(const MemoryKey& key, const std::string& value)
{
    m_storage[key] = value;
}

const std::string MemoryRepository::get(const MemoryKey& key)
{
    if (m_storage.find(key) == m_storage.end()) {
        return std::string("0");
    }

    return m_storage[key];
}
