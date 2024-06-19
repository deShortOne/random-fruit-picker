#pragma once

#include <mutex>
#include <string>

class Fruit // should be named item or something more generic
{
public:
    Fruit(const std::string &name, const uint32_t minRange, const uint32_t maxRange);
    uint32_t getRunningTotal() const noexcept { return m_runningTotal; }
    uint32_t addToRunningTotal(const uint32_t value) noexcept;
    bool isValueWithinRange(const uint32_t value) const noexcept;
    const std::string &getName() const noexcept { return m_name; }

private:
    const std::string m_name;
    const uint32_t m_minRange;
    const uint32_t m_maxRange; // inclusive
    std::mutex m_mutex;
    uint32_t m_runningTotal = 0;
};
