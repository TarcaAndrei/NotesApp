//
// Created by Andrei on 26.08.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWidget.h" resolved

#include "MainWidget.h"
#include "ui_MainWidget.h"


MainWidget::MainWidget(ServiceApp &serviceApp, AddTaskWidget *addTaskWidget, QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWidget), serviceApp(serviceApp), addTaskWidget(addTaskWidget) {
    ui->setupUi(this);
    this->serviceApp.add_follower(this);
    this->load_widget();
}

MainWidget::~MainWidget() {
    delete ui;
}

void MainWidget::load_widget() {
//    this->addTaskWidget->set_parent(this);
    this->ui->gridLayout->addWidget(this->addTaskWidget);
    this->addTaskWidget->setVisible(false);
    this->load_lists();
//    this->clear_form();
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
            this->mySecondModel->set_list_id();
//            this->clear_form();
            return;
        }
        auto selected = this->ui->listView->selectionModel()->selectedIndexes()[0];
        auto id_table = selected.data(Qt::UserRole).toInt();
        this->mySecondModel->set_list_id(id_table);
        return;
    });
    QObject::connect(this->ui->listView_2->selectionModel(), &QItemSelectionModel::selectionChanged, [&](){
        if(this->ui->listView_2->selectionModel()->selectedIndexes().isEmpty()){
//            this->clear_form();
            return;
        }
        auto selected = this->ui->listView_2->selectionModel()->selectedIndexes()[0];
        auto name_task = selected.data(Qt::DisplayRole).toString();
        auto id_task = selected.data(Qt::UserRole).toString();
//        this->ui->nameLineEdit->setText(name_task);
///asta acolo sa fac ceva public s-o setez idk..
    });
//    QObject::connect(this->ui->saveTask, &QPushButton::clicked, [&](){
//        if(this->ui->listView->selectionModel()->selectedIndexes().isEmpty()){
//            qDebug()<<"Eroare";
//            return;
//        }
//        auto selected = this->ui->listView->selectionModel()->selectedIndexes()[0];
//        auto name_table = selected.data(Qt::UserRole).toString().toStdString();
//        auto name_txt = this->ui->nameLineEdit->text().toStdString();
//        auto details_txt = this->ui->detailsLineEdit->text().toStdString();
//        auto time_due_txt = this->ui->dateTimeEdit->dateTime();
//        auto priority_txt = this->ui->prioritycombo->currentText().toStdString();
//        ///aici la priority sa setez un combobox o lista dinaia cu cateva optiuni
//        this->serviceApp.add_new_task(name_table, name_txt, details_txt, time_due_txt, priority_txt, false);
//        this->update_lists();
//        this->clear_form();
//    });
    this->ui->add_new_task_button->setIcon(QIcon(":/Icons/plus.png"));
    QObject::connect(this->ui->add_new_task_button, &QPushButton::clicked, [&](){
        this->ui->add_new_task_button->setVisible(false);
        this->addTaskWidget->setVisible(true);
        this->addTaskWidget->refresh_form();
        this->test_notificare();
    });
}


void MainWidget::update_lists() {
    this->myFirstModel->change();
    this->mySecondModel->change();
}

void MainWidget::check_tasks_due() {
    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&](){
        this->serviceApp.check_if_there_is_a_task_due();
        timer->setInterval(60 * 1000);
    });
    auto crt_date_time = QDateTime::currentDateTime();
    auto time_crt = crt_date_time.time();
    time_crt.setHMS(time_crt.hour(), time_crt.minute()+1, 0, 0);

    auto time = crt_date_time.time().msecsTo(time_crt);
    timer->start(time);
}

void MainWidget::run_app() {
    this->check_tasks_due();
}


void MainWidget::test_notificare() {
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/Icons/n_priority")); // Setarea iconiței
    trayIcon->show();
    QMenu *trayMenu = new QMenu();
    QAction *showAction = new QAction("Show", this);
    QAction *exitAction = new QAction("Exit", this);

    connect(showAction, &QAction::triggered, this, &QWidget::showNormal);
    connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    trayMenu->addAction(showAction);
    trayMenu->addAction(exitAction);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->showMessage("Titlul notificării", "Acesta este conținutul notificării.", QSystemTrayIcon::Information, 5000);

}

void MainWidget::update(const string &option, const string &option2) {
    this->update_lists();
}



