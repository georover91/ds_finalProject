#include "DbManager.h"



// Class constructor & Class destructor /////////////////////////////////////////
template<class _ItemType>
DbManager<_ItemType>::DbManager()
{
	allDbPtr = new Tree<_ItemType>;	//allDb ����.
	myDbBackStack.Push(allDbPtr);
	myCurrDbPtr = allDbPtr;
}

template<class _ItemType>
DbManager<_ItemType>::DbManager(Tree<_ItemType> T1)
{
	allDbPtr = new Tree<_ItemType>;	//allDb ����.
	(*allDbPtr) = T1;
	myDbBackStack.Push(allDbPtr);
	myCurrDbPtr = allDbPtr;
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
	Tree<_ItemType>* tempDbPtr = myCurrDbPtr;		// 1. ���� myCurrDbPtr �� ���.

	if (myCurrDbPtr == allDbPtr) {		//���� myCurrDb�� allDb�̸�,
		cout << "���̻� �ڷ� �ǵ��� Data Base History�� �����ϴ�." << endl;
		return;	//�ƹ� ���� ���ϰ� �Լ� ����.
	}
	else {
		//myCurrDbPtr
		myDbForwardStack.Push(myCurrDbPtr);		// go forward ��ɾ� ���࿡ �����, myDbForwardStack�� ���� myCurrDbPtr�� ����.
		//myDbBackStack.Top(myCurrDbPtr);
		myDbBackStack.Pop();
		myDbBackStack.Top(myCurrDbPtr);		// myCurrDbPtr ���� back���ÿ��� ���� ���� �����ֵ��� �׻� �ǽð����¸� ����.

		////command
		//comForwardStack.Push(command);
		////comBackStack.Top(command);
		//comBackStack.Pop();
		//comBackStack.Top(command);

		//oper
		operForwardStack.Push(oper);
		//operBackStack.Top(oper);
		operBackStack.Pop();
		if (!operBackStack.IsEmpty()) {	// BackStack�� ����������� Top() �ɹ��Լ��� �����ϴ� ���� �����ϱ� ���� �ڵ�. �ʱ�DbPtr�� �ǵ����� ��츦 ����� �ڵ�. 
			operBackStack.Top(oper);
		}
		else {}	

		//key
		keyForwardStack.Push(key);
		//keyBackStack.Top(key);
		keyBackStack.Pop();
		if (!operBackStack.IsEmpty()) {	// BackStack�� ����������� Top() �ɹ��Լ��� �����ϴ� ���� �����ϱ� ���� �ڵ�. �ʱ�DbPtr�� �ǵ����� ��츦 ����� �ڵ�. 
			keyBackStack.Top(key);
		}
		else {}
	}
}

template<class _ItemType>
void DbManager<_ItemType>::goForward()
{
	//Tree<_ItemType>* tempDbPtr = myCurrDbPtr;		// 1. ���� myCurrDbPtr �� ���.

	if (myDbForwardStack.IsEmpty()) {		// �����ΰ� ������°� ������,
		cout << "���̻� �շ� �ǵ��� Data Base History�� �����ϴ�." << endl;
		return;	//�ƹ� ���� ���ϰ� �Լ� ����.
	}
	else {
		//myCurrDbPtr
		myDbForwardStack.Top(myCurrDbPtr);
		myDbForwardStack.Pop();
		myDbBackStack.Push(myCurrDbPtr);		// myCurrDbPtr ���� back���ÿ��� ���� ���� �����ֵ��� �׻� �ǽð����¸� ����.

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
	}
}
/////////////////////////////////////////////////////////////////////////////



// Search & Insert /////////////////////////////////////////////////////////
template<class _ItemType>
void DbManager<_ItemType>::Search_in_myCurrDb()
// ���� oper�� key ���� backStack�� ������� ����.
{
	Tree<_ItemType>* newDbPtr;
	newDbPtr = new Tree<_ItemType>;		// �� myDb ����.

	if (myCurrDbPtr->IsEmpty()) {
		cout << "Current data base is empty, so that it can't be searched." << endl;
		//cout << "Blank DB has been produced." << endl;
	}
	else {		
		string getString;
		bool finished = false;
		if (oper == "and") {
			myCurrDbPtr->ResetTree(IN_ORDER);
			while (!finished) {
				myCurrDbPtr->GetNextItem(getString, IN_ORDER, finished);
				if (getString.find(key) != string::npos) {
					newDbPtr->InsertItem(getString);
				}
			}
		}
		else if (oper == "or") {
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
		else {
			// �߸��� oper�� �Է��Ͽ�����, �ƹ� �۾����ϰ� �Լ� ��������. �ۿ��� oper�Է� �ݺ�.
		}
	}

	myDbBackStack.Push(newDbPtr);
	myDbForwardStack.MakeEmpty();
	myCurrDbPtr = newDbPtr;
	//comBackStack.Push(command);		
	//comForwardStack.MakeEmpty();
	operBackStack.Push(oper);
	operForwardStack.MakeEmpty();
	keyBackStack.Push(key);
	keyForwardStack.MakeEmpty();
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