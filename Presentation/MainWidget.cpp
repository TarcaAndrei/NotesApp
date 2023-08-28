//
// Created by Andrei on 26.08.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWidget.h" resolved

#include "MainWidget.h"
#include "ui_MainWidget.h"


MainWidget::MainWidget(ServiceApp &serviceApp, QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWidget), serviceApp(serviceApp) {
    ui->setupUi(this);
    this->load_widget();
}

MainWidget::~MainWidget() {
    delete ui;
}

void MainWidget::load_widget() {
    this->load_lists();
    this->clear_form();
}

void MainWidget::load_lists() {
    this->myFirstModel = new MyFirstModel(this->serviceApp);
    this->ui->listView->setModel(myFirstModel);
    this->ui->listView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->mySecondModel = new MySecondModel(this->serviceApp);
    this->ui->listView_2->setModel(mySecondModel);
    this->ui->listView_2->setSelectionMode(QAbstractItemView::SingleSelection);
    QObject::connect(this->ui->listView->selectionModel(), &QItemSelectionModel::selectionChanged, [&](){
        if(this->ui->listView->selectionModel()->selectedIndexes().isEmpty()){
            this->mySecondModel->set_list_name();
            this->clear_form();
            return;
        }
        auto selected = this->ui->listView->selectionModel()->selectedIndexes()[0];
        auto name_table = selected.data(Qt::UserRole).toString().toStdString();
        this->mySecondModel->set_list_name(name_table);
        return;
    });
    QObject::connect(this->ui->listView_2->selectionModel(), &QItemSelectionModel::selectionChanged, [&](){
        if(this->ui->listView_2->selectionModel()->selectedIndexes().isEmpty()){
            this->clear_form();
            return;
        }
        auto selected = this->ui->listView_2->selectionModel()->selectedIndexes()[0];
        auto name_task = selected.data(Qt::DisplayRole).toString();
        auto id_task = selected.data(Qt::UserRole).toString();
        this->ui->nameLineEdit->setText(name_task);
        this->ui->iDLineEdit->setText(id_task);
    });
    QObject::connect(this->ui->saveTask, &QPushButton::clicked, [&](){
        if(this->ui->listView->selectionModel()->selectedIndexes().isEmpty()){
            qDebug()<<"Eroare";
            return;
        }
        auto selected = this->ui->listView->selectionModel()->selectedIndexes()[0];
        auto name_table = selected.data(Qt::UserRole).toString().toStdString();
        auto name_txt = this->ui->nameLineEdit->text().toStdString();
        auto details_txt = this->ui->detailsLineEdit->text().toStdString();
        auto time_due_txt = this->ui->dateTimeEdit->dateTime();
        auto priority_txt = this->ui->priorityLineEdit->text().toStdString();
        ///aici la priority sa setez un combobox o lista dinaia cu cateva optiuni
        this->serviceApp.add_new_task(name_table, name_txt, details_txt, time_due_txt, priority_txt);
        this->update_lists();
        this->clear_form();
    });
    /**
//    QTimer *timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, this, [](){
//        qDebug()<<"ceva";
//    });
//    timer->start(1000);
     */
    /////AIAI E M-AM SCOS...
    ////tot la un interval de timp va verifica sau pot sa il transform..idk
}

void MainWidget::clear_form() {
    this->ui->dateTimeEdit->clear();
    this->ui->dateTimeEdit->setDateTime(this->add1hour());
    this->ui->nameLineEdit->clear();
    this->ui->detailsLineEdit->clear();
    this->ui->priorityLineEdit->clear();
}

QDateTime MainWidget::add1hour() {
    auto crt_date_time = QDateTime::currentDateTime();
    auto time_only = crt_date_time.time();
    if(time_only.hour() == 23){
        crt_date_time = crt_date_time.addDays(1);
        time_only.setHMS(0, 0, 0, 0);
    }
    else{
        time_only.setHMS(time_only.hour()+1, 0, 0, 0);
    }
    crt_date_time.setTime(time_only);
    return crt_date_time;
}

void MainWidget::update_lists() {
    this->myFirstModel->change();
    this->mySecondModel->change();
}

void MainWidget::check_tasks_due() {
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&](){
        this->serviceApp.check_if_there_is_a_task_due();
    });
    timer->start(60 * 1000);
}

void MainWidget::run_app() {
    this->check_tasks_due();
}
