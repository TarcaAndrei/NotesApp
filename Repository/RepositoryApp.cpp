//
// Created by Andrei on 02.09.2023.
//

#include "RepositoryApp.h"

void RepositoryApp::set_token(const string &token) {
    this->access_token = token;
}

vector<Task> RepositoryApp::get_tasks_from_list(const string &basicString) {
    return vector<Task>();
}

vector<string> RepositoryApp::get_all_lists() {
    return vector<string>();
}

void RepositoryApp::add_Task(const string &basicString, Task task) {

}
