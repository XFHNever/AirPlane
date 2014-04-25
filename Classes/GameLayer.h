/*
 * GameLayer.h
 *
 *  Created on: 2014-4-10
 *      Author: never
 */

#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_
#include "cocos2d.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"
#include "UFOLayer.h"
#include "MutiBulletLayer.h"
#include "ControlLayer.h"

const int MAX_BIGBOOM_COUNT=100000;
const int TAG_BIGBOOM_MENUITEM=1;
const int TAG_BIGBOOMCOUNT_LABEL=2;

const int ENEMY1_SCORE=100;
const int ENEMY2_SCORE=600;
const int ENEMY3_SCORE=3000;

class GameLayer : public cocos2d::CCLayer{
public:
	GameLayer();
	~GameLayer();
	bool init();
	void backgroundMove(float dt);
	void update(float dt);
	void updateBigBoomItem(int bigBoomCount);
	void menuBigBoomCallback(CCObject* pSender);
	virtual void keyBackClicked();//Android·µ»Ø¼ü

	CREATE_FUNC(GameLayer);

	static Level getCurLevel();
private:
	int score;
	int bigBoomsCount;

	cocos2d::CCSprite *background1;
	cocos2d::CCSprite *background2;

	PlaneLayer *planeLayer;
	BulletLayer *bulletLayer;
	EnemyLayer *enemyLayer;
	UFOLayer *ufoLayer;
	MutiBulletLayer *mutiBulletLayer;
	ControlLayer *controlLayer;

	cocos2d::CCMenu *bigBoomMenu;
	cocos2d::CCLabelBMFont *bigBoomCountItem;

	static Level level;

};
#endif /* GAMELAYER_H_ */
