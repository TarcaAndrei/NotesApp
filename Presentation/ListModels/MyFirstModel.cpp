//
// Created by Andrei on 27.08.2023.
//

#include "MyFirstModel.h"

MyFirstModel::MyFirstModel(ServiceApp &serviceApp1) : serviceApp(serviceApp1) {

}

int MyFirstModel::rowCount(const QModelIndex &parent) const {
    return (int)this->serviceApp.get_all_lists().size();
}

QVariant MyFirstModel::data(const QModelIndex &index, int role) const {
    if(role == Qt::DisplayRole){
        auto list = this->serviceApp.get_all_lists()[index.row()];
        return QString::fromStdString(list);
    }
    if(role == Qt::UserRole){
        auto list = this->serviceApp.get_all_lists()[index.row()];
        return QString::fromStdString(list);
    }
    return {};
}

void MyFirstModel::change() {
    emit layoutChanged();
}
