#include "Shop.h"
#include "GameData.h"
#include "Title.h"
#include "Game.h"

bool Shop::init(){
	if(!CCSprite::init())return false;
	_instance=this;
	Title::getInstance()->setEnabled(false);//禁点标题
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//创建背景
	CCLayerColor* bgColor = CCLayerColor::create(ccc4(0,0,0,125));
	bgColor->setPosition(ccp(-visibleSize.width*0.5f,-visibleSize.height*0.5f));
	addChild(bgColor);
	
	CCSprite* bg = CCSprite::create("shopBg.png");
	addChild(bg);

	//你拥有钻石   颗
	CCDictionary* strings = CCDictionary::createWithContentsOfFile("string.xml");
	CCString* ccStr_niyongyouzuanshi = (CCString*)strings->objectForKey("niyongyouzuanshi");
	CCString* ccStr_ke = (CCString*)strings->objectForKey("ke");
	string str = ccStr_niyongyouzuanshi->getCString();
	str+="            ";
	str+=ccStr_ke->getCString();
	CCLabelBMFont* label=CCLabelBMFont::create(str.c_str(),"bmpFont.fnt");
	label->setScale(0.7f);
	label->setPositionY(175);
	label->setColor(ccc3(64,32,0));
	addChild(label);

	//颗数
	const char* char_diamondCount = Game::getInstance()->getIntCString(Game::getInstance()->getDiamondCount(),"bmpFont.fnt");
	_diamondCountText = CCLabelBMFont::create(char_diamondCount,"bmpFont.fnt");
	_diamondCountText->setScale(0.6f);
	_diamondCountText->setPosition(55,175);
	_diamondCountText->setColor(ccc3(189,15,0));
	addChild(_diamondCountText);

	CCArray* menuItems = CCArray::create();

	float y0 = -250;
	float d = 90;
	for(int i=0; i<5; i++){
		CCSprite* btnBg = CCSprite::create("shopBtnBg.png");
		btnBg->setPositionY(y0+d*i);
		addChild(btnBg);

		CCSprite* zuanshi_a = CCSprite::create("zuanshi.png");
		zuanshi_a->setPosition(ccp(-145,y0+d*i));
		addChild(zuanshi_a);

		//购买的数量
		CCString* str_x0 = CCString::createWithFormat("x%d",GameData::getShopBuyTotal(i),NULL);
		CCLabelBMFont* label_x0 = CCLabelBMFont::create(str_x0->getCString(),"bmpFont2.fnt");
		label_x0->setScale(0.4f);
		label_x0->setPosition(ccp(-100,-265+d*i));
		addChild(label_x0);

		CCSprite* zuanshi_b = CCSprite::create("zuanshi.png");
		zuanshi_b->setScale(0.8f);
		zuanshi_b->setPosition(ccp(10,-255+d*i));
		addChild(zuanshi_b);

		//赠送的数量
		CCString* str_x1 = CCString::createWithFormat("x%d",GameData::getShopGiveTotal(i),NULL);
		CCLabelBMFont* label_x1 = CCLabelBMFont::create(str_x1->getCString(),"bmpFont2.fnt");
		label_x1->setScale(0.4f);
		label_x1->setPosition(ccp(50,-265+d*i));
		addChild(label_x1);

		CCSprite* zeng = CCSprite::create("zeng.png");
		zeng->setPosition(ccp(-50,-240+d*i));
		addChild(zeng);

		CCSprite* buyBtn=CCSprite::create("buy.png");
		buyBtn->setPosition(ccp(125,y0+d*i));
		addChild(buyBtn);

		CCString* str_money = CCString::createWithFormat("%d.00",GameData::getShopMoney(i),NULL);
		CCLabelBMFont* label_money = CCLabelBMFont::create(str_money->getCString(),"bmpFont2.fnt");
		label_money->setScale(0.3f);
		label_money->setColor(ccc3(255,50,0));
		label_money->setPosition(ccp(130,y0+d*i+3));
		addChild(label_money);

		if(i==0){
			CCSprite* zuiHuaSuan=CCSprite::create("zuiHuaSuan.png");
			zuiHuaSuan->setPosition(ccp(155,y0+d*i+36));
			addChild(zuiHuaSuan);
		}else if(i==1){
			CCSprite* reixiao=CCSprite::create("reixiao.png");
			reixiao->setPosition(ccp(155,y0+d*i+36));
			addChild(reixiao);
		}

		CCMenuItemImage* rect_cItem = CCMenuItemImage::create("rect_c.png",NULL,this,menu_selector(Shop::buyCallback));
		rect_cItem->setOpacity(0);
		rect_cItem->setTag(i);
		rect_cItem->setPosition(ccp(125,y0+d*i));
		menuItems->addObject(rect_cItem);
	}

	CCMenuItemImage* closeItem = CCMenuItemImage::create("close.png",NULL,this,menu_selector(Shop::closeCallback));
	closeItem->setPosition(ccp(-170,241));
	menuItems->addObject(closeItem);

	CCMenu* menu =CCMenu::createWithArray(menuItems);
	menu->setPosition(CCPointZero);
	addChild(menu);
	//放大出现
	setScale(0.1f);
	CCScaleTo* scaleTo = CCScaleTo::create(0.5f,1.0f,1.0f);
	runAction(scaleTo);
	return true;
}

void Shop::updateDiamondText(){
	const char* char_diamondCount = Game::getInstance()->getIntCString(Game::getInstance()->getDiamondCount(),"bmpFont.fnt");
	_diamondCountText->setString(char_diamondCount,true);
}

void Shop::closeCallback(CCObject* pSender){
	CCLOG("%s","Shop::closeCallback();");
	removeAllChildrenWithCleanup(true);
	removeFromParentAndCleanup(true);
	Title::getInstance()->setEnabled(true);
}

void Shop::buyCallback(CCObject* pSender){
	CCLOG("%s","Shop::buyCallback();");
	CCMenuItemImage* rect_cItem = (CCMenuItemImage*)pSender;
	int tag = rect_cItem->getTag();
	CCLOG("%d",tag);
	int moneys[5]={10,8,6,4,2};
	int totals[5] = {80+56, 50+40, 30+28, 20+18, 10+7};
	const char* products[5] = {"shopBuy0","shopBuy1","shopBuy2","shopBuy3","shopBuy4"};

	Game::getInstance()->gamePay(moneys[tag],products[tag],"",this,pay_cb(Shop::payCallback),totals[tag]);
}

void Shop::payCallback(bool isFinish, int buyCount){
	CCLOG("shop::payCallback():%s, %d",isFinish?"ok":"no", buyCount);
	if(isFinish){
		Game::getInstance()->setDiamondCount(buyCount,true);
		updateDiamondText();
	}
}

Shop::~Shop(){
	_instance=NULL;
}

Shop* Shop::_instance=NULL;
Shop* Shop::getInstance(){
	return _instance;
}