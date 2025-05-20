#include "joingamewindow.h"
#include "ui_joingamewindow.h"

#include <QTimer>
#include <QMessageBox>

JoinGameWindow::JoinGameWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::JoinGameWindow)
{
    ui->setupUi(this);
    setFixedSize(450, 400);
    ui->frame->setFixedSize(450, 400);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    connect(ui->closeButton, &QPushButton::clicked, this, &JoinGameWindow::close);
    connect(ui->cancelButton, &QPushButton::clicked, this, &JoinGameWindow::close);
    connect(ui->joinButton, &QPushButton::clicked, this, &JoinGameWindow::onJoinClicked);
}

JoinGameWindow::~JoinGameWindow()
{
    delete ui;
}

void JoinGameWindow::showGamesList(const QStringList &servers) {
    ui->statusLabel->setText("Servers");
    ui->gamesList->clear();
    ui->gamesList->addItems(servers);
    ui->gamesList->show();
}

void JoinGameWindow::startSearch(){
    ui->statusLabel->setText("Searching for servers...");
    //ui->gamesList->hide();

    //emit requestGamesList();

    QTimer::singleShot(5000, this, [=]() {
        QStringList servers = { "Game 1", "Game 2", "Game 3" };
        showGamesList(servers);
    });
}

void JoinGameWindow::onJoinClicked() {
    QListWidgetItem *item = ui->gamesList->currentItem();
    if (item) {
        selectedGame = item->text();
        accept();
    } else {
        QMessageBox::warning(this, "Seleccionar partida", "Por favor, seleccioná una partida.");
    }
}

QString JoinGameWindow::getSelectedGame() const {
    return selectedGame;
}

void JoinGameWindow::on_gamesList_itemDoubleClicked(QListWidgetItem *item)
{
    if (item) {
        selectedGame = item->text();
        accept();
    } else {
        QMessageBox::warning(this, "Seleccionar partida", "Por favor, seleccioná una partida.");
    }
}

