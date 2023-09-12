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
#include "ListObject.h"
#include <QSystemTrayIcon>
#include <QLineEdit>
#include <QScrollArea>
#include <QMenu>
#include <QButtonGroup>
#include <QTimer>
#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget, public ObserverApp, public ObservableApp {
Q_OBJECT

private:
    int nr_lists_before;
    std::vector<ListObject*> lista_butoane;
    QButtonGroup* buttonGroup;
    AddTaskWidget* addTaskWidget;
    ViewTaskWidget* viewTaskWidget;
    Ui::MainWidget *ui;
    ServiceApp& serviceApp;
    MyFirstModel* myFirstModel;
    MySecondModel* mySecondModel;
    QTimer* timer;
    QTimer* timer2;
    void load_widget();
    void load_lists();
    void update_lists();
    void check_tasks_due();
    void update_buttons_list();
    void close_edit_buttons();
public:
//    void test_notificare();
    explicit MainWidget(ServiceApp &serviceApp, AddTaskWidget *addTaskWidget,
                        ViewTaskWidget *viewTaskWidget, QWidget *parent= nullptr);
    void update(const std::string &option, const std::string &option2, const Task &task) override;
    void run_app();
    ~MainWidget() override;

};


#endif //APP1_MAINWIDGET_H
