#ifndef NEWGAMEWINDOW_H
#define NEWGAMEWINDOW_H

#include <QWidget>
#include <QDialog>
#include "../client_protocol.h"

namespace Ui {
class NewGameWindow;
}

class NewGameWindow : public QDialog
{
    Q_OBJECT

public:
    NewGameWindow(ClientProtocol& _clientProtocol, QWidget *parent = nullptr);
    ~NewGameWindow();

private slots:
    void on_startButton_clicked();

private:
    Ui::NewGameWindow *ui;
    ClientProtocol& clientProtocol;
};

#endif // NEWGAMEWINDOW_H
