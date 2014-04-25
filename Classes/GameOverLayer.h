/*
 * GameOverLayer.h
 *
 *  Created on: 2014-4-23
 *      Author: never
 */

#ifndef GAMEOVERLAYER_H_
#define GAMEOVERLAYER_H_

#include "cocos2d.h"

class GameOverLayer : public cocos2d::CCLayer{
public:
	GameOverLayer();
	~GameOverLayer();
	virtual bool init();

	static GameOverLayer* create(int passScore);

	void menuBackCallback(CCObject* pSender);

	virtual void keyBackClicked();//Android·µ»Ø¼ü

	void beginChangeHighestScore(CCNode* pNode);

	void showAD();


public:
	int score;
	static int highestScore;
	cocos2d::CCLabelBMFont* highestScoreLabel;
};

#endif /* GAMEOVERLAYER_H_ */
