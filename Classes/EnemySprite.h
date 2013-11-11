#ifndef __shooting__EnemySprite__
#define __shooting__EnemySprite__

#include "cocos2d.h"
#include "Config.h"

using namespace cocos2d;

enum kEnemy {
    kEnemy01,
    kEnemy02,
    kEnemy03,
    kEnemy04
};

class EnemySprite : public cocos2d::CCSprite
{
public:
    CC_SYNTHESIZE(int, tag, Tag);
    CC_SYNTHESIZE(kEnemy, type, Type);
    
    EnemySprite();
    virtual ~EnemySprite();
    virtual bool init(int tag, kEnemy type);
    static EnemySprite* create(int tag, kEnemy type);
    
    void executeAction(CCSize winSize);
    
private:
	const char* getImageFileName(kEnemy type);
};

#endif /* defined(__shooting__EnemySprite__) */
