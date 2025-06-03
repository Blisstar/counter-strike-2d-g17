#ifndef WAITINGGUESTWINDOW_H
#define WAITINGGUESTWINDOW_H

#include <QDialog>
#include <QWidget>
#include <../client_protocol.h>

namespace Ui {
class WaitingGuestWindow;
}

class WaitingGuestWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WaitingGuestWindow(QWidget *parent = nullptr, ClientProtocol& _clientProtocol);
    ~WaitingGuestWindow();

private:
    Ui::WaitingGuestWindow *ui;
    ClientProtocol& clientProtocol;
};

#endif // WAITINGGUESTWINDOW_H
