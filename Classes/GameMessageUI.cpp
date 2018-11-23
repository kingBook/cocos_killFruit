#include "GameMessageUI.h"
#include "Game.h"
#include "PropUI.h"
#include <iostream>
#include <string>
using namespace std;

bool GameMessageUI::init(){
	if(!CCLayer::init())return false;
	_instance = this;
	createBg();
	createLabels();
	setPositionY(boundingBox().size.height);

	//暂停按钮
	CCMenuItemImage* pauseItem = CCMenuItemImage::create("Button_pause.png",NULL,this,menu_selector(GameMessageUI::pauseCallback));
	pauseItem->setPosition(ccp(60,750));
	CCMenu* menu = CCMenu::create(pauseItem,NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);

	//添加滑入动作
	CCMoveTo* moveTo = CCMoveTo::create(0.8f,CCPointZero);
	CCSequence* seq = CCSequence::create(CCDelayTime::create(0.1f),moveTo,NULL);
	runAction(seq);
	return true;
}

void GameMessageUI::createBg(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	float cx = visibleSize.width*0.5f;
	float cy = visibleSize.height*0.5f;
	CCSprite* bg = CCSprite::create("messageUI_bg.png");
	bg->setPosition(ccp(cx,visibleSize.height-bg->getContentSize().height*0.5f));
	this->addChild(bg);

}

void GameMessageUI::createLabels(){
	CCDictionary* strings = CCDictionary::createWithContentsOfFile("string.xml");
	float scale = 0.5f;
	//"第"
	CCString* str_di = (CCString*)strings->objectForKey("di");
	CCLabelBMFont* _label_di=CCLabelBMFont::create(str_di->getCString(),"bmpFont.fnt");
	_label_di->setScale(scale);
	_label_di->setPosition(110.0f,750.0f);
	this->addChild(_label_di);
	//"1"
	CCString* strLevel = CCString::createWithFormat("%d",Game::getInstance()->getLevel());
	_labelLevel = CCLabelBMFont::create(strLevel->getCString(),"bmpFont.fnt");
	_labelLevel->setScale(scale);
	_labelLevel->setPosition(150.0f,750.0f);
	this->addChild(_labelLevel);
	//"关"
	CCString* str_guan = (CCString*)strings->objectForKey("guan");
	CCLabelBMFont* label_guan=CCLabelBMFont::create(str_guan->getCString(),"bmpFont.fnt");
	label_guan->setScale(scale);
	label_guan->setPosition(190.0f,750.0f);
	this->addChild(label_guan);
	//分数
	const char* char_score = Game::getInstance()->getIntCString(Game::getInstance()->getScore(),"bmpFont.fnt");
	_labelScore = CCLabelBMFont::create(char_score,"bmpFont.fnt");
	_labelScore->setScale(scale);
	_labelScore->setPosition(275.0f,752.0f);
	this->addChild(_labelScore);
	//"最高纪录"
	CCString* str_maxRecord = (CCString*)strings->objectForKey("maxRecord");
	CCLabelBMFont* label_maxRecord=CCLabelBMFont::create(str_maxRecord->getCString(),"bmpFont.fnt");
	label_maxRecord->setScale(0.4f);
	label_maxRecord->setPosition(398.0f,765.0f);
	this->addChild(label_maxRecord);
	//最高纪录分值
	const char* str_maxRecordScore = Game::getInstance()->getIntCString(Game::getInstance()->getMaxRecord(),"bmpFont.fnt");
	CCLabelBMFont* label_maxRecordScore = CCLabelBMFont::create(str_maxRecordScore,"bmpFont.fnt");
	label_maxRecordScore->setScale(0.4f);
	label_maxRecordScore->setPosition(398.0f,740.0f);
	this->addChild(label_maxRecordScore);

	//目标:1000
	CCString* ccstr_target = (CCString*)strings->objectForKey("mubiao");
	string str_target = ccstr_target->getCString();
	str_target+=Game::getInstance()->getIntCString(Game::getInstance()->getTargetScore(),"bmpFont.fnt");
	
	CCLabelBMFont* label_target = CCLabelBMFont::create(str_target.c_str(),"bmpFont.fnt");
	label_target->setColor(ccc3(189,48,0));
	label_target->setScale(0.5f);
	label_target->setAnchorPoint(ccp(0,0.5f));
	label_target->setPosition(ccp(20,675));
	addChild(label_target);

}

void GameMessageUI::updateLabelLevelText(){
	CCString* strLevel = CCString::createWithFormat("%d",Game::getInstance()->getLevel());
	_labelLevel->setString(strLevel->getCString(),true);
}

void GameMessageUI::updateLabelScoreText(){
	const char* char_score = Game::getInstance()->getIntCString(Game::getInstance()->getScore(),"bmpFont.fnt");
	_labelScore->setString(char_score,true);
}

float GameMessageUI::getScorePosX(){
	return _labelScore->getPositionX();
}

float GameMessageUI::getScorePosY(){
	return _labelScore->getPositionY();
}

void GameMessageUI::pauseCallback(CCObject* pSender){
	CCLOG("%s","GameMessageUI::pauseCallback();");
	if(Game::getInstance()->getIsGameOver())return;
	if(!Game::getInstance()->getPause())
		Game::getInstance()->createPauseUI();
}

GameMessageUI::~GameMessageUI(){
	_instance=NULL;
}
GameMessageUI* GameMessageUI::_instance=NULL;
GameMessageUI* GameMessageUI::getInstance(){
	return _instance;
}

