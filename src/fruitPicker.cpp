#include <vector>
#include <string>
#include <iostream>

#include "fruitPicker.h"

void run()
{
    std::vector<Fruit> listOfFruits;
    listOfFruits.push_back(Fruit("Seven", 0, 9));
    listOfFruits.push_back(Fruit("Bell", 10, 24));
    listOfFruits.push_back(Fruit("Melon", 25, 44));
    listOfFruits.push_back(Fruit("Plum", 45, 69)); //:)
    listOfFruits.push_back(Fruit("Orange", 70, 84));
    listOfFruits.push_back(Fruit("Lemon", 85, 94));
    listOfFruits.push_back(Fruit("Cherry", 95, 99));

    int totalNumberOfFruits = 100;

    int numberOfIterations = 15;
    std::thread threads[numberOfIterations];
    auto func = [](int valuePicked, Fruit &fruit) -> void
    {
        printf("Value is %d, which is the fruit %s, which has now been called %d times\n",
               valuePicked, fruit.getName().c_str(), fruit.addOneToRunningTotal());
    };
    for (int i = 0; i < numberOfIterations; i++)
    {
        int valuePicked = rand() % totalNumberOfFruits;
        Fruit &fruit = getFruitFromValue(listOfFruits, valuePicked);

        if (concurrentMode)
        {
            threads[i] = std::thread(func, valuePicked, std::ref(fruit));
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
            threads[i].join();
        }
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
