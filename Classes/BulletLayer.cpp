/*
 * BulletLayer.cpp
 *
 *  Created on: 2014-4-11
 *      Author: never
 */
#include "BulletLayer.h"
#include "PlaneLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

BulletLayer::BulletLayer(){
	bullets = CCArray::create();
	bullets->retain();
}

BulletLayer::~BulletLayer(){
	bullets->release();
	bullets = NULL;
}

bool BulletLayer::init(){
	bool bRet = false;

	do{
		CC_BREAK_IF(!CCLayer::init());

		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->textureForKey("ui/shoot.png");
		bulletBatchNode = CCSpriteBatchNode::createWithTexture(texture);
		this->addChild(bulletBatchNode);

		bRet = true;
	}while(0);

	return bRet;
}

void BulletLayer::AddBullet(float dt) {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/bullet.mp3");
	CCSprite * bullet = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bullet1.png"));
	bullets->addObject(bullet);
	bulletBatchNode->addChild(bullet);

	CCPoint planePoint = PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getPosition();
	CCPoint bulletPoint = ccp(planePoint.x,planePoint.y + PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getContentSize().height/2);
	bullet->setPosition(bulletPoint);

	float length = CCDirector::sharedDirector()->getWinSize().height - bulletPoint.y + bullet->getContentSize().height/2;

	float velocity = 420/1;
	float moveDuration = length/velocity;

	CCFiniteTimeAction *move = CCMoveTo::create(moveDuration,ccp(bulletPoint.x,CCDirector::sharedDirector()->getWinSize().height+bullet->getContentSize().height/2));
	CCFiniteTimeAction *disappear = CCCallFuncN::create(this,callfuncN_selector(BulletLayer::bulletMoveOut));

	CCSequence *actions = CCSequence::create(move,disappear,NULL);
	bullet->runAction(actions);
}

void BulletLayer::bulletMoveOut(CCNode* pSender){
	CCSprite* bullet = (CCSprite*)pSender;
	bullets->removeObject(bullet);
	bulletBatchNode->removeChild(bullet,true);
}

void BulletLayer::startShoot(float delay){
	this->schedule(schedule_selector(BulletLayer::AddBullet),0.20f,kCCRepeatForever,delay);
}

void BulletLayer::stopShoot(){
	this->unschedule(schedule_selector(BulletLayer::AddBullet));
}

void BulletLayer::removeBullet(CCSprite* bullet){
	if(bullet != NULL) {
		bullets->removeObject(bullet);
		bulletBatchNode->removeChild(bullet,true);
	}

}

