// 집합의 개념을 이용한 문자열 검색기. (the string search programme using the concept of set.)
// 작성자: 구본익 (경희대학교 전자공학과. 생년월일: 910211. 이메일: kubonik91@naver.com)
// 작성일: 2018년 5월 18일 시작 ~ 2018년 6월 17일 완성.
// 스택, 더블링크드리스트, 그리고 트리의 기본적인 자료구조에 대한 수업자료 일부를 참고한 것 이외에는,
// 전적으로 본인이 모두 직접 아이디어, 설계, 작성, 완성한 코딩이다.
/////////////////////////////////////////////////////////////////////////////
#include "DbManager_.h"



void OpenFile_and_InitializeFromFile(DbManager<ItemType>& DbM);

int main()
{
	//프로그램 동작을 위한 안내문 작성.
	cout << "<<<집합(교집합, 합집합, 여집합 등)의 개념을 이용한 문자열 검색기>>>" << endl;
	cout << endl;
	cout << "---프로그램을 사용하기 위한 안내문---------------------------------" << endl;
	cout << "이 문자열 검색기는 기본적으로 windows console 환경에서 동작하며, 문자열 명령어를 받아 기능을 수행합니다." << endl;
	cout << "이 문자열 검색기의 명령어는 모두 영문 소문자로 구성되어 있으며, 다음과 같은 명령어들이 있습니다." << endl;
	cout << "quit 명령어:                          프로그램을 종료합니다." << endl;
	cout << "search 명령어:                        이 명령어 이후의 추가 명령어를 입력하여, 그에 따른 검색을 수행하며, 이전 검색결과로부터 새로운 검색결과를 구성합니다." << endl;
	cout << "이전 검색결과 출력된 상태 -> search명령어 입력 -> 'and', 'or' 등의 검색연산자 입력 -> keyword 입력 -> 현재 검색결과 구성 및 출력." << endl;
	cout << "search 명령어 입력후, 검색 연산자(operator, oper) 및 검색 키워드를 추가로 입력해야 합니다." << endl;
	cout << "명령어 입력란에 검색연산자를 입력해도 정상 동작하며, 그 입력에 따른 검색을 수행합니다." << endl;
	cout << "and 명령어 또는 검색연산자:           이전 검색결과에서 keyword가 존재하는 문자열만을 선별해 현재 검색결과를 구성합니다." << endl;
	cout << "or 명령어 또는 검색연산자:            전체 문자열 초기데이터베이스에서 keyword가 존재하는 문자열만을 선별해, 그 데이더들을 이전 검색결과에 추가하여 현재 검색결과를 구성합니다." << endl;
	cout << "not 명령어 또는 검색연산자:           전제 데이터베이스에서 이전 검색결과를 제외한 나머지 문자열이 현재 검색결과를 구성합니다. 또는 전체 데이터베이스에서 keyword가 존재하는 문자열을 제외한 나머지 문자열이 현재 겸색결과를 구성합니다." << endl;
	cout << "and not 명령어 또는 검색연산자:       이전 검색결과에서, keyword가 존재하는 문자열을 제외하고, 그 나머지 문자열이 현재 검색결과를 구성합니다." << endl;
	cout << "or not 명령어 또는 검색연산자:        전체검색결과 중 keyword가 존재하는 문자열을 제외한 나머지 문자열이, 이전 검색결과에 추가됩니다." << endl;
	cout << "all data 명령어 또는 검색연산자:      입력파엘에서 읽어들여 구성했던 초기데이터베이스로, 현재 검색결과를 다시 구성합니다." << endl;
	cout << "initialize 명령어:                    이 문자열 검색기 프로그램을 처음부터 다시 시작(재부팅)합니다." << endl;
	cout << "print 명령어:                         현재 구성된 검색결과를 출력합니다. 추가 관련 명령어를 입력해야 합니다." << endl;
	cout << "print 명령어와 함께 임력한 print 서식설정사항은 다음 출력시에도 저장, 반영됩니다." << endl;
	cout << "search screen 또는 screen:            현재 검색결과 화면 전체를 출력합니다." << endl;
	cout << "search route 또는 route:              현재 검색결과 화면 중 검색루트만을 출력합니다." << endl;
	cout << "search data 또는 data:                현재 검색결과 화면 중 검색데이터만을 출력합니다." << endl;
	cout << "console:                              현재 검색결과 화면을 console에 출력합니다." << endl;
	cout << "file:                                 현재 검색결과 화면을 file에 출력합니다." << endl;
	cout << "in order:                             현재 검색결과의 데이터를 오름차순으로 출력합니다." << endl;
	cout << "reverse:                              현재 검색결과의 데이터를 내림차순으로 출력합니다." << endl;
	cout << "with numbering 또는 yes:              현재 검색결과의 데이터에 번호를 붙여 출력합니다." << endl;
	cout << "without numbering 또는 no:            현재 검색결과의 데이터에 번호를 붙이지 않고 출력합니다." << endl;
	cout << "select 명령어:                        이 명령어 입력후 숫자를 입력하면, 그 숫자 번째의 데이터 하나를 선택해 새로운 현재 검색결과를 구성합니다." << endl;
	cout << "number 명령어:                        현재 검색결과의 데이터 갯수를 출력합니다." << endl;
	cout << "초기 데이터베이스를 구성할 입력파일의 이름은 사용자가 지정할 수 있습니다. 지정한 바 없다면, in.txt 를 기본입력파일 이름으로 합니다." << endl;
	cout << "데이터를 출력할 출력파일의 이름도 사용자가 지정할 수 있습니다." << endl;
	cout << "-------------------------------------------------------------------" << endl;
	cout << endl;
	cout << endl;
	cout << endl;



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

			what = "search screen";
			pt = CONSOLE_;
			pd = IN_ORDER_;
			pwn = NONE_;

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