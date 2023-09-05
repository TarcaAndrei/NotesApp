//
// Created by Andrei on 27.08.2023.
//

#include "MyFirstModel.h"

MyFirstModel::MyFirstModel(ServiceApp &serviceApp1) : serviceApp(serviceApp1) {
    this->serviceApp.add_follower(this);    //mai bine direct la celalalt
}

int MyFirstModel::rowCount(const QModelIndex &parent) const {
    return (int) this->serviceApp.get_all_lists().size();
}

QVariant MyFirstModel::data(const QModelIndex &index, int role) const {
    if(role == Qt::DisplayRole){
        std::string nume = "ceva";
        if(not this->serviceApp.get_all_lists().empty()){
            nume = this->serviceApp.get_all_lists()[index.row()].second;
        }
        return QString::fromStdString(nume);
    }
    if(role == Qt::UserRole){
        if(not this->serviceApp.get_all_lists().empty()){
            auto lista_de_liste = this->serviceApp.get_all_lists();
            auto id_list = lista_de_liste[index.row()].first;
            return id_list;
        }
        return 0;
    }
    return {};
}

void MyFirstModel::change() {
    emit layoutChanged();
}

void MyFirstModel::update(const string &option, const string &option2) {
    if(option == LOAD_F){
        this->change();
    }
}
