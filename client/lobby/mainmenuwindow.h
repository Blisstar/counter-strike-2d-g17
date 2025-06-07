#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QWidget>
#include "../client_protocol.h"

namespace Ui {
class MainMenuWindow;
}

class MainMenuWindow : public QWidget
{
    Q_OBJECT

public:
    MainMenuWindow(const char* servname, const char* port, QWidget *parent = nullptr);
    ~MainMenuWindow();

private slots:
    void on_newgameButton_clicked();
    void on_findserversButton_clicked();
    void on_quitButton_clicked();

private:
    Ui::MainMenuWindow *ui;
    ClientProtocol clientProtocol;

    void showMenuButtons(bool show);
};

#endif // MAINMENUWINDOW_H