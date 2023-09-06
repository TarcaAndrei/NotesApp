//
// Created by Andrei on 06.09.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ViewTaskWidget.h" resolved

#include "ViewTaskWidget.h"
#include "ui_ViewTaskWidget.h"


ViewTaskWidget::ViewTaskWidget(ServiceApp &serviceApp, QWidget *parent) :
        QWidget(parent), ui(new Ui::ViewTaskWidget), serviceApp(serviceApp) {
    ui->setupUi(this);
    this->load_connections();
}

ViewTaskWidget::~ViewTaskWidget() {
    delete ui;
}

void ViewTaskWidget::set_ids(int id_task_t, int id_list_t) {
    this->id_task = id_task_t;
    this->id_list = id_list_t;
    this->load_data_for_task();
}

void ViewTaskWidget::load_connections() {
    this->ui->calendarWidget->setDateEditEnabled(true);
    this->ui->priorityCombo->addItem(QIcon(":/Icons/n_priority"), "None");
    this->ui->priorityCombo->addItem(QIcon(":/Icons/m_priority"), "Medium");
    this->ui->priorityCombo->addItem(QIcon(":/Icons/h_priority"), "High");
    //culori
    QObject::connect(this->ui->updateButton, &QPushButton::clicked, [&](){});
    QObject::connect(this->ui->deletebutton, &QPushButton::clicked, [&](){});
    QObject::connect(this->ui->toolButton, &QToolButton::clicked, [&](){
        this->notify_all(V_CLOSED);
    });

}

void ViewTaskWidget::refresh_form() {
    this->ui->timeEdit->clear();
    this->ui->calendarWidget->setSelectedDate(QDate::currentDate());
    this->ui->timeEdit->setTime(QTime::currentTime());
    this->ui->nameEdit->clear();
    this->ui->detailsEdit->clear();
}

void ViewTaskWidget::load_data_for_task() {
    auto lista_liste = this->serviceApp.get_all_lists();
    for(const auto& it : lista_liste){
        this->ui->listCombo->addItem(QString::fromStdString(it.second), it.first);
    }
    this->ui->listCombo->setCurrentIndex(0);
    auto task = this->serviceApp.get_task_from_id(id_task);
    this->ui->nameEdit->setText(QString::fromStdString(task.get_name()));
    this->ui->detailsEdit->setText(QString::fromStdString(task.get_details()));
    this->ui->timeEdit->setTime(task.get_time_due().time());
    this->ui->calendarWidget->setSelectedDate(task.get_time_due().date());
    this->ui->listCombo->setCurrentIndex(this->ui->listCombo->findData(id_list));
    this->ui->priorityCombo->setCurrentIndex(this->ui->priorityCombo->findText(QString::fromStdString(task.get_priority())));

}
