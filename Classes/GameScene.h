#ifndef __shooting__GameScene__
#define __shooting__GameScene__

#include "cocos2d.h"
#include "Config.h"
#include "ControllerSprite.h"
#include "WarShipSprite.h"
#include "EnemySprite.h"
#include "FriendSprite.h"

using namespace std;
using namespace cocos2d;

const int kFriendLimit           = 2;

const char* const kImgBackground = "background.png";
const char* const kImgGameOver   = "gameover.png";
const char* const kImgResetOut   = "reset1.png";
const char* const kImgResetOn    = "reset2.png";

const char* const kEffectWeaponA    = "lizi.plist";
const char* const kEffectWeaponB    = "circle_fire.plist";
const char* const kEffectEnemyCrash = "lizi.plist";

const char* const kSEMoveBlock   = "moveBlock.mp3";
const char* const kSERemoveBlock = "ta_ge_kotaiko02.mp3";

const char* const kBGMMain       = "bgm_main.mp3";

const char* const kFontRed    = "redFont.fnt";
const char* const kFontBlue   = "blueFont.fnt";
const char* const kFontYellow = "yellowFont.fnt";
const char* const kFontGreen  = "greenFont.fnt";
const char* const kFontGray   = "grayFont.fnt";
const char* const kFontWhite  = "whiteFont.fnt";

class GameScene : public CCLayer
{
public:
    GameScene();
    
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(GameScene);
    
    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
    
private:
    CCSprite* background;
    WarShipSprite* warShip;
    CCSize    winSize;
	CCArray*  friends;
    CCArray*  controllerFields;
    CCArray*  attackFields;
	int       score;
	int       friendCount;
	kTag      activeController;
    
    void update(float delta);
    void initForVariables();
    void createBackground();
    void createFriend(kTag tag, kFriend type);
    void createEnemy(kTag tag, kEnemy type, CCPoint spawnPoint);
	void createLabel();
    void controllerAction(CCPoint touchPoint);
    void attackAction(CCPoint touchPoint);
    CCNode* createParticle(const char* listFile, kTag tag, const CCPoint point);
    void removingNode(cocos2d::CCNode* node);
};
#endif /* defined(__shooting__GameScene__) */
