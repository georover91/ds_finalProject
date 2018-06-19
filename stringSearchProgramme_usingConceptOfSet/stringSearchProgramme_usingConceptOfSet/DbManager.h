#include <iostream>
#include <iomanip>
#include <fstream>

#include "StackType_.h"
#include "DoubleLL_.h"
#include "TreeType_.h"

#define minScreenWide 36



enum printTo { CONSOLE_, FILE_};
enum printDirection { IN_ORDER_, REVERSE_ };		//Que에서의 IN_ORDER와 헤깔리지 말것.
enum printWithNum { NONE_, WITH_NUM_};



template<class _ItemType>
class DbManager 
{
public:
	DbManager();
	DbManager(Tree<_ItemType> T1);		// Tree자료구조를 받아 database manager 객체를 구성하게 하는 생성자.
	DbManager(ifstream& inFile);		// inFile이 연 입력파일을 읽어들여 거기서 데이터 받아 초기 데이터베이스 트리를 구성하는 database manager 객체를 만드는 생성자.
	~DbManager();
	void MakeEmpty();
	void Initialize();
	void Initialize(Tree<_ItemType> T1);
	void Initialize(ifstream& inFile);
	void goBackward();
	void goForward();
	void Input_command();
	void Search();	//Tree<_ItemType>* myCurrDbPtr 는 맴버변수이므로, 맴버함수의 인수로 추가할 필요 없음.
	void Search_strings_that_have_the_key_from_(Tree<_ItemType>*& baseDbPtr, Tree<_ItemType>*& newDbPtr);
	void Search_and(Tree<_ItemType>*& newDbPtr);
	void Search_or(Tree<_ItemType>*& newDbPtr);
	void Search_not(Tree<_ItemType>*& newDbPtr);
	void Search_and_not(Tree<_ItemType>*& newDbPtr);
	void Search_or_not(Tree<_ItemType>*& newDbPtr);
	void allData();	
	void Print_SearchScreen();
	void Print_SearchScreen(printTo PT, printDirection PD, printWithNum PWN);
	void Print_SearchRoute(printTo PT);
	void Print_SearchDb(printTo PT, printDirection PD, printWithNum PWN);
	void PrintSettings(string& what, printTo& pt, printDirection& pd, printWithNum& pwn);
	void select(printDirection& pd, int n);
	int SearchEleNum();

	int comNum;
	int searchNum;
	string command;
	string oper;
	string key;
private:
	int screenWide;

	Tree<_ItemType>* allDbPtr;
	Tree<_ItemType>* myCurrDbPtr;		// myDb들 중 현재 검색되어 형성된 Db를 가라키는 포인터.

	Stack<Tree<_ItemType>*> myDbBackStack;
	Stack<Tree<_ItemType>*> myDbForwardStack;	//myDbHistory 형성하는 더블링크드 리스트 객체.
	
	DoubleLL<_ItemType> operKeyDoubleLL;
};