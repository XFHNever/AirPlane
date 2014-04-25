/*
 * Enemy.cpp
 *
 *  Created on: 2014-4-11
 *      Author: never
 */
#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy(){
	sprite = NULL;
	life = 0;
}

Enemy::~Enemy(){

}

Enemy* Enemy::create(){
	Enemy *pRet = new Enemy;
	pRet->autorelease();
	return pRet;
}

void Enemy::bindSprite(CCSprite* sprite,int life){
	this->sprite = sprite;
	this->life = life;
	this->addChild(this->sprite);
}
CCSprite* Enemy::getSprite(){
	return sprite;
}

int Enemy::getLife(){
	return life;
}

void Enemy::loseLife(){
	this->life--;
}

CCRect Enemy::getBoundingBox(){
	CCRect rect = this->sprite->boundingBox();
	CCPoint pos = this->convertToWorldSpace(rect.origin);
	CCRect enemyRect(pos.x,pos.y,rect.size.width,rect.size.height);

	return enemyRect;
}
