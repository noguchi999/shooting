#include "WarShipSprite.h"

using namespace cocos2d;

WarShipSprite::WarShipSprite()
{
}

WarShipSprite::~WarShipSprite()
{
}

WarShipSprite* WarShipSprite::create(int tag)
{
    WarShipSprite* ret = new WarShipSprite();
    
    if (ret && ret->init(tag))
    {
        return ret;
        
    } else {
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool WarShipSprite::init(int tag)
{
    if (!CCSprite::initWithFile("war_ship.png"))
    {
        return false;
    }
    
    setTag(tag);
    
    return true;
}