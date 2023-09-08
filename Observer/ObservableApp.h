//
// Created by Andrei on 05.09.2023.
//

#ifndef APP1_OBSERVABLEAPP_H
#define APP1_OBSERVABLEAPP_H


#include <vector>
#include <algorithm>
#include "ObserverApp.h"
#include "../Domain/Task.h"

class ObservableApp {

private:
    std::vector<ObserverApp*> followers;
public:
    void add_follower(ObserverApp* observer);
    void remove_follower(ObserverApp* observer);
    void notify_all(const std::string& option="", const std::string& option2="", const Task& task={});
};


#endif //APP1_OBSERVABLEAPP_H
