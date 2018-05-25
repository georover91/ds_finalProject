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
	DbManager(Tree<_ItemType> T1);
	//~DbManager();
	void goBackward();
	void goForward();
	void Search_in_myCurrDb();	//Tree<_ItemType>* myCurrDbPtr �� �ɹ������̹Ƿ�, �ɹ��Լ��� �μ��� �߰��� �ʿ� ����.
	//void Insert_command_to_backStack();
	//void Insert_tree_to_DoubleLL(Tree<_ItemType>* itemPtr);
	//void Insert_oper_to_DoubleLL(_ItemType key);
	//void Insert_key_to_DoubleLL(_ItemType itemPtr);
	void Print_myCurrDb(std::ofstream& outFile);
	void Print_to_myWriting();
	void Print_to_file();

	string command;
	string oper;
	string key;
private:
	Tree<_ItemType>* allDbPtr;
	//Tree<_ItemType> allDb;		//�����ڿ��� ó���� myCurrDbPtr�� ī��Ű���� �� Tree class�� allDB�� ������ ��.
	Tree<_ItemType>* myCurrDbPtr;		// myDb�� �� ���� �˻��Ǿ� ������ Db�� ����Ű�� ������.

	Stack<Tree<_ItemType>*> myDbBackStack;
	Stack<Tree<_ItemType>*> myDbForwardStack;	//myDbHistory �����ϴ� ����ũ�� ����Ʈ ��ü.
	//Stack<_ItemType> comBackStack;
	//Stack<_ItemType> comForwardStack;
	Stack<_ItemType> operBackStack;
	Stack<_ItemType> operForwardStack;
	Stack<_ItemType> keyBackStack;
	Stack<_ItemType> keyForwardStack;

	Stack<_ItemType> myWriting;
};