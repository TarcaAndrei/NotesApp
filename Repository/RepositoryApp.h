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
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QJsonObject>
#include<QJsonDocument>
#include "../Domain/Task.h"
#include "../Observer/ObservableApp.h"

#define LOAD_F "Loading finished"

using std::string;
using std::vector;
using std::unordered_map;

class RepositoryApp : public ObservableApp{
private:
    unordered_map<int, vector<Task>> all_data_list;
    std::vector<std::pair<int, string>> list_names;
    string access_token;
    void reload_data();
    void reload_lists();
    void reload_tasks();
    QNetworkAccessManager* accessManager;
    QNetworkReply* reply_lists;
    QNetworkReply* reply_tasks;
    QNetworkReply* reply_crud_tasks;
    //imi trebe unu dinasta la fiecare......
public:
    RepositoryApp();
    ~RepositoryApp()=default;
    void set_token(const string& token);
    std::vector<std::pair<int, string>> get_all_lists();
    vector<Task> get_tasks_from_list(int id_lista);
    void add_Task(int id_list, const Task& task);
    Task get_task_from_id(int id_task);
};


#endif //APP1_REPOSITORYAPP_H
