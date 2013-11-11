#include "FriendSprite.h"

using namespace cocos2d;

FriendSprite::FriendSprite()
{
}

FriendSprite::~FriendSprite()
{
}

FriendSprite* FriendSprite::create(int tag, kFriend type)
{
    FriendSprite* ret = new FriendSprite();
    
    if (ret && ret->init(tag, type))
    {
        return ret;
        
    } else {
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool FriendSprite::init(int tag, kFriend type)
{
    if (!CCSprite::initWithFile(getImageFileName(type)))
    {
        return false;
    }
    
    setTag(tag);
    setType(type);
    
    return true;
}

const char* FriendSprite::getImageFileName(kFriend type)
{
    switch (type) {
        case kFriend01:
            return "friend01.png";
            
        default:
            CCAssert(false, "invalid friendType");
            return "";
    }
}