#pragma once

#include <iostream>
#include <thread>
#include <vector>

#include "fruit.h"

static bool concurrentMode = true;

void run();
void printAllFruits(const std::vector<Fruit> &listOfFruits) noexcept;
Fruit &getFruitFromValue(std::vector<Fruit> &listOfFruits, uint32_t value);
