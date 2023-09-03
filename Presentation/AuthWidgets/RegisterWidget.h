//
// Created by Andrei on 26.08.2023.
//

#ifndef APP1_REGISTERWIDGET_H
#define APP1_REGISTERWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include "../../Service/ServiceAuth.h"
#include "../../Observer/ObserverAuth.h"


QT_BEGIN_NAMESPACE
namespace Ui { class RegisterWidget; }
QT_END_NAMESPACE

class RegisterWidget : public QWidget, public ObserverAuth, public ObservableAuth {
Q_OBJECT
private:
    ServiceAuth& serviceAuth;
    void load_widget();
    void connections();
    Ui::RegisterWidget *ui;
    ObserverAuth* parent;
public:
    explicit RegisterWidget(ServiceAuth& serviceAuth1, QWidget *parent = nullptr);
    ~RegisterWidget() override;
    void update(const std::string &option, const std::string &option2) override;

};


#endif //APP1_REGISTERWIDGET_H
