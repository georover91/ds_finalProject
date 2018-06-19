#include <iostream>
#include <iomanip>
#include <fstream>

#include "StackType_.h"
#include "DoubleLL_.h"
#include "TreeType_.h"

#define minScreenWide 36



enum printTo { CONSOLE_, FILE_};
enum printDirection { IN_ORDER_, REVERSE_ };		//Que������ IN_ORDER�� ����� ����.
enum printWithNum { NONE_, WITH_NUM_};



template<class _ItemType>
class DbManager 
{
public:
	DbManager();
	DbManager(Tree<_ItemType> T1);		// Tree�ڷᱸ���� �޾� database manager ��ü�� �����ϰ� �ϴ� ������.
	DbManager(ifstream& inFile);		// inFile�� �� �Է������� �о�鿩 �ű⼭ ������ �޾� �ʱ� �����ͺ��̽� Ʈ���� �����ϴ� database manager ��ü�� ����� ������.
	~DbManager();
	void MakeEmpty();
	void Initialize();
	void Initialize(Tree<_ItemType> T1);
	void Initialize(ifstream& inFile);
	void goBackward();
	void goForward();
	void Input_command();
	void Search();	//Tree<_ItemType>* myCurrDbPtr �� �ɹ������̹Ƿ�, �ɹ��Լ��� �μ��� �߰��� �ʿ� ����.
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
	Tree<_ItemType>* myCurrDbPtr;		// myDb�� �� ���� �˻��Ǿ� ������ Db�� ����Ű�� ������.

	Stack<Tree<_ItemType>*> myDbBackStack;
	Stack<Tree<_ItemType>*> myDbForwardStack;	//myDbHistory �����ϴ� ����ũ�� ����Ʈ ��ü.
	
	DoubleLL<_ItemType> operKeyDoubleLL;
};