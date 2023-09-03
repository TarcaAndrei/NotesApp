//
// Created by Andrei on 03.09.2023.
//

#ifndef APP1_OBSERVABLEAUTH_H
#define APP1_OBSERVABLEAUTH_H

#include<vector>
#include<algorithm>
#include<string>
#include "ObserverAuth.h"

class ObservableAuth {
private:
    std::vector<ObserverAuth*> followers;
public:
    void add_follower(ObserverAuth* observer);
    void remove_follower(ObserverAuth* observer);
    void notify_all(const std::string& option="", const std::string& option2="");
};


#endif //APP1_OBSERVABLEAUTH_H
