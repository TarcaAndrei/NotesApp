//
// Created by Andrei on 27.08.2023.
//

#ifndef APP1_SERVICEAPP_H
#define APP1_SERVICEAPP_H


#include "../Repository/RepositoryApp.h"

class ServiceApp : public ObserverApp, public ObservableApp{
private:
    RepositoryApp& repositoryApp;
//    int generate_id(const string& table_name);
public:
    explicit ServiceApp(RepositoryApp &repositoryApp);
    std::vector<std::pair<int, string>> get_all_lists();
    vector<Task> get_tasks_from_list(int id_list);
    void add_new_task(int id_list, const string &name_t, const string &details_t, const QDateTime& time_due_t, const string &priority_t, bool is_done=false);
    void check_if_there_is_a_task_due();
    void update(const std::string &option, const std::string &option2) override;
    Task get_task_from_id(int id_task);
    ServiceApp()=default;
    ~ServiceApp()=default;
};


#endif //APP1_SERVICEAPP_H
