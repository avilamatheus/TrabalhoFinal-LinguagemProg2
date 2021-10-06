#include "add_new.h"
#include "ui_add_new.h"
#include "novavenda.h"

add_new::add_new(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_new)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("../TrabalhoFinal_MatheusAvila/imgs/logo.png"));
    setWindowTitle("Novo Cliente - Scrap Sweet");
}

add_new::~add_new()
{
    delete ui;
}

void add_new::on_btn_salvar_clicked()
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
        novavenda::add=true;
        this->close();
    }
    }
}
