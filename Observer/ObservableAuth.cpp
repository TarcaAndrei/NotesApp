//
// Created by Andrei on 03.09.2023.
//

#include <QDebug>
#include "ObservableAuth.h"

void ObservableAuth::add_follower(ObserverAuth *observer) {
    this->followers.push_back(observer);
}

void ObservableAuth::notify_all(const std::string& option, const std::string& option2) {
    for(auto item : this->followers){
        item->update(option, option2);
    }
}

void ObservableAuth::remove_follower(ObserverAuth *observer) {
    auto gasit = std::find_if(this->followers.begin(), this->followers.end(), [observer](ObserverAuth* ele){
        return ele == observer;});
    this->followers.erase(gasit);
}