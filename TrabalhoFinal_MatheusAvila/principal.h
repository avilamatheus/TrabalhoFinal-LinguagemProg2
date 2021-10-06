#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include "login.h"
#include "novavenda.h"
#include "gestao_adms.h"
#include "gestao_vendas.h"
#include "ger_prod.h"
#include "add_produto.h"
#include "add_clientes.h"
#include "ger_cli.h"
#include "vendas_clientes.h"
#include "add_adms.h"

QT_BEGIN_NAMESPACE
namespace Ui { class principal; }
QT_END_NAMESPACE

class principal : public QMainWindow
{
    Q_OBJECT

public:
    principal(QWidget *parent = nullptr);
    ~principal();
    static bool logado;
    static QString nome_adm;
    static int id_adm;

private slots:
    void on_btn_logar_clicked();

    void on_btn_venda_clicked();

    void on_actionAdicionar_Novo_Produto_triggered();

    void on_actionGerenciar_Produtos_triggered();

    void on_actionAdicionar_Cliente_triggered();

    void on_actionGerenciar_Clientes_triggered();

    void on_actionGest_o_Vendas_triggered();

    void on_actionVendas_por_Cliente_triggered();

    void on_actionAdicionar_Novo_Admin_triggered();

    void on_actionGerenciar_Administradores_triggered();

private:
    Ui::principal *ui;
};
#endif // PRINCIPAL_H
