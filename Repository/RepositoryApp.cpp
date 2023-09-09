//
// Created by Andrei on 02.09.2023.
//

#include <QJsonArray>
#include "RepositoryApp.h"

void RepositoryApp::set_token(const string &token) {
    this->access_token = token;
    this->reload_data();
}


void RepositoryApp::add_Task(int id_list, const Task &task) {
    std::string url = getenv("host_name");
    url += ":";
    url += getenv("port");
    url += "/api/";
    url += "tasks/";                        /// nu uita sa modifici asta
    QUrl qUrl = QUrl(QString::fromStdString(url));
    QNetworkRequest request(qUrl);
    request.setRawHeader("Content-Type", "application/json");
    QByteArray auth_token;
    auth_token.append("Token ");
    auth_token.append(QString::fromStdString(this->access_token).toUtf8());
    request.setRawHeader("Authorization", auth_token);
    QByteArray postData;
    string string_to_post = R"({"taskName": ")";
    string_to_post += task.get_name();
    string_to_post += R"(", "taskDetails": ")";
    string_to_post += task.get_details();
    string_to_post += R"(", "taskList": )";
    string_to_post += std::to_string(id_list);
    string_to_post += R"(, "taskDue": ")";
    string_to_post += task.get_time_due().toString(Qt::ISODate).toStdString();
    string_to_post += R"(", "taskPriority": ")";
    string_to_post += task.get_priority();
    string_to_post += R"(", "taskDone": )";
    string_to_post += std::to_string(task.is_done());
//    string_to_post += std::to_string(task.is_done());
    string_to_post += R"(})";        //=>> create-ul la o lista
    qDebug()<<string_to_post;
    postData.append(string_to_post);
    this->reply_crud_tasks = accessManager->post(request, postData);
    QObject::connect(reply_crud_tasks, &QNetworkReply::finished, [&](){
        if(reply_crud_tasks->error() == QNetworkReply::NoError){
            auto responseData = reply_crud_tasks->readAll();
//            qDebug()<<responseData.toStdString();
        }
        else{
            qDebug()<<"Eroare la PUSH REQUEST la Tasks";
            qDebug()<<reply_crud_tasks->errorString();
        }
        this->reply_crud_tasks->deleteLater();
        this->reload_data();
    });
}

void RepositoryApp::reload_data() {
    this->list_names.clear();
    this->all_data_list.clear();
    this->reload_lists();

}

RepositoryApp::RepositoryApp() {
    this->accessManager = new QNetworkAccessManager;
}

void RepositoryApp::reload_lists() {
    std::string url = getenv("host_name");
    url += ":";
    url += getenv("port");
    url += "/api/";
    url += "lists/";
    QUrl qUrl = QUrl(QString::fromStdString(url));
    QNetworkRequest request(qUrl);
    request.setRawHeader("Content-Type", "application/json");
    QByteArray auth_token;
    auth_token.append("Token ");
    auth_token.append(QString::fromStdString(this->access_token).toUtf8());
    request.setRawHeader("Authorization", auth_token);
    this->reply_lists = accessManager->get(request);
//    qDebug()<<this->replylists;

//    QByteArray postData;
//    string string_to_post = R"({"listName": ")";
//    string_to_post += "ThirdList";
//    string_to_post += R"("})";        //=>> create-ul la o lista
//    postData.append(string_to_post);
//    this->replylists = accessManager->post(request, postData);

    QObject::connect(reply_lists, &QNetworkReply::finished, [&](){
//        qDebug()<<this->replylists;
        if(reply_lists->error() == QNetworkReply::NoError){
            auto responseData = reply_lists->readAll();
            auto jsonDoc = QJsonDocument::fromJson(responseData);
            if(not jsonDoc.isNull()){
                auto jsonArray = jsonDoc.array();
                for(auto it : jsonArray){
                    auto jsonObj = it.toObject();
                    auto id_l = jsonObj.value("id").toInt();
                    auto name_l = jsonObj.value("listName").toString().toStdString();
                    this->list_names.push_back(std::make_pair(id_l, name_l));
                }
            }
            else{
                qDebug()<<"Document null";
            }
        }
        else{
            qDebug()<<"Eroare la GET REQUEST la Lists";
        }
        this->reply_lists->deleteLater();
        this->reload_tasks();
    });
}

void RepositoryApp::reload_tasks() {
    std::string url = getenv("host_name");
    url += ":";
    url += getenv("port");
    url += "/api/";
    url += "tasks/";
    QUrl qUrl = QUrl(QString::fromStdString(url));
    QNetworkRequest request(qUrl);
    request.setRawHeader("Content-Type", "application/json");
    QByteArray auth_token;
    auth_token.append("Token ");
    auth_token.append(QString::fromStdString(this->access_token).toUtf8());
    request.setRawHeader("Authorization", auth_token);
    this->reply_tasks = accessManager->get(request);
//    qDebug()<<this->reply;
    QObject::connect(reply_tasks, &QNetworkReply::finished, [&](){
//        qDebug()<<this->reply;
        if(reply_tasks->error() == QNetworkReply::NoError){
            auto responseData = reply_tasks->readAll();
            auto jsonDoc = QJsonDocument::fromJson(responseData);
            if(not jsonDoc.isNull()){
                auto jsonArray = jsonDoc.array();
                for(auto it : jsonArray){
                    auto jsonObj = it.toObject();
//                    qDebug()<<jsonObj;
                    auto id_t = jsonObj.value("id").toInt();
                    auto name_t = jsonObj.value("taskName").toString().toStdString();
                    auto details_t = jsonObj.value("taskDetails").toString().toStdString();
                    auto time_due_t = jsonObj.value("taskDue").toString();
                    auto done_t = jsonObj.value("taskDone").toBool();
                    auto priority_t = jsonObj.value("taskPriority").toString().toStdString();
                    auto task_list_id = jsonObj.value("taskList").toInt();
                    auto time_date_due = QDateTime::fromString(time_due_t, Qt::ISODate);
                    auto task_nou = Task(id_t, name_t, details_t, time_date_due, priority_t, done_t);
                    this->all_data_list[task_list_id].push_back(task_nou);
                }
            }
        }
        else{
            qDebug()<<"Eroare la GET REQUEST la Lists";
        }
        this->reply_tasks->deleteLater();
        this->notify_all(LOAD_F);
    });
}

vector<Task> RepositoryApp::get_tasks_from_list(int id_lista) {
    return this->all_data_list[id_lista];
}

std::vector<std::pair<int, string>> RepositoryApp::get_all_lists() {
    return this->list_names;
}

Task RepositoryApp::get_task_from_id(int id_task) {
    for(const auto& it : this->all_data_list){
        for(const auto&iterator : it.second){
            if(iterator.get_id() == id_task){
                return iterator;
            }
        }
    }
    throw std::exception();
}

void RepositoryApp::modify_task(int id_task, int id_list, const string &name_t, const string &details_t, const QDateTime& time_due_t, const string &priority_t, bool is_done){
    std::string url = getenv("host_name");
    url += ":";
    url += getenv("port");
    url += "/api/";
    url += "task/";
    url += std::to_string(id_task);
    QUrl qUrl = QUrl(QString::fromStdString(url));
    QNetworkRequest request(qUrl);
    request.setRawHeader("Content-Type", "application/json");
    QByteArray auth_token;
    auth_token.append("Token ");
    auth_token.append(QString::fromStdString(this->access_token).toUtf8());
    request.setRawHeader("Authorization", auth_token);
    QByteArray postData;
    string string_to_post = R"({"taskName": ")";
    string_to_post += name_t;
    string_to_post += R"(", "taskDetails": ")";
    string_to_post += details_t;
    string_to_post += R"(", "taskList": )";
    string_to_post += std::to_string(id_list);
    string_to_post += R"(, "taskDue": ")";
    string_to_post += time_due_t.toString(Qt::ISODate).toStdString();
    string_to_post += R"(", "taskPriority": ")";
    string_to_post += priority_t;
    string_to_post += R"(", "taskDone": )";
    string_to_post += std::to_string(is_done);
//    string_to_post += std::to_string(task.is_done());
    string_to_post += R"(})";        //=>> create-ul la o lista
    postData.append(string_to_post);
    this->reply_tasks = accessManager->put(request, postData);
    QObject::connect(reply_tasks, &QNetworkReply::finished, [&](){
        if(reply_tasks->error() == QNetworkReply::NoError){
            auto responseData = reply_tasks->readAll();
//            qDebug()<<reply_tasks->readAll();
        }
        else{
            qDebug()<<"Eroare la GET REQUEST la Lists";
            qDebug()<<reply_tasks->errorString();
        }
        this->reply_tasks->deleteLater();
        this->notify_all(LOAD_F);
        this->reload_data();
    });
}

void RepositoryApp::delete_task(int id_task) {
    std::string url = getenv("host_name");
    url += ":";
    url += getenv("port");
    url += "/api/";
    url += "task/";
    url += std::to_string(id_task);
    QUrl qUrl = QUrl(QString::fromStdString(url));
    QNetworkRequest request(qUrl);
    request.setRawHeader("Content-Type", "application/json");
    QByteArray auth_token;
    auth_token.append("Token ");
    auth_token.append(QString::fromStdString(this->access_token).toUtf8());
    request.setRawHeader("Authorization", auth_token);
    this->reply_tasks = accessManager->deleteResource(request);
    QObject::connect(reply_tasks, &QNetworkReply::finished, [&](){
        if(reply_tasks->error() == QNetworkReply::NoError){
            auto responseData = reply_tasks->readAll();
//            qDebug()<<reply_tasks->readAll();
        }
        else{
            qDebug()<<"Eroare la GET REQUEST la Lists";
            qDebug()<<reply_tasks->errorString();
        }
        this->notify_all(LOAD_F);
        this->reply_tasks->deleteLater();
        this->reload_data();
    });
}

void RepositoryApp::add_new_list(const string &listName) {
    std::string url = getenv("host_name");
    url += ":";
    url += getenv("port");
    url += "/api/";
    url += "lists/";
    QUrl qUrl = QUrl(QString::fromStdString(url));
    QNetworkRequest request(qUrl);
    request.setRawHeader("Content-Type", "application/json");
    QByteArray auth_token;
    auth_token.append("Token ");
    auth_token.append(QString::fromStdString(this->access_token).toUtf8());
    request.setRawHeader("Authorization", auth_token);
    QByteArray postData;
    string string_to_post = R"({"listName": ")";
    string_to_post += listName;
    string_to_post += R"("})";        //=>> create-ul la o lista
    postData.append(string_to_post);
    this->reply_lists = accessManager->post(request, postData);
    QObject::connect(reply_lists, &QNetworkReply::finished, [&](){
//        qDebug()<<this->replylists;
        if(reply_lists->error() == QNetworkReply::NoError){
            auto responseData = reply_lists->readAll();
            qDebug()<<responseData;
        }
        else{
            qDebug()<<"Eroare la GET REQUEST la Lists";
        }
        this->reply_lists->deleteLater();
        this->reload_data();
    });
}

void RepositoryApp::delete_list(int id_l) {
    std::string url = getenv("host_name");
    url += ":";
    url += getenv("port");
    url += "/api/";
    url += "list/";
    url += std::to_string(id_l);
    QUrl qUrl = QUrl(QString::fromStdString(url));
    QNetworkRequest request(qUrl);
    request.setRawHeader("Content-Type", "application/json");
    QByteArray auth_token;
    auth_token.append("Token ");
    auth_token.append(QString::fromStdString(this->access_token).toUtf8());
    request.setRawHeader("Authorization", auth_token);
    this->reply_lists = accessManager->deleteResource(request);
    QObject::connect(reply_lists, &QNetworkReply::finished, [&](){
        if(reply_lists->error() == QNetworkReply::NoError){
            auto responseData = reply_lists->readAll();
//            qDebug()<<reply_lists->readAll();
        }
        else{
            qDebug()<<"Eroare la GET REQUEST la Lists";
            qDebug()<<reply_lists->errorString();
        }
        this->reply_lists->deleteLater();
        this->notify_all(LOAD_F);
        this->reload_data();
    });
}

void RepositoryApp::modify_list(int id_l, const string &newName) {
    std::string url = getenv("host_name");
    url += ":";
    url += getenv("port");
    url += "/api/";
    url += "list/";
    url += std::to_string(id_l);
    QUrl qUrl = QUrl(QString::fromStdString(url));
    QNetworkRequest request(qUrl);
    request.setRawHeader("Content-Type", "application/json");
    QByteArray auth_token;
    auth_token.append("Token ");
    auth_token.append(QString::fromStdString(this->access_token).toUtf8());
    request.setRawHeader("Authorization", auth_token);
    QByteArray postData;
    string string_to_post = R"({"listName": ")";
    string_to_post += newName;
    string_to_post += R"("})";
    postData.append(string_to_post);
    this->reply_lists = accessManager->put(request, postData);
    QObject::connect(reply_lists, &QNetworkReply::finished, [&](){
        if(reply_lists->error() == QNetworkReply::NoError){
            auto responseData = reply_lists->readAll();
//            qDebug()<<responseData;
        }
        else{
            qDebug()<<reply_lists->errorString();
            qDebug()<<"Eroare la GET REQUEST la Lists";
        }
        this->reply_lists->deleteLater();
        this->reload_data();
    });
}










