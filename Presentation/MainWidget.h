//
// Created by Andrei on 26.08.2023.
//

#ifndef APP1_MAINWIDGET_H
#define APP1_MAINWIDGET_H

#include <QWidget>
#include "../Service/ServiceApp.h"
#include "ListModels/MySecondModel.h"
#include "ListModels/MyFirstModel.h"
#include "../Observer/Observer.h"
#include "AddTaskWidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget, Observer {
Q_OBJECT

private:
    AddTaskWidget* addTaskWidget;
    Ui::MainWidget *ui;
    ServiceApp& serviceApp;
    MyFirstModel* myFirstModel;
    MySecondModel* mySecondModel;
    QTimer* timer;
    void load_widget();
    void load_lists();
    void update_lists();
    void check_tasks_due();
public:
    explicit MainWidget(ServiceApp &serviceApp, AddTaskWidget *addTaskWidget, QWidget *parent= nullptr);
    void run_app();
    void finised_task() override;
    ~MainWidget() override;

};


#endif //APP1_MAINWIDGET_H
