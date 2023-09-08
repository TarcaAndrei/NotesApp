//
// Created by Andrei on 26.08.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(LoginWidget *loginWidget1, RegisterWidget *registerWidget1, MainWidget *mainWidget1,
                       QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->loginWidget = loginWidget1;
    this->loginWidget->add_follower(this);
    this->registerWidget = registerWidget1;
    this->registerWidget->add_follower(this);
    this->mainWidget = mainWidget1;
    this->mainWidget->add_follower(this);
    this->load_window();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::load_login_widget() {
    QMainWindow::setCentralWidget(this->loginWidget);
//    this->loginWidget->setParent(nullptr);
}

void MainWindow::load_window() {
    this->setWindowIcon(QIcon(":/Icons/todo_logo"));
    this->load_login_widget();
    this->load_notifications();
}

void MainWindow::update(const string &option, const string &option2, const Task& task) {
    if(option == TASK_DUE){
        this->sent_notification(task);
    }
}

void MainWindow::load_notifications() {
    qSystemTrayIcon = new QSystemTrayIcon(this);
    qSystemTrayIcon->setIcon(QIcon(":/Icons/todo_logo.png")); // Setarea iconiței
    qSystemTrayIcon->show();
    QMenu *trayMenu = new QMenu();
    QAction *showAction = new QAction(QIcon(":/Icons/maximize.png"),"Show", this);
    QAction *exitAction = new QAction(QIcon(":/Icons/exit.png"), "Exit", this);
    connect(qSystemTrayIcon, &QSystemTrayIcon::activated, this, &MainWindow::qsystemactivated);
    connect(showAction, &QAction::triggered, this, &QWidget::showNormal);
    connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    trayMenu->addAction(showAction);
    trayMenu->addAction(exitAction);

    qSystemTrayIcon->setContextMenu(trayMenu);
}

void MainWindow::qsystemactivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::DoubleClick) {
        this->showNormal();
    }
}

void MainWindow::sent_notification(const Task &task_due) {
    auto priority = task_due.get_priority();
    QIcon iconita;
    if(priority == "None"){
        iconita = QIcon(":/Icons/n_priority.png");
    }
    else if(priority == "Medium"){
        iconita = QIcon(":/Icons/m_priority.png");
    }
    else if(priority == "High"){
        iconita = QIcon(":/Icons/h_priority.png");
    }
    this->qSystemTrayIcon->showMessage(QString::fromStdString(task_due.get_name()), QString::fromStdString(task_due.get_details()), iconita, 5000);
    QObject::connect(qSystemTrayIcon, &QSystemTrayIcon::messageClicked, [&](){
        this->showNormal();
    });
}

void MainWindow::update_auth(const string &option, const string &option2) {
    if(option == REGISTER_SUCC){
        this->registerWidget->setParent(nullptr);
        QMainWindow::setCentralWidget(this->loginWidget);
    }
    else if(option == LOGIN_SUCC){
        this->loginWidget->setParent(nullptr);
        QMainWindow::setCentralWidget(mainWidget);
        this->mainWidget->run_app();
    }
    else if(option == REGISTER_REQ){
        this->loginWidget->setParent(nullptr);
        QMainWindow::setCentralWidget(registerWidget);
    }
}
