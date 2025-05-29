#include "joingamewindow.h"
#include "ui_joingamewindow.h"
#include "waitingguestwindow.h"

#include <QTimer>
#include <QMessageBox>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

class ServerListItem : public QWidget {
public:
    ServerListItem(const QString &name, const QString &map, int players, QWidget *parent = nullptr)
        : QWidget(parent) {

        auto *layout = new QHBoxLayout(this);
        layout->setContentsMargins(5, 2, 5, 2);
        layout->setSpacing(15);

        QLabel *nameLabel = new QLabel(name);
        QLabel *mapLabel = new QLabel(map);
        QLabel *playersLabel = new QLabel(QString("%1/").arg(players));
        QString style = "background: transparent; border: none; color: white;";

        nameLabel->setStyleSheet(style);
        mapLabel->setStyleSheet(style);
        playersLabel->setStyleSheet(style);

        nameLabel->setMinimumWidth(150);
        mapLabel->setMinimumWidth(100);
        playersLabel->setMinimumWidth(80);

        layout->addWidget(nameLabel, 1);
        layout->addWidget(mapLabel, 1);
        layout->addWidget(playersLabel, 1);
        setLayout(layout);
    }
};

JoinGameWindow::JoinGameWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::JoinGameWindow)
{
    ui->setupUi(this);
    setFixedSize(480, 470);
    ui->frame->setFixedSize(480, 470);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    QRect parentRect = parent->rect();
    QPoint parentTopLeft = parent->mapToGlobal(parentRect.topLeft());

    int x = parentTopLeft.x() + (parentRect.width() - this->width()) / 2;
    int y = parentTopLeft.y() + (parentRect.height() - this->height()) / 2;

    this->move(x, y);

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

    for (const QString &server : servers) {
        QStringList parts = server.split('|');
        QString name = parts.value(0, "Unknown");
        QString map = parts.value(1, "Unknown Map");
        int players = parts.value(2, "0").toInt();

        QListWidgetItem *item = new QListWidgetItem(ui->gamesList);
        ServerListItem *widget = new ServerListItem(name, map, players);

        item->setSizeHint(widget->sizeHint());
        ui->gamesList->addItem(item);
        ui->gamesList->setItemWidget(item, widget);
    }

    ui->gamesList->show();
}

void JoinGameWindow::startSearch(){
    ui->statusLabel->setText("Searching for servers...");

    //emit requestGamesList();

    QTimer::singleShot(5000, this, [=]() {
        QStringList servers = {
            "Game 1|Dust2|5",
            "Game 2|Aztec|3",
            "Game 3|Nuke|7"
        };
        showGamesList(servers);
    });
}

void JoinGameWindow::onJoinClicked() {
    QListWidgetItem *item = ui->gamesList->currentItem();
    if (item) {
        selectedGame = item->text();
        accept();
    } else {
        QMessageBox::warning(this, "No server selected", "Please, select a server to join.");
    }

    WaitingGuestWindow *win = new WaitingGuestWindow(this->parentWidget());
    win->setWindowModality(Qt::ApplicationModal);
    win->show();

    this->close();
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
        QMessageBox::warning(this, "No server selected", "Please, select a server to join.");
    }
}


void JoinGameWindow::on_refreshButton_clicked()
{
    ui->gamesList->clear();
    startSearch();
}

