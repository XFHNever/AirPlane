/*
 * MutiBulletLayer.cpp
 *
 *  Created on: 2014-4-23
 *      Author: never
 */
#include "MutiBulletLayer.h"
#include "PlaneLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

MutiBulletLayer::MutiBulletLayer(){
	this->mutiBullets = CCArray::create();
	this->mutiBullets->retain();

	this->mutiBulletsBatchNode = NULL;
}

MutiBulletLayer::~MutiBulletLayer(){
	this->mutiBullets->release();
	this->mutiBullets = NULL;
}

bool MutiBulletLayer::init(){
	bool bRet = false;

	do{
		CC_BREAK_IF(!CCLayer::init());

		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->textureForKey("ui/shoot.png");
		this->mutiBulletsBatchNode = CCSpriteBatchNode::createWithTexture(texture);
		this->addChild(mutiBulletsBatchNode);

		bRet = true;
	}while(0);

	return bRet;
}

void MutiBulletLayer::AddMutiBullets(float dt) {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/bullet.mp3");
	CCLog("this is a addmutiBullets");
	CCSprite* bulletLeft = CCSprite::createWithSpriteFrameName("bullet2.png");
	CCSprite* bulletRight = CCSprite::createWithSpriteFrameName("bullet2.png");

	this->mutiBulletsBatchNode->addChild(bulletLeft);
	this->mutiBulletsBatchNode->addChild(bulletRight);

	this->mutiBullets->addObject(bulletLeft);
	this->mutiBullets->addObject(bulletRight);

	CCPoint planePoint = PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getPosition();
	CCPoint leftPoint = ccp(planePoint.x-33,planePoint.y+35);
	CCPoint rightPoint = ccp(planePoint.x+33,planePoint.y+35);

	bulletLeft->setPosition(leftPoint);
	bulletRight->setPosition(rightPoint);

	float length=CCDirector::sharedDirector()->getWinSize().height+bulletLeft->getContentSize().height/2-leftPoint.y;
	float velocity=420/1;//420pixel/sec
	float realMoveDuration=length/velocity;

	CCFiniteTimeAction *actionLeftMove = CCMoveTo::create(realMoveDuration,ccp(leftPoint.x,CCDirector::sharedDirector()->getWinSize().height+bulletLeft->getContentSize().height/2));
	CCFiniteTimeAction *actionLeftOut = CCCallFuncN::create(this,callfuncN_selector(MutiBulletLayer::mutiBulletsMoveFinished));
	CCSequence *leftSequence = CCSequence::create(actionLeftMove,actionLeftOut,NULL);
	bulletLeft->runAction(leftSequence);

	CCFiniteTimeAction *actionRightMove = CCMoveTo::create(realMoveDuration,ccp(rightPoint.x,CCDirector::sharedDirector()->getWinSize().height+bulletRight->getContentSize().height/2));
	CCFiniteTimeAction *actionRightOut = CCCallFuncN::create(this,callfuncN_selector(MutiBulletLayer::mutiBulletsMoveFinished));
	CCSequence *rightSequence = CCSequence::create(actionRightMove,actionRightOut,NULL);
	bulletRight->runAction(rightSequence);
}

void MutiBulletLayer::mutiBulletsMoveFinished(CCNode* pSender) {
	CCSprite* mutiBullet = (CCSprite*)pSender;

	this->mutiBullets->removeObject(mutiBullet);
	this->mutiBulletsBatchNode->removeChild(mutiBullet,true);
}

void MutiBulletLayer::removeMutiBullets(CCSprite* mutiBullet) {
	if(mutiBullet != NULL) {
		this->mutiBullets->removeObject(mutiBullet);
		this->mutiBulletsBatchNode->removeChild(mutiBullet,true);
	}
}

void MutiBulletLayer::StartShoot() {
	this->schedule(schedule_selector(MutiBulletLayer::AddMutiBullets),0.2f,30,0.0f);
}

void MutiBulletLayer::StopShoot() {
	this->unschedule(schedule_selector(MutiBulletLayer::AddMutiBullets));
}
