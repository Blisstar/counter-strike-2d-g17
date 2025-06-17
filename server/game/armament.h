#ifndef ARMAMENT_H
#define ARMAMENT_H

#include "../common/defs.h"
#include "game.h"
#include "vector2.h"

enum class WeaponStatus : uint8_t {
    Inactive = 0x00,
    ReadyToFire = 0x01,
    ApplyingRecoil = 0x02,
    ApplyingFrecuency = 0x03,
};

class Armament {
   private:
    WeaponType currentWeapon;
    PrimaryWeapon primaryWeapon;
    WeaponStatus state;
    unsigned int baseDamage;
    unsigned int presicion;
    unsigned int recoilDuration;
    unsigned int shotsPerBurst;
    unsigned int shotsCount;
    unsigned int frecuency;
    unsigned int timeOfLastShot;
    bool isContinuosFiring;
    bool isTriggerFree;

   public:
    Armament(PrimaryWeapon _primaryWeapon = PrimaryWeapon::NoPrimaryWeapon);

    bool canShooting();

    void updateState(Game& game);

    void startShooting(Vector2 source, uint16_t angle, Game& game);

    void stopShooting();
};

#endif