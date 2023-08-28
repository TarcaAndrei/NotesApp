//
// Created by Andrei on 27.08.2023.
//

#ifndef APP1_SERVICEAPP_H
#define APP1_SERVICEAPP_H


#include "../Repository/RepositoryApp.h"

class ServiceApp {
private:
    RepositoryApp& repositoryApp;
    int generate_id(const string& table_name);
public:
    explicit ServiceApp(RepositoryApp &repositoryApp);
    vector<string> get_all_lists();
    vector<Task> get_tasks_from_list(const string& list_name);
    void add_new_task(const string& list_name, const string &name_t, const string &details_t, const QDateTime& time_due_t, const string &priority_t);
    void check_if_there_is_a_task_due();
    ServiceApp()=default;
    ~ServiceApp()=default;
};


#endif //APP1_SERVICEAPP_H
