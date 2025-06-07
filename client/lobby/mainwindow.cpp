#include "mainwindow.h"
#include "premenu.h"
#include "mainmenuwindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    PreMenu premenu(this);
    if (premenu.exec() == QDialog::Accepted) {
        auto *menu = new MainMenuWindow(premenu.getIp().c_str(), premenu.getPort().c_str(), this);
        setCentralWidget(menu);
    } else {
        QTimer::singleShot(0, this, SLOT(close()));
    }
}

MainWindow::~MainWindow()
{
}