//
// Created by Andrei on 26.08.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(LoginWidget* loginWidget1, MainWidget* mainWidget1, QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->loginWidget = loginWidget1;
    this->mainWidget = mainWidget1;
    this->load_window();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::load_login_widget() {
    this->loginWidget->setParent(this);
    QMainWindow::setCentralWidget(this->loginWidget);
//    this->setAutoFillBackground(true);
}

void MainWindow::load_window() {
    this->load_login_widget();
}

void MainWindow::finised_login() {
    QMainWindow::setCentralWidget(mainWidget);
    this->mainWidget->run_app();
    ///aici dockerul, meniu toolbar si alte chestii
}
