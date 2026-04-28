#include "Boss.h"
Boss::Boss(float startX, float startY) {
    x = startX;
    y = startY;
    phase = 1;
    phaseTimer = 0.0f;
    isdefeated = false;
}