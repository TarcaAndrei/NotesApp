//
// Created by Andrei on 27.08.2023.
//

#include "MySecondModel.h"

MySecondModel::MySecondModel(ServiceApp &serviceApp1) : serviceApp(serviceApp1) {
    this->list_id = -1;
}

int MySecondModel::rowCount(const QModelIndex &parent) const {
    if(this->list_id == -1){
        qDebug()<<"ceva";
        return 0;
    }
    qDebug()<<"altceva";
    return this->serviceApp.get_tasks_from_list(this->list_id).size();
}

QVariant MySecondModel::data(const QModelIndex &index, int role) const {
    if(this->list_id ==-1){
        return 0;
    }
    if(role == Qt::DisplayRole){
        auto list = this->serviceApp.get_tasks_from_list(this->list_id)[index.row()];
        return QString::fromStdString(list.get_name());
    }
    if(role == Qt::UserRole){
        auto list = this->serviceApp.get_tasks_from_list(this->list_id)[index.row()];
        return list.get_id();
    }
    return {};
}

void MySecondModel::change() {
    emit layoutChanged();
}

void MySecondModel::set_list_id(int list_id_l) {
    this->list_id = list_id_l;
    this->change();
}
