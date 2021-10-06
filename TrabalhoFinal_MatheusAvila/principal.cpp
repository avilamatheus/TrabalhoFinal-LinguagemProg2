#include "principal.h"
#include "ui_principal.h"

int principal::id_adm;
QString principal::nome_adm;
bool principal::logado;

principal::principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::principal)
{
    ui->setupUi(this);
    setWindowTitle("Scrap Sweet Personalizados");
    QPixmap pix("../TrabalhoFinal_MatheusAvila/imgs/logo.png");
     int w = ui->logo->width();
     int h = ui->logo->height();
     //ui->label_picture->setPixmap(pix);
     ui->logo->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    logado=false;
}

principal::~principal()
{
    delete ui;
}


void principal::on_btn_logar_clicked()
{
    if(!logado)
    {
        login f_login;
        f_login.exec();
        if(logado)
        {
            ui->btn_logar->setText("Logado");
            ui->txt_nome->setText("Admin: "+nome_adm);
        }
    }
    else
    {
        logado=false;
        ui->btn_logar->setText("Logar");
        ui->txt_nome->setText("");
    }
}

void principal::on_btn_venda_clicked()
{
    if(logado)
    {
        novavenda f_novavenda;
        f_novavenda.exec();
    }
    else
        QMessageBox::warning(this, "Login", "Por favor efetue o login");

}

void principal::on_actionAdicionar_Novo_Produto_triggered()
{
    if(logado)
    {
        add_produto f_add;
        f_add.exec();
    }
    else
        QMessageBox::warning(this, "Login", "Por favor efetue o login");

}


void principal::on_actionGerenciar_Produtos_triggered()
{
    if(logado)
    {
        ger_prod f_ger;
        f_ger.exec();
    }
    else
        QMessageBox::warning(this, "Login", "Por favor efetue o login");
}

void principal::on_actionAdicionar_Cliente_triggered()
{
    if(logado)
    {
        add_clientes f_clientes;
        f_clientes.exec();
    }
    else
        QMessageBox::warning(this, "Login", "Por favor efetue o login");
}

void principal::on_actionGerenciar_Clientes_triggered()
{
    if(logado)
    {
        ger_cli f_ger_cli;
        f_ger_cli.exec();
    }
    else
        QMessageBox::warning(this, "Login", "Por favor efetue o login");
}

void principal::on_actionGest_o_Vendas_triggered()
{
    if(logado)
    {
        gestao_vendas f_gvendas;
        f_gvendas.exec();
    }
    else
        QMessageBox::warning(this, "Login", "Por favor efetue o login");
}

void principal::on_actionVendas_por_Cliente_triggered()
{
    if(logado)
    {
        vendas_clientes f_vendas_clientes;
        f_vendas_clientes.exec();
    }
    else
        QMessageBox::warning(this, "Login", "Por favor efetue o login");
}

void principal::on_actionAdicionar_Novo_Admin_triggered()
{
    if(logado)
    {
        if(id_adm==1)
        {
            add_adms f_add_adms;
            f_add_adms.exec();
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Apenas o Admin principal pode executar essa ação");
        }
    }
    else
        QMessageBox::warning(this, "Login", "Por favor efetue o login");
}

void principal::on_actionGerenciar_Administradores_triggered()
{
    if(logado)
    {
        gestao_adms f_adms;
        f_adms.exec();
    }
    else
        QMessageBox::warning(this, "Login", "Por favor efetue o login");
}
