/*
 * ControlLayer.h
 *
 *  Created on: 2014-4-25
 *      Author: never
 */

#ifndef CONTROLLAYER_H_
#define CONTROLLAYER_H_

#include "cocos2d.h"

static const int MAX_SCORE = 200000000;

class ControlLayer : public cocos2d::CCLayer{
public:
	ControlLayer();
	~ControlLayer();
	virtual bool init();

	CREATE_FUNC(ControlLayer);

	void menuPauseCallback();
	void updateScore(int score);
public:
	cocos2d::CCMenuItemImage *pauseItem;
	cocos2d::CCLabelBMFont *scoreItem;
};

#endif /* CONTROLLAYER_H_ */
