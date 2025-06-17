#include "armament.h"

Armament::Armament(PrimaryWeapon _primaryWeapon)
    : currentWeapon(WeaponType::Knife), primaryWeapon(_primaryWeapon) {}

bool Armament::canShooting() {
    return state == WeaponStatus::ReadyToFire;
}

void Armament::updateState(Game& game) {
    if (state == WeaponStatus::Inactive){
        state = isTriggerFree ? WeaponStatus::ReadyToFire : WeaponStatus::Inactive;
        return;
    }
    unsigned int elapsed = game.getStopWatch() - timeOfLastShot;
    switch (state) {
        case WeaponStatus::ApplyingRecoil:
            if (elapsed >= recoilDuration) {
                state = (isContinuosFiring) ? WeaponStatus::ReadyToFire
                                          : (isTriggerFree ? WeaponStatus::ReadyToFire : WeaponStatus::Inactive);
            }
            break;
        
        case WeaponStatus::ApplyingFrecuency:
            if (elapsed >= frecuency) state = WeaponStatus::ReadyToFire; 
            break;
        
        case WeaponStatus::ReadyToFire:
            if (!isTriggerFree) {
                if (shotsCount < shotsPerBurst) {
                    state = WeaponStatus::ApplyingFrecuency;
                } else {
                    state = WeaponStatus::ApplyingRecoil;
                    shotsCount = 0;
                }
            }

        default:
            break;
    }
}

void Armament::startShooting(Vector2 source, uint16_t angle, Game& game) {
    if (!canShooting()) return;

    shotsCount++;
    isTriggerFree = false;
    timeOfLastShot = game.getStopWatch();
}

void Armament::stopShooting() {
    isTriggerFree = true;
}
