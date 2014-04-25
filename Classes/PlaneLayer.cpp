/*
 * PlaneLayer.cpp
 *
 *  Created on: 2014-4-11
 *      Author: never
 */
#include "PlaneLayer.h"
#include "GameOverScene.h"

USING_NS_CC;

PlaneLayer* PlaneLayer::sharedPlane = NULL;

PlaneLayer::PlaneLayer(){
	this->isAlive = true;
	this->score = 0;
}

PlaneLayer::~PlaneLayer(){

}

PlaneLayer* PlaneLayer::create(){
	PlaneLayer *pRet = new PlaneLayer();
	if(pRet && pRet->init()) {
		pRet->autorelease();
		sharedPlane = pRet;
		return pRet;
	} else {
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

bool PlaneLayer::init(){
	bool bRet = false;

	do{
		CC_BREAK_IF(!CCLayer::init());

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CCSprite* plane = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
		plane->setPosition(ccp(winSize.width/2,plane->getContentSize().height/2));
		this->addChild(plane,0,AIRPLANE);

		CCBlink *blink = CCBlink::create(1,3);

		CCAnimation *animation = CCAnimation::create();
		animation->setDelayPerUnit(0.1f);
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero2.png"));
		CCAnimate *animate = CCAnimate::create(animation);

		plane->runAction(blink);
		plane->runAction(CCRepeatForever::create(animate));

		this->setTouchEnabled(true);

		bRet = true;
	}while(0);

	return bRet;
}

bool PlaneLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	return true;
}

void PlaneLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
	if(this->isAlive){
		CCPoint beginPoint = pTouch->getLocationInView();
		beginPoint = CCDirector::sharedDirector()->convertToGL(beginPoint);

		CCRect planeRect = this->getChildByTag(AIRPLANE)->boundingBox();
		planeRect.origin.x -= 15;
		planeRect.origin.y -= 15;
		planeRect.size.height += 30;
		planeRect.size.width += 30;

		if(planeRect.containsPoint(beginPoint)){
			CCPoint endPoint = pTouch->getPreviousLocationInView();
			endPoint = CCDirector::sharedDirector()->convertToGL(endPoint);

			CCPoint offSet = ccpSub(beginPoint,endPoint);
			CCPoint toPoint = ccpAdd(this->getChildByTag(AIRPLANE)->getPosition(),offSet);
			this->MoveTo(toPoint);
		}

	}
}

void PlaneLayer::MoveTo(CCPoint location){
	if(this->isAlive && !CCDirector::sharedDirector()->isPaused()){
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSize planeSize = this->getChildByTag(AIRPLANE)->getContentSize();

		if(location.x < planeSize.width/2) {
			location.x = planeSize.width/2;
		}

		if(location.x > winSize.width - planeSize.width/2){
			location.x = winSize.width - planeSize.width/2;
		}

		if(location.y < planeSize.height/2){
			location.y = planeSize.height/2;
		}

		if(location.y > winSize.height - planeSize.height/2) {
			location.y = winSize.height - planeSize.height/2;
		}

		this->getChildByTag(AIRPLANE)->setPosition(location);
	}
}

void PlaneLayer::registerWithTouchDispatcher(){
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void PlaneLayer::Blowup(int passScore){
	if(isAlive) {
		isAlive = false;
		score = passScore;

		CCAnimation *animation = CCAnimation::create();
		animation->setDelayPerUnit(0.2f);
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n1.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n2.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n3.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n4.png"));

		CCAnimate *animate = CCAnimate::create(animation);
		CCCallFunc *removePlane = CCCallFunc::create(this,callfunc_selector(PlaneLayer::RemovePlane));
		CCSequence *sequence = CCSequence::create(animate,removePlane,NULL);
		this->getChildByTag(AIRPLANE)->stopAllActions();
		this->getChildByTag(AIRPLANE)->runAction(sequence);


	}
}

void PlaneLayer::RemovePlane(){
	this->removeChildByTag(AIRPLANE,true);
	GameOverScene* pScene=GameOverScene::create(score);
	CCTransitionMoveInT* animateScene=CCTransitionMoveInT::create(0.8f,pScene);
	CCDirector::sharedDirector()->replaceScene(animateScene);
}
