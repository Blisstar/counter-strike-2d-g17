#include "mainmenuwindow.h"

#include <QApplication>
#include <QGuiApplication>
#include <QPalette>
#include <QPixmap>
#include <QScreen>
#include <QTimer>

#include "joingamewindow.h"
#include "newgamewindow.h"
#include "ui_mainmenuwindow.h"

MainMenuWindow::MainMenuWindow(QWidget *parent, const char *servname,
                               const char *port)
    : QWidget(parent),
      ui(new Ui::MainMenuWindow),
      clientProtocol(servname, port) {
    ui->setupUi(this);
    setFixedSize(1280, 719);

    QRect screenGeometry =
        QGuiApplication::primaryScreen()->availableGeometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);

    QPixmap bkgnd("../media/menu_bg_img.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    this->setAutoFillBackground(true);

    showMenuButtons(true);  // Siempre visible en este punto
}

MainMenuWindow::~MainMenuWindow() {
    delete ui;
}

void MainMenuWindow::showMenuButtons(bool show) {
    ui->newgameButton->setVisible(show);
    ui->findserversButton->setVisible(show);
    ui->quitButton->setVisible(show);
}

void MainMenuWindow::on_newgameButton_clicked() {
    auto *win = new NewGameWindow(this, clientProtocol);
    win->show();
}

void MainMenuWindow::on_findserversButton_clicked() {
    auto *dialog = new JoinGameWindow(this, clientProtocol);
    dialog->show();
    dialog->startSearch();

    if (dialog->exec() == QDialog::Accepted) {
        QString selectedGame = dialog->getSelectedGame();
        // mandar mensaje por red
    }

    delete dialog;
}

void MainMenuWindow::on_quitButton_clicked() {
    QApplication::quit();
}
