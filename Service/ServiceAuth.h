//
// Created by Andrei on 02.09.2023.
//

#ifndef APP1_SERVICEAUTH_H
#define APP1_SERVICEAUTH_H

#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<cstdlib>
#include<QDebug>
#include "../Repository/RepositoryApp.h"
#include "../Observer/ObservableAuth.h"

#define LOGIN_SUCC "LoginSucceed"
#define LOGIN_N_SUCC "LoginNotSucceed"
#define REGISTER_SUCC "RegisterSucceed"
#define REGISTER_N_SUCC "RegisterNotSucceed"

class ServiceAuth: public ObservableAuth {
private:
    RepositoryApp& repositoryApp;
    std::string auth_file;
    std::string username;
    std::string password;
    std::string token;
    QNetworkAccessManager* accessManager;
    QNetworkReply* reply;
    void load_auth_credentials_from_file();
    void write_auth_credentials_to_file();
public:
    explicit ServiceAuth(const std::string &auth_filename, RepositoryApp &repositoryApp);
    ~ServiceAuth()=default;
    std::vector<std::string> get_auth_credentials();
    void set_auth_credentials(const std::string& username1, const std::string& password1, bool save=false);
    void connect_to_api();
    void register_to_api(const std::string &username1, const std::string &password1, const std::string& email1);
};


#endif //APP1_SERVICEAUTH_H
