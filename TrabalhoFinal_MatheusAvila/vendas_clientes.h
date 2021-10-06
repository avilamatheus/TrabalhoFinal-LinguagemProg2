#ifndef VENDAS_CLIENTES_H
#define VENDAS_CLIENTES_H

#include <QDialog>
#include "Conexao.h"
#include <QMessageBox>

namespace Ui {
class vendas_clientes;
}

class vendas_clientes : public QDialog
{
    Q_OBJECT

public:
    explicit vendas_clientes(QWidget *parent = nullptr);
    ~vendas_clientes();
    Conexao con;

private slots:
    void on_tw_clientes_itemSelectionChanged();

    void on_tw_pedidos_itemSelectionChanged();

    void on_btn_filtrar_clicked();

private:
    Ui::vendas_clientes *ui;
};

#endif // VENDAS_CLIENTES_H
