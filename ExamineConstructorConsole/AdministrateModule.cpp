#include "AdministrateModule.h"
#include <string>
#include <iostream>
#include "Structures.h"
#include "FileModule.h"
#include <windows.h>
#include "ControlTestModule.h"
void AdminUI(User user) {
	while (true) {
		system("cls");
		cout << "=======================================" << endl;
		cout << "| ����� ����������, ������������� " << user.login << "!" << endl;
		cout << "| �������� ��������:                  |" << endl;
		cout << "| 1. ����������� ���� �������������   |" << endl;
		cout << "| 2. ����������� ��������� �����      |" << endl;
		cout << "| 3. �����                            |" << endl;
		cout << "=======================================" << endl;
		int choice;
		string temp_cin;
		getline(cin, temp_cin);
		try {
			choice = stoi(temp_cin);
		}
		catch (const std::exception&)
		{
			cout << "�������� ����" << endl;
			continue;
		}
		if (choice < 1 || choice > 3) {
			cout << "�������� ����" << endl;
			continue;
		}
		switch (choice) {
		case 1: {
			system("cls");
			cout << "������ �������������:" << endl;
			cout << "====================" << endl;
			ShowUsers();


			cout << "������� ����� ������ ��� �����������";
			cin.get();
			break;
		}
		case 2: {
			system("cls");
			Test test = Test();
			Test* temp = new Test();
			cout << "���� ��������� ��������� ������" << endl;
			while (true) {
				TestsContainer* p = Read("tests/publicTests.txt", false, user);

				if (p == nullptr) {
					cout << "��� ��������� ������" << endl;
					Sleep(500);
					break;
				}

				ShowTests(p);

				cout << "-------------------------------------------------------------------" << endl;
				cout << "| ������� ����� ����� ��� ��� ������� ���                         |" << endl;
				cout << "| ������� (-1) ��� ������                                         |" << endl;
				cout << "| ������� (-2) ��� ���������� ������ (�� ����������� ���������)   |" << endl;
				cout << "| ������� (-3) ��� ���������� ������ (�� �������� ���������)      |" << endl;
				cout << "| ������� (-4) ��� ���������� ������ �� �������� (�� �����������) |" << endl;
				cout << "| ������� (-5) ��� ���������� ������ �� �������� (�� ��������)    |" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				int choice;
				string temp_cin;
				getline(cin, temp_cin);
				try {
					choice = stoi(temp_cin);
				}
				catch (const std::exception&)
				{
					cout << "�������� ����" << endl;
					continue;
				}
				if (choice == -1) {
					break;
				}
				if (choice == -2) {
					//temp = sortTests(p->tests, p->count_tests, 2);
					temp = InsertionSort(p->tests, p->count_tests);
					p->tests = temp;
					continue;
				}
				if (choice == -3) {
					temp = sortTests(p->tests, p->count_tests, 3);
					p->tests = temp;
					continue;
				}
				if (choice == -4) {
					temp = sortTests(p->tests, p->count_tests, 4);
					p->tests = temp;
					continue;
				}
				if (choice == -5) {
					temp = sortTests(p->tests, p->count_tests, 5);
					p->tests = temp;
					continue;
				}
				// cheah is valid number
				if (choice > p->count_tests || choice < 0) {
					cout << "�������� ����� �����!" << endl;
					continue;
				}

				for (int i = 0; i < p->count_tests; i++) {
					if (i == choice - 1) {
						test = p->tests[i];
						break;
					}
				}


				showTestMenu(test, &user, false);
			}
			break;
		}
		case 3: {
			return;
		}
		}

	}

}

void ShowUsers() {
	UsersContainer* data = ReadUsers();
	if (data == nullptr) {
		cout << "������ ������������� ����" << endl;
		return;
	}
	UserNode* temp = data->head;
	while (temp != nullptr) {

		cout << "| ID        " << temp->data.id << "." << endl;
		cout << "| Login:    " << temp->data.login << endl;
		cout << "| Name:     " << temp->data.name << endl;
		cout << "| Surname:  " << temp->data.surname << endl;
		cout << "| Email:    " << temp->data.email << endl;
		cout << "| Age:      " << temp->data.age << endl;
		cout << "==========================" << endl;
		temp = temp->next;
	}


}