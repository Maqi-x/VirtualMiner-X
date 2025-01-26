// --------------------------------------------------- //
//                    VirtualMiner-X                   //
//                       main.cpp                      //
// (c) 2025 Maqi-x                                     //
// --------------------------------------------------- //

// -------------- Qt------------- //
#include <QApplication>
#include <QMessageBox>
#include <QSettings>
// ----------------------------- //

#include <MainWin.hpp>
#include <data.hpp>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // QMessageBox::information(nullptr, "foo", settings.fileName());
    QFile style(":/main.qss");
    if (style.open(QFile::ReadOnly)) {
        app.setStyleSheet(style.readAll());
    }

    MainWindow w;
    w.setWindowIcon(QIcon(":/images/logo.png"));
    w.setWindowTitle("VirtualMiner-X");
    w.show();
    return app.exec();
}
