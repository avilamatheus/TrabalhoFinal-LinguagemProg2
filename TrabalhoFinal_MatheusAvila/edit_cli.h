#ifndef EDIT_CLI_H
#define EDIT_CLI_H

#include <QDialog>

namespace Ui {
class edit_cli;
}

class edit_cli : public QDialog
{
    Q_OBJECT

public:
    explicit edit_cli(QWidget *parent = nullptr, int id=0);
    ~edit_cli();

private slots:
    void on_btn_gravar_clicked();

private:
    Ui::edit_cli *ui;
};

#endif // EDIT_CLI_H
