// 1.	현재 프로젝트에서 자료구조를 짜놓은 구조상,
//		Tree 객체에 InsertItem 또는 DeleteItem 등을 하여 원소가 바뀌면, preQue, inQue, postQue 모두 갱신해줘야 함!!!
// 2.	
/////////////////////////////////////////////////////////////////////////////
#include "DbManager_.h"



int main()
{
	//프로젝트 본문 시작.
	Tree<ItemType> T1;

	string command_data;
	//int numCommands;
	int numData;

	ifstream inFile("in.txt");	//초기 데이터 베이스는 파일(초기DB구성파일) 하나에서 읽어와 구성.
	//numCommands = 0;
	numData = 0;
	if (!inFile.is_open()) {
		cout << "데이터 베이스를 구성할 파일을 열 수 없습니다." << endl;
	}
	else {
		getline(inFile, command_data);	// '초기DB구성파일'의 한 줄을 명령으로 받아옴.
		if (command_data == "InsertStrings") {
			getline(inFile, command_data);
			while (command_data != "Quit") {	// 입력파일의 입력문장들을 하나씩 게속 읽어들인다.
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

	ofstream outFile("out.txt");		// 내가 찾은 문자열을 저장하는 텍스트 파일.
	ofstream garbage("garbage.txt");	//그냥 cout으로만 출력하고 싶을 때, ofstream으로 출력되는 값을 한곳에 모아 출력하여, 버릴때 쓰는 출력 파일스트림.

	cout << endl;
	cout << "<<<" << "초기 데이터 베이스(0번째 검색)." << ">>>" << endl;
	T1.Print(garbage);
	cout << endl;


	
	// 본격적으로 string DB 검색 프로그램을 실행.
	DbManager<ItemType> DbM(T1);

	cout << endl;
	cout << endl;
	DbM.cumNum++;
	cout << "<<<" << DbM.cumNum << "번째 명령." << ">>>" << endl;
	cout << "프로그램 실행명령을 입력하세요: ";
	getline(cin, DbM.command);
	// (command의 history를 저장할 필요없다. 따라서 command를 저장할 backStack, forwardStack 또는 DoubleLL을 만들 필요는 없다.)

	while (DbM.command != "Quit")
	{
		if (DbM.command == "go back") {
			DbM.goBackward();

			cout << endl;
			cout << "<<<" << DbM.searchNum << "번째 검색." << ">>>" << endl;
			DbM.Print_myCurrDb();
			cout << endl;
		}
		else if (DbM.command == "go forward") {
			DbM.goForward();

			cout << endl;
			cout << "<<<" << DbM.searchNum << "번째 검색." << ">>>" << endl;
			DbM.Print_myCurrDb();
			cout << endl;
		}
		else if (DbM.command == "search") {
			while (1) {
				cout << "검색 연산자를 입력하세요: ";
				getline(cin, DbM.oper);
				if ((DbM.oper == "and") || (DbM.oper == "or") || (DbM.oper == "not") || (DbM.oper == "and not") || (DbM.oper == "or not")) {
					break;
				}
			}
			
			cout << "검색 키워드를 입력하세요: ";
			getline(cin, DbM.key);
			
			DbM.Search();

			cout << endl;
			cout << "<<<" << DbM.searchNum << "번째 검색." << ">>>" << endl;
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
		cout << "<<<" << DbM.cumNum << "번째 명령." << ">>>" << endl;
		cout << "프로그램 실행명령을 입력하세요: ";
		getline(cin, DbM.command);
	};



	return 0;
}