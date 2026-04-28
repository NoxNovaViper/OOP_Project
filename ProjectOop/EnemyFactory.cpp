#include "EnemyFactory.h"
#include "Botom.h"
#include "FlyngFoogaFoog.h"
#include "Tornado.h"
#include "Mogera.h"
#include "Gamakichi.h"

Enemy* EnemyFactory::e(const std::string& type, float x, float y) {
    if (type == "Botom")
        return new Botom(x, y);
    if (type == "Flyng")
        return new FlyngFoogafoog(x, y);
    if (type == "Tornado")
        return new Tornado(x, y);
    if (type == "Mogera")
        return new Mogera(x, y);
    if (type == "Gamakichi")
        return new Gamakichi(x, y);

    return nullptr;
}