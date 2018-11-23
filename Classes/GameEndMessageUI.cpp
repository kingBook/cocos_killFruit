#include "GameEndMessageUI.h"
#include <iostream>
#include <string>
using namespace std;

bool GameEndMessageUI::init(){
	if(!CCLayer::init())return false;
	_instance=this;
	CCDictionary* strings = CCDictionary::createWithContentsOfFile("string.xml");
	//奖励分数
	CCString* str_rewardScore = (CCString*)strings->objectForKey("rewardScore");
	_labelRewardScore = CCLabelBMFont::create(str_rewardScore->getCString(),"bmpFont.fnt");
	_labelRewardScore->setScale(0.7f);
	_labelRewardScore->setPositionY(18);
	addChild(_labelRewardScore);
	//剩下的星星
	CCString* str_remainStars = (CCString*)strings->objectForKey("remainStars");
	_labelRemainStars = CCLabelBMFont::create(str_remainStars->getCString(),"bmpFont.fnt");
	_labelRemainStars->setScale(0.7f);
	_labelRemainStars->setPositionY(-18);
	addChild(_labelRemainStars);
	
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	setPosition(ccp(visibleSize.width+boundingBox().size.width*0.5,visibleSize.height*0.5f));

	CCMoveTo* moveIn = CCMoveTo::create(0.25f,ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	runAction(moveIn);

	return true;
}

void GameEndMessageUI::moveOut(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCMoveTo* moveOut = CCMoveTo::create(0.25f,ccp(-boundingBox().size.width*0.5,visibleSize.height*0.5f));
	runAction(moveOut);
	scheduleOnce(schedule_selector(GameEndMessageUI::dispose),0.25f);
}

void GameEndMessageUI::dispose(float t){
	removeFromParentAndCleanup(true);
}

void GameEndMessageUI::setRemainStars(int value){
	CCDictionary* strings = CCDictionary::createWithContentsOfFile("string.xml");
	CCString* str_remainStars = (CCString*)strings->objectForKey("remainStars");
	CCString* str_count = CCString::createWithFormat("%d",value);
	string newStr = str_remainStars->getCString();
	newStr+=str_count->getCString();
	_labelRemainStars->setString(newStr.c_str(),true);
}

void GameEndMessageUI::updateLabelReWardScore(int value){
	CCDictionary* strings = CCDictionary::createWithContentsOfFile("string.xml");
	CCString* str_rewardScore = (CCString*)strings->objectForKey("rewardScore");
	CCString* str_count = CCString::createWithFormat("%d",value);
	string newStr = str_rewardScore->getCString();
	newStr+=str_count->getCString();
	_labelRewardScore->setString(newStr.c_str(),true);
}

void GameEndMessageUI::setRewardScore(int value){
	_rewardScore=value;
	updateLabelReWardScore(value);
}

int GameEndMessageUI::getRewardScore(){
	return _rewardScore;
}

GameEndMessageUI* GameEndMessageUI::_instance=NULL;
GameEndMessageUI* GameEndMessageUI::getInstance(){
	return _instance;
}
GameEndMessageUI::~GameEndMessageUI(){
	_instance=NULL;
}