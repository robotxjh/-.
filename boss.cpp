#include<iostream>
#include<string>
#include"boss.h"

Boss::Boss(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_DeptId = dId;
	this->m_Name = name;
}

void Boss::showInfo()
{
	cout << "职工编号：" << this->m_Id 
		<< "\t职工姓名：" << this->m_Name 
		<< "\t岗位：" << this->getDeptName()
		<< "\t员工职责：" << "给经理下发任务" << endl;
}

string Boss::getDeptName()
{
	return("老板");
}