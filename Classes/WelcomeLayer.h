/*
 * WelcomeLayer.h
 *
 *  Created on: 2014-4-25
 *      Author: never
 */

#ifndef WELCOMELAYER_H_
#define WELCOMELAYER_H_
#include "cocos2d.h"

class WelcomeLayer : public cocos2d::CCLayer{
public:
	WelcomeLayer();
	~WelcomeLayer();
	virtual bool init();
	CREATE_FUNC(WelcomeLayer);
	bool isHaveSaveFile();
	void getHighestHistorySorce();
	virtual void keyBackClicked();//Android·µ»Ø¼ü
	void loadingDone(CCNode* pNode);
};
#endif /* WELCOMELAYER_H_ */
