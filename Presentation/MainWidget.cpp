//
// Created by Andrei on 26.08.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWidget.h" resolved

#include "MainWidget.h"
#include "ui_MainWidget.h"


MainWidget::MainWidget(ServiceApp &serviceApp, QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWidget), serviceApp(serviceApp) {
    ui->setupUi(this);
    this->load_widget();
}

MainWidget::~MainWidget() {
    delete ui;
}

void MainWidget::load_widget() {
    this->load_lists();
}

void MainWidget::load_lists() {
    this->myFirstModel = new MyFirstModel(this->serviceApp);
    this->ui->listView->setModel(myFirstModel);
    this->ui->listView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->mySecondModel = new MySecondModel(this->serviceApp);
    this->ui->listView_2->setModel(mySecondModel);
    this->ui->listView_2->setSelectionMode(QAbstractItemView::SingleSelection);
    QObject::connect(this->ui->listView->selectionModel(), &QItemSelectionModel::selectionChanged, [&](){
        if(this->ui->listView->selectionModel()->selectedIndexes().isEmpty()){
            this->mySecondModel->set_list_name();
            this->ui->dateDueLineEdit->clear();
            this->ui->iDLineEdit->clear();
            this->ui->nameLineEdit->clear();
            this->ui->detailsLineEdit->clear();
            this->ui->priorityLineEdit->clear();
            return;
        }
        auto selected = this->ui->listView->selectionModel()->selectedIndexes()[0];
        auto name_table = selected.data(Qt::UserRole).toString().toStdString();
        this->mySecondModel->set_list_name(name_table);
        return;
    });
    QObject::connect(this->ui->listView_2->selectionModel(), &QItemSelectionModel::selectionChanged, [&](){
        if(this->ui->listView_2->selectionModel()->selectedIndexes().isEmpty()){
            this->ui->dateDueLineEdit->clear();
            this->ui->iDLineEdit->clear();
            this->ui->nameLineEdit->clear();
            this->ui->detailsLineEdit->clear();
            this->ui->priorityLineEdit->clear();
            return;
        }
        auto selected = this->ui->listView_2->selectionModel()->selectedIndexes()[0];
        auto name_task = selected.data(Qt::DisplayRole).toString();
        auto id_task = selected.data(Qt::UserRole).toString();
        this->ui->nameLineEdit->setText(name_task);
        this->ui->iDLineEdit->setText(id_task);
    });
}
