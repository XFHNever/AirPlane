/*
 * UFOLayer.h
 *
 *  Created on: 2014-4-23
 *      Author: never
 */

#ifndef UFOLAYER_H_
#define UFOLAYER_H_

#include "cocos2d.h"
class UFOLayer : public cocos2d::CCLayer{
public:
	UFOLayer();
	~UFOLayer();
	virtual bool init();
	CREATE_FUNC(UFOLayer);

	void addMutiBullets(float dt);
	void mutiBulletMoveFinished(cocos2d::CCNode* pSender);

	void addBigBooms(float dt);
	void bigBoomMoveFinished(cocos2d::CCNode* pSender);

	void removeBigBooms(cocos2d::CCSprite* bigBoom);
	void removeMutiBullets(cocos2d::CCSprite* mutiBullet);

public:
	cocos2d::CCArray *bigBooms;
	cocos2d::CCArray *mutiBullets;
};

#endif /* UFOLAYER_H_ */
