#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "CCPlaySE.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

GameScene::GameScene()
:winSize(CCDirector::sharedDirector()->getWinSize())
,score(0)
{
    srand((unsigned)time(NULL));
}

CCScene* GameScene::scene()
{
    CCScene* scene   = CCScene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool GameScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    
    initForVariables();
    createBackground();
    createLabel();
    
    //SimpleAudioEngine::sharedEngine()->preloadEffect(kSEMoveBlock);
    //SimpleAudioEngine::sharedEngine()->preloadEffect(kSERemoveBlock);
    //SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(kBGMMain);
    
    //SimpleAudioEngine::sharedEngine()->playBackgroundMusic(kBGMMain, true);
    
    this->scheduleUpdate();
    
    return true;
}

void GameScene::update(float delta)
{
	switch (activeController) {
		case kTagControllerTop:
		case kTagControllerUnder:
		case kTagControllerLeft:
		case kTagControllerRight:
        {
			ControllerSprite* controller = dynamic_cast<ControllerSprite*>(this->getChildByTag(activeController));
			controller->executeAction(warShip, winSize);
        }
            break;
            
		default:
			break;
	}
	
	CCObject* obj = NULL;
	CCARRAY_FOREACH(this->getChildren(), obj)
	{
        CCNode* weaponA = this->getChildByTag(kTagEffectWeaponA);
        CCNode* weaponB = this->getChildByTag(kTagEffectWeaponB);
		CCNode* friendWeaponA01 = this->getChildByTag(kTagEffectFriendWeaponA01);
		CCNode* friendWeaponA02 = this->getChildByTag(kTagEffectFriendWeaponA02);
		CCNode* child = dynamic_cast<CCNode*>(obj);
        
        if (child->getTag() == kTagEnemy)
        {
            EnemySprite* enemy = dynamic_cast<EnemySprite*>(child);
            if (enemy->getPositionX() < 0) {
                enemy->removeFromParentAndCleanup(true);
            }
            
            if (enemy->boundingBox().containsPoint(warShip->getPosition()))
            {
            }
            
            if (weaponA && enemy->boundingBox().containsPoint(weaponA->getPosition()))
            {
                weaponA->removeFromParentAndCleanup(true);
                
                CCScaleTo* burst   = CCScaleTo::create(0.3f, 2.5f);
                CCScaleTo* clear   = CCScaleTo::create(0.3f, 1);
                CCCallFuncN* removingNodeFunction = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingNode));
                CCFiniteTimeAction* burnout = CCSequence::create(burst, clear, removingNodeFunction, NULL);
                CCNode* partial = createParticle(kEffectEnemyCrash, kTagEffectOther, enemy->getPosition());
                
                partial->runAction(burnout);
                enemy->removeFromParentAndCleanup(true);
                
                score += 10;
                CCLabelBMFont* score_label = (CCLabelBMFont*)this->getChildByTag(kTagWhiteLabel);
                score_label->setString(ccsf("%05d", score));
            }
            else if (friendWeaponA01 && enemy->boundingBox().containsPoint(friendWeaponA01->getPosition()))
            {
                friendWeaponA01->removeFromParentAndCleanup(true);
                
                CCScaleTo* burst   = CCScaleTo::create(0.3f, 2.5f);
                CCScaleTo* clear   = CCScaleTo::create(0.3f, 1);
                CCCallFuncN* removingNodeFunction = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingNode));
                CCFiniteTimeAction* burnout = CCSequence::create(burst, clear, removingNodeFunction, NULL);
                CCNode* partial = createParticle(kEffectEnemyCrash, kTagEffectOther, enemy->getPosition());
                
                partial->runAction(burnout);
                enemy->removeFromParentAndCleanup(true);
                
                //score += 10;
                //CCLabelBMFont* score_label = (CCLabelBMFont*)this->getChildByTag(kTagWhiteLabel);
                //score_label->setString(ccsf("%05d", score));
            }
            else if (friendWeaponA02 && enemy->boundingBox().containsPoint(friendWeaponA02->getPosition()))
            {
                friendWeaponA02->removeFromParentAndCleanup(true);
                
                CCScaleTo* burst   = CCScaleTo::create(0.3f, 2.5f);
                CCScaleTo* clear   = CCScaleTo::create(0.3f, 1);
                CCCallFuncN* removingNodeFunction = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingNode));
                CCFiniteTimeAction* burnout = CCSequence::create(burst, clear, removingNodeFunction, NULL);
                CCNode* partial = createParticle(kEffectEnemyCrash, kTagEffectOther, enemy->getPosition());
                
                partial->runAction(burnout);
                enemy->removeFromParentAndCleanup(true);
                
                //score += 10;
                //CCLabelBMFont* score_label = (CCLabelBMFont*)this->getChildByTag(kTagWhiteLabel);
                //score_label->setString(ccsf("%05d", score));
            }
            else if (weaponB && enemy->boundingBox().containsPoint(weaponB->getPosition()))
            {
                weaponB->removeFromParentAndCleanup(true);
                
                createEnemy(kTagWeakenEnemy, kEnemy02, enemy->getPosition());
                enemy->removeFromParentAndCleanup(true);
                
                score += 10;
                CCLabelBMFont* score_label = (CCLabelBMFont*)this->getChildByTag(kTagWhiteLabel);
                score_label->setString(ccsf("%05d", score));
            }
            else
            {
                if (enemy->getType() == kEnemy01) {
                    CCAction* action = CCMoveTo::create(0.1f, ccp(enemy->getPositionX() - 3, enemy->getPositionY()));
                    enemy->runAction(action);
                }
                else if (enemy->getType() == kEnemy03)
                {
                    float x = enemy->getPositionX();
                    float y = enemy->getPositionY();
                    ccBezierConfig bezier;
                    bezier.controlPoint_1 = CCPoint(winSize.width, winSize.height);
                    bezier.controlPoint_2 = CCPoint(0, winSize.height * 0.8);
                    bezier.endPosition    = CCPoint(x, y);
                    CCActionInterval* bezierMove = CCBezierTo::create(20.0f, bezier);
                    CCCallFuncN* removingNodeFunction = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingNode));
                    CCFiniteTimeAction* action = CCSequence::create(bezierMove, removingNodeFunction, NULL);
                    
                    enemy->runAction(action);
                }
            }
        }
        
        if (child->getTag() == kTagWeakenEnemy)
        {
            if (weaponB && child->boundingBox().containsPoint(weaponB->getPosition()))
            {
                weaponB->removeFromParentAndCleanup(true);
                
                CCMoveTo* move = CCMoveTo::create(0.5f, warShip->getPosition());
                CCActionInterval* actionRotate = CCRotateBy::create(0.5f, 360);
                CCCallFuncN* removingNodeFunction = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingNode));
                CCFiniteTimeAction* capture = CCSequence::create(move, removingNodeFunction, NULL);
                CCSpawn* spawn = CCSpawn::createWithTwoActions(actionRotate, capture);
                child->runAction(spawn);
                
                //createFriend(kTagFriend, kFriend01);
                
                score += 110;
                CCLabelBMFont* score_label = (CCLabelBMFont*)this->getChildByTag(kTagWhiteLabel);
                score_label->setString(ccsf("%05d", score));
            }
        }
	}
    
	if (rand()%150 == 1)
	{
        float enemy_height = winSize.height*(rand()%100+1)/100;
        if (enemy_height < winSize.height * 0.4) {
            enemy_height = winSize.height * 0.4;
        } else if (enemy_height > winSize.height * 0.8) {
            enemy_height = winSize.height * 0.8;
        }
        
		createEnemy(kTagEnemy, kEnemy01, ccp(winSize.width, enemy_height));
	}
    else if (rand()%150 == 2)
    {
        createEnemy(kTagEnemy, kEnemy03, ccp(winSize.width * 0.8, 0));
    }
    else if (rand()%150 == 3)
    {
        createEnemy(kTagEnemy, kEnemy04, ccp(winSize.width, winSize.height));
        createEnemy(kTagEnemy, kEnemy04, ccp(winSize.width, winSize.height));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(this->getChildren(), obj)
        {
            CCNode* child = dynamic_cast<CCNode*>(obj);
            if (child->getTag() == kTagEnemy) {
                EnemySprite* enemy = dynamic_cast<EnemySprite*>(child);
                if (enemy->getType() == kEnemy04) {
                    CCActionInterval* actionMove = CCMoveTo::create(5.0f, warShip->getPosition());
                    CCActionInterval* bounce = CCEaseBounceInOut::create(actionMove);
                    CCMoveTo* move = CCMoveTo::create(0.2f, ccp(-1, winSize.height / 2));
                    CCCallFuncN* removingNodeFunction = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingNode));
                    CCFiniteTimeAction* action = CCSequence::create(bounce, move, removingNodeFunction, NULL);
                    
                    enemy->runAction(action);
                }
            }
        }
    }
    
}

bool GameScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
    //CCPoint touchPoint = background->convertTouchToNodeSpace(pTouch);
	controllerAction(pTouch->getLocation());
    attackAction(pTouch->getLocation());
    
    return true;
}

void GameScene::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
    //CCPoint touchPoint = background->convertTouchToNodeSpace(pTouch);
}

void GameScene::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	activeController = kTagUnDefine;
}

void GameScene::initForVariables()
{
    warShip = WarShipSprite::create(kTagWarShip);
    warShip->setPosition(ccp(warShip->getContentSize().width*3/2, winSize.height/1.7));
    this->addChild(warShip, kZOrderWarShip, kTagWarShip);
    
    ControllerSprite* top = ControllerSprite::create(kTagControllerTop, kControllerTop, warShip);
    top->setPosition(ccp(top->getContentSize().width*4/2, top->getContentSize().height*2));
    this->addChild(top, kZOrderController, kTagControllerTop);
    
    ControllerSprite* under = ControllerSprite::create(kTagControllerUnder, kControllerUnder, warShip);
    under->setPosition(ccp(under->getContentSize().width*4/2, under->getContentSize().height));
    this->addChild(under, kZOrderController, kTagControllerUnder);
    
    ControllerSprite* left = ControllerSprite::create(kTagControllerLeft, kControllerLeft, warShip);
    left->setPosition(ccp(left->getContentSize().width*2/2, left->getContentSize().height*2));
    this->addChild(left, kZOrderController, kTagControllerLeft);
    
    ControllerSprite* right = ControllerSprite::create(kTagControllerRight, kControllerRight, warShip);
    right->setPosition(ccp(right->getContentSize().width*6/2, right->getContentSize().height*2));
    this->addChild(right, kZOrderController, kTagControllerRight);
    
    ControllerSprite* weaponA = ControllerSprite::create(kTagControllerWeaponA, kControllerWeaponA, warShip);
    weaponA->setPosition(ccp(winSize.width - weaponA->getContentSize().width*2, weaponA->getContentSize().height*2));
    this->addChild(weaponA, kZOrderController, kTagControllerWeaponA);
    
    ControllerSprite* weaponB = ControllerSprite::create(kTagControllerWeaponB, kControllerWeaponB, warShip);
    weaponB->setPosition(ccp(winSize.width - weaponB->getContentSize().width*3.5, weaponB->getContentSize().height*2));
    this->addChild(weaponB, kZOrderController, kTagControllerWeaponB);
    
    controllerFields = CCArray::create();
    controllerFields->addObject(top);
    controllerFields->addObject(under);
    controllerFields->addObject(left);
    controllerFields->addObject(right);
    controllerFields->retain();
    
    attackFields = CCArray::create();
    attackFields->addObject(weaponA);
    attackFields->addObject(weaponB);
    attackFields->retain();
    
	friends = CCArray::create();
	friends->retain();
}

void GameScene::createBackground()
{
    CCSprite* bg1 = CCSprite::create("bg1.png");
    CCSprite* bg2 = CCSprite::create("bg2.png");
    CCSprite* bg3 = CCSprite::create("bg3.png");
    
    CCParallaxNode* paraNode = CCParallaxNode::create();
    paraNode->addChild(bg1, 1, ccp(0.5f, 0), ccp(0, winSize.height));
    paraNode->addChild(bg2, 2, ccp(1.5f, 0), ccp(0, winSize.height / 10));
    paraNode->addChild(bg3, 3, ccp(2.0f, 0), ccp(0, winSize.height / 3));
    paraNode->setPosition(ccp(winSize.width, winSize.height / 5));
    this->addChild(paraNode, kZOrderBackground);
    
    CCMoveBy* move1 = CCMoveBy::create(10.0f, ccp(-winSize.width, 0));
    CCMoveBy* move2 = CCMoveBy::create(0.0f, ccp(winSize.width, 0));
    CCSequence* seq = (CCSequence*)CCSequence::create(move1, move2, NULL);
    CCRepeatForever* repeat = CCRepeatForever::create(seq);
    
    paraNode->runAction(repeat);
}

void GameScene::createFriend(kTag tag, kFriend type)
{
	if (warShip && friendCount < kFriendLimit)
	{
        CCLog("create_friend");
		FriendSprite* ally = FriendSprite::create(tag, type);
		ally->setPosition(ccp(warShip->getPositionX() - (warShip->getContentSize().width / 2), warShip->getPositionY() - (warShip->getContentSize().height * friendCount)));
		this->addChild(ally, kZOrderWarShip, tag);
		friends->addObject(ally);
        
		++friendCount;
	}
}

void GameScene::createEnemy(kTag tag, kEnemy type, CCPoint spawnPoint)
{
    EnemySprite* enemy = EnemySprite::create(tag, type);
    enemy->setPosition(spawnPoint);
    this->addChild(enemy, kZOrderWarShip, tag);
}

void GameScene::createLabel()
{
    const char* initCountStr = ccsf("%05d", 0);
    CCLabelBMFont* score_label = CCLabelBMFont::create(initCountStr, kFontWhite);
    
    score_label->setPosition(ccp(winSize.width * 0.8, winSize.height * 0.1));
    
    this->addChild(score_label, kZOrderLabel, kTagWhiteLabel);
}

void GameScene::controllerAction(CCPoint touchPoint)
{
    CCObject* obj = NULL;
    CCARRAY_FOREACH(controllerFields, obj)
    {
		ControllerSprite* controller = dynamic_cast<ControllerSprite*>(obj);
        if (controller->boundingBox().containsPoint(touchPoint))
        {
            //controller->executeAction(warShip, winSize);
			activeController = (kTag)controller->getTag();
        }
    }
}

void GameScene::attackAction(CCPoint touchPoint)
{
    CCObject* obj = NULL;
    CCARRAY_FOREACH(attackFields, obj)
    {
		ControllerSprite* controller = dynamic_cast<ControllerSprite*>(obj);
        if (controller->boundingBox().containsPoint(touchPoint))
        {
			if (controller->getTag() == kTagControllerWeaponA)
			{
                CCNode* weaponA = createParticle(kEffectWeaponA, kTagEffectWeaponA, warShip->getPosition());
                weaponA->setScale(0.6f);
                CCMoveTo* move = CCMoveTo::create(0.5f, ccp(winSize.width, weaponA->getPositionY()));
                CCCallFuncN* removingNodeFunction = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingNode));
                CCFiniteTimeAction* openFireAction = CCSequence::create(move, removingNodeFunction, NULL);
                weaponA->runAction(openFireAction);
                
				CCObject* friendObj = NULL;
				int friendCount = 0;
				CCARRAY_FOREACH(friends, friendObj)
				{
					FriendSprite* ally = dynamic_cast<FriendSprite*>(friendObj);
					CCNode* friendWeaponA;
					if (friendCount == 0)
					{
						friendWeaponA = createParticle(kEffectWeaponA, kTagEffectFriendWeaponA01, ally->getPosition());
					}
					else
					{
						friendWeaponA = createParticle(kEffectWeaponA, kTagEffectFriendWeaponA02, ally->getPosition());
					}
					friendWeaponA->setScale(0.6f);
					CCMoveTo* move = CCMoveTo::create(0.5f, ccp(winSize.width, friendWeaponA->getPositionY()));
					CCCallFuncN* removingNodeFunction = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingNode));
					CCFiniteTimeAction* openFireAction = CCSequence::create(move, removingNodeFunction, NULL);
					friendWeaponA->runAction(openFireAction);
                    
					++friendCount;
				}
			}
            
			if (controller->getTag() == kTagControllerWeaponB)
			{
				if (score % 50 == 0)
				{
                    CCNode* weaponB = createParticle(kEffectWeaponB, kTagEffectWeaponB, warShip->getPosition());
                    weaponB->setContentSize(weaponB->getContentSize()*10);
                    CCScaleTo* scaleUp = CCScaleTo::create(0.3f, 1.0f);
                    CCMoveTo* move = CCMoveTo::create(1.0f, ccp(winSize.width, weaponB->getPositionY()));
                    CCCallFuncN* removingNodeFunction = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingNode));
                    CCFiniteTimeAction* openFireAction = CCSequence::create(scaleUp, move, removingNodeFunction, NULL);
                    weaponB->runAction(openFireAction);
				}
			}
        }
    }
}

CCNode* GameScene::createParticle(const char* listFile, kTag tag, const CCPoint point)
{
    CCParticleSystemQuad* particle = CCParticleSystemQuad::create(listFile);
    particle->setPosition(point);
    this->addChild(particle, kZOrderPartical, tag);
    
    return particle;
}

void GameScene::removingNode(cocos2d::CCNode* node)
{
    node->removeFromParentAndCleanup(true);
}
