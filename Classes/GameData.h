#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__
#include <iostream>
#include <vector>
using namespace std;

class GameData{
public:
	static int getTargetScore(int level);
	static int getShopBuyTotal(int id);//买的数量
	static int getShopGiveTotal(int id); //赠送的数量
	static int getShopMoney(int id);//需要花费的金钱
private:
	static int _shopData[5][3];
};
#endif