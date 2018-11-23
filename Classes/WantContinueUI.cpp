#include "WantContinueUI.h"
#include "Game.h"
#include "GameEndAnim.h"

bool WantContinueUI::init(){
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

	CCSprite* titleTest = CCSprite::create("wantContinueText.png");
	titleTest->setPositionY(246.8f);
	addChild(titleTest);

	CCSprite* buyText=CCSprite::create("buyText.png");
	buyText->setPosition(ccp(-83,117));
	addChild(buyText);

	CCSprite* zuanShi_a=CCSprite::create("zuanShi_a.png");
	zuanShi_a->setScale(0.6f);
	zuanShi_a->setPosition(ccp(46,125));
	addChild(zuanShi_a);

	CCSprite* x60 = CCSprite::create("x60.png");
	x60->setPosition(ccp(46,78));
	addChild(x60);

	CCSprite* zeng = CCSprite::create("zeng.png");
	zeng->setPosition(ccp(-114,-11.5f));
	zeng->setScale(1.5f);
	addChild(zeng);

	CCSprite* guang = CCSprite::create("guang.png");
	guang->setPosition(ccp(65,0));
	guang->setScale(0.9f);
	addChild(guang);

	CCSprite* zuanShi_b = CCSprite::create("zuanShi_a.png");
	zuanShi_b->setPosition(ccp(50,-15));
	addChild(zuanShi_b);

	CCSprite* x50 = CCSprite::create("x50.png");
	x50->setPosition(ccp(38,-78));
	addChild(x50);

	CCSprite* lingqu=CCSprite::create("lingqu.png");
	lingqu->setPositionY(-140);
	addChild(lingqu);
	//领取按钮缩放动作
	CCScaleTo* scaleTo_a=CCScaleTo::create(0.5f,0.8f,0.8f);
	CCScaleTo* scaleTo_b=CCScaleTo::create(0.5f,1,1);
	CCSequence* scaleSeq = CCSequence::create(scaleTo_a,scaleTo_b,NULL);
	CCRepeatForever* repeatForever=CCRepeatForever::create(scaleSeq);
	lingqu->runAction(repeatForever);

	CCSprite* tick = CCSprite::create("tick.png");
	tick->setPosition(ccp(182,196));
	addChild(tick);

	CCMenuItemImage* closeItem = CCMenuItemImage::create("close.png",NULL,this,menu_selector(WantContinueUI::closeCallback));
	closeItem->setPosition(ccp(-170,201));

	CCMenuItemImage* rect_aItem = CCMenuItemImage::create("rect_a.png",NULL,this,menu_selector(WantContinueUI::okCallback));
	rect_aItem->setPosition(ccp(120,120));
	rect_aItem->setOpacity(0);
	CCMenuItemImage* rect_bItem = CCMenuItemImage::create("rect_b.png",NULL,this,menu_selector(WantContinueUI::okCallback));
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

void WantContinueUI::closeCallback(CCObject* pSender){
	CCLOG("%s","WantContinueUI::closeCallback();");
	removeAllChildrenWithCleanup(true);
	removeFromParentAndCleanup(true);

	GameEndAnim* endAnim = GameEndAnim::create();
	GameLevel::getInstance()->addChild(endAnim);
}

void WantContinueUI::okCallback(CCObject* pSender){
	CCLOG("%s","WantContinueUI::okCallback();");
	Game::getInstance()->gamePay(6,"wantContinueBag","",this,pay_cb(WantContinueUI::payCallback),110);
}

void WantContinueUI::payCallback(bool isFinish, int buyCount){
	CCLOG("WantContinueUI::payCallback():%s, %d",isFinish?"ok":"no", buyCount);
	if(isFinish){
		Game::getInstance()->setDiamondCount(buyCount,true);
	}
}