#ifndef __TEST_H__
#define __TEST_H__
#include "cocos2d.h"
USING_NS_CC;
class CA{
public:
	CA();
	
	float x;
};
class Test:public cocos2d::CCLayer {
public:
	virtual bool init();
	void testCA(CA ca);
	Test(float x=0);
	void hei(int &num);
	
	float x;
	CREATE_FUNC(Test);
private:
	bool _isFirst;
};

#endif