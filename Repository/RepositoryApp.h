//
// Created by Andrei on 25.08.2023.
//

#ifndef APP1_REPOSITORYAPP_H
#define APP1_REPOSITORYAPP_H
#include <QtSql>
#include <string>
#include <QString>
#include <QSqlDatabase>
using std::string;

class RepositoryApp {
private:
    QSqlDatabase repository_database;
    bool connect_to_db(const string& host_name, const string& db_name, const string& user_name, const string& passwd, int port);
public:
    ~RepositoryApp();
    RepositoryApp(const string& host_name, const string& db_name, const string& user_name, const string& passwd, int port);
    void print_data();      ///MERGE
        ///ACUM TREBUIE SA FACI SCHEMA PE HARTIE CU CE SA CONTINA SI CUM SA MEARGA
        ///TRE SA VEZI CUM POTI ACCESA TOATE TABELELE SI ETC WTC
};


#endif //APP1_REPOSITORYAPP_H
