#include "ActivityBag.h"
#include "Title.h"
#include "Game.h"

bool ActivityBag::init(){
	if(!CCSprite::init())return false;
	CCLOG("%s","ActivityBag::init();");
	if(Title::getInstance()!=NULL){
		Title::getInstance()->setEnabled(false);
	}
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

	CCSprite* receiveTitle = CCSprite::create("activityBagTitle.png");
	receiveTitle->setPositionY(246.8f);
	addChild(receiveTitle);

	CCSprite* buyText=CCSprite::create("buyText.png");
	buyText->setPosition(ccp(-83,117));
	addChild(buyText);

	CCSprite* zuanShi_a=CCSprite::create("zuanShi_a.png");
	zuanShi_a->setScale(0.6f);
	zuanShi_a->setPosition(ccp(46,125));
	addChild(zuanShi_a);

	CCSprite* x100 = CCSprite::create("x100.png");
	x100->setPosition(ccp(46,78));
	addChild(x100);

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

	CCSprite* x120 = CCSprite::create("x120.png");
	x120->setPosition(ccp(38,-78));
	addChild(x120);

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

	CCMenuItemImage* closeItem = CCMenuItemImage::create("close.png",NULL,this,menu_selector(ActivityBag::closeCallback));
	closeItem->setPosition(ccp(-170,201));

	CCMenuItemImage* rect_aItem = CCMenuItemImage::create("rect_a.png",NULL,this,menu_selector(ActivityBag::okCallback));
	rect_aItem->setPosition(ccp(120,120));
	rect_aItem->setOpacity(0);
	CCMenuItemImage* rect_bItem = CCMenuItemImage::create("rect_b.png",NULL,this,menu_selector(ActivityBag::okCallback));
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

void ActivityBag::closeCallback(CCObject* pSender){
	CCLOG("%s","ActivityBag::closeCallback();");
	removeFromParentAndCleanup(true);
}

void ActivityBag::okCallback(CCObject* pSender){
	CCLOG("%s","ActivityBag::okCallback();");
	Game::getInstance()->gamePay(12,"bigBag","",this,pay_cb(ActivityBag::payCallback),220);
}

void ActivityBag::payCallback(bool isFinish, int buyCount){
	CCLOG("ActivityBag::payCallback():%s, %d",isFinish?"ok":"no", buyCount);
	if(isFinish){
		Game::getInstance()->setDiamondCount(buyCount,true);
	}
}

ActivityBag::~ActivityBag(){
	if(Title::getInstance()!=NULL){
		Title::getInstance()->setEnabled(true);
	}
}