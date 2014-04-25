/*
 * GameOverScene.h
 *
 *  Created on: 2014-4-23
 *      Author: never
 */

#ifndef GAMEOVERSCENE_H_
#define GAMEOVERSCENE_H_
#include "cocos2d.h"
#include "GameOverLayer.h"
class GameOverScene : public cocos2d::CCScene{
public:
	GameOverScene();
	~GameOverScene();
	virtual bool init();
	static GameOverScene* create(int passScore);
public:
	GameOverLayer *gameOverLayer;
	int score;
};


#endif /* GAMEOVERSCENE_H_ */
