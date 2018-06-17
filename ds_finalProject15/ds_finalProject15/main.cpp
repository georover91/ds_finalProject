// 1.	���� ������Ʈ���� �ڷᱸ���� ¥���� ������,
//		Tree ��ü�� InsertItem �Ǵ� DeleteItem ���� �Ͽ� ���Ұ� �ٲ��, preQue, inQue, postQue ��� ��������� ��!!!
// 2.	�Լ� ������ ����� ���ϰ�, ���� ������� ¥��, �����Ϸ��� �� �Լ� ���� ������ �´��� ����� üũ�� �����ش�.
// 3.	
/////////////////////////////////////////////////////////////////////////////
#include "DbManager_.h"

void OpenFile_and_InitializeFromFile(DbManager<ItemType>& DbM);

int main()
{
	//instanciating Database Manager class. 
	DbManager<ItemType> DbM;

	// ����� ���� ������ ����.
	string what = "search screen";
	printTo pt = CONSOLE_;
	printDirection pd = NONE_;
	printWithNum pwn= NONE__;

	//�Է����Ϸ� �˻����� �ʱ� �����ͺ��̽� ����.
	OpenFile_and_InitializeFromFile(DbM);
	cout << endl;
	DbM.Print_SearchScreen(pt, pd, pwn);

	// ���������� string DB �˻� ���α׷��� ����.
	DbM.Input_command();

	while (DbM.command != "Quit")
	{
		if (DbM.command == "go back") {
			DbM.goBackward();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "go forward") {
			DbM.goForward();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "search") {
			while (1) {
				cout << "�˻� �����ڸ� �Է��ϼ���: ";
				getline(cin, DbM.oper);
				if ((DbM.oper == "and") || (DbM.oper == "or") || (DbM.oper == "not") || (DbM.oper == "and not") || (DbM.oper == "or not") || (DbM.oper == "all data")) {
					break;
				}
			}
			
			if (DbM.oper != "all data") {
				cout << "�˻� Ű���带 �Է��ϼ���: ";
				getline(cin, DbM.key);

				DbM.Search();
				cout << endl;
				DbM.Print_SearchScreen(pt, pd, pwn);
			}
			else {
				DbM.allData();
				cout << endl;
				DbM.Print_SearchScreen(pt, pd, pwn);
			}
		
		}
		else if (DbM.command == "and") {
			DbM.oper = "and";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "or") {
			DbM.oper = "or";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "not") {
			DbM.oper = "not";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "and not") {
			DbM.oper = "and not";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "or not") {
			DbM.oper = "or not";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "all data") {
			DbM.allData();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "initialize") {
			OpenFile_and_InitializeFromFile(DbM);
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "print") {
			DbM.Print_Settings(what, pt, pd, pwn);
			
			if ((what == "search screen") || (what == "screen")) {
				cout << endl;
				DbM.Print_SearchScreen(pt, pd, pwn);
			}
			else if ((what == "search route") || (what == "route")) {
				cout << endl;
				DbM.Print_SearchRoute(pt);
			}
			else if ((what == "search data") || (what == "data")) {
				cout << endl;
				DbM.Print_SearchDb(pt, pd, pwn);
			}

			cout << endl;
			//��� ����� �� �����ϸ�, ��� �ɼ� �� pt�� console�� ����ϴ� �������� �ʱ�ȭ.
			what = "search screen";
			pt = CONSOLE_;
		}
		else if (DbM.command == "select") {

		}

		DbM.Input_command();
	};
	



	/*
	// Tree ��ü�� operator==, operator!= �����ε��� �� test�ϱ� ���� code.
	Tree<ItemType> T1;
	T1.InsertItem("hello");
	T1.InsertItem("world");
	T1.InsertItem("z");

	Tree<ItemType> T2;
	T2.InsertItem("hello");
	T2.InsertItem("world");
	T2.InsertItem("z");

	cout << (bool)(T1 != T2) << endl;
	*/


	
	return 0;
}



void OpenFile_and_InitializeFromFile(DbManager<ItemType>& DbM)
{
	//�Է����Ϸ� �˻����� �ʱ� �����ͺ��̽� ����.
	string inputFileName;
	cout << "�˻����� �ʱ� �����ͺ��̽��� ������ �Է������� �̸��� �Է��ϼ���: ";
	getline(cin, inputFileName);
	//cout << endl;

	ifstream inFile(inputFileName.c_str());	//�ʱ� ������ ���̽��� ����(�ʱ�DB��������) �ϳ����� �о�� ����.
	if (!inFile.is_open()) {
		cout << "������ ���̽��� ������ ������ �� �� �����ϴ�." << endl;
		exit(1);
	}

	DbM.Initialize(inFile);	//

	inFile.seekg(0, ios::beg);		// ���� �б� �����ϴ� ��ġ �ʱ�ȭ . �̰� �����ָ�, ������ �ٽ� ���� �̸��� ���� ��� ������, �� ������ ������ ������, ���� �� ���� �κк��� �о ������.
	inFile.close();
}