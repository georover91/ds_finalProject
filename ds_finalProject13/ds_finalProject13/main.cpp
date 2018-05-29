// 1.	현재 프로젝트에서 자료구조를 짜놓은 구조상,
//		Tree 객체에 InsertItem 또는 DeleteItem 등을 하여 원소가 바뀌면, preQue, inQue, postQue 모두 갱신해줘야 함!!!
// 2.	
/////////////////////////////////////////////////////////////////////////////
#include "DbManager_.h"



int main()
{
	//입력파일로 검색기의 초기 데이터베이스 구성.
	string inputFileName;
	cout << "검색기의 초기 데이터베이스를 구성할 입력파일의 이름을 입력하세요: ";
	getline(cin, inputFileName);
	cout << endl;

	ifstream inFile(inputFileName.c_str());	//초기 데이터 베이스는 파일(초기DB구성파일) 하나에서 읽어와 구성.
	if (!inFile.is_open()) {
		cout << "데이터 베이스를 구성할 파일을 열 수 없습니다." << endl;
		return 0;
	}

	DbManager<ItemType> DbM(inFile);
	DbM.Print_Nth_Search();
	inFile.close();


	
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
			
			if (DbM.oper == "all data") {
				DbM.allData();
				DbM.Print_Nth_Search();
			}
			else {
				cout << "검색 키워드를 입력하세요: ";
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
			DbM.Initailize(inFile);
			DbM.Print_Nth_Search();
		}
		else if (DbM.command == "select") {

		}
		else if (DbM.command == "print") {

		}

		DbM.Input_command();
	};

	inFile.close();
	


	return 0;
}