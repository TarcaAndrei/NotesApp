//
// Created by Andrei on 08.09.2023.
//

#ifndef APP1_LISTOBJECT_H
#define APP1_LISTOBJECT_H

#include <QPushButton>
#include <QWidget>
#include <string>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class ListObject; }
QT_END_NAMESPACE

class ListObject : public QWidget {
Q_OBJECT

public:
    explicit ListObject(QWidget *parent = nullptr);
    QPushButton* get_del_btn();
    void set_id(int id, const std::string& name);
    int get_id();
    std::string get_name();
    QPushButton* get_rename_btn();
    QLineEdit* get_line_edit();
    ~ListObject() override;
    void refresh();
private:
    int id_lista;
    std::string list_name;
    Ui::ListObject *ui;
};


#endif //APP1_LISTOBJECT_H
