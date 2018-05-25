#include "DbManager_.h"



int main()
{
	DbManager<ItemType> DB1;

	string command;
	string dataLine;
	int numCommands;
	int numData;

	

	//초기 데이터 베이스는 파일(초기DB구성파일) 하나에서 읽어와 구성.
	ifstream inFile1("in1.txt");
	getline(inFile1, command);	// '초기DB구성파일'의 한 줄을 명령으로 받아옴.
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



	// 본격적으로 string DB 검색 프로그램을 실행.
	ofstream outFile1("out1.txt");		// 내가 찾은 문자열을 저장하는 텍스트 파일.
	ofstream garbage("garbage.txt");	//그냥 cout으로만 출력하고 싶을 때, ofstream으로 출력되는 값을 한곳에 모아 출력하여, 버릴때 쓰는 출력 파일스트림.
	DB1.Print(garbage);
	cout << endl;
	garbage << endl;
	DB1.Print_Reverse(garbage);
	cout << endl;
	garbage << endl;



	return 0;
}