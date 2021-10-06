#include "edit_venda_gestao.h"
#include "ui_edit_venda_gestao.h"
#include "gestao_edit_v.h"
#include <QMessageBox>

edit_venda_gestao::edit_venda_gestao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_venda_gestao)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("../TrabalhoFinal_MatheusAvila/imgs/logo.png"));
    setWindowTitle("Editar Venda - Scrap Sweet");
    ui->txt_produto->setText(gestao_edit_v::g_prod);
    ui->txt_qtd->setText(gestao_edit_v::g_qtd);
    ui->txt_un->setText(gestao_edit_v::g_vu);
}

edit_venda_gestao::~edit_venda_gestao()
{
    delete ui;
}

void edit_venda_gestao::on_btn_salvar_clicked()
{
    if(ui->txt_qtd->text()=="" || ui->txt_un->text()=="")
        QMessageBox::warning(this, "ERRO", "Por favor preencha todos os dados");
    else
    {
        QString aux;
        gestao_edit_v::alt=true;
        gestao_edit_v::g_qtd=ui->txt_qtd->text();
        aux=ui->txt_un->text();
        std::replace(aux.begin(),aux.end(), ',','.');
        gestao_edit_v::g_vu=aux;
        gestao_edit_v::g_vt=QString::number(ui->txt_qtd->text().toFloat()*aux.toFloat());
        close();
    }
}

void edit_venda_gestao::on_btn_cancelar_clicked()
{
    gestao_edit_v::alt=false;
    close();
}
