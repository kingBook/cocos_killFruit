#include "HelpUI.h"
#include "Title.h"

bool HelpUI::init(){
	if(!CCSprite::init())return false;
	if(Title::getInstance()!=NULL){
		Title::getInstance()->setEnabled(false);
	}
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

	CCSprite* titleText = CCSprite::create("helpUI_titleText.png");
	titleText->setPositionY(296.8f);
	addChild(titleText);

	CCSprite* content = CCSprite::create("helpContent.png");
	content->setPosition(ccp(0,-25));
	addChild(content);

	CCMenuItemImage* closeItem = CCMenuItemImage::create("close.png",NULL,this,menu_selector(HelpUI::closeCallback));
	closeItem->setPosition(ccp(-170,251));

	CCMenu* menu =CCMenu::create(closeItem,NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);
	//放大出现
	setScale(0.1f);
	CCScaleTo* scaleTo = CCScaleTo::create(0.5f,1.0f,1.0f);
	runAction(scaleTo);
	return true;
}

void HelpUI::closeCallback(CCObject* pSender){
	//CCLOG("%s","MysteryPrizeBag::closeCallback();");
	removeAllChildrenWithCleanup(true);
	removeFromParentAndCleanup(true);
}

HelpUI::~HelpUI(){
	if(Title::getInstance()!=NULL){
		Title::getInstance()->setEnabled(true);
	}
}