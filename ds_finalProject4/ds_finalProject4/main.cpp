// 1.	���� ������Ʈ���� �ڷᱸ���� ¥���� ������,
//		Tree ��ü�� InsertItem �Ǵ� DeleteItem ���� �Ͽ� ���Ұ� �ٲ��, preQue, inQue, postQue ��� ��������� ��!!!
// 2.	
/////////////////////////////////////////////////////////////////////////////
#include "DbManager_.h"



int main()
{
	Tree<ItemType> T1;

	string command;
	string dataLine;
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
	cout << endl;
	cout << endl;
	cout << endl;



	// ���������� string DB �˻� ���α׷��� ����.
	ofstream outFile1("out1.txt");		// ���� ã�� ���ڿ��� �����ϴ� �ؽ�Ʈ ����.
	ofstream garbage("garbage.txt");	//�׳� cout���θ� ����ϰ� ���� ��, ofstream���� ��µǴ� ���� �Ѱ��� ��� ����Ͽ�, ������ ���� ��� ���Ͻ�Ʈ��.
	
		//Test codes
	T1.Print(garbage);
	cout << endl;
	garbage << endl;
	T1.Print_Reverse(garbage);
	cout << endl;
	garbage << endl;
	



	return 0;
}