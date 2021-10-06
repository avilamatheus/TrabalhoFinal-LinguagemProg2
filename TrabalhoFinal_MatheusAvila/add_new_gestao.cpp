#include "add_new_gestao.h"
#include "ui_add_new_gestao.h"
#include "gestao_edit_v.h"
#include <QMessageBox>
#include "Conexao.h"

add_new_gestao::add_new_gestao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_new_gestao)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("../TrabalhoFinal_MatheusAvila/imgs/logo.png"));
    setWindowTitle("Novo Cliente - Scrap Sweet");
}

add_new_gestao::~add_new_gestao()
{
    delete ui;
}


void add_new_gestao::on_btn_salvar_clicked()
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
        gestao_edit_v::add=true;
        this->close();
    }
    }
}
