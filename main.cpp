#include <QApplication>
#include <cstdlib>
#include <iostream>
#include "Presentation/AuthWidgets/LoginWidget.h"
#include "Presentation/MainWindow.h"
#include "Service/ServiceApp.h"
#include "Presentation/TasksWidgets/AddTaskWidget.h"
#include "Service/ServiceAuth.h"
#include "Presentation/TasksWidgets/ViewTaskWidget.h"
#include <QDateTime>
#include <QSystemTrayIcon>

int main(int argc, char*argv[]){
    QApplication a(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);
    RepositoryApp repositoryApp = RepositoryApp();
    ServiceAuth serviceAuth = ServiceAuth("../Data/authentification", repositoryApp);
    ServiceApp serviceApp = ServiceApp(repositoryApp);
    LoginWidget* loginWidget = new LoginWidget(serviceAuth);
    RegisterWidget* registerWidget = new RegisterWidget(serviceAuth);
    AddTaskWidget* addTaskWidget = new AddTaskWidget(serviceApp);
    ViewTaskWidget* viewTaskWidget = new ViewTaskWidget(serviceApp);
    MainWidget* mainWidget = new MainWidget(serviceApp, addTaskWidget, viewTaskWidget);
    MainWindow* mainWindow = new MainWindow(loginWidget, registerWidget, mainWidget);
    mainWindow->show();

    return QApplication::exec();
}

//int main_old(int argc, char *argv[]) {
//    QApplication a(argc, argv);
//    OldRepositoryApp repositoryApp = OldRepositoryApp();
//    LoginService loginService = LoginService("../Data/authentification", repositoryApp);
//    ServiceApp serviceApp = ServiceApp(repositoryApp);
//    LoginWidget* loginWidget = new LoginWidget(loginService);
//    AddTaskWidget* addTaskWidget = new AddTaskWidget(serviceApp);
//    MainWidget* mainWidget = new MainWidget(serviceApp, addTaskWidget);
//    MainWindow* mainWindow = new MainWindow(loginWidget, nullptr, mainWidget, nullptr);
//    mainWindow->show();
//    return QApplication::exec();
//    ///acuma trebuie sa ma apuc sa integrez conexiunea
//    ///trebuie sa introduc registration wtf
//}


//#include <QCoreApplication>
//#include <QNetworkAccessManager>
//#include <QNetworkReply>
//#include <QJsonDocument>
//#include <QJsonObject>
//
////int main(int argc, char *argv[])
////{
////    QCoreApplication a(argc, argv);
////
////    QNetworkAccessManager manager;
////
////    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl("http://127.0.0.1:8000/api/login")));
////
////    QObject::connect(reply, &QNetworkReply::finished, [&]() {
////        if (reply->error() == QNetworkReply::NoError) {
////            QByteArray response = reply->readAll();
////            QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
////            QJsonObject jsonObject = jsonResponse.object();
////            qDebug()<<"Cred ca o mers";
////            qDebug()<<jsonObject;
////            // Acum poți procesa jsonObject sau actualiza interfața grafică
////        } else {
////            qDebug() << "Error: " << reply->errorString();
////        }
////
////        reply->deleteLater();
////        a.quit();
////    });
////
////    return a.exec();
////}
//
//#include <QtNetwork>
//#include <QUrl>
//#include <QNetworkAccessManager>
//#include <QNetworkRequest>
//#include <QNetworkReply>
//#include <QApplication>
//
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//
//    // Crează un obiect QNetworkAccessManager
//    QNetworkAccessManager manager;
//
//    // Construiește URL-ul pentru cererea POST
//    QUrl url("http://127.0.0.1:8000/api/list/");
//
//    // Construiește cererea HTTP
//    QNetworkRequest request(url);
//
//    // Setează metoda HTTP la POST
//    request.setRawHeader("Content-Type", "application/json");
//
//    // Adaugă datele pe care dorești să le trimiți (în acest exemplu, JSON)
//    QByteArray postData;
//    postData.append(R"({"listName": "Prima lista din qt"})");
////    qDebug()<<postData.toStdString();
// //    Autentificare token (dacă este necesară)
//    QString token = "d5125aea46c6b0c66787fb95d6e23d7d091cb898";
//    QString headerData = "Token " + token;
//    request.setRawHeader("Authorization", headerData.toLocal8Bit());
////    qDebug()<<request.rawHeaderList();
//
//    // Trimite cererea POST
//    QNetworkReply *reply = manager.get(request);
////    QNetworkReply *reply = manager.post(request, postData); ->pentru post
//    // Conectează un slot pentru a trata răspunsul
//    QObject::connect(reply, &QNetworkReply::finished, [&]() {
//        if (reply->error() == QNetworkReply::NoError) {
//            // Răspunsul este OK
//            QByteArray responseData = reply->readAll();
//            qDebug() << "Răspuns:" << responseData;
//        } else {
//            // A apărut o eroare
//            qDebug() << "Eroare:" << reply->errorString();
//        }
//
//        // Eliberează resursele
//        reply->deleteLater();
//    });
//
//    return a.exec();
//}
