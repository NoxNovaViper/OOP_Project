#include "Boss.h"
Boss::Boss(float startX, float startY) {
    x = startX;
    y = startY;
    phase = 1;
    phase_timer = 0.0f;
    is_defeated = false;
}