#include<iostream>
#include<string>
#include"worker.h"

class Manager :public Worker
{
public:
	Manager(int id, string name, int dId);
	virtual void showInfo();
	virtual string getDeptName();

};