//顺风车版本，直接完成最先收到的请求，然后沿途捡客
#include"Elevator.h"
#include"Passenger.h"
#include<iostream>
#include <fstream>
using namespace std;
Elevator elevator;
void read() {
	ifstream infile("input.txt");
	if (!infile)
	{
		cerr << "open infile wrong!\n";
		exit(1);
	}
	int n;
	infile >> n;
	passengers* man = new passengers[n+1];
	for (int i = 0;i <= n;i++) {
		infile >> man[i].time >> man[i].location >> man[i].direction;
	}
}
void wirte()
{
	ofstream outfile("output.txt");
	if (!outfile)//判断文件打开是否成功
	{
		cerr << "open outfile wrong!\n";
		exit(1);
	}
	outfile << elevator.time << " " << elevator.location << endl;
}
bool judge(int n, passengers *man) {
	for (int i = 1;i <= n;i++)
		if (man[i].status == "wait" || man[i].status == "in")
			return 1;
	return 0;
}
bool finish(int n, passengers *man) {
	int ans = 0;
	for (int i = 1;i <= n;i++)
		if (man[i].status == "out")
			ans++;
	if (ans == n - 1)
		return true;
	else
		return false;
}
int main() {
	int in, out,num=0,j,index=1;
	ifstream infile("input.txt");
	if (!infile)
	{
		cerr << "open infile wrong!\n";
		exit(1);
	}
	ofstream outfile("output.txt");
	if (!outfile)//判断文件打开是否成功
	{
		cerr << "open outfile wrong!\n";
		exit(1);
	}
	int n;
	infile >> n;
	passengers* man = new passengers[n + 1];
		//输入每个人的时间、位置、方向(如果方向为0的话，将其赋值10）
		for (int i = 1;i <= n;i++)
		{
			infile>> man[i].time >> man[i].location >> man[i].direction;
			man[i].status = "offline";
		}
		//给第0个乘客的终点赋值1
		man[0].direction = 1;
		//重置数据
		elevator.time = 0;
		elevator.location = 0;
		for (j = 1;;) {
			//重置in和put
			in = 0;
			out = 0;
			//判断是否开始等待
			for (int i = 1;i <= n;i++)
				if (elevator.time >= man[i].time&&man[i].status == "offline")
					man[i].status = "wait";
			//判断是否接客
			for (int z = 1;z <= n && elevator.time >= man[z].time;z++) {
				if (man[z].status == "in" || man[z].status == "out")
					continue;
				if (elevator.location == man[z].location)
				{
					man[z].status = "in";
					num++;
					in++;
				}
			}
			//判断是否送客
			for (int x = 1;x <= n;x++)
				if (elevator.location == man[x].direction&&man[x].status == "in"&&elevator.time >= man[x].time)
				{
					out++;
					man[x].status = "out";
					index = x;
				}
			//输出控制
			if (in != 0)
			{
				if (out == 0)
					outfile << elevator.time << " " << man[index].direction << endl; 
				else
				{
					num -= out;
					outfile << elevator.time << " " << man[index].direction << endl; 
				}
			}
			else
				if (in == 0 && out != 0)
				{
					num -= out;
					outfile << elevator.time << " " << man[index].direction << endl;
				}
			//电梯位置控制
			if ((in + out) == 0 && judge(n, man))
				if (man[j].status == "wait")
				{
					if (man[j].location - elevator.location>0)
						elevator.location++;
					else
						elevator.location--;
				}
				else
				{
					if (man[j].direction - elevator.location>0)
						elevator.location++;
					else
						elevator.location--;
				}

			//设置循环结束
			if (finish(n, man))
			{
				break;
			}
			//时间轴向前
			elevator.time++;
			j += out;
	
		}
		delete[]man;
	return 0;
}