#include<iostream>
#include<string>
#include"WorkerManager.h"
#include<fstream>


WorkerManager::WorkerManager()
{
	//文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}
	
	//文件存在 数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}
	//3.文件存在，并且记录数据
	int num = this->get_EmpNum();
	//cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;

	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->Init_Emp();

	//for (int i = 0; i < m_EmpNum; i++)
	//{
	//	cout << "员工编号：" << this->m_EmpArray[i]->m_Id 
	//	 << "\t 员工姓名：" << this->m_EmpArray[i]->m_Name 
	//	 << "\t 所属部门：" << this->m_EmpArray[i]->m_DeptId << endl;
	//}
}
//展示菜单函数
void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//退出系统
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	exit(0);
}

//获取已有职工编号
int WorkerManager::get_EmpId(int id = 0)
{
	
	if (!this->m_FileIsEmpty && m_EmpNum == 0)
	{
		return -1;
	}
	else
	{ 
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (id == this->m_EmpArray[i]->m_Id)
			{
				return id;
			}
			
		}
		return -1;
		
	}
	
}

//增加职工
void WorkerManager::Add_Emp()
{
	int AddNum = 0;
	cout << "请输入要添加的人数:" << endl;
	cin >> AddNum;
	if (AddNum > 0)
	{
		int newsize = this->m_EmpNum + AddNum;
		//开辟新空间
		Worker** newSpace = new Worker * [newsize];
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < m_EmpNum; i++)
			{
				newSpace[i] = m_EmpArray[i];
			}
		}
		//添加新数据
		for (int i = 0; i < AddNum; i++)
		{
			int id = 0;
			bool idValid = true;
			while (idValid)
			{
				cout << "请输入新职工的编号：" << endl;
				cin >> id;

				// 检查编号是否已存在
				if (this->get_EmpId(id) == -1)  // get_EmpId返回-1表示编号不存在
				{
					idValid = false;
				}
				else
				{
					cout << "该编号员工已存在，请重新输入" << endl;
				}
			}						
			string name;
			int dSelect = 0;
			cout << "新职工的名字：" << endl;
			cin >> name;
			cout << "请选择新职工的岗位：" << endl;
			cout << "1、员工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				cout << "输入有误，请重新输入" << endl;
				i--;
				continue;
			}
			if (worker != NULL)
			{
				newSpace[this->m_EmpNum + i] = worker;
			}
		}
		//释放原有空间
		if (m_EmpArray != NULL)
		{
			delete[] m_EmpArray;
		}
		//更新空间指向
		this->m_EmpArray = newSpace;
		//更新职工人数
		this->m_EmpNum = newsize;
		this->m_FileIsEmpty = false;
		cout << "成功添加 " << AddNum << " 名新职工" << endl;
		cout << "职工人数：" << this->m_EmpNum << endl;

		this->save();
		system("pause");
		system("cls");
	}
	else
	{
		cout << "输入错误，请重新输入" << endl;
		system("pause");
		system("cls");
	}
}
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			ofs << this->m_EmpArray[i]->m_Id << " "
				<< this->m_EmpArray[i]->m_Name << " "
				<< this->m_EmpArray[i]->m_DeptId << endl;
		}
		ofs.close();

}
//统计文件中人数
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//统计人数变量
		num++;
	}
	ifs.close();
	return num;

}
//初始化员工
void WorkerManager::Init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if(dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else if(dId == 3)
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

//显示员工
void WorkerManager::show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或不为空" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}system("pause");
	system("cls");
}

//删除职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者为空" << endl;
	}
	else
	{
		cout << "输入想要删除的员工编号：" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);
		cout << index << endl;
		string name;
		for (int i = index; i < this->m_EmpNum - 1; i++)
		{
			name = this->m_EmpArray[i]->m_Name ;
		}
		cout << "确定要删除职工" << name << endl;
		cout << "1、删除     2、不删除" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			if (index != -1)
			{

				for (int i = index; i < this->m_EmpNum - 1; i++)
				{
					this->m_EmpArray[i] = this->m_EmpArray[i + 1];
				}
				this->m_EmpNum--;
				this->save();
				cout << "删除成功" << endl;
			}
			else
			{
				cout << "员工不存在" << endl;
			}
		}
		else
		{
			cout << "取消删除" << endl;

		}
		
	}

	system("pause");
	system("cls");
}
//判断职工是否存在，如果存在返回职工数组中的位置，不存在返回-1
int WorkerManager::IsExist(int id)

{
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//找到职工
			index = i;
			break;
		}
	}
	return index;
}

//修改职工
void WorkerManager::mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件为空或者不存在" << endl;
	}
	else
	{
		int id = 0;
		cout << "请输入要修改职工的id" << endl;
		cin >> id;
		int ret = this->IsExist(id);
		cout << ret;
		if (ret != -1)
		{
			int newid = 0;
			string newname = "";
			int newdid = 0;
			//delete[] m_EmpArray[ret];
			cout << "请输入员工新id:" << endl;
			cin >> newid;
			cout << "请输入员工姓名:" << endl;
			cin >> newname;
			cout << "请选择员工新部门编号:" << endl;
			cout << "1、普通员工" << endl <<
				"2、经理" << endl <<
				"3、老板" << endl;

			cin >> newdid;
			delete this->m_EmpArray[ret];
			Worker* worker = NULL;

			switch (newdid)
			{
			case 1:
				worker = new Employee(newid, newname, newdid);
				break;
			case 2:
				worker = new Manager(newid, newname, newdid);
				break;
			case 3:
				worker = new Boss(newid, newname, newdid);
				break;
			default:
				break;

			}
			this->m_EmpArray[ret] = worker;
			this->save();
			cout << "修改编号为" << newid << "的员工 信息成功" << endl;
		}
		else
		{
			cout << "未找到员工" << endl;
		}
	}
	system("pause");
	system("cls");
	
}

//查找职工
void WorkerManager::find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件为空或者文件不存在" << endl;
	}
	else
	{
		int id = 0;
		cout << "请输入要查找的职工id:" << endl;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			cout << "职工编号:" << this->m_EmpArray[ret]->m_Id << endl
				<< "职工姓名:" << this->m_EmpArray[ret]->m_Name << endl
				<< "部门编号:" << this->m_EmpArray[ret]->m_DeptId << endl;
		}
		else
		{
			cout << "未找到编号为：" << id << " 职工" << endl;
		}
	}
	system("pause");
	system("cls");
}

//员工排序
void WorkerManager::sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序的方式" << endl;
		cout << "1、按照职工编号升序" << endl;
		cout << "2、按照职工编号降序" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i+1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//升序
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}
			//判断一开始认定 最小值或最大值 是不是 计算的最小值或最大值， 如果不是，交换数据
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
	}
	cout << "排序成功，排序后的结果为：" << endl;
	this->save();
	this->show_Emp();
}
//清空文件
void WorkerManager::clean_File()
{
	cout << "确认清空文件吗" << endl;
	cout << "1、确定     2、取消" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		//删除堆区每个职工对象
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}

			//删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
		system("pause");
		system("cls");
	}
}
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[]this->m_EmpArray;
		this->m_EmpArray = NULL;
	}

}