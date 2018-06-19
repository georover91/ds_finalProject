// ������ ������ �̿��� ���ڿ� �˻���. (the string search programme using the concept of set.)
// �ۼ���: ������ (������б� ���ڰ��а�. �������: 910211. �̸���: kubonik91@naver.com)
// �ۼ���: 2018�� 5�� 18�� ���� ~ 2018�� 6�� 17�� �ϼ�.
// ����, ����ũ�帮��Ʈ, �׸��� Ʈ���� �⺻���� �ڷᱸ���� ���� �����ڷ� �Ϻθ� ������ �� �̿ܿ���,
// �������� ������ ��� ���� ���̵��, ����, �ۼ�, �ϼ��� �ڵ��̴�.
/////////////////////////////////////////////////////////////////////////////
#include "DbManager_.h"



void OpenFile_and_InitializeFromFile(DbManager<ItemType>& DbM);

int main()
{
	//���α׷� ������ ���� �ȳ��� �ۼ�.
	cout << "<<<����(������, ������, ������ ��)�� ������ �̿��� ���ڿ� �˻���>>>" << endl;
	cout << endl;
	cout << "---���α׷��� ����ϱ� ���� �ȳ���---------------------------------" << endl;
	cout << "�� ���ڿ� �˻���� �⺻������ windows console ȯ�濡�� �����ϸ�, ���ڿ� ��ɾ �޾� ����� �����մϴ�." << endl;
	cout << "�� ���ڿ� �˻����� ��ɾ�� ��� ���� �ҹ��ڷ� �����Ǿ� ������, ������ ���� ��ɾ���� �ֽ��ϴ�." << endl;
	cout << "quit ��ɾ�:                          ���α׷��� �����մϴ�." << endl;
	cout << "search ��ɾ�:                        �� ��ɾ� ������ �߰� ��ɾ �Է��Ͽ�, �׿� ���� �˻��� �����ϸ�, ���� �˻�����κ��� ���ο� �˻������ �����մϴ�." << endl;
	cout << "���� �˻���� ��µ� ���� -> search��ɾ� �Է� -> 'and', 'or' ���� �˻������� �Է� -> keyword �Է� -> ���� �˻���� ���� �� ���." << endl;
	cout << "search ��ɾ� �Է���, �˻� ������(operator, oper) �� �˻� Ű���带 �߰��� �Է��ؾ� �մϴ�." << endl;
	cout << "��ɾ� �Է¶��� �˻������ڸ� �Է��ص� ���� �����ϸ�, �� �Է¿� ���� �˻��� �����մϴ�." << endl;
	cout << "and ��ɾ� �Ǵ� �˻�������:           ���� �˻�������� keyword�� �����ϴ� ���ڿ����� ������ ���� �˻������ �����մϴ�." << endl;
	cout << "or ��ɾ� �Ǵ� �˻�������:            ��ü ���ڿ� �ʱⵥ���ͺ��̽����� keyword�� �����ϴ� ���ڿ����� ������, �� ���̴����� ���� �˻������ �߰��Ͽ� ���� �˻������ �����մϴ�." << endl;
	cout << "not ��ɾ� �Ǵ� �˻�������:           ���� �����ͺ��̽����� ���� �˻������ ������ ������ ���ڿ��� ���� �˻������ �����մϴ�. �Ǵ� ��ü �����ͺ��̽����� keyword�� �����ϴ� ���ڿ��� ������ ������ ���ڿ��� ���� �������� �����մϴ�." << endl;
	cout << "and not ��ɾ� �Ǵ� �˻�������:       ���� �˻��������, keyword�� �����ϴ� ���ڿ��� �����ϰ�, �� ������ ���ڿ��� ���� �˻������ �����մϴ�." << endl;
	cout << "or not ��ɾ� �Ǵ� �˻�������:        ��ü�˻���� �� keyword�� �����ϴ� ���ڿ��� ������ ������ ���ڿ���, ���� �˻������ �߰��˴ϴ�." << endl;
	cout << "all data ��ɾ� �Ǵ� �˻�������:      �Է��Ŀ����� �о�鿩 �����ߴ� �ʱⵥ���ͺ��̽���, ���� �˻������ �ٽ� �����մϴ�." << endl;
	cout << "initialize ��ɾ�:                    �� ���ڿ� �˻��� ���α׷��� ó������ �ٽ� ����(�����)�մϴ�." << endl;
	cout << "print ��ɾ�:                         ���� ������ �˻������ ����մϴ�. �߰� ���� ��ɾ �Է��ؾ� �մϴ�." << endl;
	cout << "print ��ɾ�� �Բ� �ӷ��� print ���ļ��������� ���� ��½ÿ��� ����, �ݿ��˴ϴ�." << endl;
	cout << "search screen �Ǵ� screen:            ���� �˻���� ȭ�� ��ü�� ����մϴ�." << endl;
	cout << "search route �Ǵ� route:              ���� �˻���� ȭ�� �� �˻���Ʈ���� ����մϴ�." << endl;
	cout << "search data �Ǵ� data:                ���� �˻���� ȭ�� �� �˻������͸��� ����մϴ�." << endl;
	cout << "console:                              ���� �˻���� ȭ���� console�� ����մϴ�." << endl;
	cout << "file:                                 ���� �˻���� ȭ���� file�� ����մϴ�." << endl;
	cout << "in order:                             ���� �˻������ �����͸� ������������ ����մϴ�." << endl;
	cout << "reverse:                              ���� �˻������ �����͸� ������������ ����մϴ�." << endl;
	cout << "with numbering �Ǵ� yes:              ���� �˻������ �����Ϳ� ��ȣ�� �ٿ� ����մϴ�." << endl;
	cout << "without numbering �Ǵ� no:            ���� �˻������ �����Ϳ� ��ȣ�� ������ �ʰ� ����մϴ�." << endl;
	cout << "select ��ɾ�:                        �� ��ɾ� �Է��� ���ڸ� �Է��ϸ�, �� ���� ��°�� ������ �ϳ��� ������ ���ο� ���� �˻������ �����մϴ�." << endl;
	cout << "number ��ɾ�:                        ���� �˻������ ������ ������ ����մϴ�." << endl;
	cout << "�ʱ� �����ͺ��̽��� ������ �Է������� �̸��� ����ڰ� ������ �� �ֽ��ϴ�. ������ �� ���ٸ�, in.txt �� �⺻�Է����� �̸����� �մϴ�." << endl;
	cout << "�����͸� ����� ��������� �̸��� ����ڰ� ������ �� �ֽ��ϴ�." << endl;
	cout << "-------------------------------------------------------------------" << endl;
	cout << endl;
	cout << endl;
	cout << endl;



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

			what = "search screen";
			pt = CONSOLE_;
			pd = IN_ORDER_;
			pwn = NONE_;

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