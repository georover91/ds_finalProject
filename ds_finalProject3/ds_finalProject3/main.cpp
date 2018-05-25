// 1.	현재 프로젝트에서 자료구조를 짜놓은 구조상,
//		Tree 객체에 InsertItem 또는 DeleteItem 등을 하여 원소가 바뀌면, preQue, inQue, postQue 모두 갱신해줘야 함!!!
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

	

	ifstream inFile1("in1.txt");	//초기 데이터 베이스는 파일(초기DB구성파일) 하나에서 읽어와 구성.
	numCommands = 0;
	numData = 0;
	if (!inFile1.is_open()) {
		cout << "데이터 베이스를 구성할 파일을 열 수 없습니다." << endl;
	}
	else {
		getline(inFile1, command);	// '초기DB구성파일'의 한 줄을 명령으로 받아옴.
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



	// 본격적으로 string DB 검색 프로그램을 실행.
	ofstream outFile1("out1.txt");		// 내가 찾은 문자열을 저장하는 텍스트 파일.
	ofstream garbage("garbage.txt");	//그냥 cout으로만 출력하고 싶을 때, ofstream으로 출력되는 값을 한곳에 모아 출력하여, 버릴때 쓰는 출력 파일스트림.
	
		//Test codes
	T1.Print(garbage);
	cout << endl;
	garbage << endl;
	T1.Print_Reverse(garbage);
	cout << endl;
	garbage << endl;
	



	return 0;
}