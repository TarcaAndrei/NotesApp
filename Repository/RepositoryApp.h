//
// Created by Andrei on 25.08.2023.
//

#ifndef APP1_REPOSITORYAPP_H
#define APP1_REPOSITORYAPP_H
#include <QtSql>
#include <string>
#include <QString>
#include <QSqlDatabase>
#include<vector>
#include<unordered_map>
#include "../Domain/Task.h"

using std::string;
using std::vector;
using std::unordered_map;

class RepositoryApp {
private:
    unordered_map<string, vector<Task>> all_data_list;
    QSqlDatabase repository_database;
    void load_data_from_db();
public:
    ~RepositoryApp();
    RepositoryApp();
    void print_data();
    bool connect_to_db(const string& host_name, const string& db_name, const string& user_name, const string& passwd, int port);
    vector<string> get_all_lists();
    vector<Task> get_tasks_from_list(const string& list_name);
    ///MERGE
        ///ACUM TREBUIE SA FACI SCHEMA PE HARTIE CU CE SA CONTINA SI CUM SA MEARGA
        ///TRE SA VEZI CUM POTI ACCESA TOATE TABELELE SI ETC WTC
        //////nu asa -> nu da toate datele de conectare aici...fa alta functie de connect
};


#endif //APP1_REPOSITORYAPP_H
