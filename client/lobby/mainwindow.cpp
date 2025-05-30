#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "premenu.h"
#include "joingamewindow.h"
#include "newgamewindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1280, 719);

    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);

    QPixmap bkgnd("../media/menu_bg_img.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    this->setAutoFillBackground(true);

    showMenuButtons(false);

    PreMenu premenu(this);
    if (premenu.exec() == QDialog::Accepted) {
        //QString ip = premenu.getIp();
        //int port = premenu.getPort();

        showMenuButtons(true);
    } else {
        QTimer::singleShot(0, this, SLOT(close()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMenuButtons(bool show){
    ui->newgameButton->setVisible(show);
    ui->findserversButton->setVisible(show);
    ui->quitButton->setVisible(show);
}


void MainWindow::on_newgameButton_clicked()
{
    auto *win = new NewGameWindow(this);
    win->show();
}

void MainWindow::on_findserversButton_clicked()
{
    auto *dialog = new JoinGameWindow(this);
    dialog->show();
    dialog->startSearch();

    if (dialog->exec() == QDialog::Accepted) {
        QString selectedGame = dialog->getSelectedGame();

        // mandar mensaje por red
    }

    delete dialog;
}

void MainWindow::on_quitButton_clicked()
{
    QApplication::quit();
}

