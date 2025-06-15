#include "armament.h"

Armament::Armament(PrimaryWeapon _primaryWeapon)
    : currentWeapon(WeaponType::Knife), primaryWeapon(_primaryWeapon) {}

void Armament::fire(Vector2 source, uint16_t angle, Game& game) {
    if (state == WeaponStatus::Inactive) return;
    unsigned int elapsed = game.getStopWatch() - ;

    switch (currentWeapon) {
    case WeaponType::Knife :
        game.hurtPlayer()
        break;
    
    default:
        break;
    }
}