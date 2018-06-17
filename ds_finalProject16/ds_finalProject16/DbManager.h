#include <iostream>
#include <iomanip>
#include <fstream>

#include "StackType_.h"
#include "DoubleLL_.h"
#include "TreeType_.h"

#define minScreenWide 36



enum printTo { CONSOLE_, FILE_, MY_WRITING_ };
enum printDirection { NONE_, REVERSE_ };
enum printWithNum { NONE__, WITH_NUM_};



template<class _ItemType>
class DbManager 
{
public:
	DbManager();
	DbManager(Tree<_ItemType> T1);
	DbManager(ifstream& inFile);
	~DbManager();
	void MakeEmpty();
	void Initialize();
	void Initialize(Tree<_ItemType> T1);
	void Initialize(ifstream& inFile);
	void goBackward();
	void goForward();
	void Search();	//Tree<_ItemType>* myCurrDbPtr 는 맴버변수이므로, 맴버함수의 인수로 추가할 필요 없음.
	void Search_strings_that_have_the_key_from_(Tree<_ItemType>*& baseDbPtr, Tree<_ItemType>*& newDbPtr);
	void Search_and(Tree<_ItemType>*& newDbPtr);
	void Search_or(Tree<_ItemType>*& newDbPtr);
	void Search_not(Tree<_ItemType>*& newDbPtr);
	void Search_and_not(Tree<_ItemType>*& newDbPtr);
	void Search_or_not(Tree<_ItemType>*& newDbPtr);
	void allData();
	//void Insert_command_to_backStack();
	//void Insert_tree_to_DoubleLL(Tree<_ItemType>* itemPtr);
	//void Insert_oper_to_DoubleLL(_ItemType key);
	//void Insert_key_to_DoubleLL(_ItemType itemPtr);
	void Input_command();
	void Print_SearchDb(printTo PT, printDirection PD, printWithNum PWN);
	void Print_SearchRoute(printTo PT);
	void Print_SearchScreen();
	void Print_SearchScreen(printTo PT, printDirection PD, printWithNum PWN);
	void Print_Settings(string& what, printTo& pt, printDirection& pd, printWithNum& pwn);
	void Print_to_myWriting();
	void Print_to_file();
	void select(printDirection& pd, int n);

	int cumNum;
	int searchNum;
	string command;
	string oper;
	string key;
private:
	int screenWide;

	Tree<_ItemType>* allDbPtr;
	//Tree<_ItemType> allDb;		//생성자에서 처음에 myCurrDbPtr이 카리키도록 한 Tree class를 allDB로 여기기로 함.
	Tree<_ItemType>* myCurrDbPtr;		// myDb들 중 현재 검색되어 형성된 Db를 가라키는 포인터.

	Stack<Tree<_ItemType>*> myDbBackStack;
	Stack<Tree<_ItemType>*> myDbForwardStack;	//myDbHistory 형성하는 더블링크드 리스트 객체.
	//Stack<_ItemType> comBackStack;
	//Stack<_ItemType> comForwardStack;
	//Stack<_ItemType> operBackStack;
	//Stack<_ItemType> operForwardStack;
	//Stack<_ItemType> keyBackStack;
	//Stack<_ItemType> keyForwardStack;
	//DoubleLL<_ItemType> operDoubleLL;
	//DoubleLL<_ItemType> keyDoubleLL;
	DoubleLL<_ItemType> operKeyDoubleLL;
	
	//DoubleLL<_ItemType> myWriting;
};