// 1.	현재 프로젝트에서 자료구조를 짜놓은 구조상,
//		Tree 객체에 InsertItem 또는 DeleteItem 등을 하여 원소가 바뀌면, preQue, inQue, postQue 모두 갱신해줘야 함!!!
// 2.	
/////////////////////////////////////////////////////////////////////////////
#include "DbManager_.h"



int main()
{
	//프로젝트 본문 시작.
	Tree<ItemType> T1;

	string command;
	ItemType dataLine;
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

	ofstream outFile1("out1.txt");		// 내가 찾은 문자열을 저장하는 텍스트 파일.
	ofstream garbage("garbage.txt");	//그냥 cout으로만 출력하고 싶을 때, ofstream으로 출력되는 값을 한곳에 모아 출력하여, 버릴때 쓰는 출력 파일스트림.

	cout << endl;
	T1.Print(garbage);
	cout << endl;


	
	// 본격적으로 string DB 검색 프로그램을 실행.
	DbManager<ItemType> DbM(T1);

	cout << endl;
	cout << "프로그램 실행명령을 입력하세요: ";
	getline(cin, DbM.command);
	// (command의 history를 저장할 필요없다. 따라서 command를 저장할 backStack 또는 forwardStack을 만들 필요는 없다.)
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
			cout << "검색 연산자를 입력하세요: ";
			getline(cin, DbM.oper);
			cout << "검색 키워드를 입력하세요: ";
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

		cout << "프로그램 실행명령을 입력하세요: ";
		getline(cin, DbM.command);
	};




	



	// 본격적이었던 string DB 검색 프로그램을 실행 종료.
	// 프로젝트 본문 끝.



	/* //초기DB구성파일 잘 읽혔는지 Test 시작.
	T1.Print(garbage);
	cout << endl;
	garbage << endl;
	T1.Print_Reverse(garbage);
	cout << endl;
	garbage << endl;
	*/ ////초기DB구성파일 잘 읽혔는지 Test 끝.



	/* //TreeType의 merge함수 Test 시작.
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
	*/ //TreeType의 merge함수 Test 끝.

	return 0;
}