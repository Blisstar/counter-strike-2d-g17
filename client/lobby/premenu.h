#ifndef PREMENU_H
#define PREMENU_H

#include <QDialog>

namespace Ui {
class PreMenu;
}

class PreMenu : public QDialog
{
    Q_OBJECT

public:
    explicit PreMenu(QWidget *parent = nullptr);
    ~PreMenu();
    
    std::string getIp();

    std::string getPort();

private slots:
    void on_closeButton_clicked();

private:
    Ui::PreMenu *ui;
};

#endif // PREMENU_H
