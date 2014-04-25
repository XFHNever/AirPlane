/*
 * GameScene.h
 *
 *  Created on: 2014-4-10
 *      Author: never
 */

#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_
#include "cocos2d.h"
#include "GameLayer.h"

class GameScene : public cocos2d::CCScene {
public:
	GameScene(void);
	~GameScene(void);
	virtual bool init();

	CREATE_FUNC(GameScene);

public:
	GameLayer *_gameLayer;
};


#endif /* GAMESCENE_H_ */
