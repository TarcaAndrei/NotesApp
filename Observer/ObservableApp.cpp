//
// Created by Andrei on 05.09.2023.
//

#include "ObservableApp.h"

void ObservableApp::add_follower(ObserverApp *observer) {
    this->followers.push_back(observer);
}

void ObservableApp::notify_all(const std::string& option, const std::string& option2) {
    for(auto item : this->followers){
        item->update(option, option2);
    }
}

void ObservableApp::remove_follower(ObserverApp *observer) {
    auto gasit = std::find_if(this->followers.begin(), this->followers.end(), [observer](ObserverApp* ele){
        return ele == observer;});
    this->followers.erase(gasit);
}