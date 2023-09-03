//
// Created by Andrei on 26.08.2023.
//

#ifndef APP1_LOGINWIDGET_H
#define APP1_LOGINWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include "../../Service/ServiceAuth.h"
#include "../../Observer/ObserverAuth.h"

#define REGISTER_REQ "REGISTER_REQUIERED"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWidget; }
QT_END_NAMESPACE

class LoginWidget : public QWidget, public ObserverAuth, public ObservableAuth{
Q_OBJECT
private:
    ServiceAuth& serviceAuth;
    void load_widget();
    void connections();
    Ui::LoginWidget *ui;
public:
    explicit LoginWidget(ServiceAuth &serviceAuth1, QWidget *parent=nullptr);
    ~LoginWidget() override;
    void update(const std::string &option, const std::string &option2) override;
};


#endif //APP1_LOGINWIDGET_H
