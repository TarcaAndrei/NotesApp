//
// Created by Andrei on 02.09.2023.
//

#include "ServiceAuth.h"

ServiceAuth::ServiceAuth(const std::string &auth_filename, RepositoryApp &repositoryApp1)
        : repositoryApp(repositoryApp1) {
    this->auth_file = auth_filename;
    this->accessManager = new QNetworkAccessManager;
    this->load_auth_credentials_from_file();
}

void ServiceAuth::load_auth_credentials_from_file() {
    std::ifstream fin;
    fin.open(this->auth_file);
    if(fin.fail()){
//        qDebug()<<this->auth_file;
        throw std::exception();
    }
    if(fin.good()){
        std::string buffer;
        std::getline(fin, buffer);
        if(buffer.empty()){
//            qDebug()<<"No auth";
            return;
        }
        this->username = buffer;
//        qDebug()<<buffer;//username
        buffer.clear();
        std::getline(fin, buffer);
        if(buffer.empty()){
//            qDebug()<<"No auth";
            this->username.clear();
            this->password.clear();
            return;
        }
        this->password = buffer;
//        qDebug()<<buffer;//parola -> ulterior si sa fac criptare
    }
}

void ServiceAuth::write_auth_credentials_to_file() {
    std::ofstream fout;
    fout.open(this->auth_file);
    if(fout.fail()){
        throw std::exception();
    }
    fout<<username<<'\n'<<password<<'\n';
}

std::vector<std::string> ServiceAuth::get_auth_credentials() {
    std::vector<std::string> return_vector;
    if(not this->username.empty()) {
        return_vector.push_back(this->username);
        return_vector.push_back(this->password);
    }
    return return_vector;
}

void ServiceAuth::set_auth_credentials(const std::string &username1, const std::string &password1, bool save) {
    this->username = username1;
    this->password = password1;
    if(save){
        this->write_auth_credentials_to_file();
    }
}

void ServiceAuth::connect_to_api() {
    std::string url = getenv("host_name");
    url += ":";
    url += getenv("port");
    url += "/api/login/";
    //aici avem url-ul
    QUrl qUrl = QUrl(QString::fromStdString(url));
    QNetworkRequest request(qUrl);
    //headerul
//    qDebug()<<qUrl;
    request.setRawHeader("Content-Type", "application/json");
    QByteArray postData;
    string string_to_post = R"({"username": ")";
    string_to_post += username;
    string_to_post += R"(", "password": ")";
    string_to_post += password;
    string_to_post += R"("})";
    postData.append(string_to_post);
    this->reply = accessManager->post(request, postData);
//    QNetworkReply* reply = accessManager.get(request);
    QObject::connect(reply, &QNetworkReply::finished, [&](){
        if(reply->error() == QNetworkReply::NoError){
            auto responseData = reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
//            qDebug()<<jsonDocument;
            if(not jsonDocument.isNull()){
                QJsonObject jsonObject = jsonDocument.object();
                QJsonValue jsonToken = jsonObject.value("token");
                auto stringToken = jsonToken.toString().toStdString();
                this->token = stringToken;
                this->repositoryApp.set_token(token);
//                qDebug()<<"Connected successfully";
                this->notify_all(LOGIN_SUCC); //logged successfully
//                QJsonObject jsonObject1 = jsonObject.value("user").toObject();
//                QJsonValue jsonValue1 = jsonObject1.value("username");
//                qDebug()<<jsonValue1;
            }
        }
        else{
            this->notify_all(LOGIN_N_SUCC, this->reply->errorString().toStdString());
        }
        reply->deleteLater();
    });
}

void ServiceAuth::register_to_api(const std::string &username1, const std::string &password1, const std::string& email1) {
    std::string url = getenv("host_name");
    url += ":";
    url += getenv("port");
    url += "/api/register/";
    QUrl qUrl = QUrl(QString::fromStdString(url));
    QNetworkRequest request(qUrl);
    request.setRawHeader("Content-Type", "application/json");
    QByteArray postData;
    string string_to_post = R"({"username": ")";
    string_to_post += username1;
    string_to_post += R"(", "password": ")";
    string_to_post += password1;
    string_to_post += R"(", "email": ")";
    string_to_post += email1;
    string_to_post += R"("})";
    postData.append(string_to_post);
    this->reply = accessManager->post(request, postData);
//    QNetworkReply* reply = accessManager.get(request);
    QObject::connect(reply, &QNetworkReply::finished, [&](){
        if(reply->error() == QNetworkReply::NoError){
            auto responseData = reply->readAll();
//            qDebug()<<responseData;
            QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
//            qDebug()<<jsonDocument;
            if(not jsonDocument.isNull()){
                QJsonObject jsonObject = jsonDocument.object();
                QJsonValue jsonToken = jsonObject.value("token");
                auto stringToken = jsonToken.toString().toStdString();
                this->notify_all(REGISTER_SUCC);
//                this->token = stringToken;
//                this->repositoryApp.set_token(token);
//                QJsonObject jsonObject1 = jsonObject.value("user").toObject();
//                QJsonValue jsonValue1 = jsonObject1.value("username");
//                qDebug()<<jsonValue1;
            }
        }
        else{
//            qDebug()<<this->reply->errorString();
            this->notify_all(REGISTER_N_SUCC, this->reply->errorString().toStdString());
//            qDebug()<<"Eroare: "<<reply->errorString();
        }
        reply->deleteLater();
    });
}

