/*
 * GameScene.cpp
 *
 *  Created on: 2014-4-10
 *      Author: never
 */
#include "GameScene.h"

USING_NS_CC;

GameScene::GameScene(void)
{
	_gameLayer=NULL;
}

GameScene::~GameScene(void)
{
}

bool GameScene::init()
{
	bool bRet=false;
	do
	{
		CC_BREAK_IF(!CCScene::init());
		_gameLayer=GameLayer::create();
		this->_gameLayer->retain();
		CC_BREAK_IF(!_gameLayer);
		this->addChild(_gameLayer);
		bRet=true;
	} while (0);

	return bRet;
}

