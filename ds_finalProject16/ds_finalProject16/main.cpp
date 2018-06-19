// ������ ������ �̿��� ���ڿ� �˻���
// �ۼ���: ������ (������б� ���ڰ��а�)
// �ۼ���: 2018�� 5�� 18�� ���� ~ 2018�� 6�� 17�� �ϼ�.
// ����, ����ũ�帮��Ʈ, �׸��� Ʈ���� �⺻���� �ڷᱸ���� ���� �����ڷ� �Ϻθ� ������ �� �̿ܿ���,
// �������� ������ ��� ���� ���̵��, ����, �ۼ�, �ϼ��� �ڵ��̴�.
/////////////////////////////////////////////////////////////////////////////
#include "DbManager_.h"



void OpenFile_and_InitializeFromFile(DbManager<ItemType>& DbM);

int main()
{
	//instanciating Database Manager class. 
	DbManager<ItemType> DbM;

	// ��¼��ļ����� ���� ������ ����.
	string what = "search screen";
	printTo pt = CONSOLE_;
	printDirection pd = IN_ORDER_;
	printWithNum pwn= NONE_;



	//�Է����Ϸ� �˻����� �ʱ� �����ͺ��̽� ����.
	OpenFile_and_InitializeFromFile(DbM);
	cout << endl;
	DbM.Print_SearchScreen(pt, pd, pwn);



	// ���������� string DB �˻� ���α׷��� ����.
	DbM.Input_command();

	while (DbM.command != "quit")
	{
		if (DbM.command == "go back") {
			DbM.goBackward();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "go forward") {
			DbM.goForward();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "search") {
			while (1) {
				cout << "�˻� �����ڸ� �Է��ϼ���: ";
				getline(cin, DbM.oper);
				if ((DbM.oper == "and") || (DbM.oper == "or") || (DbM.oper == "not") || (DbM.oper == "and not") || (DbM.oper == "or not") || (DbM.oper == "all data")) {
					break;
				}
			}
			
			if (DbM.oper != "all data") {
				cout << "�˻� Ű���带 �Է��ϼ���: ";
				getline(cin, DbM.key);

				DbM.Search();
				cout << endl;
				DbM.Print_SearchScreen(pt, pd, pwn);
			}
			else {
				DbM.allData();
				cout << endl;
				DbM.Print_SearchScreen(pt, pd, pwn);
			}
		
		}
		else if (DbM.command == "and") {
			DbM.oper = "and";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "or") {
			DbM.oper = "or";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "not") {
			DbM.oper = "not";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "and not") {
			DbM.oper = "and not";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "or not") {
			DbM.oper = "or not";

			cout << "�˻� Ű���带 �Է��ϼ���: ";
			getline(cin, DbM.key);

			DbM.Search();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "all data") {
			DbM.allData();
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "initialize") {
			OpenFile_and_InitializeFromFile(DbM);
			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "print") {
			DbM.PrintSettings(what, pt, pd, pwn);
			
			if ((what == "search screen") || (what == "screen")) {
				if (pt != FILE_) {
					cout << endl;
				}
				DbM.Print_SearchScreen(pt, pd, pwn);
			}
			else if ((what == "search route") || (what == "route")) {
				if (pt != FILE_) {
					cout << endl;
				}
				DbM.Print_SearchRoute(pt);
			}
			else if ((what == "search data") || (what == "data")) {
				if (pt != FILE_) {
					cout << endl;
				}
				DbM.Print_SearchDb(pt, pd, pwn);
			}

			//��� ����� �� �����ϸ�, ��� �ɼ� �� pt�� console�� ����ϴ� �������� �ʱ�ȭ.
			what = "search screen";
			pt = CONSOLE_;
		}
		else if (DbM.command == "select") {
			int n;
			cout << "������ �������� ��°���� �Է��ϼ���: ";
			cin >> n;
			DbM.select(pd, n);

			cout << endl;
			DbM.Print_SearchScreen(pt, pd, pwn);
		}
		else if (DbM.command == "number") {
			int m;
			m = DbM.SearchEleNum();
			cout << "���� �˻������ ������ ������ ";
			cout << m << " �� �Դϴ�." << endl;
		}

		DbM.Input_command();
	};

	return 0;
}

void OpenFile_and_InitializeFromFile(DbManager<ItemType>& DbM)
{
	//�Է����Ϸ� �˻����� �ʱ� �����ͺ��̽� ����.
	string inputFileName;
	cout << "�˻����� �ʱ� �����ͺ��̽��� ������ �Է������� �̸��� �Է��ϼ���: ";
	getline(cin, inputFileName);
	//cout << endl;

	ifstream inFile(inputFileName.c_str());	//�ʱ� ������ ���̽��� ����(�ʱ�DB��������) �ϳ����� �о�� ����.
	if (!inFile.is_open()) {
		cout << "������ ���̽��� ������ ������ �� �� �����ϴ�." << endl;
		exit(1);
	}

	DbM.Initialize(inFile);	//

	inFile.seekg(0, ios::beg);		// ���� �б� �����ϴ� ��ġ �ʱ�ȭ . �̰� �����ָ�, ������ �ٽ� ���� �̸��� ���� ��� ������, �� ������ ������ ������, ���� �� ���� �κк��� �о ������.
	inFile.close();
}