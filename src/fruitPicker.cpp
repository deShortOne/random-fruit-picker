#include <iostream>
#include <string>
#include <vector>

#include "fruitPicker.h"

void run(int argc, char *argv[])
{
    bool concurrentMode;
    int numUI;
    cxxopts::Options options("Random fruit", "Picks a random fruit given a set probability");
    options.add_options()                                                                                    //
        ("c,concurrency", "Enable concurrency", cxxopts::value<bool>(concurrentMode)->default_value("true")) //
        ("uiNum", "Number of interactions at the end of the program", cxxopts::value<int>(numUI)->default_value("3"));
    options.parse(argc, argv);

    std::vector<std::shared_ptr<Fruit>> listOfFruits;
    listOfFruits.push_back(std::make_shared<Fruit>("Seven", 0, 9));
    listOfFruits.push_back(std::make_shared<Fruit>("Bell", 10, 24));
    listOfFruits.push_back(std::make_shared<Fruit>("Melon", 25, 44));
    listOfFruits.push_back(std::make_shared<Fruit>("Plum", 45, 69)); //:)
    listOfFruits.push_back(std::make_shared<Fruit>("Orange", 70, 84));
    listOfFruits.push_back(std::make_shared<Fruit>("Lemon", 85, 94));
    listOfFruits.push_back(std::make_shared<Fruit>("Cherry", 95, 99));

    int totalNumberOfFruits = 100;

    int numberOfIterations = 15;
    std::vector<std::thread> threadList;
    auto func = [](int valuePicked, std::shared_ptr<Fruit> &fruit) -> void
    {
        printf("Value is %d, which is the fruit %s, which has now been called %d times\n",
               valuePicked, (*fruit).getName().c_str(), (*fruit).addToRunningTotal(1));
    };
    for (int i = 0; i < numberOfIterations; i++)
    {
        int valuePicked = rand() % totalNumberOfFruits;
        std::shared_ptr<Fruit> &fruit = getFruitFromValue(listOfFruits, valuePicked);

        if (concurrentMode)
        {
            threadList.push_back(std::thread(func, valuePicked, std::ref(fruit)));
        }
        else
        {
            func(valuePicked, fruit);
        }
    }

    if (concurrentMode)
    {
        for (auto iter = threadList.begin(); iter < threadList.end(); iter++)
        {
            iter->join();
        }
    }

    printAllFruits(listOfFruits);

    // below is not needed for brief
    int n;
    for (int i = 0; i < numUI; i++)
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
            std::shared_ptr<Fruit> fruit = getFruitFromValue(listOfFruits, n);
            printf("You called fruit %s, which has now been called %d times\n",
                   (*fruit).getName().c_str(), (*fruit).addToRunningTotal(1));
        }
        std::cout << "\n";
    }
}

void printAllFruits(const std::vector<std::shared_ptr<Fruit>> &listOfFruits) noexcept
{
    std::cout << " === \nSummary results for these fruits\n";
    for (const std::shared_ptr<Fruit> &fruit : listOfFruits)
    {
        printf("Fruit %s has been called a total of %d times\n",
               (*fruit).getName().c_str(), (*fruit).getRunningTotal());
    }
}

std::shared_ptr<Fruit> &getFruitFromValue(std::vector<std::shared_ptr<Fruit>> &listOfFruits, uint32_t value)
{
    std::vector<std::shared_ptr<Fruit>>::iterator iter = listOfFruits.begin();
    for (; iter < listOfFruits.end(); iter++)
    {
        if ((*iter)->isValueWithinRange(value))
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
