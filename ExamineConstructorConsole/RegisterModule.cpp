#include <iostream>
#include "Structures.h"
#include "FileModule.h"
using namespace std;



void RegisterModule() {

	cout << "�����������" << endl;
	cout << "������� �����: ";
	string login;
	cin >> login;
	cout << "������� ������: ";
	string password;
	cin >> password;
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

/*
int id;
	string name;
	string surname;
	string login;
	int age;
	string email;
*/