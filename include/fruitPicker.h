#pragma once

#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "fruit.h"

static bool concurrentMode = true;

void run();
void printAllFruits(const std::vector<std::shared_ptr<Fruit>> &listOfFruits) noexcept;
std::shared_ptr<Fruit> &getFruitFromValue(std::vector<std::shared_ptr<Fruit>> &listOfFruits, uint32_t value);
