#include "DbManager_.h"



int main()
{
	DbManager<ItemType> DB1;

	string command;
	string dataLine;
	int numCommands;
	int numData;

	

	//�ʱ� ������ ���̽��� ����(�ʱ�DB��������) �ϳ����� �о�� ����.
	ifstream inFile1("in1.txt");
	getline(inFile1, command);	// '�ʱ�DB��������'�� �� ���� ������� �޾ƿ�.
	numCommands = 0;
	numData = 0;
	while (command != "Quit")
	{
		if (command == "InsertStrings") {
			getline(inFile1, dataLine);
			cout << "dataLine: " << dataLine << endl;
			DB1.InsertItem(dataLine);
			numData++;
		}
		//else if () {
		//
		//}
		else {

		}

		numCommands++;
		cout << "Command input number " << numCommands << ": " << command << " completed."<< endl;
		getline(inFile1, command);
	};
	cout << endl;
	cout << endl;
	cout << endl;



	// ���������� string DB �˻� ���α׷��� ����.
	ofstream outFile1("out1.txt");		// ���� ã�� ���ڿ��� �����ϴ� �ؽ�Ʈ ����.
	ofstream garbage("garbage.txt");	//�׳� cout���θ� ����ϰ� ���� ��, ofstream���� ��µǴ� ���� �Ѱ��� ��� ����Ͽ�, ������ ���� ��� ���Ͻ�Ʈ��.
	DB1.Print(garbage);
	cout << endl;
	garbage << endl;
	DB1.Print_Reverse(garbage);
	cout << endl;
	garbage << endl;



	return 0;
}