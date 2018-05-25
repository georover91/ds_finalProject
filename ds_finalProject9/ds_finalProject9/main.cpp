// 1.	���� ������Ʈ���� �ڷᱸ���� ¥���� ������,
//		Tree ��ü�� InsertItem �Ǵ� DeleteItem ���� �Ͽ� ���Ұ� �ٲ��, preQue, inQue, postQue ��� ��������� ��!!!
// 2.	
/////////////////////////////////////////////////////////////////////////////
#include "DbManager_.h"



int main()
{
	//������Ʈ ���� ����.
	Tree<ItemType> T1;

	string command;
	ItemType dataLine;
	int numCommands;
	int numData;

	ifstream inFile1("in1.txt");	//�ʱ� ������ ���̽��� ����(�ʱ�DB��������) �ϳ����� �о�� ����.
	numCommands = 0;
	numData = 0;
	if (!inFile1.is_open()) {
		cout << "������ ���̽��� ������ ������ �� �� �����ϴ�." << endl;
	}
	else {
		getline(inFile1, command);	// '�ʱ�DB��������'�� �� ���� ������� �޾ƿ�.
		while (command != "Quit")
		{
			if (command == "InsertStrings") {
				getline(inFile1, dataLine);
				T1.InsertItem(dataLine);
				numData++;
				cout << numData << "th dataLine input: " << dataLine << endl;
				numCommands++;
				cout << numCommands << "th command  input: " << command << " completed." << endl;
			}
			//else if () {
			//
			//}
			else {
				getline(inFile1, dataLine);
				dataLine = "\0";
				numData++;
				cout << numData << "th dataLine input: " << "Nullified!" << endl;
				numCommands++;
				command = "Command Error!";
				cout << numCommands << "th command  input: " << command << endl;
			}

			getline(inFile1, command);
		};
		inFile1.close();
	}

	ofstream outFile1("out1.txt");		// ���� ã�� ���ڿ��� �����ϴ� �ؽ�Ʈ ����.
	ofstream garbage("garbage.txt");	//�׳� cout���θ� ����ϰ� ���� ��, ofstream���� ��µǴ� ���� �Ѱ��� ��� ����Ͽ�, ������ ���� ��� ���Ͻ�Ʈ��.

	cout << endl;
	T1.Print(garbage);
	cout << endl;


	
	// ���������� string DB �˻� ���α׷��� ����.
	DbManager<ItemType> DbM(T1);

	cout << endl;
	cout << "���α׷� �������� �Է��ϼ���: ";
	getline(cin, DbM.command);
	// (command�� history�� ������ �ʿ����. ���� command�� ������ backStack �Ǵ� forwardStack�� ���� �ʿ�� ����.)
	while (DbM.command != "Quit")
	{
		if (DbM.command == "go back") {
			DbM.goBackward();

			cout << endl;
			DbM.Print_myCurrDb(garbage);
			cout << endl;
		}
		else if (DbM.command == "go forward") {
			DbM.goForward();

			cout << endl;
			DbM.Print_myCurrDb(garbage);
			cout << endl;
		}
		else if (DbM.command == "search") {
			cout << "�˻� �����ڸ� �Է��ϼ���: ";
			getline(cin, DbM.oper);
			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);
			DbM.Search_in_myCurrDb();

			cout << endl;
			DbM.Print_myCurrDb(garbage);
			cout << endl;
		}
		//else if () {
		//
		//}
		else {
			
		}

		cout << "���α׷� �������� �Է��ϼ���: ";
		getline(cin, DbM.command);
	};




	



	// �������̾��� string DB �˻� ���α׷��� ���� ����.
	// ������Ʈ ���� ��.



	/* //�ʱ�DB�������� �� �������� Test ����.
	T1.Print(garbage);
	cout << endl;
	garbage << endl;
	T1.Print_Reverse(garbage);
	cout << endl;
	garbage << endl;
	*/ ////�ʱ�DB�������� �� �������� Test ��.



	/* //TreeType�� merge�Լ� Test ����.
	ofstream outFile("garbage.txt");

	Tree<ItemType> tem1;
	tem1.InsertItem("a");
	tem1.InsertItem("b");
	tem1.InsertItem("c");
	tem1.Print(outFile);
	cout << endl;

	Tree<ItemType> tem2;
	tem2.InsertItem("d");
	tem2.InsertItem("e");
	tem2.InsertItem("f");
	tem2.Print(outFile);
	cout << endl;
	
	Tree<ItemType> tem3;
	tem1.Merge(tem2);
	tem3 = tem1;
	tem3.Print(outFile);
	*/ //TreeType�� merge�Լ� Test ��.

	return 0;
}