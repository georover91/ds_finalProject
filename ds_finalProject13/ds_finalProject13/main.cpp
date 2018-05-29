// 1.	���� ������Ʈ���� �ڷᱸ���� ¥���� ������,
//		Tree ��ü�� InsertItem �Ǵ� DeleteItem ���� �Ͽ� ���Ұ� �ٲ��, preQue, inQue, postQue ��� ��������� ��!!!
// 2.	
/////////////////////////////////////////////////////////////////////////////
#include "DbManager_.h"



int main()
{
	//������Ʈ ���� ����.
	ifstream inFile("in.txt");	//�ʱ� ������ ���̽��� ����(�ʱ�DB��������) �ϳ����� �о�� ����.
	if (!inFile.is_open()) {
		cout << "������ ���̽��� ������ ������ �� �� �����ϴ�." << endl;
		return 0;
	}
	//else {
		DbManager<ItemType> DbM(inFile);
		DbM.Print_Nth_Search();
		inFile.close();
	//}
	
	ofstream outFile("out.txt");		// ���� ã�� ���ڿ��� �����ϴ� �ؽ�Ʈ ����.
	ofstream garbage("garbage.txt");	//�׳� cout���θ� ����ϰ� ���� ��, ofstream���� ��µǴ� ���� �Ѱ��� ��� ����Ͽ�, ������ ���� ��� ���Ͻ�Ʈ��.

	//cout << endl;
	//cout << "<<<" << "�ʱ� ������ ���̽�(0��° �˻�)." << ">>>" << endl;
	//T1.Print(garbage);
	//cout << endl;


	
	// ���������� string DB �˻� ���α׷��� ����.
	cout << endl;
	cout << endl;
	DbM.cumNum++;
	cout << "<<<" << DbM.cumNum << "��° ���." << ">>>" << endl;
	cout << "���α׷� �������� �Է��ϼ���: ";
	getline(cin, DbM.command);
	// (command�� history�� ������ �ʿ����. ���� command�� ������ backStack, forwardStack �Ǵ� DoubleLL�� ���� �ʿ�� ����.)

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
			DbM.Initailize();
		}
		else if (DbM.command == "select") {

		}
		else if (DbM.command == "print") {

		}

		cout << endl;
		cout << endl;
		DbM.cumNum++;
		cout << "<<<" << DbM.cumNum << "��° ���." << ">>>" << endl;
		cout << "���α׷� �������� �Է��ϼ���: ";
		getline(cin, DbM.command);
	};



	return 0;
}