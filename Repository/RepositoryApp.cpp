//
// Created by Andrei on 25.08.2023.
//

#include "RepositoryApp.h"

bool RepositoryApp::connect_to_db(const string &host_name, const string &db_name, const string &user_name,
                                  const string &passwd, int port) {
    this->repository_database.setHostName(QString::fromStdString(host_name));
    this->repository_database.setDatabaseName(QString::fromStdString(db_name));
    this->repository_database.setUserName(QString::fromStdString(user_name));
    this->repository_database.setPassword(QString::fromStdString(passwd));
    this->repository_database.setPort(port);
    auto ok = this->repository_database.open();
    if(ok){
        qDebug()<<"Database opened successfully!";
        this->reload_data_from_db();
    }
    else{
        throw std::domain_error(this->repository_database.lastError().text().toStdString());
    }
    return true;
}

RepositoryApp::~RepositoryApp() {
    this->repository_database.close();
}



RepositoryApp::RepositoryApp() {
    this->repository_database = QSqlDatabase::addDatabase("QMYSQL");
}

void RepositoryApp::reload_data_from_db() {
    this->all_data_list.clear();
    auto lista_tabele = this->repository_database.tables();
    for(auto& it : lista_tabele){
        QSqlQuery qSqlQuery;
        string sqlquerytxt = "SELECT * from ";
        sqlquerytxt += it.toStdString();
//        qDebug()<<sqlquerytxt;
        if(qSqlQuery.exec(QString::fromStdString(sqlquerytxt))){
            while(qSqlQuery.next()) {
                auto id = qSqlQuery.value(0).toInt();
                auto name = qSqlQuery.value(1).toString().toStdString();
                auto details = qSqlQuery.value(2).toString().toStdString();
                auto due = qSqlQuery.value(3).toString();
                auto created = qSqlQuery.value(4).toString();
                auto priority = qSqlQuery.value(5).toString().toStdString();
                auto date_format_due = QDateTime::fromString(due, Qt::ISODate);
                auto date_format_created = QDateTime::fromString(created, Qt::ISODate);
                auto is_done = qSqlQuery.value(6).toBool();
                auto task_nou = Task(id, name, details, date_format_due, date_format_created, priority, is_done);
                this->all_data_list[it.toStdString()].push_back(task_nou);
            }
        }
        else{
            qDebug()<<"Eroare la query";
        }
    }///in teorie nu ar trebui sa salvez doar numele tabelelor...
    ///deci asta ar trb sa schimb amu
}

vector<string> RepositoryApp::get_all_lists() {
    vector<string> list_tables;
    for(auto& it : this->all_data_list){
        list_tables.push_back(it.first);
    }
    return list_tables;
}

vector<Task> RepositoryApp::get_tasks_from_list(const string &list_name) {
    return this->all_data_list[list_name];
}

void RepositoryApp::add_Task(const string &list_name, const Task &new_task) {
    auto lista_tabele = this->repository_database.tables();
    auto list_name_qt = QString::fromStdString(list_name);
    auto found = std::find_if(lista_tabele.begin(), lista_tabele.end(), [list_name_qt](const QString& elem){
        return list_name_qt == elem;
    });
    if(found == lista_tabele.end()){
        qDebug()<<"Eroare";
        throw std::exception();
    }
    QSqlQuery qSqlQuery;
    string sqlquerytxt = "INSERT INTO " + list_name + " VALUES (";
    sqlquerytxt += std::to_string(new_task.get_id());
    sqlquerytxt += ", \"";
    sqlquerytxt += new_task.get_name();
    sqlquerytxt += "\", \"";
    sqlquerytxt += new_task.get_details();
    sqlquerytxt += "\", \"";
    sqlquerytxt += new_task.get_time_due().toString(Qt::ISODate).toStdString();
    sqlquerytxt += "\", \"";
    sqlquerytxt += new_task.get_last_updated().toString(Qt::ISODate).toStdString();
    sqlquerytxt += "\", \"";
    sqlquerytxt += new_task.get_priority();
    sqlquerytxt += "\", ";
    sqlquerytxt += std::to_string(new_task.is_done());
    sqlquerytxt += ");";
//    qDebug()<<sqlquerytxt;
    std::cout<<sqlquerytxt;
    if(qSqlQuery.exec(QString::fromStdString(sqlquerytxt))){

    }
    else{
        qDebug()<<qSqlQuery.lastError().text();
        throw std::exception();
    }
    this->reload_data_from_db();
}

