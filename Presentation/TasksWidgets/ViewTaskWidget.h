//
// Created by Andrei on 06.09.2023.
//

#ifndef APP1_VIEWTASKWIDGET_H
#define APP1_VIEWTASKWIDGET_H

#include <QWidget>
#include "../../Service/ServiceApp.h"

#define V_CLOSED "View closed"


QT_BEGIN_NAMESPACE
namespace Ui { class ViewTaskWidget; }
QT_END_NAMESPACE

class ViewTaskWidget : public QWidget, public ObservableApp {
Q_OBJECT


private:
    Ui::ViewTaskWidget *ui;
    ServiceApp& serviceApp;
    int id_task;
    int id_list;
    void load_connections();
    void refresh_form();
    void load_data_for_task();
public:
    void set_ids(int id_task_t, int id_list_t);
    explicit ViewTaskWidget(ServiceApp &serviceApp, QWidget *parent= nullptr);
    ~ViewTaskWidget() override;
};


#endif //APP1_VIEWTASKWIDGET_H
