#ifndef LOGIN_H
#define LOGIN_H
#include "Conexao.h"
#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    Conexao con;
    QString nome;

private slots:
    void on_btn_logar_clicked();

    void on_btn_cancelar_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
