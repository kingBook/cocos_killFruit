#include "PauseUI.h"
#include "Game.h"
#include "PropUI.h"
bool PauseUI::init(){
	if(!CCSprite::init())return false;
	Game::getInstance()->setPause(true);
	if(PropUI::getInstance()!=NULL){
		PropUI::getInstance()->setEnabled(false);
	}
	//
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//创建背景
	CCLayerColor* bgColor = CCLayerColor::create(ccc4(0,0,0,125));
	bgColor->setPosition(ccp(-visibleSize.width*0.5f,-visibleSize.height*0.5f));
	addChild(bgColor);
	
	CCSprite* bg = CCSprite::create("bagBg.png");
	addChild(bg);

	CCSprite* caiDai = CCSprite::create("caiDai.png");
	caiDai->setPositionY(211);
	addChild(caiDai);

	CCSprite* pauseTitle = CCSprite::create("pauseTitle.png");
	pauseTitle->setPositionY(246.8f);
	addChild(pauseTitle);

	CCMenuItemImage* closeItem = CCMenuItemImage::create("close.png",NULL,this,menu_selector(PauseUI::continueCallback));
	closeItem->setPosition(ccp(-170,201));

	CCMenuItemImage* continueItem = CCMenuItemImage::create("continueGame.png",NULL,this,menu_selector(PauseUI::continueCallback));
	continueItem->setPositionY(60);
	continueItem->setScale(1.2f);
	//按钮缩放动作
	CCScaleTo* scaleTo_a=CCScaleTo::create(0.5f,1.0f,1.0f);
	CCScaleTo* scaleTo_b=CCScaleTo::create(0.5f,1.2f,1.2f);
	CCSequence* scaleSeq = CCSequence::create(scaleTo_a,scaleTo_b,NULL);
	CCRepeatForever* repeatForever=CCRepeatForever::create(scaleSeq);
	continueItem->runAction(repeatForever);

	CCMenuItemImage* backItem = CCMenuItemImage::create("back.png",NULL,this,menu_selector(PauseUI::backCallback));
	backItem->setPositionY(-60);

	CCMenu* menu =CCMenu::create(closeItem,continueItem,backItem,NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);
	//放大出现
	setScale(0.1f);
	CCScaleTo* scaleTo = CCScaleTo::create(0.5f,1.0f,1.0f);
	runAction(scaleTo);
	return true;
}

void PauseUI::backCallback(CCObject* pSender){
	//CCLOG("%s","PauseUI::backCallback();");
	removeFromParentAndCleanup(true);
	Game::getInstance()->setPause(false);
	Game::getInstance()->createTitle(false,true);
}

void PauseUI::continueCallback(CCObject* pSender){
//	CCLOG("%s","PauseUI::continueCallback();");
	removeFromParentAndCleanup(true);
	Game::getInstance()->setPause(false);

}

PauseUI::~PauseUI(){
	if(PropUI::getInstance()!=NULL){
		PropUI::getInstance()->setEnabled(true);
	}
	Game::getInstance()->setPause(false);
}