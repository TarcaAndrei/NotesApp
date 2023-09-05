//
// Created by Andrei on 26.08.2023.
//

#include "Task.h"

Task::Task(int id_t, const string &name_t, const string &details_t, const QDateTime &time_due_t,
           const string &priority_t,
           bool done_t, const QDateTime &last_updated_t) {
    this->id = id_t;
    this->name = name_t;
    this->details = details_t;
    this->time_due = time_due_t;
    this->last_updated = last_updated_t;
    this->priority = priority_t;
    this->done = done_t;
}

int Task::get_id() const {
    return this->id;
}

string Task::get_name()const {
    return this->name;
}

string Task::get_details()const {
    return this->details;
}

QDateTime Task::get_time_due() const{
    return this->time_due;
}

QDateTime Task::get_last_updated() const{
    return this->last_updated;
}

string Task::get_priority()const {
    return this->priority;
}

void Task::set_id(int id_n) {
    this->id = id_n;
}

void Task::set_name(const string &name_n) {
    this->name = name_n;
}

void Task::set_details(const string &details_n) {
    this->details = details_n;
}

void Task::set_time_due(const QDateTime &time_due_n) {
    this->time_due = time_due_n;
}

void Task::set_last_updated(const QDateTime &last_updated_n) {
    this->last_updated = last_updated_n;
}

bool Task::is_done() const {
    return this->done;
}

void Task::set_is_done(bool done_t) {
    this->done = done_t;
}
