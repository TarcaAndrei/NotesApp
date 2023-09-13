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
#define NAME_MODIF 1
#define DETAILS_MODIF 2
#define LIST_MODIF 3
#define DATE_TIME_MODIF 4
#define PRIORITY_MODIF 5
#define DONE_MODIF 6

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
    void modify_task(int id_task, int id_list, const string &name_t, const string &details_t, const QDateTime& time_due_t, const string &priority_t, bool is_done=false);

    void delete_task(int id_task);

    void add_new_list(const string &listName);

    void modify_list(int id_l, const string &newName);

    void delete_list(int id_l);

    void set_task_done(int id_task, int id_list, bool is_done);
};


#endif //APP1_REPOSITORYAPP_H
