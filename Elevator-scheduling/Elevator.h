#pragma once
#include<queue>
using namespace std;
class Elevator
{
public:
	queue < int > destinationQueue; //目的地队列
	int time=0;//当前时间
	int location=0; //当前位置
	int direction; //运行方向
	void goToFloor(); //前往队列首的楼层
	void stop(); //停靠在当前楼层
	void updateDestinationQueue();//更新目的地队列
	Elevator();
	~Elevator();
};



