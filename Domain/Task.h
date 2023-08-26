//
// Created by Andrei on 26.08.2023.
//

#ifndef APP1_TASK_H
#define APP1_TASK_H
#include <string>
#include <QDate>
#include <QDateTime>
using std::string;

class Task {
private:
    int id;
    string name;
    string details;
    QDateTime time_due;
    QDateTime last_updated;
    string priority;
public:
    Task(int id_t, const string& name_t, const string& details_t, const QDateTime& time_due_t, const QDateTime& last_updated_t, const string& priority_t);
    int get_id() const;
    string get_name()const;
    string get_details()const;
    QDateTime get_time_due()const;
    QDateTime get_last_updated()const;
    string get_priority()const;
    Task()=default;
    ~Task()=default;
    void set_id(int id_n);
    void set_name(const string& name_n);
    void set_details(const string& details_n);
    void set_time_due(const QDateTime& time_due_n);
    void set_last_updated(const QDateTime& last_updated_n=QDateTime::currentDateTime());
};


#endif //APP1_TASK_H
