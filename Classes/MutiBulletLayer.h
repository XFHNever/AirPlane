/*
 * MutiBulletLayer.h
 *
 *  Created on: 2014-4-23
 *      Author: never
 */

#ifndef MUTIBULLETLAYER_H_
#define MUTIBULLETLAYER_H_
#include "cocos2d.h"

class MutiBulletLayer : public cocos2d::CCLayer{
public:
	MutiBulletLayer();
	~MutiBulletLayer();
	virtual bool init();
	CREATE_FUNC(MutiBulletLayer);

	void AddMutiBullets(float dt);

	void mutiBulletsMoveFinished(CCNode* pSender);

	void removeMutiBullets(cocos2d::CCSprite* mutiBullet);

	void StartShoot();

	void StopShoot();
public:
	cocos2d::CCArray *mutiBullets;
	cocos2d::CCSpriteBatchNode *mutiBulletsBatchNode;
};

#endif /* MUTIBULLETLAYER_H_ */
