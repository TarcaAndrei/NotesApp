//
// Created by Andrei on 27.08.2023.
//

#ifndef APP1_MYFIRSTMODEL_H
#define APP1_MYFIRSTMODEL_H
#include <QAbstractListModel>
#include "../../Service/ServiceApp.h"


class MyFirstModel : public QAbstractListModel, public ObserverApp{
private:
    ServiceApp& serviceApp;
public:
    MyFirstModel(ServiceApp &serviceApp);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void update(const std::string &option, const std::string &option2) override;
    void change();
};


#endif //APP1_MYFIRSTMODEL_H
