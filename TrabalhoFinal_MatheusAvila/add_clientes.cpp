#include "add_clientes.h"
#include "ui_add_clientes.h"

add_clientes::add_clientes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_clientes)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("../TrabalhoFinal_MatheusAvila/imgs/logo.png"));
    setWindowTitle("Novo Cliente - Scrap Sweet");
    ui->txt_nome->setFocus();
    if(!con.aberto())
        con.abrir();
}

add_clientes::~add_clientes()
{
    delete ui;
    con.fechar();
}

void add_clientes::on_btn_gravar_clicked()
{
    QString nome=ui->txt_nome->text();
    QString end=ui->txt_end->text();
    QString tel=ui->txt_tel->text();
    if(nome == "" || end == "" || tel=="")
        QMessageBox::warning(this, "ERRO", "Por favor preencha todos os campos.");
    else
    {
    QSqlQuery query;
    query.prepare("insert into tb_clientes (nome_cliente,end_cliente,telefone_cliente) values"
     "('"+nome+"','"+end+"','"+tel+"')");
    if(!query.exec())
    {
        QMessageBox::warning(this, "ERRO", "Erro ao inserir cliente");
    }
    else
    {
        QMessageBox::information(this, "Cliente", "Cliente inserido com sucesso");
        ui->txt_nome->clear();
        ui->txt_end->clear();
        ui->txt_tel->clear();
        ui->txt_nome->setFocus();
    }
    }
}
