#include <chrono>
#include <thread>

#include "fruit.h"

Fruit::Fruit(const std::string &name,
             const uint32_t minRange,
             const uint32_t maxRange) : m_name(name),
                                        m_minRange(minRange),
                                        m_maxRange(maxRange)
{
}

uint32_t Fruit::addToRunningTotal(const uint32_t value) noexcept
{
    std::lock_guard<std::mutex> guard(m_mutex);
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
    m_runningTotal += value;
    return m_runningTotal;
}

bool Fruit::isValueWithinRange(const uint32_t value) const noexcept
{
    return value >= m_minRange && value <= m_maxRange;
}
