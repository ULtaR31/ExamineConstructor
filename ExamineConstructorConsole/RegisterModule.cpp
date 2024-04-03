#include <iostream>
#include "Structures.h"
#include "FileModule.h"
using namespace std;

string encrypt(string str) {
	string encrypted = "";
	for (int i = 0; i < str.length(); i++) {
		encrypted += str[i] + 1;
	}
	return encrypted;
}
string decrypt(string str) {
	string decrypted = "";
	for (int i = 0; i < str.length(); i++) {
		decrypted += str[i] - 1;
	}
	return decrypted;
}

void RegisterModule() {
	system("cls");
	cout << "�����������" << endl;
	cout << "������� �����: ";
	string login;
	cin >> login;
	cout << "������� ������: ";
	string password;
	cin >> password;
	// ���������� ������
	password = encrypt(password);

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
	cin >> age;

	string UserPath= "users/users.txt";
	string UserDataPath= "users/usersData.txt";

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
		password = encrypt(password);

		string UserPath = "users/users.txt";
		string UserDataPath = "users/usersData.txt";

		User user = FindUser(UserPath, login);
		cout << user.password << " " << password << endl;
		if (password != user.password) {
			cout << "�������� ������" << endl;
			continue;
		}
		else {
			UserData usd = getUserData(user.id, UserDataPath);
			cout << "���� ��������" << endl;
			cout << "�� ����� ��� " << usd.name << endl;
			cout << "=========================" << endl;
			return user;
		}
	}

}






/*
int id;
	string name;
	string surname;
	string login;
	int age;
	string email;
*/