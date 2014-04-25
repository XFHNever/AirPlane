/*
 * BulletLayer.h
 *
 *  Created on: 2014-4-11
 *      Author: never
 */

#ifndef BULLETLAYER_H_
#define BULLETLAYER_H_

#include "cocos2d.h"

class BulletLayer : public cocos2d::CCLayer{
public:
	BulletLayer(void);
	~BulletLayer(void);
	bool init();
	void AddBullet(float dt);
	void bulletMoveOut(cocos2d::CCNode* pSender);

	void startShoot(float delay = 0.0f);
	void stopShoot();
	void removeBullet(cocos2d::CCSprite* bullet);

	CREATE_FUNC(BulletLayer);
public:
	cocos2d::CCSpriteBatchNode *bulletBatchNode;
	cocos2d::CCArray *bullets;
};
#endif /* BULLETLAYER_H_ */
