//
// Created by Andrei on 26.08.2023.
//

#ifndef APP1_MAINWINDOW_H
#define APP1_MAINWINDOW_H

#include <QMainWindow>
#include "LoginWidget.h"
#include "../Observer/Observer.h"
#include "MainWidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public Observer{
Q_OBJECT

private:
    Ui::MainWindow *ui;
    LoginWidget* loginWidget;
    MainWidget* mainWidget;
    void load_window();
    void load_login_widget();

public:
    void finised_login() override;
    explicit MainWindow(LoginWidget* loginWidget1, MainWidget* mainWidget1 ,QWidget *parent = nullptr);
    ~MainWindow() override;

};


#endif //APP1_MAINWINDOW_H
