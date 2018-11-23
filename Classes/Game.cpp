#include "Game.h"
#include "GameEndMessageUI.h"
#include "GameData.h"
#include "ReceiveBag.h"
#include "ActivityBag.h"
#include "NoviceBag.h"
#include "Shop.h"
#include "FailureUI.h"
#include "WantContinueUI.h"
#include "PauseUI.h"
#include "MysteryPrizeBag.h"
#include <iostream>
#include <string>
#include "SimpleAudioEngine.h"
#include "PropUI.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../proj.android/jni/hellocpp/ttest.h"
#endif

using namespace CocosDenshion;
using namespace std;
USING_NS_CC;

Game* Game::_instance=NULL;
Game* Game::getInstance(){
	if(!_instance)_instance=new Game();
	return _instance;
}

void Game::keyBackClicked(){
	if(_gameLevel!=NULL)return;
	if(_isCreateMysteryPrize){
		//退出
		exit();
	}else{
		createMysteryPrizeBag();
	}
}

void Game::exit(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}

bool Game::init(){
	if(!CCLayer::init())return false;
	_mute=false;
	_instance=this;
	_diamondCount=0;
	_isGameOver=true;
	_pause=false;
	_scoreMul = 1;
	_gameLevel=NULL;
	_isReceiveNoviceBag=CCUserDefault::sharedUserDefault()->getBoolForKey("isReceiveNoviceBag",false);
	setKeypadEnabled(true);
	//
	setDiamondCount(-1);//设置钻石数量为存储中的值
	//第一次玩游戏 赠送20颗钻石
	if(!CCUserDefault::sharedUserDefault()->getBoolForKey("isgived",false)){
		setDiamondCount(20);
		CCUserDefault::sharedUserDefault()->setBoolForKey("isgived",true);
	}
	//
	createTitle();
	if(!_isReceiveNoviceBag){
		//隔0.5秒创建弹出新手大礼包
		scheduleOnce(schedule_selector(Game::startDelayComplete),0.5f);
	}
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);
	//

	return true;
}

void Game::startDelayComplete(float t){
	createNoviceBag();
}

void Game::setDiamondCount(int value/*=-1*/,bool isAdd/*=false*/){
	const char* key = "diamondCount";
	if(value==-1){
		_diamondCount=CCUserDefault::sharedUserDefault()->getIntegerForKey(key,0);
	}else{
		if(isAdd) _diamondCount+=value;
		else _diamondCount = value;
		CCUserDefault::sharedUserDefault()->setIntegerForKey(key,_diamondCount);
	}

	//更新显示
	if(Shop::getInstance()!=NULL){
		Shop::getInstance()->updateDiamondText();
	}
	if(PropUI::getInstance()!=NULL){
		PropUI::getInstance()->updateDiamondText();
	}
}

void Game::clearSaveData(){
	CCUserDefault::sharedUserDefault()->setIntegerForKey("level",1);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("score",0);
}

void Game::newGame(){
	clearSaveData();
	createGameLevel();
}

void Game::continueGame(){
	createGameLevel();
}

void Game::createGameLevel(){
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	_isPopOneing=false;
	_isSelectColoring=false;
	_isGameOver=false;
	_pause=false;

	_level = CCUserDefault::sharedUserDefault()->getIntegerForKey("level",1);
	_score = CCUserDefault::sharedUserDefault()->getIntegerForKey("score",0);
	_maxRecord = CCUserDefault::sharedUserDefault()->getIntegerForKey("maxRecord",0);
	_targetScore = GameData::getTargetScore(_level);
	_gameLevel = GameLevel::create();
	this->addChild(_gameLevel);
}

void Game::checkGameVictoryFailure(){
	_pause=false;
	if(_score>=_targetScore)victory();
	else failure();
}

void Game::victory(){
	//保存最高记录分数
    if(_score>_maxRecord)CCUserDefault::sharedUserDefault()->setIntegerForKey("maxRecord",_score);
    //保存当前得分
	CCUserDefault::sharedUserDefault()->setIntegerForKey("score",_score);
    //保存关卡
	CCUserDefault::sharedUserDefault()->setIntegerForKey("level",_level+1);
    //////////////////////////////////////////////////////////////////////////
    //创建领取礼包界面,true表示关闭界面后继续游戏
    createReceiveBag(true);
}



void Game::failure(){
    //创建失败界面
	createFailureUI();
}

void Game::addScore(int value){
	_score+=value;
}

void Game::setPause(bool value, bool isStopOpengl/*=false*/,bool isStopSound/*=false*/){
	_pause=value;
	if(_pause){
		if(isStopOpengl)CCDirector::sharedDirector()->stopAnimation();
		if(isStopSound){
			SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			SimpleAudioEngine::sharedEngine()->stopAllEffects();
		}
	}else{
		if(isStopOpengl)CCDirector::sharedDirector()->startAnimation();
		if(isStopSound){
			SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
			SimpleAudioEngine::sharedEngine()->resumeAllEffects();
		}
	}
}
bool Game::getPause(){
	return _pause;
}

void Game::setIsCreateMysteryPrize(bool value){
	_isCreateMysteryPrize=value;
}

void Game::setIsReceiveNoviceBaged(){
	_isReceiveNoviceBag=true;
	CCUserDefault::sharedUserDefault()->setBoolForKey("isReceiveNoviceBag",_isReceiveNoviceBag);
}
void Game::setMute(bool value){
	_mute = value;
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(_mute?0:0.5f);
}
void Game::setIsGameOver(bool value){_isGameOver=value;}
void Game::setIsPopOneing(bool value){_isPopOneing = value;}
void Game::setIsSelectColoring(bool value){_isSelectColoring=value;}
void Game::setScoreMul(int value){_scoreMul = value;}
//get
bool Game::getIsReceiveNoviceBag(){return _isReceiveNoviceBag;}
bool Game::getIsGameOver(){return _isGameOver;}
bool Game::isSelectColoring(){return _isSelectColoring;}
bool Game::isPopOneing(){return _isPopOneing;}
int Game::getLevel(){return _level;}
int Game::getTargetScore(){return _targetScore;}
int Game::getScore(){return _score;}
int Game::getMaxRecord(){return _maxRecord;}
int Game::getDiamondCount(){return _diamondCount;}
int Game::getScoreMul(){return _scoreMul;}
bool Game::getMute(){ return _mute;}

/**创建神秘大奖包*/
void Game::createMysteryPrizeBag(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	MysteryPrizeBag* mysteryPrizeBag = MysteryPrizeBag::create();
	mysteryPrizeBag->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	addChild(mysteryPrizeBag);
}

void Game::createPauseUI(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	PauseUI* pauseUI = PauseUI::create();
	pauseUI->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	addChild(pauseUI);
}

void Game::createTitle(bool isClearSaveData, bool isDestroyLevel){
	if(isClearSaveData) clearSaveData();
	if(isDestroyLevel){
		if(_gameLevel!=NULL){
			_gameLevel->removeAllChildrenWithCleanup(true);
			_gameLevel->removeFromParentAndCleanup(true);
			_gameLevel=NULL;
		}
	}
	_title = Title::create();
	this->addChild(_title);
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/bg.ogg",true);
}

void Game::createShop(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	Shop* shop = Shop::create();
	shop->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	addChild(shop);
}

void Game::createGameEndMessageUI(){
	GameEndMessageUI* gameEndMessageUI = GameEndMessageUI::create();
	addChild(gameEndMessageUI);
}

/**创建领取大礼包*/
void Game::createReceiveBag(bool isContinueGame){
	int tag = 10;
	if(getChildByTag(tag)!=NULL)return;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	ReceiveBag* receiveBag = ReceiveBag::create();
	receiveBag->setIsContinueGame(isContinueGame);
	receiveBag->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	receiveBag->setTag(tag);
	addChild(receiveBag);
}

void Game::createWantContinueUI(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	WantContinueUI* wantContinueUI = WantContinueUI::create();
	wantContinueUI->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	addChild(wantContinueUI);
}

/**创建活动大礼包*/
void Game::createActivityBag(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	ActivityBag* activityBag = ActivityBag::create();
	activityBag->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	addChild(activityBag);
}

void Game::createFailureUI(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	FailureUI* failureUI = FailureUI::create();
	failureUI->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	addChild(failureUI);
}

/**创建新手礼包*/
void Game::createNoviceBag(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	NoviceBag* noviceBag = NoviceBag::create();
	noviceBag->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	addChild(noviceBag);
}

void Game::createGameOverAnim(){
	CCSprite* gameOverSp = CCSprite::create("gameOverText.png");
	
}

const char* Game::getIntCString(const int n, const char* fntFile) const{
	CCString* ccStr_n=NULL;
	if(n>=10000){
		float nn = n*0.0001;
		CCDictionary* strings = CCDictionary::createWithContentsOfFile("string.xml");
		CCString* ccStr_wan=(CCString*)strings->objectForKey("wan");
		ccStr_n=CCString::createWithFormat("%.2f",nn);
		string str = ccStr_n->getCString();
		str+=ccStr_wan->getCString();
		ccStr_n = CCString::create(str);
	}else{
		ccStr_n = CCString::createWithFormat("%d",n);
	}
	return ccStr_n->getCString();
}

void Game::gamePay(const int money, const char* product, const char* extData,CCObject*payCB_this,PayCB cb,int buyCount){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	_payCB_this = payCB_this;
	_payCB=cb;
	_buyCount = buyCount;
	ccPay(money*100,product,extData);
#endif
	
}

void Game::payCallback(const char* result){
	(_payCB_this->*_payCB)(result=="yes",_buyCount);
}

void Game::resumeAnimation(float t){
	
}

Game::~Game(){
	_instance=NULL;
	_payCB=NULL;
	_payCB_this=NULL;
	_title=NULL;
	_gameLevel=NULL;
}



