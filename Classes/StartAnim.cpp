#include "StartAnim.h"
#include "Game.h"
USING_NS_CC;
bool StartAnim::init(){
	if(!CCLayer::init())return false;
	createLevelText();
	createTargetScoreText();
	schedule(schedule_selector(StartAnim::scheduleCallback),1.5f);
	return true;
}

void StartAnim::createLevelText(){
	CCSize visibleSize=CCDirector::sharedDirector()->getVisibleSize();
	float cx = visibleSize.width*0.5f;
	float cy = visibleSize.height*0.5f;

	CCLayer* layer = CCLayer::create();
	this->addChild(layer);

	//文字部分
	CCDictionary* strings = CCDictionary::createWithContentsOfFile("string.xml");
	const char* str_targetScore = ((CCString*)strings->objectForKey("level"))->getCString();
	CCLabelBMFont* label_a = CCLabelBMFont::create(str_targetScore, "bmpFont.fnt");
	label_a->setAnchorPoint(ccp(0.0f,0.5f));
	layer->addChild(label_a);
	//数字部分
	CCString* ccStr = CCString::createWithFormat("%d",Game::getInstance()->getLevel());
	CCLabelBMFont* label_b = CCLabelBMFont::create(ccStr->getCString(),"bmpFont.fnt");
	label_b->setAnchorPoint(ccp(0.0f,0.5f));
	label_b->setPosition(ccp(label_a->getContentSize().width,0.0f));
	layer->addChild(label_b);
	//居中
	float totalW = label_a->getContentSize().width+label_b->getContentSize().width;
	label_a->setPositionX(label_a->getPositionX()-totalW*0.5f);
	label_b->setPositionX(label_b->getPositionX()-totalW*0.5f);
	//缩小
	float scale = 1.0f;
	layer->setScale(scale);
	layer->setPosition(ccp(visibleSize.width*scale,(cy+30)*scale));//设置在屏幕右边
	//执行动作
	CCMoveTo* moveTo0 = CCMoveTo::create(0.25,ccp(cx*scale,(cy+30)*scale));
	CCMoveTo* moveTo1 = CCMoveTo::create(0.25,ccp(-totalW*scale,(cy+30)*scale));
	CCSequence* actionSequence = CCSequence::create(moveTo0,CCDelayTime::create(1.0f),moveTo1,NULL);
	layer->runAction(actionSequence);
}

void StartAnim::createTargetScoreText(){
	CCSize visibleSize=CCDirector::sharedDirector()->getVisibleSize();
	float cx = visibleSize.width*0.5f;
	float cy = visibleSize.height*0.5f;

	CCLayer* layer = CCLayer::create();
	this->addChild(layer);
	//文字部分
	CCDictionary* strings = CCDictionary::createWithContentsOfFile("string.xml");
	const char* str_targetScore = ((CCString*)strings->objectForKey("targetScore"))->getCString();
	CCLabelBMFont* label_a = CCLabelBMFont::create(str_targetScore, "bmpFont.fnt");
	label_a->setAnchorPoint(ccp(0.0f,0.5f));
	layer->addChild(label_a);
	//数字部分
	CCString* ccStr = CCString::createWithFormat("%d",Game::getInstance()->getTargetScore());
	CCLabelBMFont* label_b = CCLabelBMFont::create(ccStr->getCString(),"bmpFont.fnt");
	label_b->setAnchorPoint(ccp(0.0f,0.5f));
	label_b->setPosition(ccp(label_a->getContentSize().width,0.0f));
	layer->addChild(label_b);
	//居中
	float totalW = label_a->getContentSize().width+label_b->getContentSize().width;
	label_a->setPositionX(label_a->getPositionX()-totalW*0.5f);
	label_b->setPositionX(label_b->getPositionX()-totalW*0.5f);
	//缩小
	float scale = 0.8f;
	layer->setScale(scale);
	layer->setPosition(ccp(visibleSize.width*scale,(cy-30)*scale));//设置在屏幕右边
	//执行动作
	CCMoveTo* moveTo0 = CCMoveTo::create(0.25,ccp(cx*scale,(cy-30)*scale));
	CCMoveTo* moveTo1 = CCMoveTo::create(0.25,ccp(-totalW*scale,(cy-30)*scale));
	CCSequence* actionSequence = CCSequence::create(CCDelayTime::create(0.25f),moveTo0,CCDelayTime::create(0.75f),moveTo1,NULL);
	layer->runAction(actionSequence);
}

void StartAnim::scheduleCallback(float t){
	unschedule(schedule_selector(StartAnim::scheduleCallback));
	this->removeFromParentAndCleanup(true);
}