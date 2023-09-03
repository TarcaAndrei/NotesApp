//
// Created by Andrei on 26.08.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LoginWidget.h" resolved

#include "LoginWidget.h"
#include "ui_LoginWidget.h"


LoginWidget::LoginWidget(ServiceAuth &serviceAuth1,QWidget *parent) :
        QWidget(parent), ui(new Ui::LoginWidget), serviceAuth(serviceAuth1){
    ui->setupUi(this);
    this->serviceAuth.add_follower(this);
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
    QPalette pal2=palette();   //get button palette
    pal2.setBrush(QPalette::Button,Qt::red);  //makes my button black
    pal2.setBrush(QPalette::ButtonText, Qt::white);
    ui->buttonRegister->setPalette(pal2);
    this->ui->password_txt->clear();
    this->ui->user_txt->clear();
    this->ui->password_txt->setPlaceholderText("PASSWORD");
    this->ui->user_txt->setPlaceholderText("USERNAME");
    this->ui->keep_logged_check->setChecked(true);
    this->ui->password_txt->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    auto list_auth = this->serviceAuth.get_auth_credentials();
    if(list_auth.size() == 2){
        this->ui->user_txt->setText(QString::fromStdString(list_auth[0]));
        this->ui->password_txt->setText(QString::fromStdString(list_auth[1]));
    }

    ui->groupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void LoginWidget::connections() {
    QObject::connect(ui->butonlogin, &QPushButton::clicked, [&](){
        auto username_txt = this->ui->user_txt->text().toStdString();
        auto password_txt_txt = this->ui->password_txt->text().toStdString();
        auto save_auth = false;
        if(this->ui->keep_logged_check->isChecked()) {
            save_auth = true;
        }
        this->serviceAuth.set_auth_credentials(username_txt, password_txt_txt, save_auth);
        try {
            this->serviceAuth.connect_to_api();
            qDebug()<<"Trece de eroare";
//            auto db_connected = this->serviceAuth.connect_repository();
//            this->parent->finished_login();
        }
        catch (const std::domain_error&e){
            ui->lbl_eroare->setAlignment(Qt::AlignCenter);
            ui->lbl_eroare->setText(e.what());
        }
    });
    QObject::connect(ui->buttonRegister, &QPushButton::clicked, [&](){
        this->notify_all(REGISTER_REQ);
    });
}

void LoginWidget::update(const string &option, const string &option2) {
    if(option == "Logged"){
        this->notify_all(LOGIN_SUCC);
//        qDebug()<<"Logged";
    }
    else if(option == "NotLogged"){
        this->ui->lbl_eroare->setText(QString::fromStdString(option2));
    }
}

