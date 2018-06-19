#include "DbManager.h"



template<class _ItemType>
DbManager<_ItemType>::DbManager()
{
	//allDbPtr �� allDb �ʱ� ����.
	allDbPtr = new Tree<_ItemType>;	//allDb ����.
	/// allDb Tree ���� ���� ����.


	// myCurrDbPtr �ʱ� ����.
	myCurrDbPtr = allDbPtr;


	// �˻���� �����丮 �ʱ� ����.
	myDbBackStack.Push(allDbPtr);		// == myDbBackStack.Push(myCurrDbPtr);


	// �˻������� �� �˻��� �����丮 �ʱ� ����.
	oper = "all data";
	key = "\0";
	operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
	operKeyDoubleLL.Insert_with_Deleting_nextPos(key);


	////////// �� �κ��� initialize �ɹ��Լ����� ������, �����ڿ�  MakeEmpty �ɹ��Լ����� �ִ� �ڵ� �κ�.///
	// �˻�Ƚ�� �� ���Ƚ�� �ʱ�ȭ.
	searchNum = 0;
	comNum = 0;


	// ��ɾ�, �˻� ������, �˻��� �����ϴ� ���ڿ� �ʱ�ȭ.
	command = "\0";
	oper = "\0";
	key = "\0";
}

template<class _ItemType>
DbManager<_ItemType>::DbManager(Tree<_ItemType> T1)
{
	//allDbPtr �� allDb �ʱ� ����.
	allDbPtr = new Tree<_ItemType>;	//allDb ����.
	/// allDb Tree ���� ����.
	(*allDbPtr) = T1;


	// myCurrDbPtr �ʱ� ����.
	myCurrDbPtr = allDbPtr;


	// �˻���� �����丮 �ʱ� ����.
	myDbBackStack.Push(allDbPtr);		// == myDbBackStack.Push(myCurrDbPtr);


	// �˻������� �� �˻��� �����丮 �ʱ� ����.
	oper = "all data";
	key = "\0";
	operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
	operKeyDoubleLL.Insert_with_Deleting_nextPos(key);


	// �˻�Ƚ�� �� ���Ƚ�� �ʱ�ȭ.
	searchNum = 0;
	comNum = 0;


	// ��ɾ�, �˻� ������, �˻��� �����ϴ� ���ڿ� �ʱ�ȭ.
	command = "\0";
	oper = "\0";
	key = "\0";
}

template<class _ItemType>
DbManager<_ItemType>::DbManager(ifstream& inFile)
{
	//allDbPtr �� allDb �ʱ� ����.
	allDbPtr = new Tree<_ItemType>;	//allDb ����.

	// �Է������� ������ �о�, allDb�� ���� �����ϱ�.
	string command_data;
	int numData = 0;
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
	cout << endl;
	cout << endl;


	// myCurrDbPtr �ʱ� ����.
	myCurrDbPtr = allDbPtr;


	// �˻���� �����丮 �ʱ� ����.
	myDbBackStack.Push(allDbPtr);		// == myDbBackStack.Push(myCurrDbPtr);


	// �˻������� �� �˻��� �����丮 �ʱ� ����.
	oper = "all data";
	key = "\0";
	operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
	operKeyDoubleLL.Insert_with_Deleting_nextPos(key);


	// �˻�Ƚ�� �� ���Ƚ�� �ʱ�ȭ.
	searchNum = 0;
	comNum = 0;


	// ��ɾ�, �˻� ������, �˻��� �����ϴ� ���ڿ� �ʱ�ȭ.
	command = "\0";
	oper = "\0";
	key = "\0";
}

template<class _ItemType>
DbManager<_ItemType>::~DbManager()
{
	cout << "���α׷��� �����ϴ� �� �Դϴ�..." << endl;
	MakeEmpty();
	cout << "���α׷��� �����մϴ�." << endl;
}

template<class _ItemType>
void DbManager<_ItemType>::MakeEmpty()
{
	// allDb �� allDbPtr �ʱ�ȭ.
	Tree<_ItemType>* tempPtr;

	//////�Ʒ� while�� 2������ �ڲ� ���� ���µ�, all data ��ɾ ���� ����Ǿ� ����, �� �����Ͱ� �ϳ��� ���� ��ü�� ����Ű�� ��찡 ���ܼ�, �� ��ü delete �ϴµ� �������� ��ü�� �Ҹ�õ� �� ��.
	while (!myDbBackStack.IsEmpty()) {
		myDbBackStack.Top(tempPtr);
		////// �Ʒ��� �� ù��° ����° ������ �����ؼ� ����Ǵ� ���� �ϳ��� �ι�° ������ ����Ǵ� �Ͱ� ����?
		tempPtr->MakeEmpty();
		tempPtr->~Tree();
		delete tempPtr;
		myDbBackStack.Pop();
	}
	myDbBackStack.MakeEmpty();

	while (!myDbForwardStack.IsEmpty()) {
		myDbForwardStack.Top(tempPtr);
		////// �Ʒ��� �� ù��° ����° ������ �����ؼ� ����Ǵ� ���� �ϳ��� �ι�° ������ ����Ǵ� �Ͱ� ����?
		tempPtr->MakeEmpty();
		tempPtr->~Tree();
		delete tempPtr;
		myDbForwardStack.Pop();
	}
	myDbForwardStack.MakeEmpty();
	//�� �������� delete allDbPtr; ���Ե�.

	allDbPtr = NULL;
	
	
	// myCurrDbPtr �ʱ�ȭ.
	myCurrDbPtr = NULL;
	

	// operKeyDoubleLL �����丮 �ʱ�ȭ.
	operKeyDoubleLL.MakeEmpty();


	// �˻�Ƚ�� �� ���Ƚ�� �ʱ�ȭ.
	searchNum = 0;
	comNum = 0;


	// ��ɾ�, �˻� ������, �˻��� �����ϴ� ���ڿ� �ʱ�ȭ.
	command = "\0";
	oper = "\0";
	key = "\0";
}



template<class _ItemType>
void DbManager<_ItemType>::Initialize()
{
	MakeEmpty();


	//allDbPtr �� allDb �ʱ� ����.
	allDbPtr = new Tree<_ItemType>;	//allDb ����.
	// allDb Tree ���� ������ ����.

	
	// myCurrDbPtr �ʱ� ����.
	myCurrDbPtr = allDbPtr;


	// �˻���� �����丮 �ʱ� ����.
	myDbBackStack.Push(allDbPtr);		// == myDbBackStack.Push(myCurrDbPtr);


	// �˻������� �� �˻��� �����丮 �ʱ� ����.
	oper = "all data";
	key = "\0";
	operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
	operKeyDoubleLL.Insert_with_Deleting_nextPos(key);
}

template<class _ItemType>
void DbManager<_ItemType>::Initialize(Tree<_ItemType> T1)
{
	MakeEmpty();


	//allDbPtr �� allDb �ʱ� ����.
	allDbPtr = new Tree<_ItemType>;	//allDb ����.
	/// allDb Tree ���� ����.
	(*allDbPtr) = T1;


	// myCurrDbPtr �ʱ� ����.
	myCurrDbPtr = allDbPtr;


	// �˻���� �����丮 �ʱ� ����.
	myDbBackStack.Push(allDbPtr);		// == myDbBackStack.Push(myCurrDbPtr);


	// �˻������� �� �˻��� �����丮 �ʱ� ����.
	oper = "all data";
	key = "\0";
	operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
	operKeyDoubleLL.Insert_with_Deleting_nextPos(key);
}

template<class _ItemType>
void  DbManager<_ItemType>::Initialize(ifstream& inFile)
{
	MakeEmpty();


	//allDbPtr �� allDb �ʱ� ����.
	allDbPtr = new Tree<_ItemType>;	//allDb ����.

	// �Է������� ������ �о�, allDb�� ���� �����ϱ�.
	string command_data;
	int numData = 0;
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
	//cout << endl;
	//cout << endl;


	// myCurrDbPtr �ʱ� ����.
	myCurrDbPtr = allDbPtr;


	// �˻���� �����丮 �ʱ� ����.
	myDbBackStack.Push(allDbPtr);		// == myDbBackStack.Push(myCurrDbPtr);
	

	// �˻������� �� �˻��� �����丮 �ʱ� ����.
	oper = "all data";
	key = "\0";
	operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
	operKeyDoubleLL.Insert_with_Deleting_nextPos(key);
}



template<class _ItemType>
void DbManager<_ItemType>::goBackward()
{
	//myCurrDbPtr////
	myDbBackStack.Pop();

	if (myDbBackStack.IsEmpty()) {		//���� myCurrDb�� allDb�̸�,
		cout << "���̻� �ڷ� �ǵ��� Data Base History�� �����ϴ�." << endl;
		myDbBackStack.Push(allDbPtr);
		return;	//�ƹ� ���� ���ϰ� �Լ� ����.
	}
	else {
		//myCurrDbPtr////
		myDbForwardStack.Push(myCurrDbPtr);		// go forward ��ɾ� ���࿡ �����, myDbForwardStack�� ���� myCurrDbPtr�� ����.
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
		cout << "���̻� ������ �� Data Base History�� �����ϴ�." << endl;
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



template<class _ItemType>
void DbManager<_ItemType>::Input_command()
{
	cout << endl;
	cout << endl;
	cout << endl;
	comNum++;
	cout << "<<<" << comNum << "��° ���" << ">>>" << endl;
	cout << "���α׷� �������� �Է��ϼ���: ";
	getline(cin, command);
}



template<class _ItemType>
void DbManager<_ItemType>::Search()
// �Է¹��� �˻� �����ڿ� �˻���� �˻� ����.
// ���ο� �˻������ ���� �� ���.
// ���� oper�� key ���� backStack�� ������� ����.
{
	Tree<_ItemType>* newDbPtr;
	newDbPtr = new Tree<_ItemType>;		// �� myDb ����.
	string getString;


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


	if ((*myCurrDbPtr) != (*newDbPtr)) {
		myDbBackStack.Push(newDbPtr);
		myDbForwardStack.MakeEmpty();
		myCurrDbPtr = newDbPtr;

		operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
		operKeyDoubleLL.Insert_with_Deleting_nextPos(key);

		searchNum++;
	}
	else {
		cout << "���� �˻������ �����ϴ�. ���ο� �˻��� �������� �ʽ��ϴ�." << endl;
	}
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
	else {		// key == NULL�� ���.
		(*newDbPtr) = (*allDbPtr) - (*myCurrDbPtr);

		// ��ü �����ͺ��̽����� 'key������ �˻��� �� �� �ӽ�Db'(*newDbPtr)�� �����Ѵ�.
	}
	
}

template<class _ItemType>
void DbManager<_ItemType>::Search_and_not(Tree<_ItemType>*& newDbPtr)
{
	Search_not(newDbPtr);
	(*newDbPtr) = (*myCurrDbPtr) * (*newDbPtr);		// ���⼭ (*newDbPtr)�� key���� ���� ���ڿ����� �����տ� �ش���. 
													// *myCurrDbPtr�� ����������.
}

template<class _ItemType>
void DbManager<_ItemType>::Search_or_not(Tree<_ItemType>*& newDbPtr)
{
	Search_not(newDbPtr);
	(*newDbPtr) = (*myCurrDbPtr) + (*newDbPtr);		//*myCurrDbPtr�� *newDbPtr�� ����������.
}



template<class _ItemType>
void DbManager<_ItemType>::allData()
{
	Tree<_ItemType>* tempPtr;
	tempPtr = new Tree<_ItemType>;
	(*tempPtr) = (*allDbPtr);		// (*tempPtr) Tree ��ü��, �ʱ� �����ͺ��̽� ��ü(*allDbPtr)�� ���Ұ����� �״�� �����Ͽ� ����.

	if ((*myCurrDbPtr) != (*tempPtr)) {
		myDbBackStack.Push(tempPtr);
		myDbForwardStack.MakeEmpty();
		myCurrDbPtr = tempPtr;

		oper = "all data";
		operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
		key = "\0";
		operKeyDoubleLL.Insert_with_Deleting_nextPos(key);

		searchNum++;
	}
	else {
		cout << "���� �˻������ �����ϴ�. ���ο� �˻��� �������� �ʽ��ϴ�." << endl;
	}
	
}



template<class _ItemType>
void DbManager<_ItemType>::Print_SearchScreen()
{
	Print_SearchScreen(CONSOLE_, IN_ORDER_, NONE_);
}

template<class _ItemType>
void DbManager<_ItemType>::Print_SearchScreen(printTo PT, printDirection PD, printWithNum PWN)
{
	// Tree�� ������ �ִ� ������ �� ���� �� ���ڿ��� ���� ����: myCurrDbPtr->MaxLengthIs();
	// minScreenWide�� ���ȭ���� �ּҳʺ�.
	// screenWide: ��µǴ� ���ڿ� �� ���� �� ���ڿ��� ���̸�ŭ ��Լ� ���̸� �ø��� ���� ������ ����.
	screenWide = myCurrDbPtr->MaxLengthIs();
	if (screenWide < minScreenWide) {
		screenWide = minScreenWide;
	}


	if (PT == CONSOLE_) {
		if (searchNum == 0) {
			cout << setw(screenWide) << setfill('=') << setiosflags(ios::left) << "<<<�ʱ� �����ͺ��̽�>>>";
			cout << endl;
		}
		else {
			cout << "<<<"; 
			cout << setw(3) << setfill(' ') << resetiosflags(ios::left) << setiosflags(ios::right) << searchNum; 
			cout << setw(screenWide - 6) << setfill('=') << resetiosflags(ios::right) << setiosflags(ios::left) << "��° �˻����>>>";
			cout << endl;
		}

		cout << setw(screenWide) << setfill('-') << "---�˻� ������ �� �˻��� �����丮---";
		cout << endl;

		Print_SearchRoute(PT);		///////////

		cout << setw(screenWide) << setfill('-') << "-";
		cout << endl;

		if (PD == IN_ORDER_) {
			if (PWN == NONE_) {
				myCurrDbPtr->Print();	//////////
			}
			else if (PWN == WITH_NUM_) {
				myCurrDbPtr->Print_with_Num();	//////////
			}
		}
		else if (PD == REVERSE_) {
			if (PWN == NONE_) {
				myCurrDbPtr->Print_Reverse();	//////////
			}
			else if (PWN == WITH_NUM_) {
				myCurrDbPtr->Print_Reverse_with_Num();	//////////
			}
		}
		
		cout << setw(screenWide) << setfill('=') << "=";
		cout << endl;
	}
	else if (PT == FILE_) {		
		string outputFileName;
		cout << "�˻��⿡�� ������ �����ͺ��̽��� ����� ��������� �̸��� �Է��ϼ���: ";
		getline(cin, outputFileName);
		ofstream outFile;
		outFile.open(outputFileName.c_str(), ios::out | ios::app);
		if (!outFile.is_open()) {
			cout << "�����ͺ��̽��� ����� ������ �� �� �����ϴ�." << endl;
			exit(1);
		}

		if (searchNum == 0) {
			outFile << setw(screenWide) << setfill('=') << setiosflags(ios::left) << "<<<�ʱ� �����ͺ��̽�>>>";
			outFile << endl;
		}
		else {
			outFile << setw(screenWide) << setfill('=') << "<<<" << searchNum << "��° �˻����" << ">>>";
			outFile << endl;
		}

		outFile << setw(screenWide) << setfill('-') << "---�˻� ������ �� �˻��� �����丮---";
		outFile << endl;

		Print_SearchRoute(PT);		///////////

		outFile << setw(screenWide) << setfill('-') << "-";
		outFile << endl;

		if (PD == IN_ORDER_) {
			if (PWN == NONE_) {
				myCurrDbPtr->Print(outFile);	//////////
			}
			else if (PWN == WITH_NUM_) {
				myCurrDbPtr->Print_with_Num(outFile);	//////////
			}
		}
		else if (PD == REVERSE_) {
			if (PWN == NONE_) {
				myCurrDbPtr->Print_Reverse(outFile);	//////////
			}
			else if (PWN == WITH_NUM_) {
				myCurrDbPtr->Print_Reverse_with_Num(outFile);	//////////
			}
		}

		outFile << setw(screenWide) << setfill('=') << "=";
		outFile << endl;

		cout << "���Ͽ� ����� �Ϸ�Ǿ����ϴ�." << endl;
		outFile.close();

	}
}

template<class _ItemType>
void DbManager<_ItemType>::Print_SearchRoute(printTo PT)
{
	screenWide = myCurrDbPtr->MaxLengthIs();
	if (screenWide < minScreenWide) {
		screenWide = minScreenWide;
	}

	if (PT == CONSOLE_) {
		if (operKeyDoubleLL.WhatIsCurrentPos() != operKeyDoubleLL.WhatIsHeaderPtr()) {
			DoubleLLNode<_ItemType>* tempPtr = operKeyDoubleLL.WhatIsHeaderPtr();

			int searchRoute_PrintLength = 0;

			while (tempPtr != operKeyDoubleLL.WhatIsCurrentPos()) {
				tempPtr = tempPtr->bottomPtr;

				if (tempPtr != ((operKeyDoubleLL.WhatIsHeaderPtr())->bottomPtr)) {
					searchRoute_PrintLength += (2);
					if (searchRoute_PrintLength > screenWide) {
						cout << endl;
						searchRoute_PrintLength = 0;
					}
					cout << "->";

					searchRoute_PrintLength += (1);
					if (searchRoute_PrintLength > screenWide) {
						cout << endl;
						searchRoute_PrintLength = 0;
					}
					cout << " ";
				}

				searchRoute_PrintLength += ((tempPtr->info).length());
				if (searchRoute_PrintLength > screenWide) {
					cout << endl;
					searchRoute_PrintLength = 0;
				}
				cout << tempPtr->info;		//oper print.

				searchRoute_PrintLength += (1);
				if (searchRoute_PrintLength > screenWide) {
					cout << endl;
					searchRoute_PrintLength = 0;
				}
				cout << " ";

				tempPtr = tempPtr->bottomPtr;

				if (tempPtr->info != "\0") {		//tempPtr->->info == "\0" �̸� key print ���ϱ�
					searchRoute_PrintLength += (2 + (tempPtr->info).length());
					if (searchRoute_PrintLength > screenWide) {
						cout << endl;
						searchRoute_PrintLength = 0;
					}
					cout << "\"";
					cout << tempPtr->info;		//key print.
					cout << "\"";

					searchRoute_PrintLength += (1);
					if (searchRoute_PrintLength > screenWide) {
						cout << endl;
						searchRoute_PrintLength = 0;
					}
					cout << " ";
				}
			}

			cout << endl;
		}
	} 
	else if (PT == FILE_) {
		string outputFileName;
		cout << "�˻��⿡�� ������ �����ͺ��̽��� ����� ��������� �̸��� �Է��ϼ���: ";
		getline(cin, outputFileName);
		ofstream outFile;
		outFile.open(outputFileName.c_str(), ios::out | ios::app);
		if (!outFile.is_open()) {
			cout << "�����ͺ��̽��� ����� ������ �� �� �����ϴ�." << endl;
			exit(1);
		}

		if (operKeyDoubleLL.WhatIsCurrentPos() != operKeyDoubleLL.WhatIsHeaderPtr()) {
			DoubleLLNode<_ItemType>* tempPtr = operKeyDoubleLL.WhatIsHeaderPtr();
			//cout << tempPtr->info;
			//cout << " ";
			int searchRoute_PrintLength = 0;

			while (tempPtr != operKeyDoubleLL.WhatIsCurrentPos()) {
				tempPtr = tempPtr->bottomPtr;

				if (tempPtr != ((operKeyDoubleLL.WhatIsHeaderPtr())->bottomPtr)) {
					searchRoute_PrintLength += (2);
					if (searchRoute_PrintLength > screenWide) {
						outFile << endl;
						searchRoute_PrintLength = 0;
					}
					outFile << "->";

					searchRoute_PrintLength += (1);
					if (searchRoute_PrintLength > screenWide) {
						outFile << endl;
						searchRoute_PrintLength = 0;
					}
					outFile << " ";
				}

				searchRoute_PrintLength += ((tempPtr->info).length());
				if (searchRoute_PrintLength > screenWide) {
					outFile << endl;
					searchRoute_PrintLength = 0;
				}
				outFile << tempPtr->info;		//oper print.

				searchRoute_PrintLength += (1);
				if (searchRoute_PrintLength > screenWide) {
					outFile << endl;
					searchRoute_PrintLength = 0;
				}
				outFile << " ";

				tempPtr = tempPtr->bottomPtr;

				if (tempPtr->info != "\0") {		//tempPtr->->info == "\0" �̸� key print ���ϱ�
					searchRoute_PrintLength += (2 + (tempPtr->info).length());
					if (searchRoute_PrintLength > screenWide) {
						outFile << endl;
						searchRoute_PrintLength = 0;
					}
					outFile << "\"";
					outFile << tempPtr->info;		//key print.
					outFile << "\"";

					searchRoute_PrintLength += (1);
					if (searchRoute_PrintLength > screenWide) {
						outFile << endl;
						searchRoute_PrintLength = 0;
					}
					outFile << " ";
				}
			}

			outFile << endl;
		}

		cout << "���Ͽ� ����� �Ϸ�Ǿ����ϴ�." << endl;
		outFile.close();
	}
}


template<class _ItemType>
void DbManager<_ItemType>::Print_SearchDb(printTo PT, printDirection PD, printWithNum PWN)
{
	if (PT == CONSOLE_) {
		if (PD == IN_ORDER_) {
			if (PWN == NONE_) {
				myCurrDbPtr->Print();					////////////
			}
			else if (PWN == WITH_NUM_) {
				myCurrDbPtr->Print_with_Num();			////////////
			}
		}
		else if (PD == REVERSE_) {
			if (PWN == NONE_) {
				myCurrDbPtr->Print_Reverse();			////////////
			}
			else if (PWN == WITH_NUM_) {
				myCurrDbPtr->Print_Reverse_with_Num();	////////////
			}
		}
	}
	else if (PT == FILE_) {
		string outputFileName;
		cout << "�˻��⿡�� ������ �����ͺ��̽��� ����� ��������� �̸��� �Է��ϼ���: ";
		getline(cin, outputFileName);
		ofstream outFile;
		outFile.open(outputFileName.c_str(), ios::out | ios::app);
		if (!outFile.is_open()) {
			cout << "�����ͺ��̽��� ����� ������ �� �� �����ϴ�." << endl;
			exit(1);
		}
		
		if (PD == IN_ORDER_) {
			if (PWN == NONE_) {
				myCurrDbPtr->Print(outFile);
			}
			else if (PWN == WITH_NUM_) {
				myCurrDbPtr->Print_with_Num(outFile);
			}
		}
		else if (PD == REVERSE_) {
			if (PWN == NONE_) {
				myCurrDbPtr->Print_Reverse(outFile);
			}
			else if (PWN == WITH_NUM_) {
				myCurrDbPtr->Print_Reverse_with_Num(outFile);
			}
		}

		cout << "���Ͽ� ����� �Ϸ�Ǿ����ϴ�." << endl;
		outFile.close();
	}
}

template<class _ItemType>
void DbManager<_ItemType>::PrintSettings(string& what, printTo& pt, printDirection& pd, printWithNum& pwn)
{
	string WHAT_ = " ";
	string PT_ = " ";
	string PD_ = " ";
	string PWN_ = " ";

	//�����Լ� ���κ����� �̵�.
	//string what = "screen";
	//printTo pt;
	//printDirection pd;
	//printWithNum pwn;

	cout << "������ ��¼���:   1) ";
	//what
	if ((what == "search screen") || (what == "screen")) {
		cout << "screen��   2) ";
	}
	else if ((what == "search route") || (what == "route")) {
		cout << "reute��   2) ";
	}
	else if ((what == "search data") || (what == "data")) {
		cout << "data��   2) ";
	}
	//pt
	if (pt == CONSOLE_) {
		cout << "console��   3) ";
	}
	else if (pt == FILE_) {
		cout << "file��   3) ";
	}
	//pd
	if (pd == IN_ORDER_) {
		cout << "������������   4) ";
	}
	else if (pd == REVERSE_) {
		cout << "������������   4) ";
	}
	//pwn
	if (pwn == WITH_NUM_) {
		cout << "��ȣ�� �ٿ�   ����մϴ�.";
	}
	else if (pwn == NONE_) {
		cout << "��ȣ�� ������ �ʰ�   ����մϴ�.";
	}
	cout << endl;
	cout << "����� ������ ���� ����� �Ŀ���,   1) screen��   2) console�� ����ϴ� ������,   �ڵ� �ʱ�ȭ �մϴ�." << endl;
	cout << "������ ������ ���� ������ �����մϴ�." << endl;


	while ((WHAT_ != "\0") && (WHAT_ != "search screen") && (WHAT_ != "screen") && (WHAT_ != "search route") && (WHAT_ != "route") && (WHAT_ != "search data") && (WHAT_ != "data")) {
		cout << "1) ������ ����ұ��?: ";
		getline(cin, WHAT_);
	}
	if (WHAT_ == "\0") {
		//what = what;		//���� ���� ����.
	}
	else if ((WHAT_ == "search screen") || (WHAT_ == "screen")) {
		what = WHAT_;
	}
	else if ((WHAT_ == "search route") || (WHAT_ == "route")) {
		what = WHAT_;
	}
	else if ((WHAT_ == "search data") || (WHAT_ == "data")) {
		what = WHAT_;
	}

	while ((PT_ != "\0") && (PT_ != "console") && (PT_ != "file") && (PT_ != "myWriting")) {
		cout << "2) ��� ����ұ��?: ";
		getline(cin, PT_);
	}
	if (PT_ == "\0") {
		//pt = pt;		//���� ���� ����.
	}
	else if (PT_ == "console") {
		pt = CONSOLE_;
	}
	else if (PT_ == "file") {
		pt = FILE_;
	}

	if ((what != "search route") && (what != "route")) {
		while ((PD_ != "\0") && (PD_ != "in order") && (PD_ != "reverse")) {
			cout << "3) � ������ ����ұ��?: ";
			getline(cin, PD_);
		}
		if (PD_ == "\0") {
			//pd = pd;		//���� ���� ����.
		}
		else if (PD_ == "in order") {
			pd = IN_ORDER_;
		}
		else if (PD_ == "reverse") {
			pd = REVERSE_;
		}

		while ((PWN_ != "\0") && (PWN_ != "yes") && (PWN_ != "no") && (PWN_ != "with numbering") && (PWN_ != "without numbering")) {
			cout << "4) ��µǴ� ������ ���� ��ȣ�� �ٿ� ����ұ��?: ";
			getline(cin, PWN_);
		}
		if (PWN_ == "\0") {
			//pwn = pwn;		//���� ���� ����.
		}
		else if ((PWN_ == "yes") || (PWN_ == "with numbering")) {
			pwn = WITH_NUM_;
		}
		else if ((PWN_ == "no") || (PWN_ == "without numbering")) {
			pwn = NONE_;
		}
	}
}



template<class _ItemType>
void DbManager<_ItemType>::select(printDirection& pd, int n)
{
	_ItemType tempString;
	Tree<_ItemType>* newTempTreePtr = new Tree<_ItemType>;
	bool finished = false;

	if (pd == IN_ORDER_) {
		myCurrDbPtr->ResetTree(IN_ORDER);
		int i = 0;
		while ((i < n) && (!finished)) {
			myCurrDbPtr->GetNextItem(tempString, IN_ORDER, finished);
			i++;
		}

		myCurrDbPtr->MakeInQueEmpty();
	}
	else if (pd == REVERSE_) {
		myCurrDbPtr->ResetTree(REVERSE_ORDER);
		int i = 0;
		while ((i < n) && (!finished)) {
			myCurrDbPtr->GetNextItem(tempString, REVERSE_ORDER, finished);
			i++;
		}

		myCurrDbPtr->MakeReverseQueEmpty();
	}

	if (finished == false) {
		newTempTreePtr->InsertItem(tempString);

		if ((*myCurrDbPtr) != (*newTempTreePtr)) {
			myDbBackStack.Push(newTempTreePtr);
			myDbForwardStack.MakeEmpty();
			myCurrDbPtr = newTempTreePtr;

			oper = "select";
			operKeyDoubleLL.Insert_with_Deleting_nextPos(oper);
			key = std::to_string(n);
			operKeyDoubleLL.Insert_with_Deleting_nextPos(key);

			searchNum++;
		}
		else {
			cout << "���� �˻������ �����ϴ�. ���ο� �˻��� �������� �ʽ��ϴ�." << endl;
		}
	}
	else {
		cout << "�������� �������� Ů�ϴ�." << endl;
		cout << "���� �˻������ �����ϴ�. ���ο� �˻��� �������� �ʽ��ϴ�." << endl;
	}
	
}



template<class _ItemType>
int DbManager<_ItemType>::SearchEleNum()
{
	return (myCurrDbPtr->EleNumIs());
}