#include "Title.h"
#include "Game.h"
#include "HelpUI.h"

Title* Title::_instance = NULL;
bool Title::init(){
	if(!CCLayer::init())return false;
	_instance=this;
	_enabled=true;
	_shopOnceItem=NULL;
	createBg();
	createMenuItem();
	return true;
}

void Title::createBg(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* bg = CCSprite::create("title_bg.jpg");
	bg->setPosition(ccp(visibleSize.width*0.5,visibleSize.height*0.5f));
	this->addChild(bg);
}

void Title::createMenuItem(){
	//��ȡ����λ��
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	float cx = visibleSize.width*0.5f;
	float cy = visibleSize.height*0.5f;
	//
	CCArray* menuItems = CCArray::create();
	//�������������ť
	if(!Game::getInstance()->getIsReceiveNoviceBag()){
		_shopOnceItem = CCMenuItemImage::create("Shop_Onece.png",NULL,this,menu_selector(Title::shopOnceCallback));
		_shopOnceItem->setPosition(ccp(420,330));
		CCScaleTo* scaleTo_a = CCScaleTo::create(0.5f,0.8f,0.8f);
		CCScaleTo* scaleTo_b = CCScaleTo::create(0.5f,1.0f,1.0f);
		CCSequence* sequence = CCSequence::create(scaleTo_a,scaleTo_b,NULL);
		CCRepeatForever* repeatAcion = CCRepeatForever::create(sequence);
		_shopOnceItem->runAction(repeatAcion);
		menuItems->addObject(_shopOnceItem);
	}
	//������ť
	CCMenuItemImage* helpItem = CCMenuItemImage::create("startUI_help.png",NULL,this,menu_selector(Title::helpCallback));
	helpItem->setPosition(ccp(60,240));
	menuItems->addObject(helpItem);
	//������ť
	CCMenuItemImage* mute1Item = CCMenuItemImage::create("mute0001.png",NULL,this,menu_selector(Title::muteCallback));
	mute1Item->setTag(1);
	CCMenuItemImage* mute2Item = CCMenuItemImage::create("mute0002.png",NULL,this,menu_selector(Title::muteCallback));
	mute2Item->setTag(2);
	bool curMute = Game::getInstance()->getMute();
	CCMenuItemToggle* muteItem =CCMenuItemToggle::createWithTarget(this,menu_selector(Title::muteCallback),curMute?mute2Item:mute1Item,curMute?mute1Item:mute2Item,NULL);
	muteItem->setPosition(ccp(60,320));
	menuItems->addObject(muteItem);
	//������ʼ��ť
	CCMenuItemImage* startItem = CCMenuItemImage::create("menu_start.png",NULL,this,menu_selector(Title::startCallback));
	startItem->setPosition(ccp(-startItem->getContentSize().width*0.5f,cy-80));
	CCMoveTo* moveTo = CCMoveTo::create(0.4f,ccp(cx,cy-80));
	startItem->runAction(moveTo);
	//����������Ϸ��ť
	CCMenuItemImage* continueItem = CCMenuItemImage::create("menu_continue.png",NULL,this,menu_selector(Title::continueCallback));
	continueItem->setPosition(ccp(visibleSize.width+continueItem->getContentSize().width*0.5f,cy-160));
	moveTo = CCMoveTo::create(0.4f,ccp(cx,cy-160));
	continueItem->runAction(moveTo);
	//�����̳ǰ�ť
	CCMenuItemImage* shopItem = CCMenuItemImage::create("menu_shop.png",NULL,this,menu_selector(Title::shopCallback));
	shopItem->setPosition(ccp(-shopItem->getContentSize().width*0.5f,cy-240));
	moveTo = CCMoveTo::create(0.4f,ccp(cx,cy-240));
	shopItem->runAction(moveTo);
	//
	menuItems->addObject(startItem);
	menuItems->addObject(continueItem);
	menuItems->addObject(shopItem);
	//��ӵ��˵�
	CCMenu* menu=CCMenu::createWithArray(menuItems);
	menu->setPosition(CCPointZero);
	this->addChild(menu);
}

void Title::startCallback(CCObject* pSender){
	if(!_enabled)return;
	removeFromParentAndCleanup(true);
	Game::getInstance()->newGame();
}

void Title::continueCallback(CCObject* pSender){
	if(!_enabled)return;
	removeFromParentAndCleanup(true);
	Game::getInstance()->continueGame();
}

void Title::shopCallback(CCObject* pSender){
	if(!_enabled)return;
	Game::getInstance()->createShop();
}

void Title::shopOnceCallback(CCObject* pSender){
	if(!_enabled)return;
	Game::getInstance()->createNoviceBag();
}

void Title::helpCallback(CCObject* pSender){
	int tag = 101;
	if(getChildByTag(101)!=NULL)return;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	HelpUI* helpUI = HelpUI::create();
	helpUI->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	helpUI->setTag(101);
	addChild(helpUI);
}

void Title::muteCallback(CCObject* pSender){
	bool curMute = Game::getInstance()->getMute();
	Game::getInstance()->setMute(!curMute);
}

void Title::setEnabled(bool value){
	_enabled = value;
}

void Title::hideShopOnceItem(){
	if(_shopOnceItem!=NULL){
		_shopOnceItem->setVisible(false);
	}
}

Title::~Title(){
	_instance=NULL;
	_shopOnceItem=NULL;
}

Title* Title::getInstance(){return _instance;}