/*
 * GameOverLayer.cpp
 *
 *  Created on: 2014-4-23
 *      Author: never
 */
#include "GameOverLayer.h"
#include <cstring>
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

int GameOverLayer::highestScore = 0;

GameOverLayer::GameOverLayer(){
	score = 0;
	highestScoreLabel = NULL;
}

GameOverLayer::~GameOverLayer(){

}

bool GameOverLayer::init(){
	bool bRet = false;
	do{
		CC_BREAK_IF(!CCLayer::init());

		if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		}

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/game_over.mp3");

		CCSize winSize=CCDirector::sharedDirector()->getWinSize();
		CCSprite* background=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gameover.png"));
		background->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(background);

		CCSprite* normalBackToGame=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_finish.png"));
		CCSprite* pressedBackToGame=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_finish.png"));
		CCMenuItemImage* pBackItem=CCMenuItemImage::create();
		pBackItem->initWithNormalSprite(normalBackToGame,pressedBackToGame,NULL,this,menu_selector(GameOverLayer::menuBackCallback));
		pBackItem->setPosition(ccp(winSize.width-normalBackToGame->getContentSize().width/2-10,normalBackToGame->getContentSize().height/2+10));
		CCMenu *menuBack=CCMenu::create(pBackItem,NULL);
		menuBack->setPosition(CCPointZero);
		this->addChild(menuBack);

		CCString* strScore=CCString::createWithFormat("%d",score);
		CCLabelBMFont* finalScore=CCLabelBMFont::create(strScore->getCString(),"font/font.fnt");
		finalScore->setColor(ccColor3B{143,146,147});
		finalScore->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(finalScore);

		CCDelayTime *delay = CCDelayTime::create(1.0f);
		CCScaleTo *scalebig = CCScaleTo::create(1.0f,3.0f);
		CCScaleTo *scalelittle = CCScaleTo::create(0.3f,2.0f);
		CCCallFunc *showAD = CCCallFunc::create(this,callfunc_selector(GameOverLayer::showAD));
		CCFiniteTimeAction *sequence = CCSequence::create(delay,scalebig,scalelittle,showAD,NULL);
		finalScore->runAction(sequence);

		CCString* strHighestScore=CCString::createWithFormat("历史最高:%d",this->highestScore);
		this->highestScoreLabel=CCLabelBMFont::create(strHighestScore->getCString(),"font/font.fnt");
		highestScoreLabel->setColor(ccColor3B{143,146,147});
		highestScoreLabel->setAnchorPoint(ccp(0,0.5));
		highestScoreLabel->setPosition(ccp(20,winSize.height - 40));
		this->addChild(highestScoreLabel);

		if(score>highestScore){
			CCUserDefault::sharedUserDefault()->setIntegerForKey("HighestScore",score);
			highestScore=score;
			CCDelayTime* delayChange=CCDelayTime::create(1.3f);
			CCMoveBy* moveOut=CCMoveBy::create(0.1f,ccp(0,100));
			CCCallFuncN* beginChange=CCCallFuncN::create(this,callfuncN_selector(GameOverLayer::beginChangeHighestScore));
			CCMoveBy* moveIn=CCMoveBy::create(0.1f,ccp(0,-100));
			CCFiniteTimeAction* sequence=CCSequence::create(delayChange,moveOut,beginChange,moveIn,NULL);
			highestScoreLabel->runAction(sequence);
		}

		this->setKeypadEnabled(true);

		bRet = true;
	}while(0);

	return bRet;
}

GameOverLayer* GameOverLayer::create(int passScore){
	GameOverLayer *pRet = new GameOverLayer();
	pRet->score = passScore;

	if(pRet && pRet->init()) {
		pRet->autorelease();
		return pRet;
	}else{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void GameOverLayer::menuBackCallback(CCObject* pSender){
	CCScene* pScene=GameScene::create();
	CCTransitionSlideInL* animateScene=CCTransitionSlideInL::create(1.0f,pScene);
	CCDirector::sharedDirector()->replaceScene(animateScene);
}

void GameOverLayer::beginChangeHighestScore(CCNode* pNode){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/achievement.mp3");
	CCString* changeScore=CCString::createWithFormat("历史最高:%d",score);
	this->highestScoreLabel->setString(changeScore->getCString());
}

void GameOverLayer::keyBackClicked(){
	CCDirector::sharedDirector()->end();
}

void GameOverLayer::showAD(){

}
