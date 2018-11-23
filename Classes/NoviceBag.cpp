#include "NoviceBag.h"
#include "Title.h"
#include "Game.h"

bool NoviceBag::init(){
	if(!CCSprite::init())return false;
	Title::getInstance()->setEnabled(false);
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

	CCSprite* receiveTitle = CCSprite::create("xinShouLiBaoText.png");
	receiveTitle->setPositionY(246.8f);
	addChild(receiveTitle);

	CCSprite* guang = CCSprite::create("guang.png");
	guang->setPosition(ccp(0,10));
	addChild(guang);

	CCSprite* zuanShi_b = CCSprite::create("zuanShi_a.png");
	zuanShi_b->setPosition(ccp(0,-5));
	addChild(zuanShi_b);

	CCSprite* x5 = CCSprite::create("x5.png");
	x5->setPosition(ccp(0,-70));
	x5->setScale(1.2f);
	addChild(x5);

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

	CCMenuItemImage* closeItem = CCMenuItemImage::create("close.png",NULL,this,menu_selector(NoviceBag::closeCallback));
	closeItem->setPosition(ccp(-170,201));

	CCMenuItemImage* rect_aItem = CCMenuItemImage::create("rect_a.png",NULL,this,menu_selector(NoviceBag::okCallback));
	rect_aItem->setPosition(ccp(120,120));
	rect_aItem->setOpacity(0);
	CCMenuItemImage* rect_bItem = CCMenuItemImage::create("rect_b.png",NULL,this,menu_selector(NoviceBag::okCallback));
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

void NoviceBag::closeCallback(CCObject* pSender){
	//CCLOG("%s","NoviceBag::closeCallback();");
	removeFromParentAndCleanup(true);
}

void NoviceBag::okCallback(CCObject* pSender){
	//CCLOG("%s","NoviceBag::okCallback();");
	//领取新手大礼包
	removeFromParentAndCleanup(true);
	Title::getInstance()->hideShopOnceItem();//隐藏新手礼包按钮
	Game::getInstance()->setDiamondCount(5,true);
	Game::getInstance()->setIsReceiveNoviceBaged();//设置为已经领取了新手礼包
	Game::getInstance()->createActivityBag();//创建活动大礼包
}

NoviceBag::~NoviceBag(){
	//CCLOG("%s","~NoviceBag()");
	Title::getInstance()->setEnabled(true);
}