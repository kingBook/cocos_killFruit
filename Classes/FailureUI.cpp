#include "FailureUI.h"
#include "Game.h"
#include "GameEndAnim.h"

bool FailureUI::init(){
	if(!CCSprite::init())return false;
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

	CCSprite* titleText = CCSprite::create("zaijiezailiText.png");
	titleText->setPositionY(246.8f);
	addChild(titleText);

	CCSprite* failureText = CCSprite::create("failureText.png");
	failureText->setScale(0.9f);
	failureText->setPositionY(20);
	addChild(failureText);

	CCSprite* continueGame=CCSprite::create("continueGame.png");
	continueGame->setPositionY(-140);
	addChild(continueGame);
	//领取按钮缩放动作
	CCScaleTo* scaleTo_a=CCScaleTo::create(0.5f,0.8f,0.8f);
	CCScaleTo* scaleTo_b=CCScaleTo::create(0.5f,1,1);
	CCSequence* scaleSeq = CCSequence::create(scaleTo_a,scaleTo_b,NULL);
	CCRepeatForever* repeatForever=CCRepeatForever::create(scaleSeq);
	continueGame->runAction(repeatForever);

	CCSprite* tick = CCSprite::create("tick.png");
	tick->setPosition(ccp(182,196));
	addChild(tick);

	CCMenuItemImage* closeItem = CCMenuItemImage::create("close.png",NULL,this,menu_selector(FailureUI::closeCallback));
	closeItem->setPosition(ccp(-170,201));

	CCMenuItemImage* rect_aItem = CCMenuItemImage::create("rect_a.png",NULL,this,menu_selector(FailureUI::okCallback));
	rect_aItem->setPosition(ccp(120,120));
	rect_aItem->setOpacity(0);
	CCMenuItemImage* rect_bItem = CCMenuItemImage::create("rect_b.png",NULL,this,menu_selector(FailureUI::okCallback));
	rect_bItem->setPositionY(-200);
	rect_bItem->setOpacity(0);

	CCMenu* menu =CCMenu::create(closeItem,rect_aItem,rect_bItem,NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);
	//放大出现
	setScale(0.1f);
	CCScaleTo* scaleTo = CCScaleTo::create(0.5f,1.0f,1.0f);
	runAction(scaleTo);
	return true;
}

void FailureUI::closeCallback(CCObject* pSender){
	CCLOG("%s","FailureUI::closeCallback();");
	removeFromParentAndCleanup(true);

	GameEndAnim* endAnim = GameEndAnim::create();
	GameLevel::getInstance()->addChild(endAnim);
}

void FailureUI::okCallback(CCObject* pSender){
	CCLOG("%s","FailureUI::okCallback();");
	removeFromParentAndCleanup(true);
	Game::getInstance()->createWantContinueUI();

}