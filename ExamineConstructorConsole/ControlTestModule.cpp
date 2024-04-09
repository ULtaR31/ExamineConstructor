// Code for the ControlTestModule
#include <iostream>
#include <string>
#include "Structures.h"
#include "FileModule.h"
#include "ControlTestModule.h"

using namespace std;

// �������� ����� (�������)
void ShowTests(TestsContainer* tests) {
	system("cls");
	cout << "������ ������: " << endl;
	for (int i = 0; i < tests->count_tests; i++) {
		cout << i + 1 << ". ��������\t" << tests->tests[i].name << "\n���������:\t " << tests->tests[i].difficulty << endl << endl;
	}

	cout << endl <<"================" << endl << endl;
	

}



// �������� �����
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

// ���� ������������
void PersonUI(User user) {
	system("cls");
	cout << "����� ����������, " << user.login << "!" << endl << endl;
	while (true) {
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

// ���� �����
void GuestUI(User user) {
	cout << "����� ����������, �����!" << endl << endl;
	while (true) {
		system("cls");
		cout << "�������� ��������:" << endl;
		cout << "1. ����������� ��������� �����" << endl;
		cout << "2. ������ ��������� ����" << endl;
		cout << "3. �����" << endl;
		int choice;
		cin >> choice;
		Test test = Test();
		switch (choice) {
		case 1: {
			Test* temp = new Test();
			TestsContainer * p = Read("tests/publicTests.txt", true, user);
			cout << "���� ��������� ��������� ������" << endl;
			while (true) {
				ShowTests(p);
				cout << " ������� -1 ��� ������" << endl;
				cout << " ������� -2 ��� ���������� ������ (�� ����������� ���������)" << endl;
				cout << " ������� -3 ��� ���������� ������ (�� �������� ���������)" << endl;
				cout << " ������� -4 ��� ���������� ������ �� �������� (�� �����������)" << endl;
				cout << " ������� -5 ��� ���������� ������ �� �������� (�� ��������)" << endl;
				int choice;
				cin >> choice;
				if (choice == -1) {
					break;
				}
				if (choice == -2) {
					temp = sortTests(p->tests, p->count_tests, 2);
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
				

				showTestMenu(test);
			}

			break;
		}
		case 2: {
			cout << "���� ����������� ���������� �����" << endl;


			//int result = startTest(test);

			break;
		}
		case 3: {
			cout << "�� ��������!" << endl;
			return;
		}
		}
	}
};
// �������� ����
void ShowTest(Test test) {
	system("cls");
	cout << "�������� �����: " << test.name << endl;
	cout << "�����: " << test.author << endl;
	cout << "���������: " << test.difficulty << endl;
	cout << "================" << endl;
	cout << "����������� �������: " << endl;
	for (int i = 0; i < test.count_q_standart; i++) {
		cout << i + 1 << ". " << test.q_standart[i].question << endl;
	}
	cout << "================" << endl;
	cout << "������� ������� ����: " << endl;
	for (int i = 0; i < test.count_q_guest; i++) {
		cout << i + 1 << ". " << test.q_guest[i].question << endl;
	}
	cout << "================" << endl;

	cout << "������� ����� ������� ��� �����������..." << endl;
	cin.get();
	cin.get();
}

// �������� ���� �����
void showTestMenu(Test test) {
	while (true) {
		system("cls");
		cout << "�� ������� ����: " << test.name << endl;
		cout << "�������� ��������:" << endl;
		cout << "1. ������ ����" << endl;
		cout << "2. ����������� ����" << endl;
		cout << "3. ����������� �������" << endl;
		cout << "4. ��������� �����" << endl;
		int choice;
		cin >> choice;
		switch (choice) {
		case 1: {
			int result = startTest(test);
			cout << "���� �������!" << endl;
			cout << "��� ���������: " << result << endl;
			float mark = getMark(result);
			cout << "���� ������: " << mark << endl;
			cout << "================" << endl;
			cout << "������� ����� ������� ��� �����������..." << endl;
			cin.get();
			break;
		}
		case 2: {
			ShowTest(test);
			break;
		}
		case 3: {
			return;
		}
		}
	}
}




// ������ ����
int startTest(Test test) {
	int result = 0;
	cout << "================" << endl;
	cout << "���� �������!" << endl;
	cout << "================" << endl;
	cout << "����������� �������: " << endl;
	for (int i = 0; i < test.count_q_standart; i++) {
		cout << i + 1 << ". " << test.q_standart[i].question << endl;
		string answer;
		cout << "������� �����: ";
		cin.ignore();
		getline(cin, answer);
		if (answer == test.q_standart[i].answer) {
			result += test.q_standart[i].difficulty;
		}
	}
	cout << "================" << endl;
	cout << "������� ������� ����: " << endl;
	for (int i = 0; i < test.count_q_guest; i++) {
		cout << i + 1 << ". " << test.q_guest[i].question << endl;
		cout << "�������� ������: " << endl;
		for (int j = 0; j < test.q_guest[i].count_answers; j++) {
			cout << j + 1 << ". " << test.q_guest[i].answer[j] << endl;
		}
		int answer;
		cout << "������� ����� ������: ";
		cin >> answer;
		cin >> answer;
		if (answer == test.q_guest[i].right_answer) {
			result += test.q_guest[i].difficulty;
		}
	}
	cout << "================" << endl;
	return result;
}


float getMark(int result){
	//need the mark from 0 to 10
	if (result == 0) {
		return 0;
	}
	return result % 10;

}

// merge sort
Test* sortTests(Test* tests,int _size, int choice) {
	int size = _size;
	if (size == 1) {
		return tests;
	}
	int mid = size / 2;
	Test* left = new Test[mid];
	Test* right = new Test[size - mid];
	for (int i = 0; i < mid; i++) {
		left[i] = tests[i];
	}
	for (int i = mid; i < size; i++) {
		right[i - mid] = tests[i];
	}
	left = sortTests(left, mid,choice);
	right = sortTests(right,size-mid,choice);
	return merge(left, right, mid, size - mid, choice);
}

Test* merge(Test* left, Test* right, int l, int r, int choice) {
	// 2- �� ����������� ���������
	// 3 - �� �������� ���������
	// 4 - �� �������� (�� �����������)
	// 5 - �� �������� (�� ��������)
	Test* result = new Test[l + r];

	if (choice == 2) {
		int i = 0;
		int j = 0;
		int k = 0;
		while (i < l && j < r) {
			if (left[i].difficulty < right[j].difficulty) {
				result[k] = left[i];
				i++;
			}
			else {
				result[k] = right[j];
				j++;
			}
			k++;
		}
		while (i < l) {
			result[k] = left[i];
			i++;
			k++;
		}
		while (j < r) {
			result[k] = right[j];
			j++;
			k++;
		}
	}
	else if (choice == 3) {
		int i = 0;
		int j = 0;
		int k = 0;
		while (i < l && j < r) {
			if (left[i].difficulty > right[j].difficulty) {
				result[k] = left[i];
				i++;
			}
			else {
				result[k] = right[j];
				j++;
			}
			k++;
		}
		while (i < l) {
			result[k] = left[i];
			i++;
			k++;
		}
		while (j < r) {
			result[k] = right[j];
			j++;
			k++;
		}
	}
	else if (choice == 4) {
		int i = 0;
		int j = 0;
		int k = 0;
		while (i < l && j < r) {
			if (left[i].name < right[j].name) {
				result[k] = left[i];
				i++;
			}
			else {
				result[k] = right[j];
				j++;
			}
			k++;
		}
		while (i < l) {
			result[k] = left[i];
			i++;
			k++;
		}
		while (j < r) {
			result[k] = right[j];
			j++;
			k++;
		}
	}
	else if (choice == 5) {
		int i = 0;
		int j = 0;
		int k = 0;
		while (i < l && j < r) {
			if (left[i].name > right[j].name) {
				result[k] = left[i];
				i++;
			}
			else {
				result[k] = right[j];
				j++;
			}
			k++;
		}
		while (i < l) {
			result[k] = left[i];
			i++;
			k++;
		}
		while (j < r) {
			result[k] = right[j];
			j++;
			k++;
		}
	}
	return result;
}