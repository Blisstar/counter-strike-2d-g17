#ifndef JOINGAMEWINDOW_H
#define JOINGAMEWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QListWidgetItem>
#include <../client_protocol.h>

namespace Ui {
class JoinGameWindow;
}

class JoinGameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit JoinGameWindow(QWidget *parent = nullptr, ClientProtocol& _clientProtocol);
    ~JoinGameWindow();

    QString selectedGame;

    void showGamesList(const std::vector<RoomData>& rooms);

    void startSearch();

    QString getSelectedGame() const;

signals:

    void requestGamesList();

private slots:
    void on_gamesList_itemDoubleClicked(QListWidgetItem *item);

    void on_refreshButton_clicked();

private:
    Ui::JoinGameWindow *ui;
    ClientProtocol& clientProtocol;

    void onJoinClicked();
};

#endif // JOINGAMEWINDOW_H
