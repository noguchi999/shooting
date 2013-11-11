#include "ControllerSprite.h"

using namespace cocos2d;

ControllerSprite::ControllerSprite()
{
}

ControllerSprite::~ControllerSprite()
{
}

ControllerSprite* ControllerSprite::create(int tag, kController type, CCNode* target)
{
    ControllerSprite* ret = new ControllerSprite();
    
    if (ret && ret->init(tag, type, target))
    {
        return ret;
        
    } else {
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool ControllerSprite::init(int tag, kController type, CCNode* target)
{
    if (!CCSprite::initWithFile(getImageFileName(type)))
    {
        return false;
    }
    
    setTag(tag);
    setType(type);
    
    return true;
}

const char* ControllerSprite::getImageFileName(kController type)
{
    switch (type) {
        case kControllerTop:
            return "top.png";
            
        case kControllerUnder:
            return "under.png";
            
        case kControllerLeft:
            return "left.png";
            
        case kControllerRight:
            return "right.png";
            
        case kControllerWeaponA:
            return "weapon_a.png";
            
        case kControllerWeaponB:
            return "weapon_b.png";
            
        default:
            CCAssert(false, "invalid controllerType");
            return "";
    }
}

void ControllerSprite::executeAction(CCNode* target, CCSize winSize)
{
    CCAction* action = NULL;
    switch (type) {
        case kControllerTop:
            if (target->getPositionY() >= (winSize.height - target->getContentSize().height)) {
                return;
            }
            action = CCMoveTo::create(0.1f, ccp(target->getPositionX(), target->getPositionY() + 10));
            break;
            
        case kControllerUnder:
            if (target->getPositionY() < target->getContentSize().height*3) {
                return;
            }
            action = CCMoveTo::create(0.1f, ccp(target->getPositionX(), target->getPositionY() - 10));
            break;
            
        case kControllerLeft:
            if (target->getPositionX() < target->getContentSize().width) {
                return;
            }
            action = CCMoveTo::create(0.1f, ccp(target->getPositionX() - 10, target->getPositionY()));
            break;
            
        case kControllerRight:
            if (target->getPositionX() >= (winSize.width - target->getContentSize().width)) {
                return;
            }
            action = CCMoveTo::create(0.1f, ccp(target->getPositionX() + 10, target->getPositionY()));
            break;
            
        default:
            CCAssert(false, "invalid controllerType");
            break;
    }
    
    target->runAction(action);
}
