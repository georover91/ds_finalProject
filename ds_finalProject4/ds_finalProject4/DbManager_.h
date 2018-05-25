#include "DbManager.h"



// Class constructor & Class destructor /////////////////////////////////////////
template<class _ItemType>
DbManager<_ItemType>::DbManager()
{
	myCurrDbPtr = new Tree<_ItemType>;	//allDb ����.
}

//template<class _ItemType>
//DbManager<_ItemType>::~DbManager()
//{
//
//}

template<class _ItemType>
void DbManager<_ItemType>::goForward();

template<class _ItemType>
void DbManager<_ItemType>::goBackward();

template<class _ItemType>
void DbManager<_ItemType>::search_in_myCurrDb(char oper, _ItemType key);	//Tree<_ItemType>* myCurrDbPtr �� �ɹ������̹Ƿ�, �ɹ��Լ��� �μ��� �߰��� �ʿ� ����.

template<class _ItemType>
void DbManager<_ItemType>::Print_myCurrDb();

template<class _ItemType>
void DbManager<_ItemType>::Print_to_myWriting();

template<class _ItemType>
void DbManager<_ItemType>::Print_to_file();
