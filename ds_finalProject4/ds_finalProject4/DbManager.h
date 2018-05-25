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
	void search_in_myCurrDb(char oper, _ItemType key);	//Tree<_ItemType>* myCurrDbPtr �� �ɹ������̹Ƿ�, �ɹ��Լ��� �μ��� �߰��� �ʿ� ����.
	void Print_myCurrDb();
	void Print_to_myWriting();
	void Print_to_file();

private:
	Tree<_ItemType>* allDbPtr;
	//Tree<_ItemType> allDb;		//�����ڿ��� ó���� myCurrDbPtr�� ī��Ű���� �� Tree class�� allDB�� ������ ��.
	Tree<_ItemType>* myCurrDbPtr;		// myDb�� �� ���� �˻��Ǿ� ������ Db�� ����Ű�� ������.
	Stack<Tree<_ItemType>*> myDbStack;
	Stack<_ItemType> comStack;
	Stack<_ItemType> keyStack;
	DoubleLL<_ItemType> myWriting;
};