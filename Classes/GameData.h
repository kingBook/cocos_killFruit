#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__
#include <iostream>
#include <vector>
using namespace std;

class GameData{
public:
	static int getTargetScore(int level);
	static int getShopBuyTotal(int id);//�������
	static int getShopGiveTotal(int id); //���͵�����
	static int getShopMoney(int id);//��Ҫ���ѵĽ�Ǯ
private:
	static int _shopData[5][3];
};
#endif