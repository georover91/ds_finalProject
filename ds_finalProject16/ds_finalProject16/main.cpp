// 집합의 개념을 이용한 문자열 검색기
// 작성자: 구본익 (경희대학교 전자공학과)
// 작성일: 2018년 5월 18일 시작 ~ 2018년 6월 17일 완성.
// 스택, 더블링크드리스트, 그리고 트리의 기본적인 자료구조에 대한 수업자료 일부를 참고한 것 이외에는,
// 전적으로 본인이 모두 직접 아이디어, 설계, 작성, 완성한 코딩이다.
/////////////////////////////////////////////////////////////////////////////
#include "DbManager_.h"



void OpenFile_and_InitializeFromFile(DbManager<ItemType>& DbM);

int main()
{
	//instanciating Database Manager class. 
	DbManager<ItemType> DbM;

	// 출력서식설정을 위한 변수들 선언.
	string what = "search screen";
	printTo pt = CONSOLE_;
	printDirection pd = IN_ORDER_;
	printWithNum pwn= NONE_;



	//입력파일로 검색기의 초기 데이터베이스 구성.
	OpenFile_and_InitializeFromFile(DbM);
	cout << endl;
	DbM.Print_SearchScreen(pt, pd, pwn);



	// 본격적으로 string DB 검색 프로그램을 실행.
	DbM.Input_command();

	while (DbM.command != "quit")
	{
		if (DbM.command == "go back") {
			DbM.goBackward();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "go forward") {
			DbM.goForward();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
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
				cout << endl;
				DbM.Print_SearchScreen(pt, pd, pwn);
			}
			else {
				DbM.allData();
				cout << endl;
				DbM.Print_SearchScreen(pt, pd, pwn);
			}
		
		}
		else if (DbM.command == "and") {
			DbM.oper = "and";

			cout << "검색 키워드를 입력하세요: ";
			getline(cin, DbM.key);

			DbM.Search();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "or") {
			DbM.oper = "or";

			cout << "검색 키워드를 입력하세요: ";
			getline(cin, DbM.key);

			DbM.Search();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "not") {
			DbM.oper = "not";

			cout << "검색 키워드를 입력하세요: ";
			getline(cin, DbM.key);

			DbM.Search();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "and not") {
			DbM.oper = "and not";

			cout << "검색 키워드를 입력하세요: ";
			getline(cin, DbM.key);

			DbM.Search();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "or not") {
			DbM.oper = "or not";

			cout << "검색 키워드를 입력하세요: ";
			getline(cin, DbM.key);

			DbM.Search();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "all data") {
			DbM.allData();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "initialize") {
			OpenFile_and_InitializeFromFile(DbM);
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "print") {
			DbM.PrintSettings(what, pt, pd, pwn);
			
			if ((what == "search screen") || (what == "screen")) {
				if (pt != FILE_) {
					cout << endl;
				}
				DbM.Print_SearchScreen(pt, pd, pwn);
			}
			else if ((what == "search route") || (what == "route")) {
				if (pt != FILE_) {
					cout << endl;
				}
				DbM.Print_SearchRoute(pt);
			}
			else if ((what == "search data") || (what == "data")) {
				if (pt != FILE_) {
					cout << endl;
				}
				DbM.Print_SearchDb(pt, pd, pwn);
			}

			//출력 기능을 다 수행하면, 출력 옵션 중 pt를 console에 출력하는 설정으로 초기화.
			what = "search screen";
			pt = CONSOLE_;
		}
		else if (DbM.command == "select") {
			int n;
			cout << "선택할 데이터의 번째수를 입력하세요: ";
			cin >> n;
			DbM.select(pd, n);

			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "number") {
			int m;
			m = DbM.SearchEleNum();
			cout << "현재 검색결과의 데이터 갯수는 ";
			cout << m << " 개 입니다." << endl;
		}

		DbM.Input_command();
	};

	return 0;
}

void OpenFile_and_InitializeFromFile(DbManager<ItemType>& DbM)
{
	//입력파일로 검색기의 초기 데이터베이스 구성.
	string inputFileName;
	cout << "검색기의 초기 데이터베이스를 구성할 입력파일의 이름을 입력하세요: ";
	getline(cin, inputFileName);
	//cout << endl;

	ifstream inFile(inputFileName.c_str());	//초기 데이터 베이스는 파일(초기DB구성파일) 하나에서 읽어와 구성.
	if (!inFile.is_open()) {
		cout << "데이터 베이스를 구성할 파일을 열 수 없습니다." << endl;
		exit(1);
	}

	DbM.Initialize(inFile);	//

	inFile.seekg(0, ios::beg);		// 파일 읽기 시작하는 위치 초기화 . 이거 안해주면, 다음에 다시 같은 이름의 파일 열어서 읽으면, 그 파일이 열리긴 열리나, 파일 다 끝난 부분부터 읽어서 오류남.
	inFile.close();
}