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
