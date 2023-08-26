#include <QApplication>
#include <QSqlDatabase>
#include <cstdlib>
#include <QSql>
#include <QPushButton>
#include "Repository/RepositoryApp.h"
#include "Service/LoginService.h"
#include "Presentation/LoginWidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    LoginService loginService = LoginService("../Data/authentification");
    LoginWidget loginWidget = LoginWidget(loginService);
    loginWidget.show();
//    QPushButton button("Hello world!", nullptr);
//    QObject::connect(button, &QPushButton::clicked, [](){
//    auto repo = RepositoryApp(getenv("host_name"), getenv("database"), getenv("user_name"), getenv("password"), std::stoi(getenv("port")));
//    repo.print_data();
//    });

    return QApplication::exec();
}
