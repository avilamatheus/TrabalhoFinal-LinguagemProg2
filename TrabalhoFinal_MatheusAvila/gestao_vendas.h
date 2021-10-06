#ifndef GESTAO_VENDAS_H
#define GESTAO_VENDAS_H

#include <QDialog>
#include "Conexao.h"
#include <QMessageBox>
#include "gestao_edit_v.h"

namespace Ui {
class gestao_vendas;
}

class gestao_vendas : public QDialog
{
    Q_OBJECT

public:
    explicit gestao_vendas(QWidget *parent = nullptr);
    ~gestao_vendas();
    Conexao con;

private slots:
    void on_tw_vendas_itemSelectionChanged();

    void on_btn_filtrar_clicked();

    void on_btn_all_clicked();

    void on_btn_pdf_clicked();

    void on_btn_excluir_clicked();

    void on_btn_edit_clicked();

private:
    Ui::gestao_vendas *ui;
};

#endif // GESTAO_VENDAS_H
