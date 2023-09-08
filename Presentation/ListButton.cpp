//
// Created by Andrei on 08.09.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ListButton.h" resolved

#include "ListButton.h"
#include "ui_ListButton.h"


ListButton::ListButton(int listId, const std::string& listName, QWidget *parent) :
        QWidget(parent), ui(new Ui::ListButton), list_name(listName), list_id(listId) {
    ui->setupUi(this);
    this->load_connections();
    this->ui->mainButton->setText(QString::fromStdString(listName));
}

ListButton::~ListButton() {
    delete ui;
}

void ListButton::set_list(int id_list, const std::string &list_namee) {
    this->list_id = id_list;
    this->list_name = list_namee;
}

void ListButton::load_connections() {
    this->ui->mainButton->setAutoExclusive(true);
    this->ui->mainButton->setParent(this->parentWidget());
    this->ui->deleteButton->setVisible(false);
    this->ui->renameButton->setVisible(false);
    this->ui->lineEdit->setVisible(false);
    this->ui->mainButton->setCheckable(true);
    this->ui->deleteButton->setIcon(QIcon(":/Icons/trash.png"));
    this->ui->renameButton->setIcon(QIcon(":/Icons/edit.png"));
    QObject::connect(this->ui->mainButton, &QPushButton::toggled, [&](bool checked){
        if(checked) {
            this->ui->deleteButton->setVisible(true);
            this->ui->renameButton->setVisible(true);
        }
        else{
            this->ui->deleteButton->setVisible(false);
            this->ui->renameButton->setVisible(false);
            this->ui->lineEdit->setVisible(false);
        }
//        this->ui->mainButton->setChecked(true);
    });
//    QObject::connect(this->ui->mainButton, &QPushButton::released, [&](){
//        this->ui->deleteButton->setVisible(false);
//        this->ui->renameButton->setVisible(false);
//        this->ui->lineEdit->setVisible(false);
//    });
    QObject::connect(this->ui->deleteButton, &QPushButton::clicked, [&](){
        //sterg lista
    });
    QObject::connect(this->ui->renameButton, &QPushButton::clicked, [&](){
        this->ui->mainButton->setVisible(false);
        this->ui->lineEdit->setVisible(true);
        this->ui->renameButton->setVisible(false);
    });
    QObject::connect(this->ui->lineEdit, &QLineEdit::editingFinished, [&](){
        //redenumesc butonul
        auto text = this->ui->lineEdit->text();
        this->ui->mainButton->setText(text);
        this->list_name = text.toStdString();
        this->ui->lineEdit->setVisible(false);
        this->ui->mainButton->setVisible(true);
        this->ui->renameButton->setVisible(true);
        this->ui->deleteButton->setVisible(true);
    });
}

int ListButton::get_list_id() {
    return this->list_id;
}
