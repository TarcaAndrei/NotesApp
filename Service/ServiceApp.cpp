//
// Created by Andrei on 27.08.2023.
//

#include "ServiceApp.h"

ServiceApp::ServiceApp(RepositoryApp &repositoryApp) : repositoryApp(repositoryApp) {
    this->repositoryApp.add_follower(this);
}

void ServiceApp::add_new_task(int id_list, const string &name_t, const string &details_t, const QDateTime &time_due_t,
                              const string &priority_t, bool is_done) {
    auto id_generated = 100;
    auto task_nou = Task(id_generated, name_t, details_t, time_due_t, priority_t, is_done);
    this->repositoryApp.add_Task(id_list, task_nou);
}

//int ServiceApp::generate_id(const string &table_name) {
//    auto nr = 100;
//    auto lista_tasks = this->get_tasks_from_list(table_name);
//    for(const auto& it : lista_tasks){
//        if(it.get_id() >= nr){
//            nr = it.get_id() + 1;
//        }
//    }
//    return nr;
//}

void ServiceApp::check_if_there_is_a_task_due() {
    for(const auto&table : this->get_all_lists()){
        auto id_table = table.first;
        for(const auto&item : this->get_tasks_from_list(id_table)){
            auto date_time_due = item.get_time_due();
            auto crt_date = QDate::currentDate();
            if(date_time_due.date() == crt_date){
//                qDebug()<<"Avem ceva astazi";
                auto time_due = date_time_due.time();
                auto crt_time = QTime::currentTime();
                if(time_due.hour() == crt_time.hour()){
//                    qDebug()<<"Avem ceva ora asta";
                    if(time_due.minute() == crt_time.minute()){
//                        qDebug()<<"AVEM CEVA AMU AMU AMU AMU";
                        this->notify_all(TASK_DUE, std::to_string(item.get_id()));
                    }
                }
            }///ghici cu ce trebe sa faci aici??? OBSERVER TATI
        }
    }
}

std::vector<std::pair<int, string>> ServiceApp::get_all_lists() {
    return this->repositoryApp.get_all_lists();
}

vector<Task> ServiceApp::get_tasks_from_list(int id_list) {
    return this->repositoryApp.get_tasks_from_list(id_list);
}

void ServiceApp::update(const std::string &option, const std::string &option2, const Task &task) {
    this->notify_all(option, option2);
}

Task ServiceApp::get_task_from_id(int id_task) {
    return this->repositoryApp.get_task_from_id(id_task);
}

void ServiceApp::modify_task(int id_task, int id_list, const string &name_t, const string &details_t,
                             const QDateTime &time_due_t, const string &priority_t, bool is_done) {
    this->repositoryApp.modify_task(id_task, id_list, name_t, details_t, time_due_t, priority_t, is_done);
}

void ServiceApp::delete_task(int id_task) {
    this->repositoryApp.delete_task(id_task);
}

void ServiceApp::add_new_list(const string &listname) {
    auto lists = this->repositoryApp.get_all_lists();
    for(auto const& it : lists){
        if(it.second == listname){
            throw std::exception();
            //nu uita de try catch
        }
    }
    this->repositoryApp.add_new_list(listname);
}

void ServiceApp::modifiy_list(int id_l, const string &newname) {
    auto lists = this->repositoryApp.get_all_lists();
    for(auto const& it : lists){
        if(it.second == newname){
            if(id_l != it.first) {
                throw std::exception();
            }
            //nu uita de try catch
        }
    }
    this->repositoryApp.modify_list(id_l, newname);
}

void ServiceApp::delete_list(int id_l) {
    this->repositoryApp.delete_list(id_l);
}

void ServiceApp::check_task_due() {
    this->timer = new QTimer();
    this->timer->start();
    this->timer->setInterval(60 * 1000);
    QObject::connect(timer, &QTimer::timeout, [&](){
        qDebug()<<"verificare...";
        this->check_if_there_is_a_task_due();
    });
}
