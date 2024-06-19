#include <iostream>
#include <string>
#include <vector>

#include "fruitPicker.h"

void run()
{
    std::vector<std::shared_ptr<Fruit>> listOfFruits;
    listOfFruits.push_back(std::shared_ptr<Fruit>(new Fruit("Seven", 0, 9)));
    listOfFruits.push_back(std::shared_ptr<Fruit>(new Fruit("Bell", 10, 24)));
    listOfFruits.push_back(std::shared_ptr<Fruit>(new Fruit("Melon", 25, 44)));
    listOfFruits.push_back(std::shared_ptr<Fruit>(new Fruit("Plum", 45, 69))); //:)
    listOfFruits.push_back(std::shared_ptr<Fruit>(new Fruit("Orange", 70, 84)));
    listOfFruits.push_back(std::shared_ptr<Fruit>(new Fruit("Lemon", 85, 94)));
    listOfFruits.push_back(std::shared_ptr<Fruit>(new Fruit("Cherry", 95, 99)));

    int totalNumberOfFruits = 100;

    int numberOfIterations = 15;
    std::thread threadList[numberOfIterations];
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
            threadList[i] = std::thread(func, valuePicked, std::ref(fruit));
        }
        else
        {
            func(valuePicked, fruit);
        }
    }

    if (concurrentMode)
    {
        for (int i = 0; i < numberOfIterations; i++)
        {
            threadList[i].join();
        }
    }

    printAllFruits(listOfFruits);

    // below is not needed for brief
    int n;
    for (int i = 0; i < 0; i++)
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
