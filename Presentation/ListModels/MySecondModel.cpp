//
// Created by Andrei on 27.08.2023.
//

#include "MySecondModel.h"

MySecondModel::MySecondModel(ServiceApp &serviceApp1) : serviceApp(serviceApp1) {

}

int MySecondModel::rowCount(const QModelIndex &parent) const {
    if(this->list_name.empty()){
        return 0;
    }
    return this->serviceApp.get_tasks_from_list(this->list_name).size();
}

QVariant MySecondModel::data(const QModelIndex &index, int role) const {
    if(this->list_name.empty()){
        return 0;
    }
    if(role == Qt::DisplayRole){
        auto list = this->serviceApp.get_tasks_from_list(this->list_name)[index.row()];
        return QString::fromStdString(list.get_name());
    }
    if(role == Qt::UserRole){
        auto list = this->serviceApp.get_tasks_from_list(this->list_name)[index.row()];
        return list.get_id();
    }
    return {};
}

void MySecondModel::change() {
    emit layoutChanged();
}

void MySecondModel::set_list_name(const string &list_name_r) {
    this->list_name = list_name_r;
    this->change();
}
