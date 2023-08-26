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
    }
    else{
        throw std::domain_error(this->repository_database.lastError().text().toStdString());
    }
    return true;
}

RepositoryApp::~RepositoryApp() {
    this->repository_database.close();
}

void RepositoryApp::print_data() {
    if(this->repository_database.isOpen()){
        QSqlQuery qry;
        if(qry.exec("SELECT * from first_list")){
            while(qry.next()){
                auto id = qry.value(0).toInt();
                auto name = qry.value(1).toString();
                auto details = qry.value(2).toString();
                auto due = qry.value(3).toString();
                auto priority = qry.value(5).toString();
                qDebug() << id << name << details<< due<< priority;
            }
        }
        else{
            qDebug()<<"Eroare la query";
        };
    }
    else{
        qDebug()<<"EROARE";
    }
}

RepositoryApp::RepositoryApp() {
    this->repository_database = QSqlDatabase::addDatabase("QMYSQL");
}
