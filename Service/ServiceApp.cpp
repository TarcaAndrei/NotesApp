//
// Created by Andrei on 27.08.2023.
//

#include "ServiceApp.h"

ServiceApp::ServiceApp(RepositoryApp &repositoryApp) : repositoryApp(repositoryApp) {

}

vector<string> ServiceApp::get_all_lists() {
    return repositoryApp.get_all_lists();
}

vector<Task> ServiceApp::get_tasks_from_list(const string &list_name) {
    return repositoryApp.get_tasks_from_list(list_name);
}

void ServiceApp::add_new_task(const string& list_name, const string &name_t, const string &details_t, const QDateTime &time_due_t,
                              const string &priority_t) {
    auto last_updated_t = QDateTime::currentDateTime();
    auto id_generated = this->generate_id(list_name);
    auto task_nou = Task(id_generated, name_t, details_t, time_due_t, last_updated_t, priority_t);
    this->repositoryApp.add_Task(list_name, task_nou);
}

int ServiceApp::generate_id(const string &table_name) {
    auto nr = 100;
    auto lista_tasks = this->get_tasks_from_list(table_name);
    for(const auto& it : lista_tasks){
        if(it.get_id() >= nr){
            nr = it.get_id() + 1;
        }
    }
    return nr;
}

void ServiceApp::check_if_there_is_a_task_due() {
    for(const auto&table : this->get_all_lists()){
        for(const auto&item : this->get_tasks_from_list(table)){
            auto date_time_due = item.get_time_due();
            auto crt_date = QDate::currentDate();
            if(date_time_due.date() == crt_date){
                qDebug()<<"Avem ceva astazi";
                auto time_due = date_time_due.time();
                auto crt_time = QTime::currentTime();
                if(time_due.hour() == crt_time.hour()){
                    qDebug()<<"Avem ceva ora asta";
                    if(time_due.minute() == crt_time.minute()){
                        qDebug()<<"AVEM CEVA AMU AMU AMU AMU";
                    }
                }
            }
        }
    }
}

