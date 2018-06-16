// 1.	현재 프로젝트에서 자료구조를 짜놓은 구조상,
//		Tree 객체에 InsertItem 또는 DeleteItem 등을 하여 원소가 바뀌면, preQue, inQue, postQue 모두 갱신해줘야 함!!!
// 2.	
/////////////////////////////////////////////////////////////////////////////
#include "DbManager_.h"

void OpenFile_and_Initialize(DbManager<ItemType>& DbM);

int main()
{
	DbManager<ItemType> DbM;

	//입력파일로 검색기의 초기 데이터베이스 구성.
	OpenFile_and_Initialize(DbM);
	DbM.Print_Nth_Search();

	// 본격적으로 string DB 검색 프로그램을 실행.
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
				cout << "검색 연산자를 입력하세요: ";
				getline(cin, DbM.oper);
				if ((DbM.oper == "and") || (DbM.oper == "or") || (DbM.oper == "not") || (DbM.oper == "and not") || (DbM.oper == "or not") || (DbM.oper == "all data")) {
					break;
				}
			}
			
			if (DbM.oper != "all data") {
				cout << "검색 키워드를 입력하세요: ";
				getline(cin, DbM.key);

				DbM.Search();
				DbM.Print_Nth_Search();
			}
			else {
				DbM.allData();
				DbM.Print_Nth_Search();
			}
		
		}
		else if (DbM.command == "and") {
			DbM.oper = "and";

			cout << "검색 키워드를 입력하세요: ";
			getline(cin, DbM.key);

			DbM.Search();
			DbM.Print_Nth_Search();
		}
		else if (DbM.command == "or") {
			DbM.oper = "or";

			cout << "검색 키워드를 입력하세요: ";
			getline(cin, DbM.key);

			DbM.Search();
			DbM.Print_Nth_Search();
		}
		else if (DbM.command == "not") {
			DbM.oper = "not";

			cout << "검색 키워드를 입력하세요: ";
			getline(cin, DbM.key);

			DbM.Search();
			DbM.Print_Nth_Search();
		}
		else if (DbM.command == "and not") {
			DbM.oper = "and not";

			cout << "검색 키워드를 입력하세요: ";
			getline(cin, DbM.key);

			DbM.Search();
			DbM.Print_Nth_Search();
		}
		else if (DbM.command == "or not") {
			DbM.oper = "or not";

			cout << "검색 키워드를 입력하세요: ";
			getline(cin, DbM.key);

			DbM.Search();
			DbM.Print_Nth_Search();
		}
		else if (DbM.command == "all data") {
			DbM.allData();
			DbM.Print_Nth_Search();
		}
		else if (DbM.command == "initialize") {
			OpenFile_and_Initialize(DbM);
			DbM.Print_Nth_Search();
		}
		else if (DbM.command == "print") {
			DbM.Print_Nth_Search();
		}
		else if (DbM.command == "select") {

		}

		DbM.Input_command();
	};
	



	/*
	// Tree 객체의 operator==, operator!= 오버로딩한 거 test하기 위한 code.
	Tree<ItemType> T1;
	T1.InsertItem("hello");
	T1.InsertItem("world");
	T1.InsertItem("z");

	Tree<ItemType> T2;
	T2.InsertItem("hello");
	T2.InsertItem("world");
	T2.InsertItem("z");

	cout << (bool)(T1 != T2) << endl;
	*/


	
	return 0;
}



void OpenFile_and_Initialize(DbManager<ItemType>& DbM)
{
	//입력파일로 검색기의 초기 데이터베이스 구성.
	string inputFileName;
	cout << "검색기의 초기 데이터베이스를 구성할 입력파일의 이름을 입력하세요: ";
	getline(cin, inputFileName);
	cout << endl;

	ifstream inFile(inputFileName.c_str());	//초기 데이터 베이스는 파일(초기DB구성파일) 하나에서 읽어와 구성.
	if (!inFile.is_open()) {
		cout << "데이터 베이스를 구성할 파일을 열 수 없습니다." << endl;
		exit(1);
	}

	DbM.Initialize(inFile);	//

	inFile.seekg(0, ios::beg);		// 파일 읽기 시작하는 위치 초기화 . 이거 안해주면, 다음에 다시 같은 이름의 파일 열어서 읽으면, 그 파일이 열리긴 열리나, 파일 다 끝난 부분부터 읽어서 오류남.
	inFile.close();
}