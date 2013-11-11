#ifndef shooting_Config_h
#define shooting_Config_h

enum kTag
{
	kTagUnDefine   = -1,
    kTagBackground = 1,
    kTagRedLabel,
    kTagBlueLabel,
    kTagYellowLabel,
    kTagGreenLabel,
    kTagGrayLabel,
	kTagWhiteLabel,
    kTagWarShip,
    kTagControllerTop,
    kTagControllerUnder,
    kTagControllerLeft,
    kTagControllerRight,
    kTagControllerWeaponA,
    kTagControllerWeaponB,
    kTagEnemy,
	kTagFriend,
	kTagWeakenEnemy,
    kTagEffectWeaponA,
    kTagEffectWeaponB,
	kTagEffectFriendWeaponA01,
	kTagEffectFriendWeaponA02,
    kTagEffectOther
};

enum kZOrder
{
    kZOrderBackground,
    kZOrderLabel,
    kZOrderBlock,
    kZOrderPartical,
    kZOrderGameOver,
    kZOrderWarShip,
    kZOrderController
};

#define ccsf(...) CCString::createWithFormat(__VA_ARGS__)->getCString()

#endif
