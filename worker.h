#pragma once
#include<iostream>
using namespace std;
#include<string>

class Worker
{
public:
	string m_Name = "";
	int m_DeptId = 0;
	int m_Id = 0;

	virtual void showInfo() = 0;
	virtual string getDeptName() = 0;

};
