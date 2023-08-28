//
// Created by Andrei on 26.08.2023.
//

#ifndef APP1_MAINWIDGET_H
#define APP1_MAINWIDGET_H

#include <QWidget>
#include "../Service/ServiceApp.h"
#include "ListModels/MySecondModel.h"
#include "ListModels/MyFirstModel.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget {
Q_OBJECT

private:
    Ui::MainWidget *ui;
    ServiceApp& serviceApp;
    MyFirstModel* myFirstModel;
    MySecondModel* mySecondModel;
    void load_widget();
    void load_lists();
    void clear_form();
    void update_lists();
    void check_tasks_due();
    QDateTime add1hour();
public:
    explicit MainWidget(ServiceApp &serviceApp, QWidget *parent= nullptr);
    void run_app();
    ~MainWidget() override;

};


#endif //APP1_MAINWIDGET_H
