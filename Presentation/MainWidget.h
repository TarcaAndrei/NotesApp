//
// Created by Andrei on 26.08.2023.
//

#ifndef APP1_MAINWIDGET_H
#define APP1_MAINWIDGET_H

#include <QWidget>
#include "../Service/ServiceApp.h"
#include "ListModels/MySecondModel.h"
#include "ListModels/MyFirstModel.h"
#include "TasksWidgets/AddTaskWidget.h"
#include "TasksWidgets/ViewTaskWidget.h"
#include "ListButton.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget, public ObserverApp, public ObservableApp {
Q_OBJECT

private:
    std::vector<ListButton*> lista_butoane;
    AddTaskWidget* addTaskWidget;
    ViewTaskWidget* viewTaskWidget;
    Ui::MainWidget *ui;
    ServiceApp& serviceApp;
    MyFirstModel* myFirstModel;
    MySecondModel* mySecondModel;
    QTimer* timer;
    void load_widget();
    void load_lists();
    void update_lists();
    void check_tasks_due();
    void create_list();
public:
//    void test_notificare();
    explicit MainWidget(ServiceApp &serviceApp, AddTaskWidget *addTaskWidget,
                        ViewTaskWidget *viewTaskWidget, QWidget *parent= nullptr);
    void update(const std::string &option, const std::string &option2, const Task &task) override;
    void run_app();
    ~MainWidget() override;

};


#endif //APP1_MAINWIDGET_H
