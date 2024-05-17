#include <iostream>
#include "Structures.h"
#include "FileModule.h"
#include <string>
#include <windows.h>
using namespace std;

bool HasSpace(string str) {
	for (int i = 0; i < str.length(); i++)
		if (str[i] == ' ' || str[i] == '\n') return true;
	return false;
}

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
	while (true) {
		system("cls");
		cout << "===========================" << endl;
		cout << "| �����������" << endl;
		cout << "| ������� �����: ";
		string login;
		getline(cin, login);
		if (HasSpace(login)) {
			cout << "����� �� ������ ��������� ��������" << endl;
			Sleep(1000);
			continue;
		}
		if (login == "") {
			cout << "����� �� ����� ���� ������" << endl;
			Sleep(1000);
			continue;
		}
		cout << "| ������� ������: ";
		string password;
		getline(cin, password);
		if (HasSpace(password)) {
			cout << "������ �� ������ ��������� ��������" << endl;
			Sleep(1000);
			continue;
		}
		if (password == "") {
			cout << "������ �� ����� ���� ������" << endl;
			Sleep(1000);
			continue;
		}
		cout << "| ������� ���: ";
		string name;
		getline(cin, name);
		if (HasSpace(name)) {
			cout << "��� �� ������ ��������� ��������" << endl;
			Sleep(1000);
			continue;
		}
		if (name == "") {
			cout << "��� �� ����� ���� ������" << endl;
			Sleep(1000);
			continue;
		}
		cout << "| ������� �������: ";
		string surname;
		getline(cin, surname);
		if (HasSpace(surname)) {
			cout << "������� �� ������ ��������� ��������" << endl;
			Sleep(1000);
			continue;
		}
		if (surname == "") {
			cout << "������� �� ����� ���� ������" << endl;
			Sleep(1000);
			continue;
		}
		cout << "| ������� email: ";
		string email;
		getline(cin, email);
		if (HasSpace(email)) {
			cout << "Email �� ������ ��������� ��������" << endl;
			Sleep(1000);
			continue;
		}
		if (email == "") {
			cout << "Email �� ����� ���� ������" << endl;
			Sleep(1000);
			continue;
		}
		cout << "| ������� �������: ";
		int age;
		string temp;
		getline(cin, temp);
		try {
			age = stoi(temp);
		}
		catch (exception e) {
			cout << "�������� ����" << endl;
			Sleep(1000);
			continue;
		}

		if (age < 0 || age > 120) {
			cout << "�������� �������" << endl;
			Sleep(1000);
			continue;
		}

		// ���������� ������
		User get_user = FindUser("users/users.txt", login);
		if (get_user.id != -1) {
			cout << "������������ � ����� ������� ��� ����������" << endl;
			Sleep(1000);
			continue;
		}
		password = customHash(password);

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
		{
			cout << "�������� �����������" << endl;

			cout << "                                                                  " << endl;
			cout << "                                                                  " << endl;
			cout << "                                                                  " << endl;
			cout << "                                                                  " << endl;
			cout << "      =======     ||         ||   ||=====\\     ||=======    ||====\\            " << endl;
			cout << "    //            ||         ||   ||      \\\\   ||           ||     \\\\          " << endl;
			cout << "   ||             ||         ||   ||      ||   ||           ||     ||          " << endl;
			cout << "   \\\\             ||         ||   ||      //   ||           ||     //          " << endl;
			cout << "    \\======\\      ||         ||   ||=====/     ||=======    ||====/            " << endl;
			cout << "            \\\\    ||         ||   ||           ||           ||    \\\\          " << endl;
			cout << "            ||    ||         ||   ||           ||           ||     \\\\          " << endl;
			cout << "           //     \\\\        //    ||           ||           ||      \\\\         " << endl;
			cout << "     ======/        \\======/      ||           ||=======    ||       \\\\        " << endl;
			cout << "                                                                  " << endl;
			cout << "                                                                  " << endl;
			cout << "                                                                  " << endl;
			cout << "                                                                  " << endl;

			Sleep(1000);
		}
		else
			cout << "������ � ������ � �������" << endl;
		Sleep(1000);
		break;
	}

}

User Login() {
	while (true) {
		system("cls");
		cout << "===========================" << endl;
		cout << "| ����                    " << endl;
		string login;
		string password;
		cout << "| ������� �����:";
		getline(cin, login);
		cout << "| ������� ������: ";
		getline(cin, password);
		if (login == "" || password == "") {
			cout << "| ����� ��� ������ �� ����� ���� �������" << endl;
			Sleep(1000);
			continue;
		}
		if (HasSpace(login) || HasSpace(password)) {
			cout << "| ����� ��� ������ �� ����� ��������� �������" << endl;
			Sleep(1000);
			continue;
		}
		// ���������� ������
		password = customHash(password);

		string UserPath = "users/users.txt";
		string UserDataPath = "users/usersData.txt";

		User user = FindUser(UserPath, login);
		if (password != user.password) {
			cout << "| �������� ����� ��� ������" << endl;
			Sleep(1000);
			continue;
		}
		else {
			UserData usd = getUserData(user.id, UserDataPath);
			cout << "| ���� ��������" << endl;
			Sleep(1000);
			return user;
		}
	}

}


