#pragma once
#include<queue>
using namespace std;
class Elevator
{
public:
	queue < int > destinationQueue; //Ŀ�ĵض���
	int time=0;//��ǰʱ��
	int location=0; //��ǰλ��
	int direction; //���з���
	void goToFloor(); //ǰ�������׵�¥��
	void stop(); //ͣ���ڵ�ǰ¥��
	void updateDestinationQueue();//����Ŀ�ĵض���
	Elevator();
	~Elevator();
};



