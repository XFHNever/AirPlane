/*
 * WelcomeScene.cpp
 *
 *  Created on: 2014-4-25
 *      Author: never
 */
#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

WelcomeScene::WelcomeScene(){
	this->welcomeLayer = NULL;
}

WelcomeScene::~WelcomeScene(){

}

bool WelcomeScene::init() {
	bool bRet = true;
	do{
		CC_BREAK_IF(!CCScene::init());
		this->welcomeLayer = WelcomeLayer::create();
		CC_BREAK_IF(!welcomeLayer);
		this->addChild(welcomeLayer);
		this->PreloadMusic();
		bRet = true;
	}while(0);
	return bRet;
}

void WelcomeScene::PreloadMusic(){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound/game_music.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/bullet.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/enemy1_down.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/enemy2_down.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/enemy3_down.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/game_over.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/get_bomb.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/get_double_laser.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/use_bomb.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/big_spaceship_flying.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/achievement.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/out_porp.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/button.mp3");

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.mp3",true);
}
