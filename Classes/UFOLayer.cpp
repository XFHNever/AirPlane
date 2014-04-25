/*
 * UFOLayer.cpp
 *
 *  Created on: 2014-4-23
 *      Author: never
 */
#include "UFOLayer.h"

USING_NS_CC;

UFOLayer::UFOLayer(){
	this->bigBooms = CCArray::create();
	bigBooms->retain();

	this->mutiBullets = CCArray::create();
	mutiBullets->retain();
}

UFOLayer::~UFOLayer(){
	bigBooms->release();
	bigBooms = NULL;

	mutiBullets->release();
	mutiBullets = NULL;
}

bool UFOLayer::init(){
	bool bRet = false;

	do{
		CC_BREAK_IF(!CCLayer::init());
		this->schedule(schedule_selector(UFOLayer::addMutiBullets),20.0);
		this->schedule(schedule_selector(UFOLayer::addBigBooms),20.0,kCCRepeatForever,5.0);
		bRet = true;
	}while(0);

	return bRet;
}

void UFOLayer::addBigBooms(float dt) {
	CCSprite *bigBoom = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ufo2.png"));

	CCSize bigBoomSize=bigBoom->getContentSize();
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	int minX=bigBoomSize.width/2;
	int maxX=winSize.width-bigBoomSize.width/2;
	int rangeX=maxX-minX;
	int actualX=(rand()%rangeX)+minX;

	bigBoom->setPosition(ccp(actualX,winSize.height + bigBoomSize.height/2));
	this->addChild(bigBoom);
	this->bigBooms->addObject(bigBoom);

	CCMoveBy* move1 = CCMoveBy::create(0.5f,CCPointMake(0,-150));
	CCMoveBy* move2 = CCMoveBy::create(0.3f,CCPointMake(0,100));
	CCMoveBy* move3 = CCMoveBy::create(1.0f,CCPointMake(0,0-winSize.height-bigBoomSize.height/2));

	CCCallFuncN* moveDone = CCCallFuncN::create(this,callfuncN_selector(UFOLayer::bigBoomMoveFinished));
	CCFiniteTimeAction* sequence = CCSequence::create(move1,move2,move3,moveDone,NULL);
	bigBoom->runAction(sequence);
}

void UFOLayer::addMutiBullets(float dt) {
	CCSprite *mutiBullet = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ufo1.png"));

	CCSize mutiBulletSize=mutiBullet->getContentSize();
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	int minX=mutiBulletSize.width/2;
	int maxX=winSize.width-mutiBulletSize.width/2;
	int rangeX=maxX-minX;
	int actualX=(rand()%rangeX)+minX;

	mutiBullet->setPosition(ccp(actualX,winSize.height + mutiBulletSize.height/2));
	this->addChild(mutiBullet);
	this->mutiBullets->addObject(mutiBullet);

	CCMoveBy* move1 = CCMoveBy::create(0.5f,CCPointMake(0,-150));
	CCMoveBy* move2 = CCMoveBy::create(0.3f,CCPointMake(0,100));
	CCMoveBy* move3 = CCMoveBy::create(1.0f,CCPointMake(0,0-winSize.height-mutiBulletSize.height/2));

	CCCallFuncN* moveDone = CCCallFuncN::create(this,callfuncN_selector(UFOLayer::mutiBulletMoveFinished));
	CCFiniteTimeAction* sequence = CCSequence::create(move1,move2,move3,moveDone,NULL);
	mutiBullet->runAction(sequence);
}

void UFOLayer::removeBigBooms(CCSprite* bigBoom) {
	this->removeChild(bigBoom,true);
	this->bigBooms->removeObject(bigBoom);
}

void UFOLayer::removeMutiBullets(CCSprite* mutiBullet) {
	this->removeChild(mutiBullet);
	this->mutiBullets->removeObject(mutiBullet);
}

void UFOLayer::bigBoomMoveFinished(CCNode* pSender) {
	CCSprite* bigBoom=(CCSprite*)pSender;
	this->removeChild(bigBoom,true);
	this->bigBooms->removeObject(bigBoom);
}

void UFOLayer::mutiBulletMoveFinished(CCNode* pSender) {
	CCSprite* mutiBullet=(CCSprite*)pSender;
	this->removeChild(mutiBullet,true);//´ÓÆÁÄ»ÖÐÒÆ³ý
	this->mutiBullets->removeObject(mutiBullet);
}
