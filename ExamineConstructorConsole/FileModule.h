#pragma once
#include "Structures.h"


int WriteToFile(string file_path, User user);
int WriteToFile(string file_path, Test test);
int WriteToFile(string file_pass, UserData user);

UserData getUserData(int id, string file_path);
User FindUser(string file_path, string login);