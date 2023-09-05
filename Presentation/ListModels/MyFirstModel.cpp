//
// Created by Andrei on 27.08.2023.
//

#include "MyFirstModel.h"

MyFirstModel::MyFirstModel(ServiceApp &serviceApp1) : serviceApp(serviceApp1) {
}

int MyFirstModel::rowCount(const QModelIndex &parent) const {
    return (int) this->serviceApp.get_all_lists().size();
}

QVariant MyFirstModel::data(const QModelIndex &index, int role) const {
    if(role == Qt::DisplayRole){
        auto nume_list = this->serviceApp.get_all_lists()[index.row()].second;
        return QString::fromStdString(nume_list);
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

