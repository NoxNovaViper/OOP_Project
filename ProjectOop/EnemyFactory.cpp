#include "EnemyFactory.h"
#include "Botom.h"
#include "FlyngFoogaFoog.h"
#include "Tornado.h"
#include "Mogera.h"
#include "MogeraChild.h"
#include "Gamakichi.h"

Enemy* EnemyFactory::e(const std::string& type, float x, float y, float targetX) {
    if (type == "Botom")
        return new Botom(x, y);
    if (type == "Flyng")
        return new FlyngFoogafoog(x, y);
    if (type == "Tornado")
        return new Tornado(x, y);
    if (type == "TornadoRed") {
        Tornado* t = new Tornado(x, y);
        t->variant = true;
        return t;
    }
    if (type == "FlyngRed") {
        FlyngFoogafoog* f = new FlyngFoogafoog(x, y);
        f->variant = true;
        return f;
    }
    if (type == "Mogera")
        return new Mogera(x, y);
    if (type == "MogeraChild") {
        MogeraChild* child = new MogeraChild(x, y);
        child->set_direction_x(x < targetX ? 1.0f : -1.0f);
        return child;
    }
    if (type == "Gamakichi")
        return new Gamakichi(x, y);

    return nullptr;
}