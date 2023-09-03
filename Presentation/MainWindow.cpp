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
    this->load_login_widget();
}

void MainWindow::update(const string &option, const string &option2) {
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

//void MainWindow::finished_login() {
//    QMainWindow::setCentralWidget(mainWidget);
//    this->mainWidget->run_app();
//    ///aici dockerul, meniu toolbar si alte chestii
//}
//
//void MainWindow::finished_register() {
//    QMainWindow::setCentralWidget(loginWidget);
//}
//
//void MainWindow::requesting_register() {
//    QMainWindow::setCentralWidget(registerWidget);
//}
