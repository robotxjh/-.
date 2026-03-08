#pragma once
#include<iostream>
#include"Worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>

#define FILENAME "empfile.txt"


class WorkerManager
{
public:
	WorkerManager();

	//展示菜单函数
	void Show_Menu();
	//退出系统
	void ExitSystem();

	//记录职工人数
	int m_EmpNum = 0;
	//职工数组指针
	Worker** m_EmpArray = nullptr;
	//添加职工
	void Add_Emp();
	//保存文件
	void save();
	//文件是否为空
	bool m_FileIsEmpty;
	//统计文件是否为空
	int get_EmpNum();
	//初始化员工
	void Init_Emp();
	//显示员工
	void show_Emp();
	//删除职工
	void Del_Emp();
	//判断职工是否存在，如果存在返回职工数组中的位置，不存在返回-1
	int IsExist(int id);
	//修改职工
	void mod_Emp();
	//查找职工
	void find_Emp();
	//获取职工编号
	int get_EmpId(int id);//职工存在返回id，不存在或者文件为空返回-1
	//员工排序
	void sort_Emp();
	//清空文件
	void clean_File();

	~WorkerManager();

};