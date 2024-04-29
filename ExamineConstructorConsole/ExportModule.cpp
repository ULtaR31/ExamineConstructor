#include "ExportModule.h"
#include <iostream>
#include <string>
#include "Structures.h"
#include <Windows.h>
#include "FileModule.h"
using namespace std;

void ExportTestMenu(Test test, User* user) {
	while (true) {
		system("cls");
		cout << "=====================" << endl;
		cout << "������� �����: " << test.name << endl;
		cout << "=====================" << endl;
		cout << "�������� ��������:" << endl;
		cout << "1. �������������� � ��������" << endl;
		cout << "2. �������������� ��� �������" << endl;
		cout << "3. �����" << endl;
		int choice;
		string temp_cin;
		getline(cin, temp_cin);
		try
		{
			choice = stoi(temp_cin);
		}
		catch (const std::exception&)
		{
			cout << "�������� ����" << endl;
			Sleep(500);
			continue;
		}
		if (choice < 1 || choice > 3) {
			cout << "�������� ����" << endl;
			Sleep(500);
			continue;
		}
		switch (choice) {
		case 1: {
			int res = ExportTest(test, user, "export/" + test.name + ".txt",true);
			if (res == 0) {
				cout << "���� ������� �������������" << endl;
				Sleep(500);
			}
			else {
				cout << "������ ��������" << endl;
				Sleep(500);
			}
			break;
		}
		case 2: {
				int res = ExportTest(test, user, "export/" + test.name + ".txt", false);
				if (res == 0) {
				cout << "���� ������� �������������" << endl;
				Sleep(500);
			}
						else {
				cout << "������ ��������" << endl;
				Sleep(500);
			}
				break;

		}
		case 3: {
			return;
		}
		}
	}
}