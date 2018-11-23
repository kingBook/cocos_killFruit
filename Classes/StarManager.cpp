#include "StarManager.h"
#include "cocos2d.h"
#include "StarsBoard.h"
#include "RandomArr.h"
#include "Game.h"
#include "PropUI.h"
#include "ChangeColorBar.h"
#include "GameEndMessageUI.h"
#include "PropUI.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool StarManager::init(){
	if(!cocos2d::CCLayer::init())return false;
	_instance = this;
	for(int i=0;i<102;i++){_mvs[i]=0;}
	_offset = ccp(0,48);

	_stars = CCArray::create();//10*10������
	_stars->retain();
	for(int i=0; i<10; i++){
		CCArray* arr = CCArray::create();
		for(int j=0;j<10;j++)arr->addObject(new CCObject());
		_stars->addObject(arr);
	}
	setTouchEnabled(true);
	return true;
}

void StarManager::newStarsPosition(int cnts[]){
	//for(int i=0;i<5;i++){CCLOG("%d",cnts[i]);}
	//����
	_selectTotal=0;
	int i,j;
	for(i=0; i<10; i++){
		CCArray* arr = (CCArray*)_stars->objectAtIndex(i);
		arr->removeAllObjects();
		for(j=0;j<10;j++)arr->addObject(new CCObject());
	}
	//�½�
	StarsBoard* starsBoards=new StarsBoard[5];
	/*for(i=0;i<5;i++){
		StarsBoard starsBoard = starsBoards[i];
	}*/
	int id;
	for(i=0;i<5;i++){
		starsBoards[i].setAll(false);
		for(j=0;j<cnts[i];j++){
			id = RandomArr::getNextRandomElement();
			starsBoards[i].setTrue(id);
			pushStar(i,id,true);
		}
	}
	/*for(i=0;i<5;i++){
		starsBoards[i].logMy();
	}
	CCLOG("%d","--------------");*/
	_starsPosition=new StarsPosition(starsBoards);
	SimpleAudioEngine::sharedEngine()->playEffect("sounds/starShow.mp3");
}

void StarManager::pop(int posId){
	_starsPosition->getBlackByPoint(posId,_mvs);
	//CCLOG("out %d",_mvs[101]);
	if(_mvs[101]>=2){//��ͬ��ɫ�ķ���>=2
		_selectTotal=_mvs[101];
		_starsPosition->doPop(_mvs);//�Ӿ����е���
		//��������
		int x,y;
		Star* star;
		vector<Star*> popStars;
		vector<Star*> moveStars;
		for(int i = 0; i < _selectTotal; i++) {
			x = _mvs[i] >> 4;
			y = 9 - (_mvs[i] & 0xf);
			CCArray* arr_x = ((CCArray*)_stars->objectAtIndex(x));
			star = (Star*)arr_x->objectAtIndex(y);
			popStars.push_back(star);//��ӵ�Ҫɾ�������б�������ɾ��
			arr_x->removeObjectAtIndex(y);
			for(int j = y; j < (int)arr_x->count(); j++){
				star =(Star *)arr_x->objectAtIndex(j);
				star->addMoveDown(_offset);
				star->setIsStopMove(true);//��true��ֹUpdate�ƶ����ȴ����ɾ�����
				moveStars.push_back(star);
			}
		}
		//��������
		checkMoveLeft(moveStars);
		for(int i=0;i<(int)moveStars.size();i++){
			star =moveStars[i];
			//CCLOG("2. moveStars added posId:%d, x_id:%d",star->getPosId(),(star->getPosId())>>4);
		}
		int scoreMul = Game::getInstance()->getScoreMul();
        if(scoreMul>1)Game::getInstance()->setScoreMul(1);
        //һ����ɾ��
		deleteOneByOne(popStars,moveStars,true,scoreMul);
        //������ﵽ�սᣬ���㽱����ֵ��������ǰ
        checkGameOver();
	}
}

void StarManager::checkGameOver(){
	if(_starsPosition->nextGenerateMove()==0){
		destroyRemainStars();
		Game::getInstance()->setIsGameOver(true);
		PropUI::getInstance()->setEnabled(false);
		CCLOG("%s","gameOver~~!");
	}
}

void StarManager::destroyRemainStars(){
	vector<Star*> stars;
	int i,j;
	for(i=0;i<10;i++){
		CCArray* arr_i=(CCArray*)_stars->objectAtIndex(i);
		for(j=0;j<(int)arr_i->count();j++){
			Star* star = (Star*)arr_i->objectAtIndex(j);
			stars.push_back(star);
		}
		arr_i->removeAllObjects();
	}
	////��ʾ����������ʣ�µ������ı�
	Game::getInstance()->createGameEndMessageUI();
	GameEndMessageUI::getInstance()->setRemainStars((int)stars.size());
	//����Ҫ�����ķ���
	int rewardScore = 0;
    if (stars.size() < 10) rewardScore = 2000 - stars.size() * stars.size() * 20;
	GameEndMessageUI::getInstance()->setRewardScore(rewardScore);
	//
	deleteOneByOne(stars,false,1);
}

void StarManager::deleteOneByOne(vector<Star*> popStars, bool isAddScore, int scoreMul){
	int total = popStars.size();
	float interval = 0.07f;
	float time = 0;
	//���ÿ��Ҫ�ӵķ�ֵ
	int* scoreArr = new int[total];
	int tempScore=0;
	int i;
	for(i=0;i<total;i++){
		tempScore=(i*10+5)*scoreMul;
		scoreArr[i]=tempScore;
	}
	/*  0 �����ϣ�6��7
        1 �ǳ�����8��9
        2 ˧������10~
    */
	int effectTypeId=-1;
	if(isAddScore){
		if(total>10)effectTypeId=2;
        else if(total>=8&&total<=9)effectTypeId=1;
        else if(total>=6&&total<=7)effectTypeId=0;
	}
	//
	int addScore;
	for(i=0; i<total; i++){
        time+=min(0.2f,interval*i);
        if(!isAddScore){
            if(i>=10){//����Ϸ����ʱ������>10��һ��������
                for (int j = i; j < total; j++){
					popStars[j]->delayPop(time,0,(bool)(j==total-1),-1,true);//���һ��ʱ��������ʾҪ�����ķ�ֵ
                }
                break; 
            }
        }
        addScore = isAddScore?scoreArr[i]:0;
        if(i==total-1) popStars[i]->delayPop(time,addScore,!isAddScore,effectTypeId);//���������һ���������������ƶ�,����������
        else popStars[i]->delayPop(time, addScore,false,-1);
    }
	//CCLOG("%s","deleteOneByOne a");
}

void StarManager::deleteOneByOne(vector<Star*> popStars, vector<Star*> moveStars, bool isAddScore, int scoreMul){
	//CCLOG("%s","deleteOneByOne b");
	int total = popStars.size();
	float interval = 0.07f;
	float time = 0;
	//���ÿ��Ҫ�ӵķ�ֵ
	int* scoreArr = new int[total];
	int tempScore=0;
	int i;
	for(i=0;i<total;i++){
		tempScore=(i*10+5)*scoreMul;
		scoreArr[i]=tempScore;
	}
	//  0 �����ϣ�6��7
    //  1 �ǳ�����8��9
    //  2 ˧������10~
    
	int effectTypeId=-1;
	if(isAddScore){
		if(total>10)effectTypeId=2;
        else if(total>=8&&total<=9)effectTypeId=1;
        else if(total>=6&&total<=7)effectTypeId=0;
	}
	//
	int addScore;
	for(i=0; i<total; i++){
        time+=min(0.1f,interval*i);
        if(!isAddScore){
            if(i>=10){//����Ϸ����ʱ������>10��һ��������
                for (int j = i; j < total; j++){
					popStars[j]->delayPop(time,0,(bool)(j==total-1),-1);//���һ��ʱ��������ʾҪ�����ķ�ֵ
                }
                break; 
            }
        }
        addScore = isAddScore?scoreArr[i]:0;
        if(i==total-1) popStars[i]->delayPop(moveStars,time,addScore,!isAddScore,effectTypeId);//���������һ���������������ƶ�,����������
        else popStars[i]->delayPop(time, addScore,false,-1);
    }
}

void StarManager::checkMoveLeft(vector<Star*> &moveStars){
	int* tmp = _starsPosition->doMoveToLeft();
	Star* star;
	for(int i=0;i<tmp[10];i++){
		if(tmp[i]!=i){
			//������Ӧ�ô洢�Ĵ洢��LIST
			CCArray* arr_i =(CCArray*)_stars->objectAtIndex(i);
			CCArray* tmpArr = (CCArray*)_stars->objectAtIndex(tmp[i]);
			arr_i->addObjectsFromArray(tmpArr);
			 //�����ƶ�
			for(int j=0;j<(int)arr_i->count();j++){
				star = (Star*)arr_i->objectAtIndex(j);
				star->addMoveLeft(tmp[i]-i,_offset);
				star->setIsStopMove(true);
				//CCLOG("push moveStars posId:%d, x_id:%d",star->getPosId(),(star->getPosId())>>4);
				moveStars.push_back(star);
			}
			tmpArr->removeAllObjects();
		}
	}
	for(int i=0;i<(int)moveStars.size();i++){
		star =moveStars[i];
		//CCLOG("1. moveStars added posId:%d, x_id:%d",star->getPosId(),(star->getPosId())>>4);
	}
}

void StarManager::pushStar(int color,int idx,bool isTweenShow/*=false*/){
	int x_id = idx >> 4;//0-9
    int y_id = 9 - (idx & 0xf);//0-9
	CCPoint starPos = ccp(48.0f*x_id+_offset.x+24.0f,48.0f * y_id + _offset.y + 24.0f);
	Star* star=Star::create();
	star->initInstance(color,idx);
	star->setPosition(starPos);
	if(isTweenShow)star->tweenShow(_offset);
	this->addChild(star);
	CCArray* arr=(CCArray*)_stars->objectAtIndex(x_id);
	arr->replaceObjectAtIndex(y_id,star,true);
}

void StarManager::popOne(int posId){
	int scoreMul = Game::getInstance()->getScoreMul();
    if(scoreMul>1) Game::getInstance()->setScoreMul(1);
	_starsPosition->doPopOne(posId);
	vector<Star*> popStars;
	vector<Star*> moveStars;
	int x_id = posId>>4;
	int y_id = 9-(posId&0xf);
	CCArray* arr_x=(CCArray*)_stars->objectAtIndex(x_id);
	Star* star = (Star*)arr_x->objectAtIndex(y_id);
	popStars.push_back(star);
	((CCArray*)_stars->objectAtIndex(x_id))->removeObjectAtIndex(y_id);
	for(int j=y_id;j<(int)arr_x->count();j++){
		star=(Star*)arr_x->objectAtIndex(j);
		star->addMoveDown(_offset);
		star->setIsStopMove(true);
		moveStars.push_back(star);
	}
	checkMoveLeft(moveStars);
	deleteOneByOne(popStars, moveStars,true,scoreMul);
	checkGameOver();
}

void StarManager::upset(){
	vector<int> cors,posIds;
	Star* star;
	CCArray* arr_i;
	int i,j;
	for(i=0;i<10;i++){
		arr_i = (CCArray*)_stars->objectAtIndex(i);
		for(j=0;j<(int)arr_i->count();j++){
			star=(Star*)arr_i->objectAtIndex(j);
			cors.push_back(star->getColorId());
			posIds.push_back(star->getPosId());
			star->dispose();
		}
		arr_i->removeAllObjects();
		for(j=0;j<10;j++)arr_i->addObject(new CCObject());
	}
	star=NULL;
	arr_i=NULL;
	int* corArr = new int[cors.size()];
	int* posIdArr = new int[posIds.size()];
	for(i=0;i<(int)cors.size();i++)corArr[i]=cors.at(i);
	for(i=0;i<(int)posIds.size();i++)posIdArr[i]=posIds.at(i);
	/*for(i=0;i<cors.size();i++){
		CCLOG("a: %d",corArr[i]);
	}*/
	RandomArr::randomize(corArr,cors.size());
	/*for(i=0;i<cors.size();i++){
		CCLOG("b: %d",corArr[i]);
	}*/
	 //�ؽ�
	StarsBoard* starsBoards = new StarsBoard[5];
	for(i=0;i<5;i++)starsBoards[i].setAll(false);
	int cor, posId;
	for(i=0;i<(int)cors.size();i++){
		cor=corArr[i];
		posId=posIdArr[i];
		starsBoards[cor].setTrue(posId);
		pushStar(cor,posId);
	}
	_starsPosition->dispose();
	delete _starsPosition;
	_starsPosition=new StarsPosition(starsBoards);
	//�Ƴ�û�����ǵ�Ԫ��
	i=10;
	while(--i>=0){
		arr_i=(CCArray*)_stars->objectAtIndex(i);
		j=(int)arr_i->count();
		while(--j>=0){
			star = dynamic_cast<Star*>(arr_i->objectAtIndex(j));
			if(star==NULL){
				arr_i->removeObjectAtIndex(j);
			}
		}
	}
}

/**�ı�һ�����ǵ���ɫ*/
void StarManager::changeOneStarColor(int curCor, int targetCor, int curPosId){
	//////////1.�ı�starsBoards
	StarsBoard* starsBoard = _starsPosition->getStarsBoards();
	starsBoard[curCor].setFalse(curPosId);//��ǰ��ɫ�б����Ƴ�
	starsBoard[targetCor].setTrue(curPosId);//�ӵ��µ��б�
	//////////2.�ı�stars
    int x = curPosId >> 4;
    int y = 9 - (curPosId & 0xf);

	CCArray* arr_i = (CCArray*)_stars->objectAtIndex(x);
	Star* star = (Star*)arr_i->objectAtIndex(y);
	star->changeColor(targetCor);
	PropUI::getInstance()->setEnabled(true);//�ָ�����������
	setTouchEnabled(true);//�ָ����ǿɵ�
	Game::getInstance()->setIsSelectColoring(false);
}

void StarManager::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
	if(Game::getInstance()->getPause())return;
	CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint pos = touch->getLocation();
	
	Star* star=getStarAtMousePos(pos);
	if(star!=NULL){
		if(Game::getInstance()->isPopOneing()){
			popOne(star->getPosId());
			Game::getInstance()->setIsPopOneing(false);
			PropUI::getInstance()->setEnabled(true);
		}else if(Game::getInstance()->isSelectColoring()){
			createChangeColorBar(star);
			setTouchEnabled(false);
		}else{
			pop(star->getPosId());
		}
	}
}

void StarManager::createChangeColorBar(Star* star){
	ChangeColorBar* changeColorBar = ChangeColorBar::create();
	changeColorBar->initInstance(star->getColorId(),star->getPosId());
	changeColorBar->setPosition(star->getPosition());
	addChild(changeColorBar);
	SimpleAudioEngine::sharedEngine()->playEffect("sounds/coin.ogg");
}

Star* StarManager::getStarAtMousePos(const CCPoint &pos){
	int i,j,len;
	for(i=0;i<10;i++){
		CCArray* arr = (CCArray*)_stars->objectAtIndex(i);
		len = arr->count();
		for(j=0;j<len;j++){
			Star* star = (Star*)arr->objectAtIndex(j);
			CCRect r = star->boundingBox();
			if(r.containsPoint(pos)){
				/*arr->removeObjectAtIndex(j,true);
				star->removeFromParent();
				break;*/
				return star;
			}
		}
	}
	return NULL;
}

StarManager* StarManager::_instance=NULL;
StarManager* StarManager::getInstance(){
	return _instance;
}

StarManager::~StarManager(){
	_instance=NULL;
}