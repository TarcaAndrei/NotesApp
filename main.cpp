#include <QApplication>
#include <QSqlDatabase>
#include <cstdlib>
#include <iostream>
#include <QSql>
#include <QPushButton>
#include "Repository/RepositoryApp.h"
#include "Service/LoginService.h"
#include "Presentation/LoginWidget.h"
#include "Presentation/MainWindow.h"
#include "Service/ServiceApp.h"
#include "Presentation/AddTaskWidget.h"
#include <QDateTime>
#include <QSystemTrayIcon>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    RepositoryApp repositoryApp = RepositoryApp();
    LoginService loginService = LoginService("../Data/authentification", repositoryApp);
    ServiceApp serviceApp = ServiceApp(repositoryApp);
    LoginWidget* loginWidget = new LoginWidget(loginService);
    AddTaskWidget* addTaskWidget = new AddTaskWidget(serviceApp);
    MainWidget* mainWidget = new MainWidget(serviceApp, addTaskWidget);
    MainWindow* mainWindow = new MainWindow(loginWidget, mainWidget);
    mainWindow->show();
    return QApplication::exec();
//    auto altcv = QTime::currentTime();
//    qDebug()<<altcv;
//    altcv.setHMS(altcv.hour()+1, 0, 0, 0);
//    qDebug()<<altcv;
//    QApplication::setQuitOnLastWindowClosed(false);
//    Window window;
//    window.show();
//    return a.exec();
//    qDebug()<<QSqlDatabase::drivers();
    //    qDebug()<<QDateTime::currentDateTime().time().toString(); si a
///    qDebug()<<QDateTime::fromString("2023-08-26T14:39:18", Qt::ISODate); asta ii ala bun
//    qDebug()<<QDateTime::fromString("", Qt::DateFormat::ISODate)
///    qDebug()<<QDateTime::currentDateTime().toString(Qt::ISODate);asta iara ii bun
//    qDebug()<<QDateTime::currentDateTime().date().toString(Qt::DateFormat::ISODate);
//    qDebug()<<QDateTime::currentDateTime().date().toString(Qt::DateFormat::TextDate);
//    qDebug()<<QDateTime::currentDateTime().date().toString(Qt::DateFormat::ISODateWithMs);
//    qDebug()<<QDateTime::currentDateTime().date().toString(Qt::DateFormat::RFC2822Date);

}

