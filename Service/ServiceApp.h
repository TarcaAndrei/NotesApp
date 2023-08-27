//
// Created by Andrei on 27.08.2023.
//

#ifndef APP1_SERVICEAPP_H
#define APP1_SERVICEAPP_H


#include "../Repository/RepositoryApp.h"

class ServiceApp {
private:
    RepositoryApp& repositoryApp;
public:
    explicit ServiceApp(RepositoryApp &repositoryApp);
    vector<string> get_all_lists();
    vector<Task> get_tasks_from_list(const string& list_name);
    ServiceApp()=default;
    ~ServiceApp()=default;
};


#endif //APP1_SERVICEAPP_H
