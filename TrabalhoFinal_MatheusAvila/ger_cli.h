#ifndef GER_CLI_H
#define GER_CLI_H

#include <QDialog>
#include "Conexao.h"
#include <QMessageBox>

namespace Ui {
class ger_cli;
}

class ger_cli : public QDialog
{
    Q_OBJECT

public:
    explicit ger_cli(QWidget *parent = nullptr);
    ~ger_cli();
    Conexao con;
    static bool alt;

private slots:
    void on_btn_filtrar_clicked();

    void on_btn_editar_clicked();

private:
    Ui::ger_cli *ui;
};

#endif // GER_CLI_H
