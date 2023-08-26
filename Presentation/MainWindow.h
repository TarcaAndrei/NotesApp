//
// Created by Andrei on 26.08.2023.
//

#ifndef APP1_MAINWINDOW_H
#define APP1_MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

private:
    Ui::MainWindow *ui;

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

};


#endif //APP1_MAINWINDOW_H
