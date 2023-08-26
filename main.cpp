#include <QApplication>
#include <QSqlDatabase>
#include <cstdlib>
#include <QSql>
#include <QPushButton>
#include "Repository/RepositoryApp.h"
#include "Service/LoginService.h"
#include "Presentation/LoginWidget.h"
#include "Presentation/MainWindow.h"
#include <QDateTime>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    RepositoryApp repositoryApp = RepositoryApp();
    LoginService loginService = LoginService("../Data/authentification", repositoryApp);
    LoginWidget* loginWidget = new LoginWidget(loginService);
    MainWidget* mainWidget = new MainWidget();
    MainWindow* mainWindow = new MainWindow(loginWidget, mainWidget);
    mainWindow->show();
//    qDebug()<<QDateTime::currentDateTime().time().toString(); si a
///    qDebug()<<QDateTime::fromString("2023-08-26T14:39:18", Qt::ISODate); asta ii ala bun
//    qDebug()<<QDateTime::fromString("", Qt::DateFormat::ISODate)
///    qDebug()<<QDateTime::currentDateTime().toString(Qt::ISODate);asta iara ii bun
//    qDebug()<<QDateTime::currentDateTime().date().toString(Qt::DateFormat::ISODate);
//    qDebug()<<QDateTime::currentDateTime().date().toString(Qt::DateFormat::TextDate);
//    qDebug()<<QDateTime::currentDateTime().date().toString(Qt::DateFormat::ISODateWithMs);
//    qDebug()<<QDateTime::currentDateTime().date().toString(Qt::DateFormat::RFC2822Date);

    return QApplication::exec();
}
