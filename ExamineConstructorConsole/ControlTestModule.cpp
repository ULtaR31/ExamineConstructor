// Code for the ControlTestModule
#include <iostream>
#include <string>
#include <windows.h>
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
	try {
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
			getline(cin, question);
			cout << "������� �����: ";
			string answer;

			getline(cin, answer);
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
			q_guest[i] = Q_guest(question, answers, count_answers, right_answer, difficulty);
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
	}
	catch (exception e) {
		cout << "������ ��� �������� �����!" << endl;
	}
};

// ���� ������������
void PersonUI(User user) {
	while (true) {
		system("cls");
		cout << "����� ����������, " << user.login << "!" << endl << endl;
		cout << "�������� ��������:" << endl;
		cout << "1. ������� ����" << endl;
		cout << "2. ����������� �����" << endl;
		cout << "3. ����������� ��������� ����" << endl;
		cout << "4. �����" << endl;
		int choice;
		string temp_cin;
		//cin >> choice;
		getline(cin, temp_cin);
		try {
			choice = stoi(temp_cin);
		}
		catch (const std::exception&)
		{
			cout << "�������� ����" << endl;
			continue;
		}
		Test test = Test();
		Test* temp = new Test();
		switch (choice) {
		case 1: {
			cout << "���� �������� �����" << endl;
			UserData data = getUserData(user.id, "users/usersData.txt");
			CreateTest(data);
			break;
		}
		case 2: {
			cout << "���� ��������� ������" << endl;
			TestsContainer* p = Read("tests/" + to_string(user.id) + "test.txt", false, user);
			while (true) {
				ShowTests(p);
				cout << " ������� ����� ����� ��� �����������" << endl;
				cout << " ������� -1 ��� ������" << endl;
				cout << " ������� -2 ��� ���������� ������ (�� ����������� ���������)" << endl;
				cout << " ������� -3 ��� ���������� ������ (�� �������� ���������)" << endl;
				cout << " ������� -4 ��� ���������� ������ �� �������� (�� �����������)" << endl;
				cout << " ������� -5 ��� ���������� ������ �� �������� (�� ��������)" << endl;
				int choice;
				string temp_cin;
				//cin >> choice;
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


				showTestMenu(test,&user);
			}

			break;
		}
		case 3: {
			cout << "���� ��������� ������" << endl;
			TestsContainer * p = Read("tests/publicTests.txt", true, user);
			while (true) {
				ShowTests(p);
				cout << " ������� -1 ��� ������" << endl;
				cout << " ������� -2 ��� ���������� ������ (�� ����������� ���������)" << endl;
				cout << " ������� -3 ��� ���������� ������ (�� �������� ���������)" << endl;
				cout << " ������� -4 ��� ���������� ������ �� �������� (�� �����������)" << endl;
				cout << " ������� -5 ��� ���������� ������ �� �������� (�� ��������)" << endl;
				int choice;
				string temp_cin;
				//cin >> choice;
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


				showTestMenu(test,&user);
			}

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
		cout << "2. �����" << endl;
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
				cout << " ������� ����� ����� ��� �����������" << endl;
				cout << " ������� -1 ��� ������" << endl;
				cout << " ������� -2 ��� ���������� ������ (�� ����������� ���������)" << endl;
				cout << " ������� -3 ��� ���������� ������ (�� �������� ���������)" << endl;
				cout << " ������� -4 ��� ���������� ������ �� �������� (�� �����������)" << endl;
				cout << " ������� -5 ��� ���������� ������ �� �������� (�� ��������)" << endl;
				string temp_cin;
				int choice;
				//cin >> choice;
				getline(cin, temp_cin);
				try
				{
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
				

				showTestMenu(test,&user);
			}

			break;
		}
		case 2: {
			cout << "�� ��������!" << endl;
			return;
		}
		}
	}
};

// ���� ��������������
void AdminUI(User user) {}


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
}

// �������� ���� �����
void showTestMenu(Test test, User*user) {
	if(test.author == user->login){
		while (true) {
			system("cls");
			cout << "�� ������� ����: " << test.name << endl;
			cout << "�������� ��������:" << endl;
			cout << "1. ������ ����" << endl;
			cout << "2. ����������� ����" << endl;
			cout << "3. ����������� �������" << endl;
			cout << "4. ������������� ����" << endl;
			cout << "5. ��������� �����" << endl;
			string temp_cin;
			int choice;
			//cin >> choice;
			getline(cin, temp_cin);
			try
			{
				choice = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "�������� ����" << endl;
				continue;
			}

			switch (choice) {
			case 1: {
				int result = startTest(test);
				cout << "���� �������!" << endl;
				cout << "��� ���������: " << result << endl;
				float mark = getMark(result);
				cout << "���� ������: " << mark << endl;
				cout << "================" << endl;
				int res = WriteToFile("raiting/" + test.name + ".txt", test.name, getUserData(user->id, "users/usersData.txt").name, result, mark);
				if (res == 1) {
					cout << "������ ��� ������ ��������!" << endl;
				}
				else {
					cout << "������� ������� �������!" << endl;
				}
				cout << "������� ����� ������� ��� �����������..." << endl;
				cin.get();
				break;
			}
			case 2: {
				ShowTest(test);
				break;
			}
			case 3: {
				Raiting* raiting = Read("raiting/"+ test.name+".txt", &test, user);
				string user_name  = getUserData(user->id, "users/usersData.txt").name;
				showRaiting(raiting,user, user_name);

				break;
			}
			case 4: {
				//EditTest();
			}
			case 5: {
				return;
			}
			}
		}
	}
	else {
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
				int res = WriteToFile("tests/raiting.txt", test.name, getUserData(user->id, "users/usersData.txt").name, result, mark);
				if (res == 1) {
					cout << "������ ��� ������ ��������!" << endl;
				}
				else {
					cout << "������� ������� �������!" << endl;
				}
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
			case 4: {
				return;
			}
			}
		}
	}
}




// ������ ����
int startTest(Test test) {
	int result = 0;
	system("cls");
	cout << "================" << endl;
	cout << "���� "<< test.name<< " �������!" << endl;
	cout << "================" << endl;
	cout << "����������� �������: " << endl;
	for (int i = 0; i < test.count_q_standart; i++) {
		cout << i + 1 << ". " << test.q_standart[i].question << endl;
		string answer;
		cout << "������� �����: ";
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

// �������� ������
float getMark(int result){
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
// merge
Test* merge(Test* left, Test* right, int l, int r, int choice) {
	// 2- �� ����������� ���������
	// 3 - �� �������� ���������
	// 4 - �� �������� (�� �����������)
	// 5 - �� �������� (�� ��������)
	Test* result = new Test[l + r];
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < l && j < r) {

		if (choice == 2) {
			if (left[i].difficulty < right[j].difficulty) {
				result[k] = left[i];
				i++;
			}
			else {
				result[k] = right[j];
				j++;
			}
		}
		else if (choice == 3) {
			if (left[i].difficulty > right[j].difficulty) {
				result[k] = left[i];
				i++;
			}
			else {
				result[k] = right[j];
				j++;
			}
		}
		else if (choice == 4) {
			if (left[i].name > right[j].name) {
				result[k] = left[i];
				i++;
			}
			else {
				result[k] = right[j];
				j++;
			}
		}
		else if (choice == 5) {
			if (left[i].name < right[j].name) {
				result[k] = left[i];
				i++;
			}
			else {
				result[k] = right[j];
				j++;
			}
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
	return result;
}


void showRaiting(Raiting* raiting, User * user,string user_name) {
	system("cls");
	cout << "������� �����: " << raiting->test_name << endl;
	cout << "������� ���������: " << raiting->middle_result << endl;
	cout << "================" << endl;
	cout << "������������:" << endl;
	bool isGoten = false;
	Raiting_node* temp = raiting->head;
	while (temp != nullptr) {
		cout << temp->user_name<< " - " << temp->result << endl;
		if (temp->user_name == user_name) {
			isGoten = true;
		}
		temp = temp->next;
	}
	cout << "================" << endl;
	if (isGoten) {
		cout << "��� ��������� ���������: " << LinearFind(raiting, user) << endl;
		cout << "================" << endl;
	}
	else {
		cout << "�� �� ��������� ������ ����" << endl;
	}

	cout << "================" << endl;

	cout << "������� ����� ������� ��� �����������..." << endl;
	cin.get();
}

int LinearFind(Raiting* raiting, User* user) {
	int max = 0;
	Raiting_node* temp = raiting->head;
	while (temp != nullptr) {
		if (temp->user_name == getUserData(user->id, "users/usersData.txt").name && temp->result > max) {
			max = temp->result;
		}
		temp = temp->next;
	}
	return max;
}



void EditTest(Test* test, User user) {
	TestsContainer* tests = Read("tests/" + to_string(getUserData(user.id, "users/usersData.txt").id) + "test.txt", false, user);
	Test temp = Test();

	for (int i = 0; i < tests->count_tests; i++) {
		if (test->name == tests->tests[i].name) {
			temp = tests->tests[i];
			break;
		}
	}
	if (temp.name == "") {
		cout << "���� �� ������!" << endl;
		return;
	}

	while (true) {
		system("cls");
		cout << "=====================" << endl;
		cout << "�������������� �����: " << temp.name << endl;
		cout << "=====================" << endl;
		cout << "�������� ��������:" << endl;
		cout << "1. �������� ��������" << endl;
		cout << "2. �������� ���������" << endl;
		cout << "3. �������� ����������� �������" << endl;
		cout << "4. �������� ������� ��������� ����" << endl;
		cout << "5. ��������� ���������" << endl;
		cout << "6. �����" << endl;
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
		switch (choice) {
		case 1: {
			cout << "������� ����� ��������: ";
			string name;
			cin.ignore();
			getline(cin, name);
			temp.name = name;
			break;
		}
		case 2: {
			cout << "������� ����� ���������: ";
			int difficulty;
			cin >> difficulty;
			temp.difficulty = difficulty;
			break;
		}
		case 3: {
			temp = edit_Q_standart(temp);
			break;
		}
		case 4: {
			temp = edit_Q_guest(temp);
			break;
		}
		case 5: {

		}
		case 6: {
			return;
		}


		}

	}




}


Test edit_Q_standart(Test temp1){
	Test temp = temp1;
	while (true) {
		system("cls");
		cout << "=====================" << endl;
		cout << "����������� �������: " << endl;
		for (int i = 0; i < temp.count_q_standart; i++) {
			cout << i + 1 << ". " << temp.q_standart[i].question << endl;
		}
		cout << "=====================" << endl;
		cout << "�������� ��������:" << endl;
		cout << "1. �������� ������" << endl;
		cout << "2. ������������� ������" << endl;
		cout << "3. ������� ������" << endl;
		cout << "4. �����" << endl;

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
		switch (choice) {
		case 1: {
			cout << "������� ������: ";
			string question;
			cin.ignore();
			getline(cin, question);
			cout << "������� �����: ";
			string answer;
			getline(cin, answer);
			cout << "������� ��������� �������: ";
			int difficulty;
			string temp_cin;
			getline(cin, temp_cin);
			try
			{
				difficulty = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "�������� ����" << endl;
				Sleep(500);
				continue;
			}
			Q_standart* q_standart = new Q_standart[temp.count_q_standart + 1];
			for (int i = 0; i < temp.count_q_standart; i++) {
				q_standart[i] = temp.q_standart[i];
			}
			q_standart[temp.count_q_standart] = Q_standart(question, answer, difficulty);
			temp.q_standart = q_standart;
			temp.count_q_standart++;
			break;
		}
		case 2: {
			cout << "������� ����� ������� ��� ��������������: ";
			int number;
			string temp_cin;
			getline(cin, temp_cin);
			try
			{
				number = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "�������� ����" << endl;
				Sleep(500);
				continue;
			}
			if (number > temp.count_q_standart || number < 0) {
				cout << "�������� ����� �������!" << endl;
				Sleep(500);
				continue;
			}
			cout << "������� ����� ������: ";
			string question;
			cin.ignore();
			getline(cin, question);
			cout << "������� ����� �����: ";
			string answer;
			getline(cin, answer);
			cout << "������� ����� ���������: ";
			int difficulty;
			string temp_cin;
			getline(cin, temp_cin);
			try
			{
				difficulty = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "�������� ����" << endl;
				Sleep(500);
				continue;
			}
			Q_standart* q_standart = new Q_standart[temp.count_q_standart];
			for (int i = 0; i < temp.count_q_standart; i++) {
				if (i == number - 1) {
					q_standart[i] = Q_standart(question, answer, difficulty);
				}
				else {
					q_standart[i] = temp.q_standart[i];
				}
			}
			temp.q_standart = q_standart;
			break;
		}
		case 3: {
			cout << "������� ����� ������� ��� ��������: ";
			int number;
			string temp_cin;
			getline(cin, temp_cin);
			try
			{
				number = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "�������� ����" << endl;
				Sleep(500);
				continue;
			}
			if (number > temp.count_q_standart || number < 0) {
				cout << "�������� ����� �������!" << endl;
				Sleep(500);
				continue;
			}
			Q_standart* q_standart = new Q_standart[temp.count_q_standart - 1];
			int k = 0;
			for (int i = 0; i < temp.count_q_standart; i++) {
				if (i == number - 1) {
					continue;
				}
				q_standart[k] = temp.q_standart[i];
				k++;
			}
			temp.q_standart = q_standart;
			temp.count_q_standart--;
			break;
		}
		case 4: {
			return temp;
		}
		}
	}

}



Test edit_Q_guest(Test temp1) {
	Test temp = temp1;
	while (true) {
		system("cls");
		cout << "=====================" << endl;
		cout << "������� ��������� ����: " << endl;
		for (int i = 0; i < temp.count_q_guest; i++) {
			cout << i + 1 << ". " << temp.q_guest[i].question << endl;
		}
		cout << "=====================" << endl;
		cout << "�������� ��������:" << endl;
		cout << "1. �������� ������" << endl;
		cout << "2. ������������� ������" << endl;
		cout << "3. ������� ������" << endl;
		cout << "4. �����" << endl;

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
		switch (choice) {
		case 1: {
			cout << "������� ������: ";
			string question;
			cin.ignore();
			getline(cin, question);
			cout << "������� ���������� ��������� ������: ";
			int count_answers;
			string temp_cin;
			getline(cin, temp_cin);
			try
			{
				count_answers = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "�������� ����" << endl;
				Sleep(500);
				continue;
			}

			string* answers = new string[count_answers];
			cout << "������� �������� ������: " << endl;
			for (int j = 0; j < count_answers; j++) {
				cout << j + 1 << ". ";
				cin.ignore();
				getline(cin, answers[j]);
			}
			cout << "������� ����� ����������� ������: ";
			int right_answer;
			string temp_cin;
			getline(cin, temp_cin);
			try
			{
				right_answer = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "�������� ����" << endl;
				Sleep(500);
				continue;
			}
			cout << "������� ��������� �������: ";
			int difficulty;
			string temp_cin;
			getline(cin, temp_cin);
			try
			{
				difficulty = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "�������� ����" << endl;
				Sleep(500);
				continue;
			}
			Q_guest* q_guest = new Q_guest[temp.count_q_guest + 1];
			for (int i = 0; i < temp.count_q_guest; i++) {
				q_guest[i] = temp.q_guest[i];
			}
			q_guest[temp.count_q_guest] = Q_guest(question, answers, count_answers, right_answer, difficulty);
			temp.q_guest = q_guest;
			temp.count_q_guest++;
			break;
		}
		case 2: {
			cout << "������� ����� ������� ��� ��������������: ";
			int number;
			string temp_cin;
			getline(cin, temp_cin);
			try
			{
				number = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "�������� ����" << endl;
				Sleep(500);
				continue;
			}
			if (number > temp.count_q_guest || number < 0) {
				cout << "�������� ����� �������!" << endl;
				Sleep(500);
				continue;
			}
			cout << "������� ����� ������: ";
			string question;
			cin.ignore();
			getline(cin, question);
			cout << "������� ���������� ��������� ������: ";
			int count_answers;
			string temp_cin1;
			getline(cin, temp_cin1);
			try
			{
				count_answers = stoi(temp_cin1);
			}
			catch (const std::exception&)
			{
				cout << "�������� ����" << endl;
				Sleep(500);
				continue;
			}
			string* answers = new string[count_answers];
			cout << "������� �������� ������: " << endl;
			for (int j = 0; j < count_answers; j++) {
				cout << j + 1 << ". ";
				cin.ignore();
				getline(cin, answers[j]);
			}
			cout << "������� ����� ����������� ������: ";
			int right_answer;
			string temp_cin1;
			getline(cin, temp_cin1);
			try
			{
				right_answer = stoi(temp_cin1);
			}
			catch (const std::exception&)
			{
				cout << "�������� ����" << endl;
				Sleep(500);
				continue;
			}
			cout << "������� ��������� �������: ";
			int difficulty;
			string temp_cin;
			getline(cin, temp_cin);
			try
			{
				difficulty = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "�������� ����" << endl;
				Sleep(500);
				continue;
			}
			Q_guest* q_guest = new Q_guest[temp.count_q_guest];
			for (int i = 0; i < temp.count_q_guest; i++) {
				if (i == number - 1) {
					q_guest[i] = Q_guest(question, answers, count_answers, right_answer, difficulty);
				}
				else {
					q_guest[i] = temp.q_guest[i];
				}
			}
			temp.q_guest = q_guest;
			break;
		}
		case 3: {
			cout << "������� ����� ������� ��� ��������: ";
			int number;
			string temp_cin;
			getline(cin, temp_cin);
			try
			{
				number = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "�������� ����" << endl;
				Sleep(500);
				continue;
			}
			if (number > temp.count_q_guest || number < 0) {
				cout << "�������� ����� �������!" << endl;
				Sleep(500);
				continue;
			}
			Q_guest* q_guest = new Q_guest[temp.count_q_guest - 1];
			int k = 0;
			for (int i = 0; i < temp.count_q_guest; i++) {
				if (i == number - 1) {
					continue;
				}
				q_guest[k] = temp.q_guest[i];
				k++;
			}
			temp.q_guest = q_guest;
			temp.count_q_guest--;
			break;
		}
		case 4: {
			return temp;
		}
		}
	}
}




// insertion sort tests by difficulty

Test* InsertionSort(Test* tests, int size) {
	Test temp;
	for (int i = 1; i < size; i++) {
		temp = tests[i];
		int j = i - 1;
		while (j >= 0 && tests[j].difficulty > temp.difficulty) {
			tests[j + 1] = tests[j];
			j--;
		}
		tests[j + 1] = temp;
	}
	return tests;
}