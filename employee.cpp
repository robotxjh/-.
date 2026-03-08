#include<iostream>
#include<string>
#include"employee.h"

Employee::Employee(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_DeptId = dId;
	this->m_Name = name;
};
void Employee::showInfo()
{
	cout << "员工编号：" << this->m_Id 
	<< "\t员工姓名：" << this->m_Name 
	<< "\t岗位：" << this->getDeptName()
	<< "\t岗位职责：完成经理交给的任务" << endl;
}

string Employee::getDeptName()
{
	return("员工");
}

