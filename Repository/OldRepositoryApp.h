//
// Created by Andrei on 25.08.2023.
//

#ifndef APP1_OLDREPOSITORYAPP_H
#define APP1_OLDREPOSITORYAPP_H
#include <QtSql>
#include <string>
#include <QString>
#include <iostream>
#include <QSqlDatabase>
#include<vector>
#include<unordered_map>
#include "../Domain/Task.h"

using std::string;
using std::vector;
using std::unordered_map;

class OldRepositoryApp {
private:
    unordered_map<string, vector<Task>> all_data_list;
    QSqlDatabase repository_database;
    void reload_data_from_db();
public:
    ~OldRepositoryApp();
    OldRepositoryApp();
    bool connect_to_db(const string& host_name, const string& db_name, const string& user_name, const string& passwd, int port);
    vector<string> get_all_lists();
    vector<Task> get_tasks_from_list(const string& list_name);
    void add_Task(const string& list_name, const Task& new_task);
    ///MERGE
        ///ACUM TREBUIE SA FACI SCHEMA PE HARTIE CU CE SA CONTINA SI CUM SA MEARGA
        ///TRE SA VEZI CUM POTI ACCESA TOATE TABELELE SI ETC WTC
        //////nu asa -> nu da toate datele de conectare aici...fa alta functie de connect
};


#endif //APP1_OLDREPOSITORYAPP_H
