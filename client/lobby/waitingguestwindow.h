#ifndef WAITINGGUESTWINDOW_H
#define WAITINGGUESTWINDOW_H

#include <QDialog>
#include <QWidget>

namespace Ui {
class WaitingGuestWindow;
}

class WaitingGuestWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WaitingGuestWindow(QWidget *parent = nullptr);
    ~WaitingGuestWindow();

private:
    Ui::WaitingGuestWindow *ui;
};

#endif // WAITINGGUESTWINDOW_H
