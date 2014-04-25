/*
 * GameLayer.cpp
 *
 *  Created on: 2014-4-10
 *      Author: never
 */
#include "cocos2d.h"
#include "GameLayer.h"
#include "PlaneLayer.h"
#include "Enemy.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Level GameLayer::level=EASY;

GameLayer::GameLayer(){
	background1 = NULL;
	background2 = NULL;
	planeLayer = NULL;
	bulletLayer = NULL;
	enemyLayer = NULL;
	ufoLayer = NULL;
	controlLayer = NULL;

	score = 0;
	bigBoomsCount = 0;
}

GameLayer::~GameLayer(){

}

Level GameLayer::getCurLevel(){
	return level;
}

bool GameLayer::init(){
	bool bRet = false;

	do{
		CC_BREAK_IF(!CCLayer::init());

		//¼ÓÔØbackground Music
		if (!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.mp3",true);
		}

		background1 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background1->setAnchorPoint(ccp(0,0));
		background1->setPosition(ccp(0,0));
		this->addChild(background1);

		background2 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background2->setAnchorPoint(ccp(0,0));
		background2->setPosition(ccp(0,background2->getContentSize().height-2));
		this->addChild(background2);

		this->planeLayer = PlaneLayer::create();
		this->addChild(planeLayer);

		this->bulletLayer = BulletLayer::create();
		this->addChild(bulletLayer);
		this->bulletLayer->startShoot();

		this->enemyLayer = EnemyLayer::create();
		this->addChild(enemyLayer);

		this->ufoLayer = UFOLayer::create();
		this->addChild(ufoLayer);

		this->mutiBulletLayer = MutiBulletLayer::create();
		this->addChild(mutiBulletLayer);


		this->controlLayer = ControlLayer::create();
		this->addChild(controlLayer);

		this->schedule(schedule_selector(GameLayer::backgroundMove),0.01f);

		this->scheduleUpdate();

		this->setKeypadEnabled(true);

		bRet = true;
	}while(0);

	return bRet;
}

void GameLayer::update(float dt){
	if (level==EASY && score>=100000)
	{
		level=MIDDLE;
	}
	else if (level==MIDDLE && score>=200000)
	{
		level=HARD;
	}

	CCArray *bulletToDelete = CCArray::create();
	bulletToDelete->retain();
	CCObject *bt,*et;

	CCARRAY_FOREACH(this->bulletLayer->bullets,bt){
		CCSprite *bullet = (CCSprite*)bt;

		CCArray *enemy1ToDelete = CCArray::create();
		enemy1ToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->enemy1s,et){
			Enemy *enemy1 = (Enemy*)et;

			if(bullet->boundingBox().intersectsRect(enemy1->getBoundingBox())){
				if(enemy1->getLife() == 1) {
					enemy1->loseLife();
					bulletToDelete->addObject(bullet);
					enemy1ToDelete->addObject(enemy1);
					score+=ENEMY1_SCORE;
					this->controlLayer->updateScore(score);
				}
			}
		}

		CCARRAY_FOREACH(enemy1ToDelete,et) {
			Enemy *enemy1 = (Enemy*)et;
			this->enemyLayer->enemy1Blowup(enemy1);
		}
		enemy1ToDelete->release();
	}

	CCARRAY_FOREACH(bulletToDelete,bt){
		CCSprite *bullet = (CCSprite*)bt;
		this->bulletLayer->removeBullet(bullet);
	}

	bulletToDelete->removeAllObjects();

	//enemy2
	CCARRAY_FOREACH(this->bulletLayer->bullets,bt){
		CCSprite *bullet = (CCSprite*)bt;

		CCArray *enemy2ToDelete = CCArray::create();
		enemy2ToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->enemy2s,et){
			Enemy *enemy2 = (Enemy*)et;

			if(bullet->boundingBox().intersectsRect(enemy2->getBoundingBox())){
				if(enemy2->getLife() > 1){
					enemy2->loseLife();
					bulletToDelete->addObject(bullet);
				} else if(enemy2->getLife() == 1) {
					enemy2->loseLife();
					bulletToDelete->addObject(bullet);
					enemy2ToDelete->addObject(enemy2);
					score+=ENEMY2_SCORE;
					this->controlLayer->updateScore(score);
				}
			}
		}

		CCARRAY_FOREACH(enemy2ToDelete,et) {
			Enemy *enemy2 = (Enemy*)et;
			this->enemyLayer->enemy2Blowup(enemy2);
		}
		enemy2ToDelete->release();
	}

	CCARRAY_FOREACH(bulletToDelete,bt){
		CCSprite *bullet = (CCSprite*)bt;
		this->bulletLayer->removeBullet(bullet);
	}

	bulletToDelete->removeAllObjects();

	//enemy3
	CCARRAY_FOREACH(this->bulletLayer->bullets,bt){
		CCSprite *bullet = (CCSprite*)bt;

		CCArray *enemy3ToDelete = CCArray::create();
		enemy3ToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->enemy3s,et){
			Enemy *enemy3 = (Enemy*)et;

			if(bullet->boundingBox().intersectsRect(enemy3->getBoundingBox())){
				if(enemy3->getLife() > 1){
					enemy3->loseLife();
					bulletToDelete->addObject(bullet);
				}else if(enemy3->getLife() == 1) {
					enemy3->loseLife();
					bulletToDelete->addObject(bullet);
					enemy3ToDelete->addObject(enemy3);
					score+=ENEMY3_SCORE;
					this->controlLayer->updateScore(score);
				}
			}
		}

		CCARRAY_FOREACH(enemy3ToDelete,et) {
			Enemy *enemy3 = (Enemy*)et;
			this->enemyLayer->enemy1Blowup(enemy3);
		}
		enemy3ToDelete->release();
	}

	CCARRAY_FOREACH(bulletToDelete,bt){
		CCSprite *bullet = (CCSprite*)bt;
		this->bulletLayer->removeBullet(bullet);
	}

	bulletToDelete->removeAllObjects();


	CCARRAY_FOREACH(this->mutiBulletLayer->mutiBullets,bt){
			CCSprite *bullet = (CCSprite*)bt;

			CCArray *enemy1ToDelete = CCArray::create();
			enemy1ToDelete->retain();
			CCARRAY_FOREACH(this->enemyLayer->enemy1s,et){
				Enemy *enemy1 = (Enemy*)et;

				if(bullet->boundingBox().intersectsRect(enemy1->getBoundingBox())){
					if(enemy1->getLife() == 1) {
						enemy1->loseLife();
						bulletToDelete->addObject(bullet);
						enemy1ToDelete->addObject(enemy1);
						score+=ENEMY1_SCORE;
						this->controlLayer->updateScore(score);
					}
				}
			}

			CCARRAY_FOREACH(enemy1ToDelete,et) {
				Enemy *enemy1 = (Enemy*)et;
				this->enemyLayer->enemy1Blowup(enemy1);
			}
			enemy1ToDelete->release();
		}

		CCARRAY_FOREACH(bulletToDelete,bt){
			CCSprite *bullet = (CCSprite*)bt;
			this->mutiBulletLayer->removeMutiBullets(bullet);
		}

		bulletToDelete->removeAllObjects();

		//enemy2
		CCARRAY_FOREACH(this->mutiBulletLayer->mutiBullets,bt){
			CCSprite *bullet = (CCSprite*)bt;

			CCArray *enemy2ToDelete = CCArray::create();
			enemy2ToDelete->retain();
			CCARRAY_FOREACH(this->enemyLayer->enemy2s,et){
				Enemy *enemy2 = (Enemy*)et;

				if(bullet->boundingBox().intersectsRect(enemy2->getBoundingBox())){
					if(enemy2->getLife() > 1){
						enemy2->loseLife();
						bulletToDelete->addObject(bullet);
					} else if(enemy2->getLife() == 1) {
						enemy2->loseLife();
						bulletToDelete->addObject(bullet);
						enemy2ToDelete->addObject(enemy2);
						score+=ENEMY2_SCORE;
						this->controlLayer->updateScore(score);
					}
				}
			}

			CCARRAY_FOREACH(enemy2ToDelete,et) {
				Enemy *enemy2 = (Enemy*)et;
				this->enemyLayer->enemy2Blowup(enemy2);
			}
			enemy2ToDelete->release();
		}

		CCARRAY_FOREACH(bulletToDelete,bt){
			CCSprite *bullet = (CCSprite*)bt;
			this->mutiBulletLayer->removeMutiBullets(bullet);
		}

		bulletToDelete->removeAllObjects();

		//enemy3
		CCARRAY_FOREACH(this->mutiBulletLayer->mutiBullets,bt){
			CCSprite *bullet = (CCSprite*)bt;

			CCArray *enemy3ToDelete = CCArray::create();
			enemy3ToDelete->retain();
			CCARRAY_FOREACH(this->enemyLayer->enemy3s,et){
				Enemy *enemy3 = (Enemy*)et;

				if(bullet->boundingBox().intersectsRect(enemy3->getBoundingBox())){
					if(enemy3->getLife() > 1){
						enemy3->loseLife();
						bulletToDelete->addObject(bullet);
					}else if(enemy3->getLife() == 1) {
						enemy3->loseLife();
						bulletToDelete->addObject(bullet);
						enemy3ToDelete->addObject(enemy3);
						score+=ENEMY3_SCORE;
						this->controlLayer->updateScore(score);
					}
				}
			}

			CCARRAY_FOREACH(enemy3ToDelete,et) {
				Enemy *enemy3 = (Enemy*)et;
				this->enemyLayer->enemy1Blowup(enemy3);
			}
			enemy3ToDelete->release();
		}

		CCARRAY_FOREACH(bulletToDelete,bt){
			CCSprite *bullet = (CCSprite*)bt;
			this->mutiBulletLayer->removeMutiBullets(bullet);
		}

		bulletToDelete->removeAllObjects();
	bulletToDelete->release();


	CCRect airplaneRect = this->planeLayer->getChildByTag(AIRPLANE)->boundingBox();
	airplaneRect.origin.x += 30;
	airplaneRect.size.width -= 60;
	//check enemy1 & airplane collosion
	CCARRAY_FOREACH(this->enemyLayer->enemy1s,et){
		Enemy *enemy1 = (Enemy*)et;
		if(enemy1->getLife() > 0) {
			if(airplaneRect.intersectsRect(enemy1->getBoundingBox())) {
				this->unscheduleAllSelectors();
				this->bulletLayer->stopShoot();
				this->mutiBulletLayer->StopShoot();
				this->planeLayer->Blowup(score);
				return;
			}
		}

	}

	//check enemy2 & airplane collosion
	CCARRAY_FOREACH(this->enemyLayer->enemy1s,et){
		Enemy *enemy2 = (Enemy*)et;
		if(enemy2->getLife() > 0) {
			if(airplaneRect.intersectsRect(enemy2->getBoundingBox())) {
				this->unscheduleAllSelectors();
				this->bulletLayer->stopShoot();
				this->mutiBulletLayer->StopShoot();
				this->planeLayer->Blowup(score);
				return;
			}
		}

	}

	//check enemy3 & airplane collosion
	CCARRAY_FOREACH(this->enemyLayer->enemy1s,et){
		Enemy *enemy3 = (Enemy*)et;
		if(enemy3->getLife() > 0) {
			if(airplaneRect.intersectsRect(enemy3->getBoundingBox())) {
				this->unscheduleAllSelectors();
				this->bulletLayer->stopShoot();
				this->mutiBulletLayer->StopShoot();
				this->planeLayer->Blowup(score);
				return;
			}
		}

	}

	CCObject *ut;
	CCARRAY_FOREACH(this->ufoLayer->bigBooms,ut){
		CCSprite* bigBooms = (CCSprite*)ut;
		if(this->planeLayer->getChildByTag(AIRPLANE)->boundingBox().intersectsRect(bigBooms->boundingBox())){
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/get_bomb.mp3");
			this->ufoLayer->removeBigBooms(bigBooms);
			this->bigBoomsCount++;
			this->updateBigBoomItem(bigBoomsCount);
		}
	}

	CCARRAY_FOREACH(this->ufoLayer->mutiBullets,ut){
		CCSprite* mutiBullet = (CCSprite*)ut;
		if(this->planeLayer->getChildByTag(AIRPLANE)->boundingBox().intersectsRect(mutiBullet->boundingBox())){
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/get_double_laser.mp3");
			this->ufoLayer->removeMutiBullets(mutiBullet);
			this->bulletLayer->stopShoot();
			this->mutiBulletLayer->StartShoot();
			this->bulletLayer->startShoot(6.2f);
		}
	}
}

void GameLayer::backgroundMove(float dt){
	background1->setPositionY(background1->getPositionY()-2);
	background2->setPositionY(background1->getPositionY()+background1->getContentSize().height-2);
	if(background2->getPositionY() == 0) {
		background1->setPositionY(0);
	}
}

void GameLayer::updateBigBoomItem(int bigBoomCount){
	CCSprite *normalBoom = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bomb.png"));
	CCSprite *pressedBoom = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bomb.png"));

	if(bigBoomCount < 0) {
		return;
	}else if(bigBoomCount == 0) {
		if(this->getChildByTag(TAG_BIGBOOM_MENUITEM)){
			this->removeChildByTag(TAG_BIGBOOM_MENUITEM,true);
		}

		if(this->getChildByTag(TAG_BIGBOOMCOUNT_LABEL)){
			this->removeChildByTag(TAG_BIGBOOMCOUNT_LABEL,true);
		}
	}else if(bigBoomCount == 1) {
		if(!this->getChildByTag(TAG_BIGBOOM_MENUITEM)){
			CCMenuItemImage *bigBoomItem = CCMenuItemImage::create();
			bigBoomItem->initWithNormalSprite(normalBoom,pressedBoom,NULL,this,menu_selector(GameLayer::menuBigBoomCallback));
			bigBoomItem->setPosition(ccp(normalBoom->getContentSize().width/2+10,normalBoom->getContentSize().height/2+10));

			CCMenu *boomMenu = CCMenu::create(bigBoomItem,NULL);
			boomMenu->setPosition(CCPointZero);

			this->addChild(boomMenu,0,TAG_BIGBOOM_MENUITEM);

		}

		if(this->getChildByTag(TAG_BIGBOOMCOUNT_LABEL)){
			this->removeChildByTag(TAG_BIGBOOMCOUNT_LABEL,true);
		}
	}else{
		if(!this->getChildByTag(TAG_BIGBOOM_MENUITEM)){
			CCMenuItemImage *bigBoomItem = CCMenuItemImage::create();
			bigBoomItem->initWithNormalSprite(normalBoom,pressedBoom,NULL,this,menu_selector(GameLayer::menuBigBoomCallback));
			bigBoomItem->setPosition(ccp(normalBoom->getContentSize().width/2+10,normalBoom->getContentSize().height/2+10));

			CCMenu *boomMenu = CCMenu::create(bigBoomItem,NULL);
			boomMenu->setPosition(CCPointZero);

			this->addChild(boomMenu,0,TAG_BIGBOOM_MENUITEM);
		}

		if(this->getChildByTag(TAG_BIGBOOMCOUNT_LABEL)){
			this->removeChildByTag(TAG_BIGBOOMCOUNT_LABEL,true);
		}

		if(bigBoomCount <= MAX_BIGBOOM_COUNT){
			CCString *strCount = CCString::createWithFormat("X%d",bigBoomCount);

			this->bigBoomCountItem = CCLabelBMFont::create(strCount->getCString(),"font/font.fnt");
			this->bigBoomCountItem->setPosition(ccp(normalBoom->getContentSize().width + 15,normalBoom->getContentSize().height/2 + 5));
			this->bigBoomCountItem->setColor(ccColor3B{143,146,147});
			this->bigBoomCountItem->setAnchorPoint(ccp(0,0.5));
			this->addChild(bigBoomCountItem,0,TAG_BIGBOOMCOUNT_LABEL);
		}
	}
}

void GameLayer::menuBigBoomCallback(CCObject* pSender){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/use_bomb.mp3");
	this->bigBoomsCount--;
	score+=this->enemyLayer->enemy1s->count()*ENEMY1_SCORE;
	score+=this->enemyLayer->enemy2s->count()*ENEMY2_SCORE;
	score+=this->enemyLayer->enemy3s->count()*ENEMY3_SCORE;
	this->updateBigBoomItem(bigBoomsCount);
	this->enemyLayer->removeAllEnemy();
	this->controlLayer->updateScore(score);
}

void GameLayer::keyBackClicked(){
	CCDirector::sharedDirector()->end();
}

