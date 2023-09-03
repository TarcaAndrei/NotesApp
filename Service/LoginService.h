//
// Created by Andrei on 26.08.2023.
//

#ifndef APP1_LOGINSERVICE_H
#define APP1_LOGINSERVICE_H

#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<cstdlib>
#include<QDebug>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include "../Repository/OldRepositoryApp.h"

using std::string;

class LoginService {
private:
    OldRepositoryApp& repositoryApp;
    std::string auth_file;
    std::string username;
    std::string password;
    void load_auth_credentials();
    void write_auth_credentials(const std::string& username1, const string& password1);
public:
    explicit LoginService(const string &auth_filename, OldRepositoryApp &repositoryApp);
    std::vector<std::string> get_auth_credentials();
    void set_auth_credentials(const std::string& username1, const string& password1, bool save);
    bool connect_repository();
    ~LoginService()=default;
    LoginService()=default;
};


#endif //APP1_LOGINSERVICE_H
