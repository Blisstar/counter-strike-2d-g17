#include "joingamewindow.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QTimer>
#include <QWidget>

#include "ui_joingamewindow.h"
#include "waitingguestwindow.h"

class ServerListItem : public QWidget {
   public:
    ServerListItem(const QString &name, const QString &map, uint8_t players,
                   QWidget *parent = nullptr)
        : QWidget(parent) {
        auto *layout = new QHBoxLayout(this);
        layout->setContentsMargins(5, 2, 5, 2);
        layout->setSpacing(15);

        QLabel *nameLabel = new QLabel(name);
        QLabel *mapLabel = new QLabel(map);
        QLabel *playersLabel = new QLabel(QString("%1/16").arg(players));
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

JoinGameWindow::JoinGameWindow(QWidget *parent, ClientProtocol &_clientProtocol)
    : QDialog(parent),
      ui(new Ui::JoinGameWindow),
      clientProtocol(_clientProtocol) {
    ui->setupUi(this);
    setFixedSize(480, 470);
    ui->frame->setFixedSize(480, 470);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    QRect parentRect = parent->rect();
    QPoint parentTopLeft = parent->mapToGlobal(parentRect.topLeft());

    int x = parentTopLeft.x() + (parentRect.width() - this->width()) / 2;
    int y = parentTopLeft.y() + (parentRect.height() - this->height()) / 2;

    this->move(x, y);

    connect(ui->closeButton, &QPushButton::clicked, this,
            &JoinGameWindow::close);
    connect(ui->cancelButton, &QPushButton::clicked, this,
            &JoinGameWindow::close);
    connect(ui->joinButton, &QPushButton::clicked, this,
            &JoinGameWindow::onJoinClicked);
}

JoinGameWindow::~JoinGameWindow() {
    delete ui;
}

void JoinGameWindow::showGamesList(const std::vector<RoomData>& rooms) {
    ui->statusLabel->setText("Servers");
    ui->gamesList->clear();

    std::vector<std::string> maps = {"Dust2", "Aztec", "Nuke"};
    for (const RoomData &room : rooms) {
        QString name(room.gameName.c_str());
        QString map(maps.at(room.mapId).c_str());
        uint8_t players = room.playersCount;

        QListWidgetItem *item = new QListWidgetItem(ui->gamesList);
        ServerListItem *widget = new ServerListItem(name, map, players);

        item->setSizeHint(widget->sizeHint());
        ui->gamesList->addItem(item);
        ui->gamesList->setItemWidget(item, widget);
    }

    ui->gamesList->show();
}

void JoinGameWindow::startSearch() {
    ui->statusLabel->setText("Searching for servers...");

    ClientMessageType t(ClientMessageType::GetListGame);
    ClientMessage c(t, std::monostate{});
    clientProtocol.send_message(c);
    QTimer::singleShot(2500, this, [=]() {
        LobbySnapshot l = clientProtocol.recvLobbySnapshot();
        showGamesList(l.roomListData);
    });
}

void JoinGameWindow::onJoinClicked() {
    QListWidgetItem *item = ui->gamesList->currentItem();
    if (item) {
        selectedGame = item->text();
        accept();
    } else {
        QMessageBox::warning(this, "No server selected",
                             "Please, select a server to join.");
    }

    WaitingGuestWindow *win = new WaitingGuestWindow(this->parentWidget());
    win->setWindowModality(Qt::ApplicationModal);
    win->show();

    this->close();
}

QString JoinGameWindow::getSelectedGame() const {
    return selectedGame;
}

void JoinGameWindow::on_gamesList_itemDoubleClicked(QListWidgetItem *item) {
    if (item) {
        selectedGame = item->text();
        accept();
    } else {
        QMessageBox::warning(this, "No server selected",
                             "Please, select a server to join.");
    }
}

void JoinGameWindow::on_refreshButton_clicked() {
    ui->gamesList->clear();
    startSearch();
}
