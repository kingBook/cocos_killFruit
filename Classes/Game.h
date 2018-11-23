#ifndef __GAME_H__
#define __GAME_H__
#include "cocos2d.h"
#include "Title.h"
#include "GameLevel.h"

typedef void (CCObject::*PayCB)(bool,int);
#define pay_cb(_PAY_C_B) (PayCB)(&_PAY_C_B)

class Game : public cocos2d::CCLayer{
private:
	static Game* _instance;
	Title* _title;
	GameLevel* _gameLevel;
	int _level;
	int _targetScore;
	int _score;
	int _scoreMul;
	int _maxRecord;
	int _diamondCount;
	bool _mute;
	bool _isPopOneing;
	bool _isSelectColoring;
	bool _isGameOver;
	bool _pause;
	int _buyCount;
	CCObject* _payCB_this;
	PayCB _payCB;
	bool _isCreateMysteryPrize;
	bool _isReceiveNoviceBag;//是否领取了新手礼包
	void createMysteryPrizeBag();
	void createGameLevel();
	void createFailureUI();
	virtual void keyBackClicked();
	void startDelayComplete(float t);
	void exit();
	void resumeAnimation(float t);
public:
	static Game* getInstance();
	virtual bool init();
	void createTitle(bool isClearSaveData=false, bool isDestroyLevel=false);
	void createGameEndMessageUI();
	void newGame();
	void continueGame();
	void createShop();
	void setIsPopOneing(bool value);
	void setIsSelectColoring(bool value);
	void setIsGameOver(bool value);
	bool getIsGameOver();
	bool isPopOneing();
	bool isSelectColoring();
	int getLevel();
	int getTargetScore();
	void addScore(int value);
	int getScore();
	int getMaxRecord();
	void checkGameVictoryFailure();
	void victory();
	void failure();
	void createReceiveBag(bool isContinueGame);
	void createActivityBag();
	/**创建新手礼包*/
	void createNoviceBag();
	void createGameOverAnim();
	void createWantContinueUI();
	void clearSaveData();
	void createPauseUI();
	void setIsCreateMysteryPrize(bool value);
	void setDiamondCount(int value=-1,bool isAdd=false);
	void setPause(bool pause,bool isStopOpengl=false,bool isStopSound=false);
	bool getPause();
	void setIsReceiveNoviceBaged();
	bool getIsReceiveNoviceBag();
	int getDiamondCount();
	void setMute(bool value);
	bool getMute();
	void setScoreMul(int value);
	int getScoreMul();
	const char* getIntCString(const int n, const char* fntFile) const;
	//支付接口
	void gamePay(const int money, const char* product, const char* extData,CCObject*payCB_this, PayCB cb,int buyCount);
	void payCallback(const char* result);
	~Game();
	CREATE_FUNC(Game);
};

#endif
