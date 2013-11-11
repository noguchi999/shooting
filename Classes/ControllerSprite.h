#ifndef __shooting__ControllerSprite__
#define __shooting__ControllerSprite__

#include "cocos2d.h"
#include "Config.h"

using namespace cocos2d;

enum kController {
    kControllerTop,
    kControllerUnder,
    kControllerLeft,
    kControllerRight,
    kControllerWeaponA,
    kControllerWeaponB
};

class ControllerSprite : public cocos2d::CCSprite
{
public:
    CC_SYNTHESIZE(int, tag, Tag);
    CC_SYNTHESIZE(kController, type, Type);
    
    ControllerSprite();
    virtual ~ControllerSprite();
    virtual bool init(int tag, kController type, CCNode* target);
    static ControllerSprite* create(int tag, kController type, CCNode* target);
    
    void executeAction(CCNode* target, CCSize winSize);
    
private:
    CCNode* target;
    
	const char* getImageFileName(kController type);
};

#endif /* defined(__shooting__ControllerSprite__) */
