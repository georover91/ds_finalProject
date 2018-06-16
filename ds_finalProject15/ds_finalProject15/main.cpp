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
	printTo pt = CONSOLE_;
	printDirection pd = NONE_;
	printWithNum pwn= NONE__;

	//�Է����Ϸ� �˻����� �ʱ� �����ͺ��̽� ����.
	OpenFile_and_InitializeFromFile(DbM);
	DbM.Print_SearchScreen();

	// ���������� string DB �˻� ���α׷��� ����.
	DbM.Input_command();

	while (DbM.command != "Quit")
	{
		if (DbM.command == "go back") {
			DbM.goBackward();
			DbM.Print_SearchScreen();
		}
		else if (DbM.command == "go forward") {
			DbM.goForward();
			DbM.Print_SearchScreen();
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
				DbM.Print_SearchScreen();
			}
			else {
				DbM.allData();
				DbM.Print_SearchScreen();
			}
		
		}
		else if (DbM.command == "and") {
			DbM.oper = "and";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			DbM.Print_SearchScreen();
		}
		else if (DbM.command == "or") {
			DbM.oper = "or";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			DbM.Print_SearchScreen();
		}
		else if (DbM.command == "not") {
			DbM.oper = "not";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			DbM.Print_SearchScreen();
		}
		else if (DbM.command == "and not") {
			DbM.oper = "and not";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			DbM.Print_SearchScreen();
		}
		else if (DbM.command == "or not") {
			DbM.oper = "or not";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			DbM.Print_SearchScreen();
		}
		else if (DbM.command == "all data") {
			DbM.allData();
			DbM.Print_SearchScreen();
		}
		else if (DbM.command == "initialize") {
			OpenFile_and_InitializeFromFile(DbM);
			DbM.Print_SearchScreen();
		}
		else if (DbM.command == "print") {
			string what_ = " ";
			string PT_ = " ";
			string PD_ = " ";
			string PWN_ = " ";

			//�����Լ� ���κ����� �̵�.
			//printTo pt;
			//printDirection pd;
			//printWithNum pwn;

			while ((what_ != "search screen") && (what_ != "search route") && (what_ != "search data")) {
				cout << "������ ����ұ��?: ";
				getline(cin, what_);
			}
			
			while ((PT_ != "console") && (PT_ != "file") && (PT_ != "myWriting")) {
				cout << "��� ����ұ��?: ";
				getline(cin, PT_);
			}
			if ((PT_ == "\0") || (PT_ == "console")) {
				pt = CONSOLE_;
			}
			if (PT_ == "file") {
				pt = FILE_;
			}
			if (PT_ == "myWriting") {
				pt = MY_WRITING_;
			}			

			if (what_ != "search route") {
				while ((PD_ != "\0") && (PD_ != "in order") && (PD_ != "reverse")) {
					cout << "� ������ ����ұ��?: ";
					getline(cin, PD_);
				}
				if ((PD_ == "\0") || (PD_ == "in order")) {
					pd = NONE_;
				}
				if (PD_ == "reverse") {
					pd = REVERSE_;
				}

				while ((PWN_ != "yes") && (PWN_ != "no") && (PWN_ != "with numbering") && (PWN_ != "without numbering")) {
					cout << "��µǴ� ������ ���� ��ȣ�� �ٿ� ����ұ��?: ";
					getline(cin, PWN_);
				}
				if ((PWN_ == "yes") || (PWN_ == "with numbering")) {
					pwn = WITH_NUM_;
				}
				if ((PWN_ == "\0") || (PWN_ == "no") || (PWN_ == "without numbering")) {
					pwn = NONE__;
				}
			}
			
			if (what_ == "search screen") {
				DbM.Print_SearchScreen(pt, pd, pwn);
			}
			else if (what_ == "search route") {
				DbM.Print_SearchRoute(pt);
			}
			else if (what_ == "search data") {
				DbM.Print_SearchDb(pt, pd, pwn);
			}

			//��� ����� �� �����ϸ�, ��� �ɼ� �� pt�� console�� ����ϴ� �������� �ʱ�ȭ.
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
	cout << endl;

	ifstream inFile(inputFileName.c_str());	//�ʱ� ������ ���̽��� ����(�ʱ�DB��������) �ϳ����� �о�� ����.
	if (!inFile.is_open()) {
		cout << "������ ���̽��� ������ ������ �� �� �����ϴ�." << endl;
		exit(1);
	}

	DbM.Initialize(inFile);	//

	inFile.seekg(0, ios::beg);		// ���� �б� �����ϴ� ��ġ �ʱ�ȭ . �̰� �����ָ�, ������ �ٽ� ���� �̸��� ���� ��� ������, �� ������ ������ ������, ���� �� ���� �κк��� �о ������.
	inFile.close();
}