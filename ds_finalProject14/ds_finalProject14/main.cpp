// 1.	���� ������Ʈ���� �ڷᱸ���� ¥���� ������,
//		Tree ��ü�� InsertItem �Ǵ� DeleteItem ���� �Ͽ� ���Ұ� �ٲ��, preQue, inQue, postQue ��� ��������� ��!!!
// 2.	
/////////////////////////////////////////////////////////////////////////////
#include "DbManager_.h"

void OpenFile_and_Initialize(DbManager<ItemType>& DbM);

int main()
{
	DbManager<ItemType> DbM;

	//�Է����Ϸ� �˻����� �ʱ� �����ͺ��̽� ����.
	OpenFile_and_Initialize(DbM);
	DbM.Print_Nth_Search();

	// ���������� string DB �˻� ���α׷��� ����.
	DbM.Input_command();

	while (DbM.command != "Quit")
	{
		if (DbM.command == "go back") {
			DbM.goBackward();
			DbM.Print_Nth_Search();
		}
		else if (DbM.command == "go forward") {
			DbM.goForward();
			DbM.Print_Nth_Search();
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
				DbM.Print_Nth_Search();
			}
			else {
				DbM.allData();
				DbM.Print_Nth_Search();
			}
		
		}
		else if (DbM.command == "and") {
			DbM.oper = "and";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			DbM.Print_Nth_Search();
		}
		else if (DbM.command == "or") {
			DbM.oper = "or";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			DbM.Print_Nth_Search();
		}
		else if (DbM.command == "not") {
			DbM.oper = "not";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			DbM.Print_Nth_Search();
		}
		else if (DbM.command == "and not") {
			DbM.oper = "and not";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			DbM.Print_Nth_Search();
		}
		else if (DbM.command == "or not") {
			DbM.oper = "or not";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			DbM.Print_Nth_Search();
		}
		else if (DbM.command == "all data") {
			DbM.allData();
			DbM.Print_Nth_Search();
		}
		else if (DbM.command == "initialize") {
			OpenFile_and_Initialize(DbM);
			DbM.Print_Nth_Search();
		}
		else if (DbM.command == "print") {
			DbM.Print_Nth_Search();
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



void OpenFile_and_Initialize(DbManager<ItemType>& DbM)
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