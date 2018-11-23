#include "PropUI.h"
#include "Game.h"
#include "SimpleAudioEngine.h"
#include "ScreenText.h"
using namespace CocosDenshion;
bool PropUI::init(){
	if(!CCLayer::init())return false;
	_instance = this;
	_enabled = true;
	createMenuItem();
	setPositionX(boundingBox().size.width);
	//添加滑入动作
	CCMoveTo* moveTo = CCMoveTo::create(1,CCPointZero);
	CCSequence* seq = CCSequence::create(CCDelayTime::create(1.5f),moveTo,NULL);
	runAction(seq);
	setTouchEnabled(true);
	return true;
}

void PropUI::createMenuItem(){
	CCSprite* bottom = CCSprite::create("bottom0.png");
	bottom->setPosition(ccp(390,665));
	addChild(bottom);
	CCSprite* zuanshi = CCSprite::create("zuanshi.png");
	zuanshi->setPosition(ccp(335,668));
	zuanshi->setScale(0.8f);
	addChild(zuanshi);
	CCSprite* btn_addDiamond = CCSprite::create("btn_add.png");
	btn_addDiamond->setPosition(ccp(450,665));
	addChild(btn_addDiamond);

	//颗数
	const char* char_diamondCount = Game::getInstance()->getIntCString(Game::getInstance()->getDiamondCount(),"bmpFont.fnt");
	_diamondCountText = CCLabelBMFont::create(char_diamondCount,"bmpFont.fnt");
	_diamondCountText->setScale(0.6f);
	_diamondCountText->setPosition(ccp(390,665));
	_diamondCountText->setColor(ccc3(189,15,0));
	addChild(_diamondCountText);

	CCMenuItemImage* addDiamondItem=CCMenuItemImage::create("btnAddRect.png",NULL,this,menu_selector(PropUI::addDiamondCallback));
	addDiamondItem->setOpacity(0);
	addDiamondItem->setPosition(ccp(390,665));

	CCPoint pos0 = ccp(275,610);
	float interval = 58;
	CCMenuItemImage* ranItem = CCMenuItemImage::create("prop_random.png",NULL,this,menu_selector(PropUI::randCallback));
	ranItem->setPosition(pos0);
	CCMenuItemImage* selectColorItem = CCMenuItemImage::create("prop_selectColor.png",NULL,this,menu_selector(PropUI::selectColorCallback));
	selectColorItem->setPosition(pos0+ccp(interval,0));
	CCMenuItemImage* coinAddItem = CCMenuItemImage::create("prop_coinAdd.png",NULL,this,menu_selector(PropUI::coinAddCallback));
	coinAddItem->setPosition(pos0+ccp(interval*2,0));
	CCMenuItemImage* popOneItem = CCMenuItemImage::create("prop_popOne.png",NULL,this,menu_selector(PropUI::popOneCallback));
	popOneItem->setPosition(pos0+ccp(interval*3,0));
	_menu=CCMenu::create(addDiamondItem,ranItem,selectColorItem,coinAddItem,popOneItem,NULL);
	_menu->setPosition(CCPointZero);
	addChild(_menu);
}

void PropUI::updateDiamondText(){
	const char* char_diamondCount = Game::getInstance()->getIntCString(Game::getInstance()->getDiamondCount(),"bmpFont.fnt");
	CCLOG("updateDiamondText:%s",char_diamondCount);
	_diamondCountText->setString(char_diamondCount,true);
}

void PropUI::randCallback(CCObject* pSender){
	if(!_enabled)return;
	if(Game::getInstance()->getPause())return;
	if(Game::getInstance()->getDiamondCount()<5){
		Game::getInstance()->setPause(true);
		Game::getInstance()->createReceiveBag(false);
		return;
	}
	
	Game::getInstance()->setDiamondCount(Game::getInstance()->getDiamondCount()-5);
	StarManager::getInstance()->upset();
	playerClickSound();
	SimpleAudioEngine::sharedEngine()->playEffect("sounds/Props_random.ogg");
	createScreenText("screenTextPropRandom");
}

void PropUI::selectColorCallback(CCObject* pSender){
	if(!_enabled)return;
	if(Game::getInstance()->getPause())return;
	if(Game::getInstance()->getDiamondCount()<5){
		Game::getInstance()->setPause(true);
		Game::getInstance()->createReceiveBag(false);
		return;
	}
	
	Game::getInstance()->setDiamondCount(Game::getInstance()->getDiamondCount()-5);
	Game::getInstance()->setIsSelectColoring(true);
	playerClickSound();
	setEnabled(false);
	createScreenText("screenTextPropChangeColor");
}

void PropUI::coinAddCallback(CCObject* pSender){
	if(!_enabled)return;
	if(Game::getInstance()->getPause())return;
	if(Game::getInstance()->getDiamondCount()<5){
		Game::getInstance()->setPause(true);
		Game::getInstance()->createReceiveBag(false);
		return;
	}
	
	Game::getInstance()->setDiamondCount(Game::getInstance()->getDiamondCount()-5);
	Game::getInstance()->setScoreMul(2);
	playerClickSound();
	createScreenText("screenTextPropScoreMul");
}

void PropUI::popOneCallback(CCObject* pSender){
	if(!_enabled)return;
	if(Game::getInstance()->getPause())return;
	if(Game::getInstance()->getDiamondCount()<5){
		Game::getInstance()->setPause(true);
		Game::getInstance()->createReceiveBag(false);
		return;
	}
	
	Game::getInstance()->setDiamondCount(Game::getInstance()->getDiamondCount()-5);
	playerClickSound();
	Game::getInstance()->setIsPopOneing(true);
	setEnabled(false);
	createScreenText("screenTextPropPopOne");
}

void PropUI::setEnabled(bool value){
	_enabled = value;
	setTouchEnabled(value);
	if(_enabled){
		_menu->setOpacity(255);
	}else{
		_menu->setOpacity(125);
	}
}

void PropUI::createScreenText(const char* stringKey){
	CCDictionary* strings = CCDictionary::createWithContentsOfFile("string.xml");
	CCString* str = (CCString*)strings->objectForKey(stringKey);
	ScreenText* screenText = ScreenText::create();
	screenText->initInstance(str->getCString());
	GameLevel::getInstance()->addChild(screenText);
}

void PropUI::addDiamondCallback(CCObject* pSender){
	if(!_enabled)return;
	if(Game::getInstance()->getPause())return;
	Game::getInstance()->setPause(true);
	Game::getInstance()->createReceiveBag(false);
}

void PropUI::playerClickSound(){
	SimpleAudioEngine::sharedEngine()->playEffect("sounds/coin.ogg");
}

PropUI* PropUI::_instance=NULL;
PropUI* PropUI::getInstance(){
	return _instance;
}

PropUI::~PropUI(){
	_diamondCountText=NULL;
	_instance=NULL;
}