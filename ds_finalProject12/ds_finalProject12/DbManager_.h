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
	Tree<_ItemType>* tempDbPtr = myCurrDbPtr;		// 1. 현재 myCurrDbPtr 값 백업.

	if (myCurrDbPtr == allDbPtr) {		//현재 myCurrDb가 allDb이면,
		cout << "더이상 뒤로 되돌릴 Data Base History가 없습니다." << endl;
		return;	//아무 실행 안하고 함수 종료.
	}
	else {
		//myCurrDbPtr////
		myDbForwardStack.Push(myCurrDbPtr);		// go forward 명령어 실행에 대비해, myDbForwardStack에 현재 myCurrDbPtr값 저장.
		//myDbBackStack.Top(myCurrDbPtr);
		myDbBackStack.Pop();
		myDbBackStack.Top(myCurrDbPtr);		// myCurrDbPtr 값이 back스택에도 가장 위에 남아있도록 항상 실시간상태를 유지.

		//command////

		//oper////
		operDoubleLL.GoToBeforePos();

		//key////
		keyDoubleLL.GoToBeforePos();

		/*
		//oper////
		operForwardStack.Push(oper);
		//operBackStack.Top(oper);
		operBackStack.Pop();
		if (!operBackStack.IsEmpty()) {	// BackStack이 비어있음에도 Top() 맴버함수를 실행하는 것을 방지하기 위한 코딩. 초기DbPtr로 되돌리는 경우를 고려한 코딩. 
			operBackStack.Top(oper);
		}
		else {}	

		//key
		keyForwardStack.Push(key);
		//keyBackStack.Top(key);
		keyBackStack.Pop();
		if (!operBackStack.IsEmpty()) {	// BackStack이 비어있음에도 Top() 맴버함수를 실행하는 것을 방지하기 위한 코딩. 초기DbPtr로 되돌리는 경우를 고려한 코딩. 
			keyBackStack.Top(key);
		}
		else {}
		*/
	}

	searchNum--;
}

template<class _ItemType>
void DbManager<_ItemType>::goForward()
{
	//Tree<_ItemType>* tempDbPtr = myCurrDbPtr;		// 1. 현재 myCurrDbPtr 값 백업.

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

		/*
		//command
		//comForwardStack.Top(command);
		//comForwardStack.Pop();
		//comBackStack.Push(command);

		//oper
		operForwardStack.Top(oper);
		operForwardStack.Pop();
		operBackStack.Push(oper);

		//key
		keyForwardStack.Top(key);
		keyForwardStack.Pop();
		keyBackStack.Push(key);
		*/
	}

	searchNum++;
}
/////////////////////////////////////////////////////////////////////////////



// Search & Insert /////////////////////////////////////////////////////////
template<class _ItemType>
void DbManager<_ItemType>::Search_in_myCurrDb()
// 받은 oper과 key 값을 backStack에 저장까지 해줌.
{
	Tree<_ItemType>* newDbPtr;
	newDbPtr = new Tree<_ItemType>;		// 새 myDb 생성.

	if (myCurrDbPtr->IsEmpty()) {
		cout << "Current data base is empty, so that it can't be searched." << endl;
		//cout << "Blank DB has been produced." << endl;
	}
	else {		
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
		else {
			// 잘못된 oper을 입력하였으면, 아무 작업안하고 함수 빠져나감. 밖에서 oper입력 반복.
		}
	}

	myDbBackStack.Push(newDbPtr);
	myDbForwardStack.MakeEmpty();
	myCurrDbPtr = newDbPtr;

	operDoubleLL.Insert_with_Deleting_nextPos(oper);

	keyDoubleLL.Insert_with_Deleting_nextPos(key);

	/*
	//comBackStack.Push(command);		
	//comForwardStack.MakeEmpty();
	operBackStack.Push(oper);
	operForwardStack.MakeEmpty();
	keyBackStack.Push(key);
	keyForwardStack.MakeEmpty();
	*/

	searchNum++;
}

template<class _ItemType>
void DbManager<_ItemType>::Search_and(Tree<_ItemType>*& newDbPtr)
{
	string getString;
	bool finished = false;
	myCurrDbPtr->ResetTree(IN_ORDER);
	while (!finished) {
		myCurrDbPtr->GetNextItem(getString, IN_ORDER, finished);
		if (getString.find(key) != string::npos) {
			newDbPtr->InsertItem(getString);
		}
	}

}

template<class _ItemType>
void DbManager<_ItemType>::Search_or(Tree<_ItemType>*& newDbPtr)
{
	string getString;
	bool finished = false;
	allDbPtr->ResetTree(IN_ORDER);
	while (!finished) {
		allDbPtr->GetNextItem(getString, IN_ORDER, finished);
		if (getString.find(key) != string::npos) {
			newDbPtr->InsertItem(getString);
		}
	}

	Tree<_ItemType> tempDb = (*myCurrDbPtr);
	tempDb.Merge(*newDbPtr);
	(*newDbPtr) = tempDb;
	
}

template<class _ItemType>
void DbManager<_ItemType>::Search_not(Tree<_ItemType>*& newDbPtr)
{
	if ((key != NULL) {
		// 초기 데이터베이스에서 key값이 들어간 문자열을 찾아낸 후
		string getString;
		bool finished = false;
		allDbPtr->ResetTree(IN_ORDER);
		while (!finished) {
			allDbPtr->GetNextItem(getString, IN_ORDER, finished);
			if (getString.find(key) != string::npos) {
				newDbPtr->InsertItem(getString);
			}
		}

		Tree<_ItemType> tempDb = (*allDbPtr);
		tempDb.Extract(*newDbPtr);		// 전체 데이터베이스에서 'key값으로 검색된 위 새 임시Db'(*newDbPtr)를 제외한다.
		(*newDbPtr) = tempDb;		// 그리고 다시 newDb(*newDbPtr)에 그 결과Db(tempDb)를 넣어준다.

	}
	else {		// key == NULL
		Tree<_ItemType> tempDb = (*allDbPtr);
		tempDb.Extract(*myCurrDbPtr);		// 전체 데이터베이스에서 'key값으로 검색된 위 새 임시Db'(*newDbPtr)를 제외한다.
		(*newDbPtr) = tempDb;
	}
	
}

template<class _ItemType>
void DbManager<_ItemType>::Search_and_not(Tree<_ItemType>*& newDbPtr)
{
	string getString;
	bool finished = false;
	myCurrDbPtr->ResetTree(IN_ORDER);
	while (!finished) {
		myCurrDbPtr->GetNextItem(getString, IN_ORDER, finished);
		if (getString.find(key) != string::npos) {
			newDbPtr->InsertItem(getString);
		}
	}

	Tree<_ItemType> tempDb = (*myCurrDbPtr);
	tempDb.Extract(*newDbPtr);
	(*newDbPtr) = tempDb;
}

template<class _ItemType>
void DbManager<_ItemType>::Search_or_not(Tree<_ItemType>*& newDbPtr)
{

}














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
void DbManager<_ItemType>::Print_myCurrDb(std::ofstream& outFile)
{
	myCurrDbPtr->Print(outFile);
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