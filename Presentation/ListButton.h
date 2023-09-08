//
// Created by Andrei on 08.09.2023.
//

#ifndef APP1_LISTBUTTON_H
#define APP1_LISTBUTTON_H

#include <QWidget>
#include <string>
#include "../Observer/ObserverApp.h"
#include "../Observer/ObservableApp.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ListButton; }
QT_END_NAMESPACE

class ListButton : public QWidget, public ObserverApp, public ObservableApp{
Q_OBJECT

private:
    Ui::ListButton *ui;
    std::string list_name;
    int list_id;
    void load_connections();
public:
    explicit ListButton(int listId=-1, const std::string& listName="", QWidget *parent= nullptr);
    void set_list(int id_list, const std::string& list_namee);
    int get_list_id();
    void update(const std::string &option, const std::string &option2, const Task &task) override;
    ~ListButton() override;

};


#endif //APP1_LISTBUTTON_H
