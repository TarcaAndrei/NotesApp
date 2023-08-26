//
// Created by Andrei on 26.08.2023.
//

#include "LoginService.h"

LoginService::LoginService(const string &auth_filename) {
    this->auth_file = auth_filename;
    this->load_auth_credentials();
}

void LoginService::load_auth_credentials() {
    std::ifstream fin;
    fin.open(this->auth_file);
    if(fin.fail()){
        throw std::exception();
    }
    if(fin.good()){
        string buffer;
        std::getline(fin, buffer);
        if(buffer.empty()){
            qDebug()<<"No auth";
            return;
        }
        this->username = buffer;
        qDebug()<<buffer;//username
        buffer.clear();
        std::getline(fin, buffer);
        if(buffer.empty()){
            qDebug()<<"No auth";
            this->username.clear();
            this->password.clear();
            return;
        }
        this->password = buffer;
        qDebug()<<buffer;//parola -> ulterior si sa fac criptare
    }
}

void LoginService::write_auth_credentials(const string &username1, const string &password1) {
    std::ofstream fout;
    fout.open(this->auth_file);
    if(fout.fail()){
        throw std::exception();
    }
    fout<<username<<'\n'<<password<<'\n';
}

std::vector<std::string> LoginService::get_auth_credentials() {
    std::vector<std::string> return_vector;
    if(not this->username.empty()) {
        return_vector.push_back(this->username);
        return_vector.push_back(this->password);
    }
    return return_vector;
}

void LoginService::set_auth_credentials(const string &username1, const string &password1, bool save) {
    this->username = username1;
    this->password = password1;
    if(save){
        this->write_auth_credentials(this->username, this->password);
    }
}

