#ifndef NEWGAMEWINDOW_H
#define NEWGAMEWINDOW_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class NewGameWindow;
}

class NewGameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewGameWindow(QWidget *parent = nullptr);
    ~NewGameWindow();

private slots:
    void on_startButton_clicked();

private:
    Ui::NewGameWindow *ui;
};

#endif // NEWGAMEWINDOW_H
