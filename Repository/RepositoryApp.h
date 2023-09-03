//
// Created by Andrei on 02.09.2023.
//

#ifndef APP1_REPOSITORYAPP_H
#define APP1_REPOSITORYAPP_H

#include <string>
#include <QString>
#include <iostream>
#include<vector>
#include<unordered_map>
#include "../Domain/Task.h"
using std::string;
using std::vector;
using std::unordered_map;

class RepositoryApp {
private:
    string access_token;
    void reload_data();
public:
    RepositoryApp()=default;
    ~RepositoryApp()=default;
    void set_token(const string& token);

    vector<string> get_all_lists();

    vector<Task> get_tasks_from_list(const string &basicString);

    void add_Task(const string &basicString, Task task);
};


#endif //APP1_REPOSITORYAPP_H
