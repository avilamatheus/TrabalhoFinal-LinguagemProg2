#include "edit_venda.h"
#include "ui_edit_venda.h"
#include "novavenda.h"

edit_venda::edit_venda(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_venda)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("../TrabalhoFinal_MatheusAvila/imgs/logo.png"));
    setWindowTitle("Editar Venda - Scrap Sweet");
    ui->txt_produto->setText(novavenda::g_prod);
    ui->txt_qtd->setText(novavenda::g_qtd);
    ui->txt_un->setText(novavenda::g_vu);
}

edit_venda::~edit_venda()
{
    delete ui;
}

void edit_venda::on_btn_salvar_clicked()
{
    if(ui->txt_qtd->text()=="" || ui->txt_un->text()=="")
        QMessageBox::warning(this, "ERRO", "Por favor preencha todos os dados");
    else
    {
        QString aux;
        novavenda::alt=true;
        novavenda::g_qtd=ui->txt_qtd->text();
        aux=ui->txt_un->text();
        std::replace(aux.begin(),aux.end(), ',','.');
        novavenda::g_vu=aux;
        novavenda::g_vt=QString::number(ui->txt_qtd->text().toFloat()*aux.toFloat());
        close();
    }
}

void edit_venda::on_btn_cancelar_clicked()
{
    novavenda::alt=false;
    close();
}
