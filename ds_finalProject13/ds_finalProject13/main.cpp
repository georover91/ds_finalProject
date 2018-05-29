// 1.	���� ������Ʈ���� �ڷᱸ���� ¥���� ������,
//		Tree ��ü�� InsertItem �Ǵ� DeleteItem ���� �Ͽ� ���Ұ� �ٲ��, preQue, inQue, postQue ��� ��������� ��!!!
// 2.	
/////////////////////////////////////////////////////////////////////////////
#include "DbManager_.h"



int main()
{
	//�Է����Ϸ� �˻����� �ʱ� �����ͺ��̽� ����.
	string inputFileName;
	cout << "�˻����� �ʱ� �����ͺ��̽��� ������ �Է������� �̸��� �Է��ϼ���: ";
	getline(cin, inputFileName);
	cout << endl;

	ifstream inFile(inputFileName.c_str());	//�ʱ� ������ ���̽��� ����(�ʱ�DB��������) �ϳ����� �о�� ����.
	if (!inFile.is_open()) {
		cout << "������ ���̽��� ������ ������ �� �� �����ϴ�." << endl;
		return 0;
	}

	DbManager<ItemType> DbM(inFile);
	DbM.Print_Nth_Search();
	inFile.close();


	
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
			
			if (DbM.oper == "all data") {
				DbM.allData();
				DbM.Print_Nth_Search();
			}
			else {
				cout << "�˻� Ű���带 �Է��ϼ���: ";
				getline(cin, DbM.key);

				DbM.Search();
				DbM.Print_Nth_Search();
			}
		
		}
		else if (DbM.command == "all data") {
			DbM.allData();
			DbM.Print_Nth_Search();
		}
		else if (DbM.command == "initialize") {
			DbM.Initailize(inFile);
			DbM.Print_Nth_Search();
		}
		else if (DbM.command == "select") {

		}
		else if (DbM.command == "print") {

		}

		DbM.Input_command();
	};

	inFile.close();
	


	return 0;
}