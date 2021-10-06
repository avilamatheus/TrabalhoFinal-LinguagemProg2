#ifndef GER_PROD_H
#define GER_PROD_H
#include "Conexao.h"
#include <QDialog>
#include <QMessageBox>

namespace Ui {
class ger_prod;
}

class ger_prod : public QDialog
{
    Q_OBJECT

public:
    explicit ger_prod(QWidget *parent = nullptr);
    ~ger_prod();
    Conexao con;
    static bool alt;

private slots:
    void on_btn_excluir_clicked();

    void on_btn_editar_clicked();

    void on_btn_filtrar_clicked();

private:
    Ui::ger_prod *ui;
};

#endif // GER_PROD_H
