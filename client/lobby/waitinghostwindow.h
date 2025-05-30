#ifndef WAITINGHOSTWINDOW_H
#define WAITINGHOSTWINDOW_H

#include <QDialog>

namespace Ui {
class WaitingHostWindow;
}

class WaitingHostWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WaitingHostWindow(QWidget *parent = nullptr);
    ~WaitingHostWindow();

private:
    Ui::WaitingHostWindow *ui;
};

#endif // WAITINGHOSTWINDOW_H
