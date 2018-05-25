#include <iostream>
#include <fstream>

#include "StackType_.h"
#include "DoubleLL_.h"
#include "TreeType_.h"



template<class _ItemType>
class DbManager 
{
public:
	DbManager();
	//~DbManager();
	void goForward();
	void goBackward();
	void search_in_myCurrDb(char oper, _ItemType key);	//Tree<_ItemType>* myCurrDbPtr 는 맴버변수이므로, 맴버함수의 인수로 추가할 필요 없음.
	void Print_myCurrDb();
	void Print_to_myWriting();
	void Print_to_file();

private:
	Tree<_ItemType>* allDbPtr;
	//Tree<_ItemType> allDb;		//생성자에서 처음에 myCurrDbPtr이 카리키도록 한 Tree class를 allDB로 여기기로 함.
	Tree<_ItemType>* myCurrDbPtr;		// myDb들 중 현재 검색되어 형성된 Db를 가라키는 포인터.
	Stack<Tree<_ItemType>*> myDbStack;
	Stack<_ItemType> comStack;
	Stack<_ItemType> keyStack;
	DoubleLL<_ItemType> myWriting;
};