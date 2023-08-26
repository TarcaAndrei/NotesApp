#include <QApplication>
#include <QSqlDatabase>
#include <cstdlib>
#include <QSql>
#include <QPushButton>
#include "Repository/RepositoryApp.h"
#include "Service/LoginService.h"
#include "Presentation/LoginWidget.h"
#include <QDateTime>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
//    LoginService loginService = LoginService("../Data/authentification");
//    LoginWidget loginWidget = LoginWidget(loginService);
//    loginWidget.show();
//    qDebug()<<QDateTime::currentDateTime().time().toString();
    qDebug()<<QDateTime::fromString("2023-08-26T14:39:18", Qt::ISODate);
//    qDebug()<<QDateTime::fromString("", Qt::DateFormat::ISODate)
//    qDebug()<<QDateTime::currentDateTime().toString(Qt::ISODate);
//    qDebug()<<QDateTime::currentDateTime().date().toString(Qt::DateFormat::ISODate);
//    qDebug()<<QDateTime::currentDateTime().date().toString(Qt::DateFormat::TextDate);
//    qDebug()<<QDateTime::currentDateTime().date().toString(Qt::DateFormat::ISODateWithMs);
//    qDebug()<<QDateTime::currentDateTime().date().toString(Qt::DateFormat::RFC2822Date);

    return QApplication::exec();
}
