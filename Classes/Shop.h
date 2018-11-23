#ifndef __SHOP_H__
#define __SHOP_H__
#include "cocos2d.h"
USING_NS_CC;
class Shop:public cocos2d::CCSprite{
public:
	~Shop();
	virtual bool init();
	void updateDiamondText();
	static Shop* getInstance();
	CREATE_FUNC(Shop);
private:
	CCLabelBMFont* _diamondCountText;
	static Shop* _instance;
	void closeCallback(CCObject* pSender);
	void buyCallback(CCObject* pSender);
	void payCallback(bool isFinish, int buyCount);
};
#endif