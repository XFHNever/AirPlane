/*
 * EnemyLayer.h
 *
 *  Created on: 2014-4-11
 *      Author: never
 */

#ifndef ENEMYLAYER_H_
#define ENEMYLAYER_H_
#include "cocos2d.h"
#include "Enemy.h"

const int ENEMY1_MAX_LIFE = 1;
const int ENEMY2_MAX_LIFE = 2;
const int ENEMY3_MAX_LIFE = 5;

enum Level
{
	EASY,
	MIDDLE,
	HARD,
};

class EnemyLayer : public cocos2d::CCLayer{
public:
	EnemyLayer();
	~EnemyLayer();

	CREATE_FUNC(EnemyLayer);

	virtual bool init();

	void addEnemy1(float dt);
	void enemy1MoveOut(cocos2d::CCNode* pSender);
	void removeEnemy1(CCNode* pTarget, void* data);
	void removeAllEnemy1();
	void enemy1Blowup(Enemy* enemy1);

	void addEnemy2(float dt);
	void enemy2MoveOut(cocos2d::CCNode* pSender);
	void removeEnemy2(CCNode* pTarget, void* data);
	void enemy2Blowup(Enemy* enemy2);
	void removeAllEnemy2();

	void addEnemy3(float dt);
	void enemy3MoveOut(cocos2d::CCNode* pSender);
	void removeEnemy3(CCNode* pTarget, void* data);
	void removeAllEnemy3();
	void enemy3Blowup(Enemy* enemy3);
	void removeAllEnemy();
public:
	cocos2d::CCArray *enemy1s;
	cocos2d::CCArray *enemy2s;
	cocos2d::CCArray *enemy3s;

private:
	cocos2d::CCSpriteFrame *enemy1SpriteFrame;
	cocos2d::CCSpriteFrame *enemy2SpriteFrame;
	cocos2d::CCSpriteFrame *enemy3SpriteFrame_1;
	cocos2d::CCSpriteFrame *enemy3SpriteFrame_2;
};
#endif /* ENEMYLAYER_H_ */
