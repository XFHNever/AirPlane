/*
 * WelcomeScene.h
 *
 *  Created on: 2014-4-25
 *      Author: never
 */

#ifndef WELCOMESCENE_H_
#define WELCOMESCENE_H_
#include "cocos2d.h"
#include "WelcomeLayer.h"

class WelcomeScene : public cocos2d::CCScene{
public:
	WelcomeScene(void);

	~WelcomeScene(void);

	virtual bool init();

	CREATE_FUNC(WelcomeScene);

	void PreloadMusic();

private:
	WelcomeLayer *welcomeLayer;
};

#endif /* WELCOMESCENE_H_ */
