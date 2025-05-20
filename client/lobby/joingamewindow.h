#ifndef JOINGAMEWINDOW_H
#define JOINGAMEWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class JoinGameWindow;
}

class JoinGameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit JoinGameWindow(QWidget *parent = nullptr);
    ~JoinGameWindow();

    QString selectedGame;

    void showGamesList(const QStringList &servers);

    void startSearch();

    QString getSelectedGame() const;

signals:

    void requestGamesList();

private slots:
    void on_gamesList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::JoinGameWindow *ui;

    void onJoinClicked();
};

#endif // JOINGAMEWINDOW_H
