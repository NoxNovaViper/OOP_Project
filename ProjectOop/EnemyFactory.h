#pragma once
#include "Enemy.h"
#include <string>

class EnemyFactory {
public:
    static Enemy* e(const std::string& type, float x, float y);
};