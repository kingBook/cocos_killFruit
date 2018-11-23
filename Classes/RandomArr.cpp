#include "RandomArr.h"
#include <iostream>
#include <string>
using namespace std;

int RandomArr::_list[MAX_ID]={};
int RandomArr::_ranIdList[MAX_ID]={};
int RandomArr::_nextRandomId=-1;

void RandomArr::instance(){
	int id=0,i,j;
	for(i = 0; i < 10; i++) {
        for(j = 0; j < 10; j++) {
            _list[id] = (int)((i << 4) | j);
            id++;
        }
    }
	for(i=0;i<MAX_ID;i++)_ranIdList[i]=i;
	randomize(_ranIdList,MAX_ID);
}

void RandomArr::randomize(int list[], int maxId){
	int i, id0, id1;
    for(i = 0; i < maxId; i++) {
        id0 = (int)(RandomArr::nextRandom()*maxId);//ȡ0~maxId(������maxId)��������
        id1 = list[i];
        list[i] = list[id0];
        list[id0] = id1;
    }
}

//����cnt��Ԫ�أ�����Ԫ�صĺ�Ϊsum��Ԫ�ص���СֵΪmin��Ԫ�ص����ֵΪmax��32λ�������顣
int* RandomArr::randElement(int sum, int cnt, int min, int max){
	int* tmp=new int[cnt];
	int mn = sum / cnt;
    int i;
	for(i = 0; i <= cnt - 2; i++) {
        tmp[i] = mn;
    }
	//���һ��Ԫ����������ת��ʱ������С�����֣���֤�͡�
    tmp[cnt - 1] = sum - mn * (cnt - 1);
	//�������ֵ�Ӽ�
    int a1,a2,r1,rn;
	for(i = 0; i <= cnt - 1; i++) {
		//ȡһ�������
		r1 = (int)(RandomArr::nextRandom()*(max - min + 1));
		//�Ӽ������֮����������
		a1 = tmp[i] + r1;
		do //��ֹ����Ӽ����ᵼ�½���¼������������ң��������ݱ任������С��
		{
			rn = (int)(RandomArr::nextRandom()*(cnt - 1));
		} while(!(rn != i));
		a2 = tmp[rn] - r1;
		//������Χ�Ľ��мӼ�
		if(a1 >= min && a1 <= max && a2 >= min && a2 <= max) {
			tmp[i] = a1;
			tmp[rn] = a2;
		}
	}
	return tmp;
}

int RandomArr::getNextRandomElement(){
	if(_nextRandomId==MAX_ID-1)_nextRandomId=-1;
	_nextRandomId++;
	int id=_ranIdList[_nextRandomId];
	return _list[id];
}

float RandomArr::nextRandom(){
	return CCRANDOM_0_1();
}