#ifndef __shooting__WarShipSprite__
#define __shooting__WarShipSprite__

#include "cocos2d.h"
#include "Config.h"

using namespace cocos2d;

class WarShipSprite : public cocos2d::CCSprite
{
public:
    CC_SYNTHESIZE(int, tag, Tag);
    
    WarShipSprite();
    virtual ~WarShipSprite();
    virtual bool init(int tag);
    static WarShipSprite* create(int tag);
    
    void executeAction();
};


#endif /* defined(__shooting__WarShipSprite__) */
