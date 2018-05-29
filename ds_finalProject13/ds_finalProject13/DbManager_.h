#include "DbManager.h"



// Class constructor & Class destructor /////////////////////////////////////////
template<class _ItemType>
DbManager<_ItemType>::DbManager()
{
	allDbPtr = new Tree<_ItemType>;	//allDb ����.
	myDbBackStack.Push(allDbPtr);
	myCurrDbPtr = allDbPtr;

	//operKeyDoubleLL.MakeEmpty();
	oper = "all data";
	key = "\0";
	operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
	operKeyDoubleLL.Insert_with_Deleting_nextPos(key);

	searchNum = 0;
	cumNum = 0;
}

template<class _ItemType>
DbManager<_ItemType>::DbManager(Tree<_ItemType> T1)
{
	allDbPtr = new Tree<_ItemType>;	//allDb ����.
	(*allDbPtr) = T1;
	myDbBackStack.Push(allDbPtr);
	myCurrDbPtr = allDbPtr;

	//operKeyDoubleLL.MakeEmpty();
	oper = "all data";
	key = "\0";
	operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
	operKeyDoubleLL.Insert_with_Deleting_nextPos(key);

	searchNum = 0;
	cumNum = 0;
}

template<class _ItemType>
DbManager<_ItemType>::DbManager(ifstream& inFile)
{
	allDbPtr = new Tree<_ItemType>;	//allDb ����.
	
	string command_data;
	//int numCommands;
	int numData;

	numData = 0;
	getline(inFile, command_data);	// '�ʱ�DB��������'�� �� ���� ������� �޾ƿ�.
	if (command_data == "InsertStrings") {
		getline(inFile, command_data);
		while (command_data != "Quit") {	// �Է������� �Է¹������ �ϳ��� �Լ� �о���δ�.
			(*allDbPtr).InsertItem(command_data);
			numData++;
			cout << numData << "th data has been inputed: " << command_data << endl;
			getline(inFile, command_data);
		}
	}
	else {
		cout << "Command Error. or Data Error." << endl;
	}



	myDbBackStack.Push(allDbPtr);
	myCurrDbPtr = allDbPtr;

	//operKeyDoubleLL.MakeEmpty();
	oper = "all data";
	key = "\0";
	operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
	operKeyDoubleLL.Insert_with_Deleting_nextPos(key);

	searchNum = 0;
	cumNum = 0;
}

//template<class _ItemType>
//DbManager<_ItemType>::~DbManager()
//{
//
//}
///////////////////////////////////////////////////////////////////////////////



// initailize ////////////////////////////
template<class _ItemType>
void DbManager<_ItemType>::Initailize()
{
	delete allDbPtr;
	allDbPtr = new Tree<_ItemType>;	//allDb ����.

	myDbBackStack.MakeEmpty();
	myDbBackStack.Push(allDbPtr);
	myDbForwardStack.MakeEmpty();

	myCurrDbPtr = allDbPtr;

	operKeyDoubleLL.MakeEmpty();
	oper = "all data";
	key = "\0";
	operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
	operKeyDoubleLL.Insert_with_Deleting_nextPos(key);

	searchNum = 0;
	cumNum = 0;
}

template<class _ItemType>
void  DbManager<_ItemType>::Initailize(ifstream& inFile)
{
	delete allDbPtr;
	allDbPtr = new Tree<_ItemType>;	//allDb ����.

	string command_data;
	//int numCommands;
	int numData;

	numData = 0;
	getline(inFile, command_data);	// '�ʱ�DB��������'�� �� ���� ������� �޾ƿ�.
	if (command_data == "InsertStrings") {
		getline(inFile, command_data);
		while (command_data != "Quit") {	// �Է������� �Է¹������ �ϳ��� �Լ� �о���δ�.
			(*allDbPtr).InsertItem(command_data);
			numData++;
			cout << numData << "th data has been inputed: " << command_data << endl;
			getline(inFile, command_data);
		}
	}
	else {
		cout << "Command Error. or Data Error." << endl;
	}

	

	myDbBackStack.MakeEmpty();
	myDbBackStack.Push(allDbPtr);
	myDbForwardStack.MakeEmpty();

	myCurrDbPtr = allDbPtr;

	operKeyDoubleLL.MakeEmpty();
	oper = "all data";
	key = "\0";
	operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
	operKeyDoubleLL.Insert_with_Deleting_nextPos(key);

	searchNum = 0;
	cumNum = 0;
}
///////////////////////////////////////



// goBack & goForward /////////////////////////////////////////////////////////
template<class _ItemType>
void DbManager<_ItemType>::goBackward()
{
	if (myCurrDbPtr == allDbPtr) {		//���� myCurrDb�� allDb�̸�,
		cout << "���̻� �ڷ� �ǵ��� Data Base History�� �����ϴ�." << endl;
		return;	//�ƹ� ���� ���ϰ� �Լ� ����.
	}
	else {
		//myCurrDbPtr////
		myDbForwardStack.Push(myCurrDbPtr);		// go forward ��ɾ� ���࿡ �����, myDbForwardStack�� ���� myCurrDbPtr�� ����.
		myDbBackStack.Pop();
		myDbBackStack.Top(myCurrDbPtr);		// myCurrDbPtr ���� back���ÿ��� ���� ���� �����ֵ��� �׻� �ǽð����¸� ����.

		//oper & key////
		operKeyDoubleLL.GoToBeforePos();
		operKeyDoubleLL.GoToBeforePos();
	}

	searchNum--;
}

template<class _ItemType>
void DbManager<_ItemType>::goForward()
{
	if (myDbForwardStack.IsEmpty()) {		// �����ΰ� ������°� ������,
		cout << "���̻� �շ� �ǵ��� Data Base History�� �����ϴ�." << endl;
		return;	//�ƹ� ���� ���ϰ� �Լ� ����.
	}
	else {
		//myCurrDbPtr
		myDbForwardStack.Top(myCurrDbPtr);
		myDbForwardStack.Pop();
		myDbBackStack.Push(myCurrDbPtr);		// myCurrDbPtr ���� back���ÿ��� ���� ���� �����ֵ��� �׻� �ǽð����¸� ����.

		//oper & key////
		operKeyDoubleLL.GoToNextPos();
		operKeyDoubleLL.GoToNextPos();
	}

	searchNum++;
}
/////////////////////////////////////////////////////////////////////////////



// Search & Insert /////////////////////////////////////////////////////////
template<class _ItemType>
void DbManager<_ItemType>::Search()
// ���� oper�� key ���� backStack�� ������� ����.
{
	Tree<_ItemType>* newDbPtr;
	newDbPtr = new Tree<_ItemType>;		// �� myDb ����.

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
		//	// �߸��� oper�� �Է��Ͽ�����, �ƹ� �۾����ϰ� �Լ� ��������. �ۿ��� oper�Է� �ݺ�.
		//}
	//}

	myDbBackStack.Push(newDbPtr);
	myDbForwardStack.MakeEmpty();
	myCurrDbPtr = newDbPtr;

	operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
	operKeyDoubleLL.Insert_with_Deleting_nextPos(key);

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
		// �ʱ� �����ͺ��̽����� key���� �� ���ڿ��� ã�Ƴ� ��
		Search_strings_that_have_the_key_from_(allDbPtr, newDbPtr);

		// ��ü �����ͺ��̽����� 'key������ �˻��� Db'(*newDbPtr)�� �����Ѵ�.
		(*newDbPtr) = (*allDbPtr) - (*newDbPtr);	
	}
	else {		// key == NULL
		(*newDbPtr) = (*allDbPtr) - (*myCurrDbPtr);

		// ��ü �����ͺ��̽����� 'key������ �˻��� �� �� �ӽ�Db'(*newDbPtr)�� �����Ѵ�.
	}
	
}

template<class _ItemType>
void DbManager<_ItemType>::Search_and_not(Tree<_ItemType>*& newDbPtr)
{
	Search_not(newDbPtr);
	(*newDbPtr) = (*myCurrDbPtr) * (*newDbPtr);		// ���⼭ (*newDbPtr)�� key���� ���� ���ڿ����� �����տ� �ش���. 
													//*myCurrDbPtr�� ����������.
	//Search_strings_that_have_the_key_from_(myCurrDbPtr, newDbPtr);
	//(*newDbPtr) = (*myCurrDbPtr) - (*newDbPtr);					// �� ���� [not �̰�, key�� "\0"�� ���]�� ���� ���ϳ�?
}

template<class _ItemType>
void DbManager<_ItemType>::Search_or_not(Tree<_ItemType>*& newDbPtr)
{
	Search_not(newDbPtr);
	(*newDbPtr) = (*myCurrDbPtr) + (*newDbPtr);		//*myCurrDbPtr�� *newDbPtr�� ����������.
}

// Tree�� +, -, * ���� �� *������ ���� ���� �ɸ� ����. +�� - ������ ����� ����.



// allData ///////////////////////////////////////////
template<class _ItemType>
void DbManager<_ItemType>::allData()
{
	myDbBackStack.Push(allDbPtr);
	myDbForwardStack.MakeEmpty();
	myCurrDbPtr = allDbPtr;

	oper = "all data";
	operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
	key = "\0";
	operKeyDoubleLL.Insert_with_Deleting_nextPos(key);

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
	else {		// �ڷ� ���ٰ� �ٽ� �˻��ؼ� myCurrDb�� ������ ���.
		myDbDoubleLL.GoToNextPos();
		myDbDoubleLL.DeleteLine();		//DeleteLine() �Լ� ��ü�� ������, �� ������ ����� �ٷ� �� ���� ��ġ�� �ű�� ���� ���Ե�.
		//������ġ ������ ��� myDbHistory�� ������ �� �� myDb�� history�� �����ϵ��� �Ѵ�.
		Insert_tree_to_DoubleLL(itemPtr);	//�̸� recursive ���·� ����.
	}
}
myDbDoubleLL�� currentPos�� ��ġ�� comDoubleLL, operDoubleLL, �� keyDoubleLLdml currentPos�� '+��ĭ' �� ��.

template<class _ItemType>
void DbManager<_ItemType>::Insert_oper_to_DoubleLL(_ItemType oper)
{
	if (operDoubleLL.IsNextPosTrailer()) {
		operDoubleLL.InsertLine(oper);
	}
	else {		// �ڷ� ���ٰ� �ٽ� �˻��ؼ� myCurrDb�� ������ ���.
		operDoubleLL.GoToNextPos();
		operDoubleLL.DeleteLine();		//DeleteLine() �Լ� ��ü�� ������, �� ������ ����� �ٷ� �� ���� ��ġ�� �ű�� ���� ���Ե�.
										//������ġ ������ ��� myDbHistory�� ������ �� �� myDb�� history�� �����ϵ��� �Ѵ�.
		Insert_oper_to_DoubleLL(oper);	//�̸� recursive ���·� ����.
	}
}

template<class _ItemType>
void DbManager<_ItemType>::Insert_key_to_DoubleLL(_ItemType key)
{
	if (keyDoubleLL.IsNextPosTrailer()) {
		keyDoubleLL.InsertLine(key);
	}
	else {		// �ڷ� ���ٰ� �ٽ� �˻��ؼ� myCurrDb�� ������ ���.
		keyDoubleLL.GoToNextPos();
		keyDoubleLL.DeleteLine();		//DeleteLine() �Լ� ��ü�� ������, �� ������ ����� �ٷ� �� ���� ��ġ�� �ű�� ���� ���Ե�.
										//������ġ ������ ��� myDbHistory�� ������ �� �� myDb�� history�� �����ϵ��� �Ѵ�.
		Insert_key_to_DoubleLL(key);	//�̸� recursive ���·� ����.
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
	operKeyDoubleLL.Print_operKey_history();
}

template<class _ItemType>
void DbManager<_ItemType>::Print_Nth_Search()
{
	cout << endl;
	if (searchNum == 0) {
		cout << "<<<" << "�ʱ� �����ͺ��̽�." << ">>>" << "=====================" << endl;
	}
	else {
		cout << "<<<" << searchNum << "��° �˻����." << ">>>" << "============================" << endl;
	}
	cout << "---�˻� ������ �� �˻��� �����丮------------" << endl;
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