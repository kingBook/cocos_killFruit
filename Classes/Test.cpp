#include "Test.h"
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>  
#include "cocos2d.h"
#include "StarsBoard.h"
USING_NS_CC;

using namespace std;
int cmpTest( const void *pFirst, const void *pSecond){

    int nA = *(( int *)pFirst);

    int nB = *(( int *)pSecond);

    return (nA<nB ? -1 : nA>nB ? 1 : 0); // 由小到大排序

   // return (nA<nB ? 1 : nA>nB ? -1 : 0); // 由大到小排序

}
Test::Test(float x){
	this->x = x;
	CCLOG("%s","Test();");
	vector<int> list;
	list.push_back(5);
	list.push_back(3);
	list.push_back(4);
	list.push_back(2);
	list.push_back(1);
	sort(list.begin(),list.end());
	/*for(int i=0;i<list.size();i++){
		CCLOG("%d",list.at(i));
	}*/
	/*CCLOG("%d",list.at(list.size()-1));
	list.pop_back();
	for(int i=0;i<list.size();i++){
		CCLOG("%d",list.at(i));
	}*/

	int arr[]={5,3,4,1,2};

	qsort(arr,5,sizeof(arr[0]),cmpTest);

	/*for(int i=0;i<5;i++){
		CCLOG("%d",arr[i]);
	}*/

	//int nn=0;
	//hei(nn);
	//CCLOG("b %d",nn);
	//CA ca;
	//testCA(ca);
	//CCLOG("result:%f",ca.x);
	//CA* ca = new CA();
	//CCLOG("%s",typeid(ca).name());

	//StarsBoard starsBoard;
	//starsBoard=StarsBoard();
	/*int tps[102];
	for(int k=0; k<102; k++){
		CCLOG("%d",tps[k]);
	}*/
}

CA::CA(){
	cocos2d::CCLog("CA();");
}

void Test::testCA(CA ca){
	ca.x = 10;
	CCLOG("testCA changed:%f",ca.x);
}

void Test::hei(int &num){
	CCLOG("a %d",num);
	num=1;
}


bool Test::init(){
	if(!CCLayer::init())return false;

	/*CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("star.png");
	CCParticleExplosion* eff = CCParticleExplosion::create();
	eff->setTexture(texture);
	eff->setPosition(ccp(200,400));
	//eff->setDuration(1);
	//eff->setLife(1);
	eff->set
	//
	eff->setEmitterMode(kCCParticleModeGravity);
	eff->setGravity(ccp(0,-100));

	addChild(eff);*/

	//
	


	
	return true;
}

/*Color4F getColor4F(int color){
    switch(color){
    case Star::color::PURPLE:
        return Color4F(0.74,0.30,0.99,1);
        //return Color4F(189,78,253,1);
    case Star::color::BLUE:
        return Color4F(84/255.0f,203/255.0f,254/255.0f,1);
    case Star::color::RED:
        return Color4F(253/255.0f,80/255.0f,126/255.0f,1);
    case Star::color::YELLOW:
        return Color4F(253/255.0f,234/255.0f,84/255.0f,1);
    case Star::color::GREEN:
        return Color4F(132/255.0f,226/255.0f,111/255.0f,1);
    }
    return Color4F(1,1,1,0);
}*/
