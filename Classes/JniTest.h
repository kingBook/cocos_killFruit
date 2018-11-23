#ifndef JNI_TEST_H
#define JNI_TEST_H

#include "cocos2d.h"
#include "Game.h"

using namespace cocos2d;

void payCallback(const char* result)
{
	Game::getInstance()->payCallback(result);
}

#endif