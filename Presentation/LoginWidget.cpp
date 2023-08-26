//
// Created by Andrei on 26.08.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LoginWidget.h" resolved

#include "LoginWidget.h"
#include "ui_LoginWidget.h"


LoginWidget::LoginWidget(LoginService& loginService1, QWidget *parent) :
        QWidget(parent), ui(new Ui::LoginWidget), loginService(loginService1) {
    ui->setupUi(this);
    this->load_widget();
    this->connections();
}

LoginWidget::~LoginWidget() {
    delete ui;
}

void LoginWidget::load_widget() {
    QPalette pal=palette();   //get button palette
    pal.setBrush(QPalette::Button,Qt::green);  //makes my button black
    pal.setBrush(QPalette::ButtonText, Qt::white);
    ui->butonlogin->setPalette(pal);
    this->ui->password_txt->clear();
    this->ui->user_txt->clear();
    this->ui->password_txt->setPlaceholderText("PASSWORD");
    this->ui->user_txt->setPlaceholderText("USERNAME");
    this->ui->keep_logged_check->setChecked(true);
    this->ui->password_txt->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    auto list_auth = this->loginService.get_auth_credentials();
    if(list_auth.size() == 2){
        this->ui->user_txt->setText(QString::fromStdString(list_auth[0]));
        this->ui->password_txt->setText(QString::fromStdString(list_auth[1]));
    }
}

void LoginWidget::connections() {
    QObject::connect(ui->butonlogin, &QPushButton::clicked, [&](){
        auto username_txt = this->ui->user_txt->text().toStdString();
        auto password_txt_txt = this->ui->password_txt->text().toStdString();
        auto save_auth = false;
        if(this->ui->keep_logged_check->isChecked()){
            save_auth = true;
        }
        this->loginService.set_auth_credentials(username_txt, password_txt_txt, save_auth);
    });
}
