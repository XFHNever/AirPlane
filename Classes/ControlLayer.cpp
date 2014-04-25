/*
 * ControlLayer.cpp
 *
 *  Created on: 2014-4-25
 *      Author: never
 */
#include "ControlLayer.h"

USING_NS_CC;

ControlLayer::ControlLayer(){

}

ControlLayer::~ControlLayer(){

}

bool ControlLayer::init(){
	bool bRet = false;
	do{
		CC_BREAK_IF(!CCLayer::init());

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CCSprite *normalPause = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_nor.png"));
		CCSprite *pressedPause = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_pressed.png"));

		pauseItem = CCMenuItemImage::create();
		pauseItem->initWithNormalSprite(normalPause,pressedPause,NULL,this,menu_selector(ControlLayer::menuPauseCallback));
		pauseItem->setPosition(ccp(normalPause->getContentSize().width/2+10,winSize.height-normalPause->getContentSize().height/2-5));

		CCMenu *pauseMenu = CCMenu::create(pauseItem,NULL);
		pauseMenu->setPosition(CCPointZero);
		this->addChild(pauseMenu,101);

		scoreItem = CCLabelBMFont::create("0","font/font.fnt");
		scoreItem->setColor(ccColor3B{143,146,147});
		scoreItem->setAnchorPoint(ccp(0,0.5));
		scoreItem->setPosition(ccp(pauseItem->getPositionX()+normalPause->getContentSize().width/2+5,pauseItem->getPositionY()));
		this->addChild(scoreItem);

		bRet = true;
	}while(0);
	return bRet;
}

void ControlLayer::menuPauseCallback(){
	if(!CCDirector::sharedDirector()->isPaused()) {
		//更改为恢复按钮的双态
		pauseItem->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_nor.png"));
		pauseItem->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_pressed.png"));
		CCDirector::sharedDirector()->pause();//暂停游戏，这是导演控制的
	} else {
		pauseItem->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_nor.png"));
		pauseItem->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_pressed.png"));
		CCDirector::sharedDirector()->resume();
	}
}

void ControlLayer::updateScore(int score){
	if(score >= 0 && score <= MAX_SCORE) {
		CCString *strScore = CCString::createWithFormat("%d",score);
		scoreItem->setString(strScore->getCString());
	}
}



