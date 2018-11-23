#ifndef __GAME_END_MESSAGE_UI_H__
#define __GAME_END_MESSAGE_UI_H__
#include "cocos2d.h"
USING_NS_CC;

class GameEndMessageUI:public cocos2d::CCLayer{
public:
	~GameEndMessageUI();
	virtual bool init();
	static GameEndMessageUI* getInstance();
	void setRemainStars(int value);
	void setRewardScore(int value);
	void moveOut();
	int getRewardScore();
	CREATE_FUNC(GameEndMessageUI);
private:
	int _rewardScore;
	CCLabelBMFont* _labelRewardScore;//��������
	CCLabelBMFont* _labelRemainStars;//ʣ�µ�����
	static GameEndMessageUI* _instance;
	void updateLabelReWardScore(int value);
	void dispose(float t);
};
#endif