/*
 * Enemy.h
 *
 *  Created on: 2014-4-11
 *      Author: never
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "cocos2d.h"

class Enemy : public cocos2d::CCNode {
public:
	Enemy();
	~Enemy();
	static Enemy* create();
	void bindSprite(cocos2d::CCSprite* sprite,int life);
	cocos2d::CCSprite* getSprite();
	int getLife();
	void loseLife();
	cocos2d::CCRect getBoundingBox();

private:
	cocos2d::CCSprite *sprite;
	int life;
};

#endif /* ENEMY_H_ */
