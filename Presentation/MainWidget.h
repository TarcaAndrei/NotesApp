//
// Created by Andrei on 26.08.2023.
//

#ifndef APP1_MAINWIDGET_H
#define APP1_MAINWIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget {
Q_OBJECT

private:
    Ui::MainWidget *ui;

public:
    explicit MainWidget(QWidget *parent = nullptr);

    ~MainWidget() override;

};


#endif //APP1_MAINWIDGET_H
