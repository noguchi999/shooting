#ifndef __shooting__FriendSprite__
#define __shooting__FriendSprite__

#include "cocos2d.h"
#include "Config.h"

using namespace cocos2d;

enum kFriend {
    kFriend01,
    kFriend02,
    kFriend03,
    kFriend04
};

class FriendSprite : public cocos2d::CCSprite
{
public:
    CC_SYNTHESIZE(int, tag, Tag);
    CC_SYNTHESIZE(kFriend, type, Type);
    
    FriendSprite();
    virtual ~FriendSprite();
    virtual bool init(int tag, kFriend type);
    static FriendSprite* create(int tag, kFriend type);
    
    void executeAction(CCSize winSize);
    
private:
	const char* getImageFileName(kFriend type);
};

#endif /* defined(__shooting__FriendSprite__) */
