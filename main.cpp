#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <string>
#include <vector>

// would be in seperate files with header and cpp file
class Fruit // should be named item or something more generic
{
public:
    Fruit(const std::string &name, const uint32_t minRange, const uint32_t maxRange);
    uint32_t getRunningTotal() const noexcept { return m_runningTotal; }
    uint32_t addOneToRunningTotal() noexcept; // not a great name as in future you might want to add 2 or 1000
    bool isValueWithinRange(const uint32_t value) const noexcept;
    const std::string &getName() const noexcept { return m_name; }

private:
    const std::string m_name;
    const uint32_t m_minRange;
    const uint32_t m_maxRange; // inclusive
    uint32_t m_runningTotal = 0;
};

// Fruit cpp file
Fruit::Fruit(const std::string &name,
             const uint32_t minRange,
             const uint32_t maxRange) : m_name(name),
                                        m_minRange(minRange),
                                        m_maxRange(maxRange) {}

uint32_t Fruit::addOneToRunningTotal() noexcept
{
    m_runningTotal++;
    return m_runningTotal;
}

bool Fruit::isValueWithinRange(const uint32_t value) const noexcept
{
    return value >= m_minRange && value <= m_maxRange;
}

// main cpp file
void printAllFruits(const std::vector<Fruit> &listOfFruits) noexcept;
Fruit &getFruitFromValue(std::vector<Fruit> &listOfFruits, uint32_t value);

int main()
{
    std::vector<Fruit> listOfFruits = {
        Fruit("Seven", 0, 9),
        Fruit("Bell", 10, 24),
        Fruit("Melon", 25, 44),
        Fruit("Plum", 45, 69), //:)
        Fruit("Orange", 70, 84),
        Fruit("Lemon", 85, 94),
        Fruit("Cherry", 95, 99),
    };
    int totalNumberOfFruits = 100;

    int numberOfIterations = 15;
    for (int i = 0; i < numberOfIterations; i++)
    {
        int valuePicked = rand() % totalNumberOfFruits;
        Fruit &fruit = getFruitFromValue(listOfFruits, valuePicked);

        printf("Value is %d, which is the fruit %s, which has now been called %d times\n",
               valuePicked, fruit.getName().c_str(), fruit.addOneToRunningTotal());
    }

    printAllFruits(listOfFruits);

    // below is not needed for brief
    int n;
    for (int i = 0; i < 3; i++)
    {
        std::cout << "Enter a number between 0 to " << totalNumberOfFruits << " exclusive to select a fruit: ";
        std::cin >> n;
        while (std::cin.fail() || n >= totalNumberOfFruits)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Please input a number between 0 to " << totalNumberOfFruits << " exclusive: ";
            std::cin >> n;
        }
        if (n < 0)
        {
            printAllFruits(listOfFruits);
        }
        else
        {
            Fruit &fruit = getFruitFromValue(listOfFruits, n);
            printf("You called fruit %s, which has now been called %d times\n",
                   fruit.getName().c_str(), fruit.addOneToRunningTotal());
        }
        std::cout << "\n";
    }
}

void printAllFruits(const std::vector<Fruit> &listOfFruits) noexcept
{
    std::cout << " === \nSummary results for these fruits\n";
    for (const Fruit &fruit : listOfFruits)
    {
        printf("Fruit %s has been called a total of %d times\n",
               fruit.getName().c_str(), fruit.getRunningTotal());
    }
}

Fruit &getFruitFromValue(std::vector<Fruit> &listOfFruits, uint32_t value)
{
    std::vector<Fruit>::iterator iter = listOfFruits.begin();
    for (; iter < listOfFruits.end(); iter++)
    {
        if (iter->isValueWithinRange(value))
        {
            break;
        }
    }

    if (iter == listOfFruits.end())
    {
        std::cerr << "Error! Value not found: " << value << "\n";
        // should definitely throw exception instead
        iter = listOfFruits.begin();
    }
    return *iter;
}
