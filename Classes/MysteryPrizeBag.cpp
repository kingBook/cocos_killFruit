#include "MysteryPrizeBag.h"
#include "Game.h"

bool MysteryPrizeBag::init(){
	if(!CCSprite::init())return false;
	Game::getInstance()->setIsCreateMysteryPrize(true);
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//创建背景
	CCLayerColor* bgColor = CCLayerColor::create(ccc4(0,0,0,125));
	bgColor->setPosition(ccp(-visibleSize.width*0.5f,-visibleSize.height*0.5f));
	addChild(bgColor);
	
	CCSprite* bg = CCSprite::create("bagBg.png");
	bg->setScaleY(1.3f);
	addChild(bg);

	CCSprite* caiDai = CCSprite::create("caiDai.png");
	caiDai->setPositionY(261);
	addChild(caiDai);

	CCSprite* titleText = CCSprite::create("shenMiDaJiang_title.png");
	titleText->setPositionY(296.8f);
	addChild(titleText);

	CCSprite* gongxi=CCSprite::create("shenMiDaJiang_gongxi.png");
	gongxi->setPositionY(200);
	addChild(gongxi);

	CCSprite* shenmidajian = CCSprite::create("shenMiDaJiang_text.png");
	shenmidajian->setPosition(ccp(0,135));
	addChild(shenmidajian);

	CCSprite* buyText=CCSprite::create("buyText.png");
	buyText->setPosition(ccp(-83,37));
	addChild(buyText);

	CCSprite* zuanShi_a=CCSprite::create("zuanShi_a.png");
	zuanShi_a->setScale(0.6f);
	zuanShi_a->setPosition(ccp(46,50));
	addChild(zuanShi_a);

	CCSprite* x50 = CCSprite::create("x50.png");
	x50->setPosition(ccp(46,3));
	addChild(x50);

	CCSprite* zeng = CCSprite::create("zeng.png");
	zeng->setPosition(ccp(-114,-90));
	zeng->setScale(1.5f);
	addChild(zeng);

	CCSprite* guang = CCSprite::create("guang.png");
	guang->setPosition(ccp(65,-75));
	guang->setScale(0.9f);
	addChild(guang);

	CCSprite* zuanShi_b = CCSprite::create("zuanShi_a.png");
	zuanShi_b->setPosition(ccp(50,-90));
	addChild(zuanShi_b);

	CCSprite* x40 = CCSprite::create("x40.png");
	x40->setPosition(ccp(38,-153));
	addChild(x40);

	CCSprite* lingqu=CCSprite::create("lingqu.png");
	lingqu->setPositionY(-210);
	addChild(lingqu);
	//领取按钮缩放动作
	CCScaleTo* scaleTo_a=CCScaleTo::create(0.5f,0.8f,0.8f);
	CCScaleTo* scaleTo_b=CCScaleTo::create(0.5f,1,1);
	CCSequence* scaleSeq = CCSequence::create(scaleTo_a,scaleTo_b,NULL);
	CCRepeatForever* repeatForever=CCRepeatForever::create(scaleSeq);
	lingqu->runAction(repeatForever);

	CCSprite* tick = CCSprite::create("tick.png");
	tick->setPosition(ccp(182,246));
	addChild(tick);

	CCMenuItemImage* closeItem = CCMenuItemImage::create("close.png",NULL,this,menu_selector(MysteryPrizeBag::closeCallback));
	closeItem->setPosition(ccp(-170,251));

	CCMenuItemImage* rect_aItem = CCMenuItemImage::create("rect_a.png",NULL,this,menu_selector(MysteryPrizeBag::okCallback));
	rect_aItem->setPosition(ccp(120,170));
	rect_aItem->setScaleY(1.2f);
	rect_aItem->setOpacity(0);
	CCMenuItemImage* rect_bItem = CCMenuItemImage::create("rect_b.png",NULL,this,menu_selector(MysteryPrizeBag::okCallback));
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

void MysteryPrizeBag::closeCallback(CCObject* pSender){
	//CCLOG("%s","MysteryPrizeBag::closeCallback();");
	removeFromParentAndCleanup(true);
}

void MysteryPrizeBag::okCallback(CCObject* pSender){
	CCLOG("%s","MysteryPrizeBag::okCallback();");
	Game::getInstance()->gamePay(8,"mysteryPrizeBag","",this,pay_cb(MysteryPrizeBag::payCallback),90);
}

void MysteryPrizeBag::payCallback(bool isFinish, int buyCount){
	CCLOG("MysteryPrizeBag::payCallback():%s, %d",isFinish?"ok":"no", buyCount);
	if(isFinish){
		Game::getInstance()->setDiamondCount(buyCount,true);
	}
}

MysteryPrizeBag::~MysteryPrizeBag(){
	Game::getInstance()->setIsCreateMysteryPrize(false);
}