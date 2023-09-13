//
// Created by Andrei on 30.08.2023.
//

#ifndef APP1_ADDTASKWIDGET_H
#define APP1_ADDTASKWIDGET_H

#include <QWidget>
#include "../../Service/ServiceApp.h"
#include <QMessageBox>
#define ADD_DONE "Adding new task done"


QT_BEGIN_NAMESPACE
namespace Ui { class AddTaskWidget; }
QT_END_NAMESPACE

class AddTaskWidget : public QWidget, public ObservableApp {
Q_OBJECT

private:
    Ui::AddTaskWidget *ui;
    ServiceApp& serviceApp;
    void load_connections();
    QDateTime add1hour();
public:
    void refresh_form();
    explicit AddTaskWidget(ServiceApp &serviceApp, QWidget *parent= nullptr);
    ~AddTaskWidget() override;

};


#endif //APP1_ADDTASKWIDGET_H
