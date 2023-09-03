//
// Created by Andrei on 26.08.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LoginWidget.h" resolved

#include "RegisterWidget.h"
#include "ui_RegisterWidget.h"


RegisterWidget::RegisterWidget(ServiceAuth& serviceAuth1, QWidget *parent) :
        QWidget(parent), ui(new Ui::RegisterWidget), serviceAuth(serviceAuth1) {
    ui->setupUi(this);
    this->serviceAuth.add_follower(this);
    this->load_widget();
    this->connections();
}

RegisterWidget::~RegisterWidget() {
    delete ui;
}

void RegisterWidget::load_widget() {
    QPalette pal=palette();   //get button palette
    pal.setBrush(QPalette::Button,Qt::red);  //makes my button black
    pal.setBrush(QPalette::ButtonText, Qt::white);
    ui->registerButton->setPalette(pal);
    this->ui->password_txt->clear();
    this->ui->user_txt->clear();
    this->ui->password_txt->setPlaceholderText("PASSWORD");
    this->ui->user_txt->setPlaceholderText("USERNAME");
    this->ui->password2_txt->setPlaceholderText("RETYPE THE PASSWORD");
    this->ui->emal_txt->setPlaceholderText("EMAIL");
//    this->ui->keep_logged_check->setChecked(true);
    this->ui->password_txt->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    this->ui->password2_txt->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    ui->groupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void RegisterWidget::connections() {
    QObject::connect(ui->registerButton, &QPushButton::clicked, [&](){
        auto username_txt = this->ui->user_txt->text().toStdString();
        auto password_txt_txt = this->ui->password_txt->text().toStdString();
        auto email_txt = this->ui->emal_txt->text().toStdString();
        auto password_2 = this->ui->password2_txt->text().toStdString();
        if(password_txt_txt != password_2){
            this->ui->lbl_eroare->setText("Passwords don't match!");
            return;
        }
//        this->serviceAuth.set_auth_credentials(username_txt, password_txt_txt, email_txt);
        this->serviceAuth.register_to_api(username_txt, password_txt_txt, email_txt);
    });
}


void RegisterWidget::update(const string &option, const string &option2) {
    if(option == REGISTER_SUCC){
        this->notify_all(option);
    }
    else if(option == REGISTER_N_SUCC){
        this->ui->lbl_eroare->setText(QString::fromStdString(option2));
    }
}

