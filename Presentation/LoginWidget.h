//
// Created by Andrei on 26.08.2023.
//

#ifndef APP1_LOGINWIDGET_H
#define APP1_LOGINWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include "../Service/LoginService.h"
#include "../Observer/Observer.h"


QT_BEGIN_NAMESPACE
namespace Ui { class LoginWidget; }
QT_END_NAMESPACE

class LoginWidget : public QWidget {
Q_OBJECT
private:
    LoginService& loginService;
    void load_widget();
    void connections();
    Ui::LoginWidget *ui;
    Observer* parent;
public:
    explicit LoginWidget(LoginService& loginService1, QWidget *parent = nullptr);
    ~LoginWidget() override;
    void setParent(Observer* parent_window);

};


#endif //APP1_LOGINWIDGET_H
