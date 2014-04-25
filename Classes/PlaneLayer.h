/*
 * PlaneLayer.h
 *
 *  Created on: 2014-4-11
 *      Author: never
 */

#ifndef PLANELAYER_H_
#define PLANELAYER_H_

#include "cocos2d.h"

const int AIRPLANE = 100;

class PlaneLayer : public cocos2d::CCLayer {
public:
	PlaneLayer(void);
	~PlaneLayer(void);
	static PlaneLayer* create();
	virtual bool init();
	void MoveTo(cocos2d::CCPoint location);
	void Blowup(int passScore);
	void RemovePlane();

	void registerWithTouchDispatcher();
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

public:
	static PlaneLayer *sharedPlane;
	bool isAlive;
	int score;
};
#endif /* PLANELAYER_H_ */
