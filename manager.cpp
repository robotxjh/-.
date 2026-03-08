#include<iostream>
#include<string>
#include"manager.h"

Manager::Manager(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_DeptId = dId;
	this->m_Name = name;
}
void Manager::showInfo()
{
	cout << "职工编号：" << this->m_Id
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" << this->getDeptName()
		<< "\t员工职责：" << "完成老板下发的任务，给员工分配任务" << endl;
}

string Manager::getDeptName()
{
	return("经理");
}

