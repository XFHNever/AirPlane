/*
 * EnemyLayer.cpp
 *
 *  Created on: 2014-4-11
 *      Author: never
 */
#include "EnemyLayer.h"
#include "stdlib.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"

USING_NS_CC;

EnemyLayer::EnemyLayer(){
	enemy1SpriteFrame=NULL;
	enemy2SpriteFrame=NULL;
	enemy3SpriteFrame_1=NULL;
	enemy3SpriteFrame_2=NULL;

	enemy1s = CCArray::create();
	enemy1s->retain();
	enemy2s = CCArray::create();
	enemy2s->retain();
	enemy3s = CCArray::create();
	enemy3s->retain();
}

EnemyLayer::~EnemyLayer(){
	enemy1s->release();
	enemy1s = NULL;
	enemy2s->release();
	enemy2s = NULL;
	enemy3s->release();
	enemy3s = NULL;
}

bool EnemyLayer::init(){
	bool bRet = false;

	do{
		CC_BREAK_IF(!CCLayer::init());

		enemy1SpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1.png");
		enemy2SpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2.png");
		enemy3SpriteFrame_1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n1.png");
		enemy3SpriteFrame_2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n2.png");

		CCAnimation *animation1 = CCAnimation::create();
		animation1->setDelayPerUnit(0.1f);
		animation1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down1.png"));
		animation1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down2.png"));
		animation1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down3.png"));
		animation1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down4.png"));

		CCAnimationCache::sharedAnimationCache()->addAnimation(animation1,"Enemy1Blowup");

		CCAnimation *animation2 = CCAnimation::create();
		animation2->setDelayPerUnit(0.1f);
		animation2->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down1.png"));
		animation2->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down2.png"));
		animation2->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down3.png"));
		animation2->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down4.png"));

		CCAnimationCache::sharedAnimationCache()->addAnimation(animation2,"Enemy2Blowup");

		CCAnimation *animation3 = CCAnimation::create();
		animation3->setDelayPerUnit(0.1f);
		animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down1.png"));
		animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down2.png"));
		animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down3.png"));
		animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down4.png"));
		animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down5.png"));
		animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down6.png"));

		CCAnimationCache::sharedAnimationCache()->addAnimation(animation3,"Enemy3Blowup");



		this->schedule(schedule_selector(EnemyLayer::addEnemy1),0.5f);
		this->schedule(schedule_selector(EnemyLayer::addEnemy2),1.0f);
		this->schedule(schedule_selector(EnemyLayer::addEnemy3),1.5f);

		bRet = true;
	}while(0);
	return bRet;
}

void EnemyLayer::addEnemy1(float dt) {
	Enemy *enemy1 = Enemy::create();
	enemy1->bindSprite(CCSprite::createWithSpriteFrame(enemy1SpriteFrame),ENEMY1_MAX_LIFE);

	CCSize enemy1Size = enemy1->getSprite()->getContentSize();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minX = enemy1Size.width/2;
	int maxX = winSize.width - enemy1Size.width/2;
	int  rangeX = maxX-minX;
	int actualX = (rand()%rangeX) + minX;

	enemy1->setPosition(ccp(actualX,winSize.height + enemy1Size.height/2));
	this->addChild(enemy1);
	this->enemy1s->addObject(enemy1);

	//随机飞行速度
	float minDuration,maxDuration;
	switch(GameLayer::getCurLevel())
	{
	case EASY:
		minDuration=2.0;
		maxDuration=4.0;
		break;
	case MIDDLE:
		minDuration=1.8;
		maxDuration=3.6;
		break;
	case HARD:
		minDuration=1.6;
		maxDuration=3.2;
		break;
	default:
		minDuration=2.0;
		maxDuration=4.0;
		break;
	}

	int rangeDuration=maxDuration-minDuration;
	int actualDuration=(rand()%rangeDuration)+minDuration;

	CCFiniteTimeAction *move = CCMoveTo::create(actualDuration,ccp(actualX,0-enemy1->getSprite()->getContentSize().height/2));
	CCFiniteTimeAction *done=CCCallFuncN::create(this,callfuncN_selector(EnemyLayer::enemy1MoveOut));

	CCSequence *actions = CCSequence::create(move,done,NULL);

	enemy1->runAction(actions);
}

void EnemyLayer::enemy1Blowup(Enemy* enemy1)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy1_down.mp3");
	CCAnimation* animation=CCAnimationCache::sharedAnimationCache()->animationByName("Enemy1Blowup");
	CCAnimate* animate=CCAnimate::create(animation);
	CCCallFuncND* removeEnemy1=CCCallFuncND::create(this,callfuncND_selector(EnemyLayer::removeEnemy1),(void*)enemy1);
	CCSequence* sequence=CCSequence::create(animate,removeEnemy1,NULL);
	enemy1->getSprite()->runAction(sequence);
}

void EnemyLayer::removeEnemy1(CCNode* pTarget, void* data){
	Enemy* enemy1 = (Enemy*)data;
	if(enemy1 != NULL){
		enemy1s->removeObject(enemy1);
		this->removeChild(enemy1);
	}
}

void EnemyLayer::enemy1MoveOut(CCNode* pSender){
	Enemy* enemy1 = (Enemy*)pSender;
	this->removeChild(enemy1);
	this->enemy1s->removeObject(enemy1);
}

void EnemyLayer::removeAllEnemy1()
{
	CCObject* obj;
	CCARRAY_FOREACH(enemy1s,obj)
	{
		Enemy* enemy1=(Enemy*)obj;
		if (enemy1->getLife()>0)
		{
			enemy1Blowup(enemy1);
		}
	}
}

void EnemyLayer::addEnemy2(float dt) {
	Enemy *enemy2 = Enemy::create();
	enemy2->bindSprite(CCSprite::createWithSpriteFrame(enemy2SpriteFrame),ENEMY2_MAX_LIFE);

	CCSize enemy2Size = enemy2->getSprite()->getContentSize();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minX = enemy2Size.width/2;
	int maxX = winSize.width - enemy2Size.width/2;
	int  rangeX = maxX-minX;
	int actualX = (rand()%rangeX) + minX;

	enemy2->setPosition(ccp(actualX,winSize.height + enemy2Size.height/2));
	this->addChild(enemy2);
	this->enemy2s->addObject(enemy2);

	//随机飞行速度
	float minDuration,maxDuration;
	switch(GameLayer::getCurLevel())
	{
	case EASY:
		minDuration=3.0;
		maxDuration=6.0;
		break;
	case MIDDLE:
		minDuration=2.7;
		maxDuration=5.4;
		break;
	case HARD:
		minDuration=2.5;
		maxDuration=5.0;
		break;
	default:
		minDuration=3.0;
		maxDuration=6.0;
		break;
	}

	int rangeDuration=maxDuration-minDuration;
	int actualDuration=(rand()%rangeDuration)+minDuration;

	CCFiniteTimeAction *move = CCMoveTo::create(actualDuration,ccp(actualX,0-enemy2->getSprite()->getContentSize().height/2));
	CCFiniteTimeAction *done=CCCallFuncN::create(this,callfuncN_selector(EnemyLayer::enemy2MoveOut));

	CCSequence *actions = CCSequence::create(move,done,NULL);

	enemy2->runAction(actions);
}

void EnemyLayer::enemy2Blowup(Enemy* enemy2)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy2_down.mp3");
	CCAnimation* animation=CCAnimationCache::sharedAnimationCache()->animationByName("Enemy2Blowup");
	CCAnimate* animate=CCAnimate::create(animation);
	CCCallFuncND* removeEnemy2=CCCallFuncND::create(this,callfuncND_selector(EnemyLayer::removeEnemy2),(void*)enemy2);
	CCSequence* sequence=CCSequence::create(animate,removeEnemy2,NULL);
	enemy2->getSprite()->runAction(sequence);
}

void EnemyLayer::removeEnemy2(CCNode* pTarget, void* data){
	Enemy* enemy2 = (Enemy*)data;
	if(enemy2 != NULL){
		enemy2s->removeObject(enemy2);
		this->removeChild(enemy2);
	}
}

void EnemyLayer::enemy2MoveOut(CCNode* pSender){
	Enemy* enemy2 = (Enemy*)pSender;
	this->removeChild(enemy2);
	this->enemy2s->removeObject(enemy2);
}

void EnemyLayer::removeAllEnemy2()
{
	CCObject* obj;
	CCARRAY_FOREACH(enemy2s,obj)
	{
		Enemy* enemy2=(Enemy*)obj;
		if (enemy2->getLife()>0)
		{
			enemy2Blowup(enemy2);
		}
	}
}

void EnemyLayer::addEnemy3(float dt) {
	Enemy *enemy3 = Enemy::create();
	enemy3->bindSprite(CCSprite::createWithSpriteFrame(enemy3SpriteFrame_1),ENEMY3_MAX_LIFE);

	CCSize enemy3Size = enemy3->getSprite()->getContentSize();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minX = enemy3Size.width/2;
	int maxX = winSize.width - enemy3Size.width/2;
	int  rangeX = maxX-minX;
	int actualX = (rand()%rangeX) + minX;

	enemy3->setPosition(ccp(actualX,winSize.height + enemy3Size.height/2));
	this->addChild(enemy3);
	this->enemy3s->addObject(enemy3);

	//随机飞行速度
	float minDuration,maxDuration;
	switch(GameLayer::getCurLevel())
	{
	case EASY:
		minDuration=4.0;
		maxDuration=8.0;
		break;
	case MIDDLE:
		minDuration=3.6;
		maxDuration=7.2;
		break;
	case HARD:
		minDuration=3.2;
		maxDuration=6.4;
		break;
	default:
		minDuration=4.0;
		maxDuration=8.0;
		break;
	}

	int rangeDuration=maxDuration-minDuration;
	int actualDuration=(rand()%rangeDuration)+minDuration;

	CCFiniteTimeAction *move = CCMoveTo::create(actualDuration,ccp(actualX,0-enemy3->getSprite()->getContentSize().height/2));
	CCFiniteTimeAction *done=CCCallFuncN::create(this,callfuncN_selector(EnemyLayer::enemy3MoveOut));

	CCSequence *actions = CCSequence::create(move,done,NULL);

	enemy3->runAction(actions);
}

void EnemyLayer::enemy3Blowup(Enemy* enemy3)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy3_down.mp3");
	CCAnimation* animation=CCAnimationCache::sharedAnimationCache()->animationByName("Enemy3Blowup");
	CCAnimate* animate=CCAnimate::create(animation);
	CCCallFuncND* removeEnemy3=CCCallFuncND::create(this,callfuncND_selector(EnemyLayer::removeEnemy3),(void*)enemy3);
	CCSequence* sequence=CCSequence::create(animate,removeEnemy3,NULL);
	enemy3->getSprite()->runAction(sequence);
}

void EnemyLayer::removeEnemy3(CCNode* pTarget, void* data){
	Enemy* enemy3 = (Enemy*)data;
	if(enemy3 != NULL){
		enemy3s->removeObject(enemy3);
		this->removeChild(enemy3);
	}
}

void EnemyLayer::enemy3MoveOut(CCNode* pSender){
	Enemy* enemy3 = (Enemy*)pSender;
	this->removeChild(enemy3);
	this->enemy3s->removeObject(enemy3);
}

void EnemyLayer::removeAllEnemy3()
{
	CCObject* obj;
	CCARRAY_FOREACH(enemy3s,obj)
	{
		Enemy* enemy3=(Enemy*)obj;
		if (enemy3->getLife()>0)
		{
			enemy3Blowup(enemy3);
		}
	}
}

void EnemyLayer::removeAllEnemy()
{
	removeAllEnemy1();
	removeAllEnemy2();
	removeAllEnemy3();
}
