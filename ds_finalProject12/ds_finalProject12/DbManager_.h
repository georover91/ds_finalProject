#include "DbManager.h"



// Class constructor & Class destructor /////////////////////////////////////////
template<class _ItemType>
DbManager<_ItemType>::DbManager()
{
	allDbPtr = new Tree<_ItemType>;	//allDb 생성.
	myDbBackStack.Push(allDbPtr);
	myCurrDbPtr = allDbPtr;

	searchNum = 0;
	cumNum = 0;
}

template<class _ItemType>
DbManager<_ItemType>::DbManager(Tree<_ItemType> T1)
{
	allDbPtr = new Tree<_ItemType>;	//allDb 생성.
	(*allDbPtr) = T1;
	myDbBackStack.Push(allDbPtr);
	myCurrDbPtr = allDbPtr;

	searchNum = 0;
	cumNum = 0;
}

//template<class _ItemType>
//DbManager<_ItemType>::~DbManager()
//{
//
//}
///////////////////////////////////////////////////////////////////////////////



// goBack & goForward /////////////////////////////////////////////////////////
template<class _ItemType>
void DbManager<_ItemType>::goBackward()
{
	if (myCurrDbPtr == allDbPtr) {		//현재 myCurrDb가 allDb이면,
		cout << "더이상 뒤로 되돌릴 Data Base History가 없습니다." << endl;
		return;	//아무 실행 안하고 함수 종료.
	}
	else {
		//myCurrDbPtr////
		myDbForwardStack.Push(myCurrDbPtr);		// go forward 명령어 실행에 대비해, myDbForwardStack에 현재 myCurrDbPtr값 저장.
		myDbBackStack.Pop();
		myDbBackStack.Top(myCurrDbPtr);		// myCurrDbPtr 값이 back스택에도 가장 위에 남아있도록 항상 실시간상태를 유지.

		//oper////
		operDoubleLL.GoToBeforePos();

		//key////
		keyDoubleLL.GoToBeforePos();
	}

	searchNum--;
}

template<class _ItemType>
void DbManager<_ItemType>::goForward()
{
	if (myDbForwardStack.IsEmpty()) {		// 앞으로갈 저장상태가 없으면,
		cout << "더이상 앞로 되돌릴 Data Base History가 없습니다." << endl;
		return;	//아무 실행 안하고 함수 종료.
	}
	else {
		//myCurrDbPtr
		myDbForwardStack.Top(myCurrDbPtr);
		myDbForwardStack.Pop();
		myDbBackStack.Push(myCurrDbPtr);		// myCurrDbPtr 값이 back스택에도 가장 위에 남아있도록 항상 실시간상태를 유지.

		//oper////
		operDoubleLL.GoToNextPos();

		//key////
		keyDoubleLL.GoToNextPos();
	}

	searchNum++;
}
/////////////////////////////////////////////////////////////////////////////



// Search & Insert /////////////////////////////////////////////////////////
template<class _ItemType>
void DbManager<_ItemType>::Search()
// 받은 oper과 key 값을 backStack에 저장까지 해줌.
{
	Tree<_ItemType>* newDbPtr;
	newDbPtr = new Tree<_ItemType>;		// 새 myDb 생성.

	//if (myCurrDbPtr->IsEmpty()) {
	//	cout << "Current data base is empty, so that it can't be searched." << endl;
	//	//cout << "Blank DB has been produced." << endl;
	//}
	//else {		
		string getString;
		//bool finished = false;
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
		//else {
		//	// 잘못된 oper을 입력하였으면, 아무 작업안하고 함수 빠져나감. 밖에서 oper입력 반복.
		//}
	//}

	myDbBackStack.Push(newDbPtr);
	myDbForwardStack.MakeEmpty();
	myCurrDbPtr = newDbPtr;

	operDoubleLL.Insert_with_Deleting_nextPos(oper);
	keyDoubleLL.Insert_with_Deleting_nextPos(key);

	searchNum++;
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
	else {		// key == NULL
		(*newDbPtr) = (*allDbPtr) - (*myCurrDbPtr);

		// 전체 데이터베이스에서 'key값으로 검색된 위 새 임시Db'(*newDbPtr)를 제외한다.
	}
	
}

template<class _ItemType>
void DbManager<_ItemType>::Search_and_not(Tree<_ItemType>*& newDbPtr)
{
	Search_not(newDbPtr);
	(*newDbPtr) = (*myCurrDbPtr) * (*newDbPtr);		// 여기서 (*newDbPtr)는 key값을 가진 문자열들의 여집합에 해당함. 
													//*myCurrDbPtr는 원본보존됨.
	//Search_strings_that_have_the_key_from_(myCurrDbPtr, newDbPtr);
	//(*newDbPtr) = (*myCurrDbPtr) - (*newDbPtr);					// 이 경우는 [not 이고, key가 "\0"인 경우]를 포함 못하나?
}

template<class _ItemType>
void DbManager<_ItemType>::Search_or_not(Tree<_ItemType>*& newDbPtr)
{
	Search_not(newDbPtr);
	(*newDbPtr) = (*myCurrDbPtr) + (*newDbPtr);		//*myCurrDbPtr와 *newDbPtr는 원본보존됨.
}

// Tree같 +, -, * 연산 중 *연산이 제일 오래 걸릴 것임. +와 - 연산은 비슷할 것임.



// allData ///////////////////////////////////////////
template<class _ItemType>
void DbManager<_ItemType>::allData()
{
	myDbBackStack.Push(allDbPtr);
	myDbForwardStack.MakeEmpty();
	myCurrDbPtr = allDbPtr;

	oper = "all data";
	operDoubleLL.Insert_with_Deleting_nextPos(oper);
	key = "\0";
	keyDoubleLL.Insert_with_Deleting_nextPos(key);

	searchNum++;
}
///////////////////////////////////////////////////




/*
template<class _ItemType>
void DbManager<_ItemType>::Insert_command_to_backStack()
{
	comBackStack.Push(command);	
	comForwardStack.MakeEmpty();
}

template<class _ItemType>
void DbManager<_ItemType>::Insert_tree_to_DoubleLL(Tree<_ItemType>* itemPtr)
{
	if (myDbDoubleLL.IsNextPosTrailer()) {	
		myDbDoubleLL.InsertLine(itemPtr);
	}
	else {		// 뒤로 갔다가 다시 검색해서 myCurrDb를 형성한 경우.
		myDbDoubleLL.GoToNextPos();
		myDbDoubleLL.DeleteLine();		//DeleteLine() 함수 자체에 삭제후, 그 삭제된 노드의 바로 전 노드로 위치를 옮기는 과정 포함됨.
		//현재위치 이후의 모든 myDbHistory를 삭제한 후 새 myDb를 history에 삽입하도록 한다.
		Insert_tree_to_DoubleLL(itemPtr);	//이를 recursive 형태로 구현.
	}
}
myDbDoubleLL의 currentPos의 위치는 comDoubleLL, operDoubleLL, 및 keyDoubleLLdml currentPos에 '+한칸' 한 것.

template<class _ItemType>
void DbManager<_ItemType>::Insert_oper_to_DoubleLL(_ItemType oper)
{
	if (operDoubleLL.IsNextPosTrailer()) {
		operDoubleLL.InsertLine(oper);
	}
	else {		// 뒤로 갔다가 다시 검색해서 myCurrDb를 형성한 경우.
		operDoubleLL.GoToNextPos();
		operDoubleLL.DeleteLine();		//DeleteLine() 함수 자체에 삭제후, 그 삭제된 노드의 바로 전 노드로 위치를 옮기는 과정 포함됨.
										//현재위치 이후의 모든 myDbHistory를 삭제한 후 새 myDb를 history에 삽입하도록 한다.
		Insert_oper_to_DoubleLL(oper);	//이를 recursive 형태로 구현.
	}
}

template<class _ItemType>
void DbManager<_ItemType>::Insert_key_to_DoubleLL(_ItemType key)
{
	if (keyDoubleLL.IsNextPosTrailer()) {
		keyDoubleLL.InsertLine(key);
	}
	else {		// 뒤로 갔다가 다시 검색해서 myCurrDb를 형성한 경우.
		keyDoubleLL.GoToNextPos();
		keyDoubleLL.DeleteLine();		//DeleteLine() 함수 자체에 삭제후, 그 삭제된 노드의 바로 전 노드로 위치를 옮기는 과정 포함됨.
										//현재위치 이후의 모든 myDbHistory를 삭제한 후 새 myDb를 history에 삽입하도록 한다.
		Insert_key_to_DoubleLL(key);	//이를 recursive 형태로 구현.
	}
}
*/
//////////////////////////////////////////////////////////////////////////////



// Print ////////////////////////////////////////////////////////////////////
template<class _ItemType>
void DbManager<_ItemType>::Print_myCurrDb()
{
	myCurrDbPtr->Print();
}

template<class _ItemType>
void DbManager<_ItemType>::Print_searchPath()
{
	DoubleLLNode<_ItemType>* tempOperPtr = NULL;
	DoubleLLNode<_ItemType>* tempKeyPtr = NULL;

	if ((!operDoubleLL.IsCurrPosHeader()) && (!keyDoubleLL.IsCurrPosHeader())) {
		do {
			cout << "->";
			cout << " ";
			operDoubleLL.Print_NextOne(tempOperPtr);
			//cout << tempOperPtr->topPtr->info << endl;		//이 코드 살리면, 이 코드 때문에 오류난다. headerPtr이 DoubleLL class 의 private맴버변수라면, tempOperPtr에 headerPtr값을 넣더라도 tempOperPtr를 조작해서는 DoubleLL class의 private맴버변수에 접근할 수 없다.
			cout << " ";
			cout << "\"";
			keyDoubleLL.Print_NextOne(tempKeyPtr);
			cout << "\"";
			cout << " ";
		} while ((tempOperPtr != NULL) && (tempKeyPtr != NULL));
		
		cout << endl;
	}
}

template<class _ItemType>
void DbManager<_ItemType>::Print_Nth_Search()
{
	cout << endl;
	cout << "<<<" << searchNum << "번째 검색." << ">>>" << "============================" << endl;
	cout << "---검색 연산자 및 검색어 히스토리------------" << endl;
	Print_searchPath();
	cout << "---------------------------------------------" << endl;
	Print_myCurrDb();
	cout << "=============================================" << endl;
	cout << endl;
}

template<class _ItemType>
void DbManager<_ItemType>::Print_to_myWriting()
{

}

template<class _ItemType>
void DbManager<_ItemType>::Print_to_file()
{

}
////////////////////////////////////////////////////////////////////////////