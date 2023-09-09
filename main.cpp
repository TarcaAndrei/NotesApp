#include <QApplication>
#include <cstdlib>
#include <iostream>
#include "Presentation/AuthWidgets/LoginWidget.h"
#include "Presentation/MainWindow.h"
#include "Service/ServiceApp.h"
#include "Presentation/TasksWidgets/AddTaskWidget.h"
#include "Service/ServiceAuth.h"
#include "Presentation/TasksWidgets/ViewTaskWidget.h"
int main(int argc, char*argv[]){
    QApplication a(argc, argv);
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
//    auto listObject = new ListObject();
//    listObject->show();
//    QApplication::setQuitOnLastWindowClosed(false);
    return QApplication::exec();
}

