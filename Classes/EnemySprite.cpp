#include "EnemySprite.h"

using namespace cocos2d;

EnemySprite::EnemySprite()
{
}

EnemySprite::~EnemySprite()
{
}

EnemySprite* EnemySprite::create(int tag, kEnemy type)
{
    EnemySprite* ret = new EnemySprite();
    
    if (ret && ret->init(tag, type))
    {
        return ret;
        
    } else {
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool EnemySprite::init(int tag, kEnemy type)
{
    if (!CCSprite::initWithFile(getImageFileName(type)))
    {
        return false;
    }
    
    setTag(tag);
    setType(type);
    
    return true;
}

const char* EnemySprite::getImageFileName(kEnemy type)
{
    switch (type) {
        case kEnemy01:
            return "enemy01.png";

        case kEnemy02:
            return "enemy02.png";

        case kEnemy03:
            return "enemy03.png";

        case kEnemy04:
            return "enemy04.png";

        default:
            CCAssert(false, "invalid enemyType");
            return "";
    }
}