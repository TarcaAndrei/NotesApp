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
    this->modified_attributes[NAME_MODIF]=false;
    this->modified_attributes[DETAILS_MODIF]=false;
    this->modified_attributes[LIST_MODIF]=false;
    this->modified_attributes[DATE_TIME_MODIF]=false;
    this->modified_attributes[PRIORITY_MODIF]=false;
}

void ViewTaskWidget::load_connections() {
    this->ui->calendarWidget->setDateEditEnabled(true);
    this->ui->priorityCombo->addItem(QIcon(":/Icons/n_priority"), "None");
    this->ui->priorityCombo->addItem(QIcon(":/Icons/m_priority"), "Medium");
    this->ui->priorityCombo->addItem(QIcon(":/Icons/h_priority"), "High");
    //culori
    QObject::connect(this->ui->updateButton, &QPushButton::clicked, [&](){
        auto name_txt = this->ui->nameEdit->text().toStdString();
        auto details_txt = this->ui->detailsEdit->toPlainText().toStdString();
        QDateTime dateTime;
        auto time_due_txt = this->ui->timeEdit->time();
        auto date_due_txt = this->ui->calendarWidget->selectedDate();
        dateTime.setTime(time_due_txt);
        dateTime.setDate(date_due_txt);
        auto priority_txt = this->ui->priorityCombo->currentText().toStdString();
        auto is_done = this->ui->is_done->isChecked();
        this->serviceApp.modify_task(id_task, id_list, name_txt, details_txt, dateTime, priority_txt, is_done);
        this->notify_all(V_CLOSED);
    });
    QObject::connect(this->ui->deletebutton, &QPushButton::clicked, [&](){
        //aici inca ceva daca chiar vrea;
        this->serviceApp.delete_task(id_task);
        this->notify_all(V_CLOSED);
    });
    QObject::connect(this->ui->toolButton, &QToolButton::clicked, [&](){
        if(this->ui->updateButton->isVisible()){
            //inseamna ca s-o modificat date -> un promt ceva
        }
        this->notify_all(V_CLOSED);
    });
    this->ui->updateButton->setVisible(false);
    this->editing_connections();
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
    this->ui->listCombo->clear();
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
    this->ui->is_done->setChecked(task.is_done());
    this->ui->updateButton->setVisible(false);
}

void ViewTaskWidget::editing_connections() {
    QObject::connect(this->ui->nameEdit, &QLineEdit::textEdited, [&](){
        this->ui->updateButton->setVisible(true);
        this->modified_attributes[NAME_MODIF]=true;
    });
    QObject::connect(this->ui->detailsEdit, &QTextEdit::textChanged, [&](){
        this->ui->updateButton->setVisible(true);
        this->modified_attributes[DETAILS_MODIF]=true;
    });
    QObject::connect(this->ui->listCombo, &QComboBox::currentTextChanged, [&](){
        this->ui->updateButton->setVisible(true);
        this->modified_attributes[LIST_MODIF]=true;
    });
    QObject::connect(this->ui->timeEdit, &QTimeEdit::timeChanged, [&](){
        this->ui->updateButton->setVisible(true);
        this->modified_attributes[DATE_TIME_MODIF]=true;
    });
    QObject::connect(this->ui->priorityCombo, &QComboBox::currentTextChanged, [&](){
        this->ui->updateButton->setVisible(true);
        this->modified_attributes[PRIORITY_MODIF]=true;
    });
    QObject::connect(this->ui->calendarWidget, &QCalendarWidget::clicked, [&](){
        this->ui->updateButton->setVisible(true);
        this->modified_attributes[DATE_TIME_MODIF]=true;
    });

}
