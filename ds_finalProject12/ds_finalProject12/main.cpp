// 1.	���� ������Ʈ���� �ڷᱸ���� ¥���� ������,
//		Tree ��ü�� InsertItem �Ǵ� DeleteItem ���� �Ͽ� ���Ұ� �ٲ��, preQue, inQue, postQue ��� ��������� ��!!!
// 2.	
/////////////////////////////////////////////////////////////////////////////
#include "DbManager_.h"



int main()
{
	//������Ʈ ���� ����.
	Tree<ItemType> T1;

	string command_data;
	//int numCommands;
	int numData;

	ifstream inFile("in.txt");	//�ʱ� ������ ���̽��� ����(�ʱ�DB��������) �ϳ����� �о�� ����.
	//numCommands = 0;
	numData = 0;
	if (!inFile.is_open()) {
		cout << "������ ���̽��� ������ ������ �� �� �����ϴ�." << endl;
	}
	else {
		getline(inFile, command_data);	// '�ʱ�DB��������'�� �� ���� ������� �޾ƿ�.
		if (command_data == "InsertStrings") {
			getline(inFile, command_data);
			while (command_data != "Quit") {	// �Է������� �Է¹������ �ϳ��� �Լ� �о���δ�.
				T1.InsertItem(command_data);
				numData++;
				cout << numData << "th data has been inputed: " << command_data << endl;
				getline(inFile, command_data);
			}
		}
		else {
			cout << "Command Error. or Data Error." << endl;
		}
		
		inFile.close();
	}

	ofstream outFile("out.txt");		// ���� ã�� ���ڿ��� �����ϴ� �ؽ�Ʈ ����.
	ofstream garbage("garbage.txt");	//�׳� cout���θ� ����ϰ� ���� ��, ofstream���� ��µǴ� ���� �Ѱ��� ��� ����Ͽ�, ������ ���� ��� ���Ͻ�Ʈ��.

	cout << endl;
	cout << "<<<" << "�ʱ� ������ ���̽�(0��° �˻�)." << ">>>" << endl;
	T1.Print(garbage);
	cout << endl;


	
	// ���������� string DB �˻� ���α׷��� ����.
	DbManager<ItemType> DbM(T1);

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

			cout << endl;
			cout << "<<<" << DbM.searchNum << "��° �˻�." << ">>>" << endl;
			DbM.Print_myCurrDb();
			cout << endl;
		}
		else if (DbM.command == "go forward") {
			DbM.goForward();

			cout << endl;
			cout << "<<<" << DbM.searchNum << "��° �˻�." << ">>>" << endl;
			DbM.Print_myCurrDb();
			cout << endl;
		}
		else if (DbM.command == "search") {
			while (1) {
				cout << "�˻� �����ڸ� �Է��ϼ���: ";
				getline(cin, DbM.oper);
				if ((DbM.oper == "and") || (DbM.oper == "or") || (DbM.oper == "not") || (DbM.oper == "and not") || (DbM.oper == "or not")) {
					break;
				}
			}
			
			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);
			
			DbM.Search();

			cout << endl;
			cout << "<<<" << DbM.searchNum << "��° �˻�." << ">>>" << endl;
			DbM.Print_myCurrDb();
			cout << endl;
		}
		else if (DbM.command == "all data") {

		}
		else if (DbM.command == "initialize") {

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