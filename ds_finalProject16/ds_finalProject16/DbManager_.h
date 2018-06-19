#include "DbManager.h"



template<class _ItemType>
DbManager<_ItemType>::DbManager()
{
	//allDbPtr 및 allDb 초기 구성.
	allDbPtr = new Tree<_ItemType>;	//allDb 생성.
	/// allDb Tree 원소 구성 생략.


	// myCurrDbPtr 초기 구성.
	myCurrDbPtr = allDbPtr;


	// 검색결과 히스토리 초기 구성.
	myDbBackStack.Push(allDbPtr);		// == myDbBackStack.Push(myCurrDbPtr);


	// 검색연산자 및 검색어 히스토리 초기 구성.
	oper = "all data";
	key = "\0";
	operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
	operKeyDoubleLL.Insert_with_Deleting_nextPos(key);


	////////// 이 부분은 initialize 맴버함수에는 없지만, 생성자와  MakeEmpty 맴버함수에는 있는 코딩 부분.///
	// 검색횟수 및 명령횟수 초기화.
	searchNum = 0;
	comNum = 0;


	// 명령어, 검색 연산자, 검색어 저장하는 문자열 초기화.
	command = "\0";
	oper = "\0";
	key = "\0";
}

template<class _ItemType>
DbManager<_ItemType>::DbManager(Tree<_ItemType> T1)
{
	//allDbPtr 및 allDb 초기 구성.
	allDbPtr = new Tree<_ItemType>;	//allDb 생성.
	/// allDb Tree 원소 구성.
	(*allDbPtr) = T1;


	// myCurrDbPtr 초기 구성.
	myCurrDbPtr = allDbPtr;


	// 검색결과 히스토리 초기 구성.
	myDbBackStack.Push(allDbPtr);		// == myDbBackStack.Push(myCurrDbPtr);


	// 검색연산자 및 검색어 히스토리 초기 구성.
	oper = "all data";
	key = "\0";
	operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
	operKeyDoubleLL.Insert_with_Deleting_nextPos(key);


	// 검색횟수 및 명령횟수 초기화.
	searchNum = 0;
	comNum = 0;


	// 명령어, 검색 연산자, 검색어 저장하는 문자열 초기화.
	command = "\0";
	oper = "\0";
	key = "\0";
}

template<class _ItemType>
DbManager<_ItemType>::DbManager(ifstream& inFile)
{
	//allDbPtr 및 allDb 초기 구성.
	allDbPtr = new Tree<_ItemType>;	//allDb 생성.

	// 입력파일의 정보를 읽어, allDb의 원소 구성하기.
	string command_data;
	int numData = 0;
	getline(inFile, command_data);	// '초기DB구성파일'의 한 줄을 명령으로 받아옴.
	if (command_data == "InsertStrings") {
		getline(inFile, command_data);
		while (command_data != "Quit") {	// 입력파일의 입력문장들을 하나씩 게속 읽어들인다.
			(*allDbPtr).InsertItem(command_data);
			numData++;
			cout << numData << "th data has been inputed: " << command_data << endl;
			getline(inFile, command_data);
		}
	}
	else {
		cout << "Command Error. or Data Error." << endl;
	}
	cout << endl;
	cout << endl;


	// myCurrDbPtr 초기 구성.
	myCurrDbPtr = allDbPtr;


	// 검색결과 히스토리 초기 구성.
	myDbBackStack.Push(allDbPtr);		// == myDbBackStack.Push(myCurrDbPtr);


	// 검색연산자 및 검색어 히스토리 초기 구성.
	oper = "all data";
	key = "\0";
	operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
	operKeyDoubleLL.Insert_with_Deleting_nextPos(key);


	// 검색횟수 및 명령횟수 초기화.
	searchNum = 0;
	comNum = 0;


	// 명령어, 검색 연산자, 검색어 저장하는 문자열 초기화.
	command = "\0";
	oper = "\0";
	key = "\0";
}

template<class _ItemType>
DbManager<_ItemType>::~DbManager()
{
	cout << "프로그램을 종료하는 중 입니다..." << endl;
	MakeEmpty();
	cout << "프로그램을 종료합니다." << endl;
}

template<class _ItemType>
void DbManager<_ItemType>::MakeEmpty()
{
	// allDb 및 allDbPtr 초기화.
	Tree<_ItemType>* tempPtr;

	//////아래 while문 2개에서 자꾸 오류 났는데, all data 명령어에 의해 실행되어 생긴, 두 포잍터가 하나의 같은 객체를 가리키는 경우가 생겨서, 그 객체 delete 하는데 이중으로 객체가 소멸시도 된 듯.
	while (!myDbBackStack.IsEmpty()) {
		myDbBackStack.Top(tempPtr);
		////// 아래의 두 첫번째 세번째 문장이 연속해서 실행되는 것은 하나의 두번째 문장이 실행되는 것과 같다?
		tempPtr->MakeEmpty();
		tempPtr->~Tree();
		delete tempPtr;
		myDbBackStack.Pop();
	}
	myDbBackStack.MakeEmpty();

	while (!myDbForwardStack.IsEmpty()) {
		myDbForwardStack.Top(tempPtr);
		////// 아래의 두 첫번째 세번째 문장이 연속해서 실행되는 것은 하나의 두번째 문장이 실행되는 것과 같다?
		tempPtr->MakeEmpty();
		tempPtr->~Tree();
		delete tempPtr;
		myDbForwardStack.Pop();
	}
	myDbForwardStack.MakeEmpty();
	//위 과정에서 delete allDbPtr; 포함됨.

	allDbPtr = NULL;
	
	
	// myCurrDbPtr 초기화.
	myCurrDbPtr = NULL;
	

	// operKeyDoubleLL 히스토리 초기화.
	operKeyDoubleLL.MakeEmpty();


	// 검색횟수 및 명령횟수 초기화.
	searchNum = 0;
	comNum = 0;


	// 명령어, 검색 연산자, 검색어 저장하는 문자열 초기화.
	command = "\0";
	oper = "\0";
	key = "\0";
}



template<class _ItemType>
void DbManager<_ItemType>::Initialize()
{
	MakeEmpty();


	//allDbPtr 및 allDb 초기 구성.
	allDbPtr = new Tree<_ItemType>;	//allDb 생성.
	// allDb Tree 원소 구성을 생략.

	
	// myCurrDbPtr 초기 구성.
	myCurrDbPtr = allDbPtr;


	// 검색결과 히스토리 초기 구성.
	myDbBackStack.Push(allDbPtr);		// == myDbBackStack.Push(myCurrDbPtr);


	// 검색연산자 및 검색어 히스토리 초기 구성.
	oper = "all data";
	key = "\0";
	operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
	operKeyDoubleLL.Insert_with_Deleting_nextPos(key);
}

template<class _ItemType>
void DbManager<_ItemType>::Initialize(Tree<_ItemType> T1)
{
	MakeEmpty();


	//allDbPtr 및 allDb 초기 구성.
	allDbPtr = new Tree<_ItemType>;	//allDb 생성.
	/// allDb Tree 원소 구성.
	(*allDbPtr) = T1;


	// myCurrDbPtr 초기 구성.
	myCurrDbPtr = allDbPtr;


	// 검색결과 히스토리 초기 구성.
	myDbBackStack.Push(allDbPtr);		// == myDbBackStack.Push(myCurrDbPtr);


	// 검색연산자 및 검색어 히스토리 초기 구성.
	oper = "all data";
	key = "\0";
	operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
	operKeyDoubleLL.Insert_with_Deleting_nextPos(key);
}

template<class _ItemType>
void  DbManager<_ItemType>::Initialize(ifstream& inFile)
{
	MakeEmpty();


	//allDbPtr 및 allDb 초기 구성.
	allDbPtr = new Tree<_ItemType>;	//allDb 생성.

	// 입력파일의 정보를 읽어, allDb의 원소 구성하기.
	string command_data;
	int numData = 0;
	getline(inFile, command_data);	// '초기DB구성파일'의 한 줄을 명령으로 받아옴.
	if (command_data == "InsertStrings") {
		getline(inFile, command_data);
		while (command_data != "Quit") {	// 입력파일의 입력문장들을 하나씩 게속 읽어들인다.
			(*allDbPtr).InsertItem(command_data);
			numData++;
			cout << numData << "th data has been inputed: " << command_data << endl;
			getline(inFile, command_data);
		}
	}
	else {
		cout << "Command Error. or Data Error." << endl;
	}
	//cout << endl;
	//cout << endl;


	// myCurrDbPtr 초기 구성.
	myCurrDbPtr = allDbPtr;


	// 검색결과 히스토리 초기 구성.
	myDbBackStack.Push(allDbPtr);		// == myDbBackStack.Push(myCurrDbPtr);
	

	// 검색연산자 및 검색어 히스토리 초기 구성.
	oper = "all data";
	key = "\0";
	operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
	operKeyDoubleLL.Insert_with_Deleting_nextPos(key);
}



template<class _ItemType>
void DbManager<_ItemType>::goBackward()
{
	//myCurrDbPtr////
	myDbBackStack.Pop();

	if (myDbBackStack.IsEmpty()) {		//현재 myCurrDb가 allDb이면,
		cout << "더이상 뒤로 되돌릴 Data Base History가 없습니다." << endl;
		myDbBackStack.Push(allDbPtr);
		return;	//아무 실행 안하고 함수 종료.
	}
	else {
		//myCurrDbPtr////
		myDbForwardStack.Push(myCurrDbPtr);		// go forward 명령어 실행에 대비해, myDbForwardStack에 현재 myCurrDbPtr값 저장.
		myDbBackStack.Top(myCurrDbPtr);		// myCurrDbPtr 값이 back스택에도 가장 위에 남아있도록 항상 실시간상태를 유지.

		//oper & key////
		operKeyDoubleLL.GoToBeforePos();
		operKeyDoubleLL.GoToBeforePos();
	}

	searchNum--;
}

template<class _ItemType>
void DbManager<_ItemType>::goForward()
{
	if (myDbForwardStack.IsEmpty()) {		// 앞으로갈 저장상태가 없으면,
		cout << "더이상 앞으로 갈 Data Base History가 없습니다." << endl;
		return;	//아무 실행 안하고 함수 종료.
	}
	else {
		//myCurrDbPtr
		myDbForwardStack.Top(myCurrDbPtr);
		myDbForwardStack.Pop();
		myDbBackStack.Push(myCurrDbPtr);		// myCurrDbPtr 값이 back스택에도 가장 위에 남아있도록 항상 실시간상태를 유지.

		//oper & key////
		operKeyDoubleLL.GoToNextPos();
		operKeyDoubleLL.GoToNextPos();
	}

	searchNum++;
}



template<class _ItemType>
void DbManager<_ItemType>::Input_command()
{
	cout << endl;
	cout << endl;
	cout << endl;
	comNum++;
	cout << "<<<" << comNum << "번째 명령" << ">>>" << endl;
	cout << "프로그램 실행명령을 입력하세요: ";
	getline(cin, command);
}



template<class _ItemType>
void DbManager<_ItemType>::Search()
// 입력받은 검색 연산자와 검색어로 검색 수행.
// 새로운 검색결과를 생성 및 출력.
// 받은 oper과 key 값을 backStack에 저장까지 해줌.
{
	Tree<_ItemType>* newDbPtr;
	newDbPtr = new Tree<_ItemType>;		// 새 myDb 생성.
	string getString;


	if (oper == "and") {
		Search_and(newDbPtr);
	}
	else if (oper == "or") {
		Search_or(newDbPtr);
	}
	else if (oper == "not") {
		Search_not(newDbPtr);
	}
	else if (oper == "and not") {
		Search_and_not(newDbPtr);
	}
	else if (oper == "or not") {
		Search_or_not(newDbPtr);
	}


	if ((*myCurrDbPtr) != (*newDbPtr)) {
		myDbBackStack.Push(newDbPtr);
		myDbForwardStack.MakeEmpty();
		myCurrDbPtr = newDbPtr;

		operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
		operKeyDoubleLL.Insert_with_Deleting_nextPos(key);

		searchNum++;
	}
	else {
		cout << "이전 검색결과와 같습니다. 새로운 검색을 진행하지 않습니다." << endl;
	}
}

template<class _ItemType>
void DbManager<_ItemType>::Search_strings_that_have_the_key_from_(Tree<_ItemType>*& baseDbPtr, Tree<_ItemType>*& newDbPtr)
{
	_ItemType getString;
	bool finished = false;

	baseDbPtr->ResetTree(IN_ORDER);
	while (!finished) {
		baseDbPtr->GetNextItem(getString, IN_ORDER, finished);
		if (getString.find(key) != string::npos) {
			newDbPtr->InsertItem(getString);
		}
	}
}

template<class _ItemType>
void DbManager<_ItemType>::Search_and(Tree<_ItemType>*& newDbPtr)
{
	Search_strings_that_have_the_key_from_(myCurrDbPtr, newDbPtr);
	//(*newDbPtr) = ((*myCurrDbPtr) * (*newDbPtr));
}

template<class _ItemType>
void DbManager<_ItemType>::Search_or(Tree<_ItemType>*& newDbPtr)
{
	Search_strings_that_have_the_key_from_(allDbPtr, newDbPtr);
	(*newDbPtr) = (*myCurrDbPtr) + (*newDbPtr);
}

template<class _ItemType>
void DbManager<_ItemType>::Search_not(Tree<_ItemType>*& newDbPtr)
{
	if (key != "\0") {
		// 초기 데이터베이스에서 key값이 들어간 문자열을 찾아낸 후
		Search_strings_that_have_the_key_from_(allDbPtr, newDbPtr);

		// 전체 데이터베이스에서 'key값으로 검색된 Db'(*newDbPtr)를 제외한다.
		(*newDbPtr) = (*allDbPtr) - (*newDbPtr);	
	}
	else {		// key == NULL인 경우.
		(*newDbPtr) = (*allDbPtr) - (*myCurrDbPtr);

		// 전체 데이터베이스에서 'key값으로 검색된 위 새 임시Db'(*newDbPtr)를 제외한다.
	}
	
}

template<class _ItemType>
void DbManager<_ItemType>::Search_and_not(Tree<_ItemType>*& newDbPtr)
{
	Search_not(newDbPtr);
	(*newDbPtr) = (*myCurrDbPtr) * (*newDbPtr);		// 여기서 (*newDbPtr)는 key값을 가진 문자열들의 여집합에 해당함. 
													// *myCurrDbPtr는 원본보존됨.
}

template<class _ItemType>
void DbManager<_ItemType>::Search_or_not(Tree<_ItemType>*& newDbPtr)
{
	Search_not(newDbPtr);
	(*newDbPtr) = (*myCurrDbPtr) + (*newDbPtr);		//*myCurrDbPtr와 *newDbPtr는 원본보존됨.
}



template<class _ItemType>
void DbManager<_ItemType>::allData()
{
	Tree<_ItemType>* tempPtr;
	tempPtr = new Tree<_ItemType>;
	(*tempPtr) = (*allDbPtr);		// (*tempPtr) Tree 객체에, 초기 데이터베이스 객체(*allDbPtr)의 원소값들을 그대로 복사하여 구성.

	if ((*myCurrDbPtr) != (*tempPtr)) {
		myDbBackStack.Push(tempPtr);
		myDbForwardStack.MakeEmpty();
		myCurrDbPtr = tempPtr;

		oper = "all data";
		operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
		key = "\0";
		operKeyDoubleLL.Insert_with_Deleting_nextPos(key);

		searchNum++;
	}
	else {
		cout << "이전 검색결과와 같습니다. 새로운 검색을 진행하지 않습니다." << endl;
	}
	
}



template<class _ItemType>
void DbManager<_ItemType>::Print_SearchScreen()
{
	Print_SearchScreen(CONSOLE_, IN_ORDER_, NONE_);
}

template<class _ItemType>
void DbManager<_ItemType>::Print_SearchScreen(printTo PT, printDirection PD, printWithNum PWN)
{
	// Tree가 가지고 있는 데이터 중 가장 긴 문자열의 문자 길이: myCurrDbPtr->MaxLengthIs();
	// minScreenWide는 출력화면의 최소너비.
	// screenWide: 출력되는 문자열 중 가장 긴 문자열의 길이만큼 경게선 길이를 늘리기 위해 도입한 변수.
	screenWide = myCurrDbPtr->MaxLengthIs();
	if (screenWide < minScreenWide) {
		screenWide = minScreenWide;
	}


	if (PT == CONSOLE_) {
		if (searchNum == 0) {
			cout << setw(screenWide) << setfill('=') << setiosflags(ios::left) << "<<<초기 데이터베이스>>>";
			cout << endl;
		}
		else {
			cout << "<<<"; 
			cout << setw(3) << setfill(' ') << resetiosflags(ios::left) << setiosflags(ios::right) << searchNum; 
			cout << setw(screenWide - 6) << setfill('=') << resetiosflags(ios::right) << setiosflags(ios::left) << "번째 검색결과>>>";
			cout << endl;
		}

		cout << setw(screenWide) << setfill('-') << "---검색 연산자 및 검색어 히스토리---";
		cout << endl;

		Print_SearchRoute(PT);		///////////

		cout << setw(screenWide) << setfill('-') << "-";
		cout << endl;

		if (PD == IN_ORDER_) {
			if (PWN == NONE_) {
				myCurrDbPtr->Print();	//////////
			}
			else if (PWN == WITH_NUM_) {
				myCurrDbPtr->Print_with_Num();	//////////
			}
		}
		else if (PD == REVERSE_) {
			if (PWN == NONE_) {
				myCurrDbPtr->Print_Reverse();	//////////
			}
			else if (PWN == WITH_NUM_) {
				myCurrDbPtr->Print_Reverse_with_Num();	//////////
			}
		}
		
		cout << setw(screenWide) << setfill('=') << "=";
		cout << endl;
	}
	else if (PT == FILE_) {		
		string outputFileName;
		cout << "검색기에서 도출한 데이터베이스를 출력할 출력파일의 이름을 입력하세요: ";
		getline(cin, outputFileName);
		ofstream outFile;
		outFile.open(outputFileName.c_str(), ios::out | ios::app);
		if (!outFile.is_open()) {
			cout << "데이터베이스를 출력할 파일을 열 수 없습니다." << endl;
			exit(1);
		}

		if (searchNum == 0) {
			outFile << setw(screenWide) << setfill('=') << setiosflags(ios::left) << "<<<초기 데이터베이스>>>";
			outFile << endl;
		}
		else {
			outFile << setw(screenWide) << setfill('=') << "<<<" << searchNum << "번째 검색결과" << ">>>";
			outFile << endl;
		}

		outFile << setw(screenWide) << setfill('-') << "---검색 연산자 및 검색어 히스토리---";
		outFile << endl;

		Print_SearchRoute(PT);		///////////

		outFile << setw(screenWide) << setfill('-') << "-";
		outFile << endl;

		if (PD == IN_ORDER_) {
			if (PWN == NONE_) {
				myCurrDbPtr->Print(outFile);	//////////
			}
			else if (PWN == WITH_NUM_) {
				myCurrDbPtr->Print_with_Num(outFile);	//////////
			}
		}
		else if (PD == REVERSE_) {
			if (PWN == NONE_) {
				myCurrDbPtr->Print_Reverse(outFile);	//////////
			}
			else if (PWN == WITH_NUM_) {
				myCurrDbPtr->Print_Reverse_with_Num(outFile);	//////////
			}
		}

		outFile << setw(screenWide) << setfill('=') << "=";
		outFile << endl;

		cout << "파일에 출력이 완료되었습니다." << endl;
		outFile.close();

	}
}

template<class _ItemType>
void DbManager<_ItemType>::Print_SearchRoute(printTo PT)
{
	screenWide = myCurrDbPtr->MaxLengthIs();
	if (screenWide < minScreenWide) {
		screenWide = minScreenWide;
	}

	if (PT == CONSOLE_) {
		if (operKeyDoubleLL.WhatIsCurrentPos() != operKeyDoubleLL.WhatIsHeaderPtr()) {
			DoubleLLNode<_ItemType>* tempPtr = operKeyDoubleLL.WhatIsHeaderPtr();

			int searchRoute_PrintLength = 0;

			while (tempPtr != operKeyDoubleLL.WhatIsCurrentPos()) {
				tempPtr = tempPtr->bottomPtr;

				if (tempPtr != ((operKeyDoubleLL.WhatIsHeaderPtr())->bottomPtr)) {
					searchRoute_PrintLength += (2);
					if (searchRoute_PrintLength > screenWide) {
						cout << endl;
						searchRoute_PrintLength = 0;
					}
					cout << "->";

					searchRoute_PrintLength += (1);
					if (searchRoute_PrintLength > screenWide) {
						cout << endl;
						searchRoute_PrintLength = 0;
					}
					cout << " ";
				}

				searchRoute_PrintLength += ((tempPtr->info).length());
				if (searchRoute_PrintLength > screenWide) {
					cout << endl;
					searchRoute_PrintLength = 0;
				}
				cout << tempPtr->info;		//oper print.

				searchRoute_PrintLength += (1);
				if (searchRoute_PrintLength > screenWide) {
					cout << endl;
					searchRoute_PrintLength = 0;
				}
				cout << " ";

				tempPtr = tempPtr->bottomPtr;

				if (tempPtr->info != "\0") {		//tempPtr->->info == "\0" 이면 key print 안하기
					searchRoute_PrintLength += (2 + (tempPtr->info).length());
					if (searchRoute_PrintLength > screenWide) {
						cout << endl;
						searchRoute_PrintLength = 0;
					}
					cout << "\"";
					cout << tempPtr->info;		//key print.
					cout << "\"";

					searchRoute_PrintLength += (1);
					if (searchRoute_PrintLength > screenWide) {
						cout << endl;
						searchRoute_PrintLength = 0;
					}
					cout << " ";
				}
			}

			cout << endl;
		}
	} 
	else if (PT == FILE_) {
		string outputFileName;
		cout << "검색기에서 도출한 데이터베이스를 출력할 출력파일의 이름을 입력하세요: ";
		getline(cin, outputFileName);
		ofstream outFile;
		outFile.open(outputFileName.c_str(), ios::out | ios::app);
		if (!outFile.is_open()) {
			cout << "데이터베이스를 출력할 파일을 열 수 없습니다." << endl;
			exit(1);
		}

		if (operKeyDoubleLL.WhatIsCurrentPos() != operKeyDoubleLL.WhatIsHeaderPtr()) {
			DoubleLLNode<_ItemType>* tempPtr = operKeyDoubleLL.WhatIsHeaderPtr();
			//cout << tempPtr->info;
			//cout << " ";
			int searchRoute_PrintLength = 0;

			while (tempPtr != operKeyDoubleLL.WhatIsCurrentPos()) {
				tempPtr = tempPtr->bottomPtr;

				if (tempPtr != ((operKeyDoubleLL.WhatIsHeaderPtr())->bottomPtr)) {
					searchRoute_PrintLength += (2);
					if (searchRoute_PrintLength > screenWide) {
						outFile << endl;
						searchRoute_PrintLength = 0;
					}
					outFile << "->";

					searchRoute_PrintLength += (1);
					if (searchRoute_PrintLength > screenWide) {
						outFile << endl;
						searchRoute_PrintLength = 0;
					}
					outFile << " ";
				}

				searchRoute_PrintLength += ((tempPtr->info).length());
				if (searchRoute_PrintLength > screenWide) {
					outFile << endl;
					searchRoute_PrintLength = 0;
				}
				outFile << tempPtr->info;		//oper print.

				searchRoute_PrintLength += (1);
				if (searchRoute_PrintLength > screenWide) {
					outFile << endl;
					searchRoute_PrintLength = 0;
				}
				outFile << " ";

				tempPtr = tempPtr->bottomPtr;

				if (tempPtr->info != "\0") {		//tempPtr->->info == "\0" 이면 key print 안하기
					searchRoute_PrintLength += (2 + (tempPtr->info).length());
					if (searchRoute_PrintLength > screenWide) {
						outFile << endl;
						searchRoute_PrintLength = 0;
					}
					outFile << "\"";
					outFile << tempPtr->info;		//key print.
					outFile << "\"";

					searchRoute_PrintLength += (1);
					if (searchRoute_PrintLength > screenWide) {
						outFile << endl;
						searchRoute_PrintLength = 0;
					}
					outFile << " ";
				}
			}

			outFile << endl;
		}

		cout << "파일에 출력이 완료되었습니다." << endl;
		outFile.close();
	}
}


template<class _ItemType>
void DbManager<_ItemType>::Print_SearchDb(printTo PT, printDirection PD, printWithNum PWN)
{
	if (PT == CONSOLE_) {
		if (PD == IN_ORDER_) {
			if (PWN == NONE_) {
				myCurrDbPtr->Print();					////////////
			}
			else if (PWN == WITH_NUM_) {
				myCurrDbPtr->Print_with_Num();			////////////
			}
		}
		else if (PD == REVERSE_) {
			if (PWN == NONE_) {
				myCurrDbPtr->Print_Reverse();			////////////
			}
			else if (PWN == WITH_NUM_) {
				myCurrDbPtr->Print_Reverse_with_Num();	////////////
			}
		}
	}
	else if (PT == FILE_) {
		string outputFileName;
		cout << "검색기에서 도출한 데이터베이스를 출력할 출력파일의 이름을 입력하세요: ";
		getline(cin, outputFileName);
		ofstream outFile;
		outFile.open(outputFileName.c_str(), ios::out | ios::app);
		if (!outFile.is_open()) {
			cout << "데이터베이스를 출력할 파일을 열 수 없습니다." << endl;
			exit(1);
		}
		
		if (PD == IN_ORDER_) {
			if (PWN == NONE_) {
				myCurrDbPtr->Print(outFile);
			}
			else if (PWN == WITH_NUM_) {
				myCurrDbPtr->Print_with_Num(outFile);
			}
		}
		else if (PD == REVERSE_) {
			if (PWN == NONE_) {
				myCurrDbPtr->Print_Reverse(outFile);
			}
			else if (PWN == WITH_NUM_) {
				myCurrDbPtr->Print_Reverse_with_Num(outFile);
			}
		}

		cout << "파일에 출력이 완료되었습니다." << endl;
		outFile.close();
	}
}

template<class _ItemType>
void DbManager<_ItemType>::PrintSettings(string& what, printTo& pt, printDirection& pd, printWithNum& pwn)
{
	string WHAT_ = " ";
	string PT_ = " ";
	string PD_ = " ";
	string PWN_ = " ";

	//메인함수 윗부분으로 이동.
	//string what = "screen";
	//printTo pt;
	//printDirection pd;
	//printWithNum pwn;

	cout << "현재의 출력서식:   1) ";
	//what
	if ((what == "search screen") || (what == "screen")) {
		cout << "screen을   2) ";
	}
	else if ((what == "search route") || (what == "route")) {
		cout << "reute를   2) ";
	}
	else if ((what == "search data") || (what == "data")) {
		cout << "data를   2) ";
	}
	//pt
	if (pt == CONSOLE_) {
		cout << "console에   3) ";
	}
	else if (pt == FILE_) {
		cout << "file에   3) ";
	}
	//pd
	if (pd == IN_ORDER_) {
		cout << "오름차순으로   4) ";
	}
	else if (pd == REVERSE_) {
		cout << "내림차순으로   4) ";
	}
	//pwn
	if (pwn == WITH_NUM_) {
		cout << "번호를 붙여   출력합니다.";
	}
	else if (pwn == NONE_) {
		cout << "번호를 붙이지 않고   출력합니다.";
	}
	cout << endl;
	cout << "사용자 설정에 따라 출력한 후에는,   1) screen을   2) console에 출력하는 것으로,   자동 초기화 합니다." << endl;
	cout << "나머지 서식은 이전 설정을 유지합니다." << endl;


	while ((WHAT_ != "\0") && (WHAT_ != "search screen") && (WHAT_ != "screen") && (WHAT_ != "search route") && (WHAT_ != "route") && (WHAT_ != "search data") && (WHAT_ != "data")) {
		cout << "1) 무엇을 출력할까요?: ";
		getline(cin, WHAT_);
	}
	if (WHAT_ == "\0") {
		//what = what;		//이전 상태 유지.
	}
	else if ((WHAT_ == "search screen") || (WHAT_ == "screen")) {
		what = WHAT_;
	}
	else if ((WHAT_ == "search route") || (WHAT_ == "route")) {
		what = WHAT_;
	}
	else if ((WHAT_ == "search data") || (WHAT_ == "data")) {
		what = WHAT_;
	}

	while ((PT_ != "\0") && (PT_ != "console") && (PT_ != "file") && (PT_ != "myWriting")) {
		cout << "2) 어디에 출력할까요?: ";
		getline(cin, PT_);
	}
	if (PT_ == "\0") {
		//pt = pt;		//이전 상태 유지.
	}
	else if (PT_ == "console") {
		pt = CONSOLE_;
	}
	else if (PT_ == "file") {
		pt = FILE_;
	}

	if ((what != "search route") && (what != "route")) {
		while ((PD_ != "\0") && (PD_ != "in order") && (PD_ != "reverse")) {
			cout << "3) 어떤 순서로 출력할까요?: ";
			getline(cin, PD_);
		}
		if (PD_ == "\0") {
			//pd = pd;		//이전 상태 유지.
		}
		else if (PD_ == "in order") {
			pd = IN_ORDER_;
		}
		else if (PD_ == "reverse") {
			pd = REVERSE_;
		}

		while ((PWN_ != "\0") && (PWN_ != "yes") && (PWN_ != "no") && (PWN_ != "with numbering") && (PWN_ != "without numbering")) {
			cout << "4) 출력되는 순서에 따라 번호를 붙여 출력할까요?: ";
			getline(cin, PWN_);
		}
		if (PWN_ == "\0") {
			//pwn = pwn;		//이전 상태 유지.
		}
		else if ((PWN_ == "yes") || (PWN_ == "with numbering")) {
			pwn = WITH_NUM_;
		}
		else if ((PWN_ == "no") || (PWN_ == "without numbering")) {
			pwn = NONE_;
		}
	}
}



template<class _ItemType>
void DbManager<_ItemType>::select(printDirection& pd, int n)
{
	_ItemType tempString;
	Tree<_ItemType>* newTempTreePtr = new Tree<_ItemType>;
	bool finished = false;

	if (pd == IN_ORDER_) {
		myCurrDbPtr->ResetTree(IN_ORDER);
		int i = 0;
		while ((i < n) && (!finished)) {
			myCurrDbPtr->GetNextItem(tempString, IN_ORDER, finished);
			i++;
		}

		myCurrDbPtr->MakeInQueEmpty();
	}
	else if (pd == REVERSE_) {
		myCurrDbPtr->ResetTree(REVERSE_ORDER);
		int i = 0;
		while ((i < n) && (!finished)) {
			myCurrDbPtr->GetNextItem(tempString, REVERSE_ORDER, finished);
			i++;
		}

		myCurrDbPtr->MakeReverseQueEmpty();
	}

	if (finished == false) {
		newTempTreePtr->InsertItem(tempString);

		if ((*myCurrDbPtr) != (*newTempTreePtr)) {
			myDbBackStack.Push(newTempTreePtr);
			myDbForwardStack.MakeEmpty();
			myCurrDbPtr = newTempTreePtr;

			oper = "select";
			operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
			key = std::to_string(n);
			operKeyDoubleLL.Insert_with_Deleting_nextPos(key);

			searchNum++;
		}
		else {
			cout << "이전 검색결과와 같습니다. 새로운 검색을 진행하지 않습니다." << endl;
		}
	}
	else {
		cout << "데이터의 갯수보다 큽니다." << endl;
		cout << "이전 검색결과와 같습니다. 새로운 검색을 진행하지 않습니다." << endl;
	}
	
}



template<class _ItemType>
int DbManager<_ItemType>::SearchEleNum()
{
	return (myCurrDbPtr->EleNumIs());
}