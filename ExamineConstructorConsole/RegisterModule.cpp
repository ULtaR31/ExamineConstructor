#include <iostream>
#include "Structures.h"
#include "FileModule.h"
#include <string>
#include <windows.h>
using namespace std;

string customHash(const string& input) {
	// ��� 1: ������������� ���������� �������� ����
	unsigned long long hash = 0;

	// ��� 2: ������������� �������� ������� ������
	for (char c : input) {
		hash ^= static_cast<unsigned long long>(c);
		hash = (hash << 7) | (hash >> 57); // ����� ����� �� 7 ��� � ����� ������ �� 57 ���
		hash += 0xabcdef1234567890; // ��������� ������������ �����
	}

	// ��� 3: ��������� ������� ���-�������
	hash ^= (hash << 13);
	hash ^= (hash >> 47);
	hash ^= (hash << 23);

	// ��� 4: ��������� �������������� ��������� ���
	for (int i = 0; i < 10; ++i) {
		hash = ((hash << 5) ^ (hash >> 59)) * 2654435761;
	}

	// ��� 5: ����������� �������� ���� � ������ � ����������
	return to_string(hash);
}

void RegisterModule() {
	while(true){
		system("cls");
		cout << "�����������" << endl;
		cout << "������� �����: ";
		string login;
		cin >> login;
		cout << "������� ������: ";
		string password;
		cin.ignore();
		getline(cin, password);
		// ���������� ������
		password = customHash(password);

		cout << "������� ���: ";
		string name;
		cin >> name;
		cout << "������� �������: ";
		string surname;
		cin >> surname;
		cout << "������� email: ";
		string email;
		cin >> email;
		cout << "������� �������: ";
		int age;
		string temp;
		cin.ignore();
		getline(cin, temp);
		try {
			age = stoi(temp);
		}
		catch (exception e) {
			cout << "�������� ����" << endl;
			Sleep(1000);
			continue;
		}
		string UserPath = "users/users.txt";
		string UserDataPath = "users/usersData.txt";

		User::count_users = getLastId(UserPath);
		User user = User(login, password, 1);

		UserData userData = UserData(name, login, surname, email, age);

		int status = WriteToFile(UserPath, user);
		if (status == 0)
			cout << "������������ ������� �������� � ����" << endl;
		else
			cout << "������ � ������ � �������" << endl;
		status = WriteToFile(UserDataPath, userData);
		if (status == 0)
			cout << "�������� �����������" << endl;
		else
			cout << "������ � ������ � �������" << endl;
		Sleep(1000);
		break;
	}

}

User Login() {
	while (true) {
		cout << "================================" << endl;
		system("cls");
		cout << "����" << endl;
		string login;
		string password;
		cout << "������� �����: ";
		cin >> login;
		cout << "������� ������: ";
		cin >> password;
		// ���������� ������
		password = customHash(password);

		string UserPath = "users/users.txt";
		string UserDataPath = "users/usersData.txt";

		User user = FindUser(UserPath, login);
		if (password != user.password) {
			cout << "�������� ������" << endl;
			Sleep(1000);
			continue;
		}
		else {
			UserData usd = getUserData(user.id, UserDataPath);
			cout << "���� ��������" << endl;
			Sleep(1000);
			cout << "�� ����� ��� " << usd.name << endl;
			cout << "=========================" << endl;
			return user;
		}
	}

}