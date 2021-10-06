#include "add_produto.h"
#include "ui_add_produto.h"

add_produto::add_produto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_produto)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("../TrabalhoFinal_MatheusAvila/imgs/logo.png"));
    setWindowTitle("Novo Produto - Scrap Sweet");
    ui->txt_codigo->setFocus();
    if(!con.abrir())
    {
        QMessageBox::warning(this, "ERRO", "Erro ao abrir o banco de dados");
    }
}

add_produto::~add_produto()
{
    delete ui;
    con.fechar();
}

void add_produto::on_btn_salvar_clicked()
{
    if(ui->txt_codigo->text() == "" || ui->txt_produto->text() == "" || ui->txt_valor->text() == "")
    {
        QMessageBox::warning(this, "ERRO", "Preencha todos os campos antes de inserir o produto");
    }
    else
    {
    QString aux;
    QString codigo=ui->txt_codigo->text();
    QString descricao=ui->txt_produto->text();
    aux=ui->txt_valor->text();
    std::replace(aux.begin(),aux.end(),',','.');
    QString valor=aux;
    QSqlQuery query;
    query.prepare("insert into tb_produtos (id_produto,produto,valor) values"
     "("+QString::number(codigo.toInt())+",'"+descricao+"', "+QString::number(valor.toFloat())+")");
    if(!query.exec())
    {
        QMessageBox::warning(this, "ERRO", "Erro ao inserir produto");
    }
    else
    {
        QMessageBox::information(this, "Produto", "Produto inserido com sucesso");
        ui->txt_codigo->clear();
        ui->txt_valor->clear();
        ui->txt_produto->clear();
        ui->txt_produto->setFocus();
    }
    }
}

void add_produto::on_btn_cancelar_clicked()
{
    close();
}
