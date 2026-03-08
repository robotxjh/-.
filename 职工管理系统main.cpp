#include<iostream>
#include<string>
#include"WorkerManager.h"
using namespace std;

int main()
{
	WorkerManager wm;
	int choice = 0;
	while (true)
	{
		wm.Show_Menu();
		cout << "请输入所选择菜单的数字：";
		cin >> choice;
		switch (choice)
		{
		case 0: //退出系统
			wm.ExitSystem();
			break;
		case 1://添加职工
			wm.Add_Emp();
			break;
		case 2://显示职工
			wm.show_Emp();
			break;
		case 3://删除职工
			wm.Del_Emp();
			break;
		case 4://修改职工
			wm.mod_Emp();
			break;
		case 5://查找职工
			wm.find_Emp();
			break;
		case 6://排序职工
			wm.sort_Emp();
			break;
		case 7://清空文件
			wm.clean_File();
			break;
		default:
			cout << "输入错误，请重新输入" << endl;
			system("pause");
			system("cls");
		}
	}
	return 0;
}