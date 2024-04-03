// Code for the ControlTestModule
#include <iostream>
#include <string>
#include "Structures.h"
#include "FileModule.h"

using namespace std;

void CreateTest(UserData user) {
	int userId = user.id;
	string TestPathPublic = "tests/publicTests.txt";
	string TestPath = "tests/" + to_string(userId) + "test.txt";
	system("cls");
	cout << "���� �������� �����" << endl;
	cout << "������� �������� �����: " << endl;
	string name;
	cin.ignore();
	getline(cin, name);
	cout << "������� ��������� �����: ";
	int level;
	cin >> level;
	cout << "������� �� ���� �������� ���������? (1- ��, 0 - ���): ";
	int isPublic;
	cin >> isPublic;
	cout << "������� ���������� ����������� ��������: " << endl;
	cout << "(������� � ����� ���������� �������)" << endl;
	int count_q_standart;
	cin >> count_q_standart;
	Q_standart* q_standart = new Q_standart[count_q_standart];
	cout << "================" << endl;
	for (int i = 0; i < count_q_standart; i++) {
		cout << "������� ������: ";
		string question;
		cin.ignore();
		getline(cin,question);
		cout << "������� �����: ";
		string answer;
		cin.ignore();
		getline(cin,answer);
		cout << "������� ��������� �������: ";
		int difficulty;
		cin >> difficulty;
		q_standart[i] = Q_standart(question, answer, difficulty);
	}
	cout << "������� ���������� �������� ���� �����: " << endl;
	cout << "(������� � ����������� ���������� ������ (�,�,�,�)" << endl;
	int count_q_guest;
	cin >> count_q_guest;
	Q_guest* q_guest = new Q_guest[count_q_guest];
	cout << "================" << endl;
	for (int i = 0; i < count_q_guest; i++) {
		cout << "������� ������: ";
		string question;
		cin.ignore();
		getline(cin, question);
		cout << "������� ���������� ��������� ������: ";
		int count_answers;
		cin >> count_answers;
		string* answers = new string[count_answers];
		cout << "������� �������� ������: " << endl;
		for (int j = 0; j < count_answers; j++) {
			cout << j + 1 << ". ";
			cin.ignore();
			getline(cin, answers[j]);
		}
		cout << "������� ����� ����������� ������: ";
		int right_answer;
		cin >> right_answer;
		cout << "������� ��������� �������: ";
		int difficulty;
		cin >> difficulty;
		q_guest[i] = Q_guest(question, answers,count_answers, right_answer, difficulty);
	}
	Test test = Test(name, user.name, isPublic, level, count_q_standart, q_standart, count_q_guest, q_guest);
	int res = 0;
	if (isPublic == 1) {
		res = WriteToFile(TestPathPublic, test);
	}
	else {
		res = WriteToFile(TestPath, test);
	}
	if (res == 1) {
		cout << "������ ��� �������� �����!" << endl;
	}
	else {
		cout << "���� ������� ������!" << endl;
	}


};
void PersonUI(User user) {
	cout << "����� ����������, " << user.login << "!" << endl << endl;
	while (true) {
	system("cls");
		cout << "�������� ��������:" << endl;
		cout << "1. ������� ����" << endl;
		cout << "2. ����������� �����" << endl;
		cout << "3. ������ ��������� ����" << endl;
		cout << "4. �����" << endl;
		int choice;
		cin >> choice;
		switch (choice) {
		case 1: {
			cout << "���� �������� �����" << endl;
			UserData data = getUserData(user.id, "users/usersData.txt");
			CreateTest(data);
			break;
		}
		case 2: {
			cout << "���� ��������� ������" << endl;
			break;
		}
		case 3: {
			cout << "���� ����������� ���������� �����" << endl;
			break;
		}
		case 4: {
			cout << "�� ��������!" << endl;
			return;
		}
		}
	}
};


