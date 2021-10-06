#include "edit_prod.h"
#include "ui_edit_prod.h"
#include "ger_prod.h"
#include "Conexao.h"

static int id_prod;

edit_prod::edit_prod(QWidget *parent, int id) :
    QDialog(parent),
    ui(new Ui::edit_prod)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("../TrabalhoFinal_MatheusAvila/imgs/logo.png"));
    setWindowTitle("Editar Produto - Scrap Sweet");
    id_prod = id;
    QSqlQuery query;
    query.prepare("select * from tb_produtos where id_produto="+QString::number(id_prod));
    if(query.exec())
    {
        query.first();
        ui->txt_id->setText(query.value(0).toString());
        ui->txt_produto->setText(query.value(1).toString());
        ui->txt_valor->setText(query.value(2).toString());
    }
}

edit_prod::~edit_prod()
{
    delete ui;
}

void edit_prod::on_btn_gravar_clicked()
{
    QString id_produto=ui->txt_id->text();
    QString produto=ui->txt_produto->text();
    QString aux=ui->txt_valor->text();
    std::replace(aux.begin(),aux.end(),',','.');
    QString valor = aux;
    if(id_produto == "" || produto == "" || valor == "")
        QMessageBox::warning(this, "ERRO", "Por favor preencha todos os dados do produto.");
    else
    {
    QSqlQuery query;
    query.prepare("update tb_produtos set id_produto='"+id_produto+"',produto='"+produto+"',valor="+valor+" where id_produto="+QString::number(id_prod));
    if(query.exec())
    {
        this->close();
        ger_prod::alt=true;
    }
    else
        QMessageBox::warning(this, "ERRO", "Erro ao atualizar dados do produto");
    }
}
