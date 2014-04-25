/*
 * GameOverScene.cpp
 *
 *  Created on: 2014-4-23
 *      Author: never
 */
#include "GameOverScene.h"

USING_NS_CC;

GameOverScene::GameOverScene(){
	this->gameOverLayer = NULL;
	score = 0;
}

GameOverScene::~GameOverScene(){

}

bool GameOverScene::init(){
	bool bRet = false;
	do{
		CC_BREAK_IF(!CCScene::init());

		gameOverLayer=GameOverLayer::create(score);
		this->addChild(gameOverLayer);
		bRet = true;
	}while(0);
	return bRet;
}

GameOverScene* GameOverScene::create(int passScore) {
	GameOverScene *pRet = new GameOverScene();
	pRet->score=passScore;
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
