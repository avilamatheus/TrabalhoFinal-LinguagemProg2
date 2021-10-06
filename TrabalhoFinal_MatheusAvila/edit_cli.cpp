#include "edit_cli.h"
#include "ui_edit_cli.h"
#include "ger_cli.h"
#include "Conexao.h"

static int id_cliente;

edit_cli::edit_cli(QWidget *parent, int id) :
    QDialog(parent),
    ui(new Ui::edit_cli)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("../TrabalhoFinal_MatheusAvila/imgs/logo.png"));
    setWindowTitle("Editar Cliente - Scrap Sweet");
    id_cliente = id;
    QSqlQuery query;
    query.prepare("select * from tb_clientes where id_cliente="+QString::number(id_cliente));
    if(query.exec())
    {
        query.first();
        ui->txt_id->setText(query.value(0).toString());
        ui->txt_nome->setText(query.value(1).toString());
        ui->txt_end->setText(query.value(2).toString());
        ui->txt_tel->setText(query.value(3).toString());
    }
}

edit_cli::~edit_cli()
{
    delete ui;
}

void edit_cli::on_btn_gravar_clicked()
{
    if(ui->txt_nome->text() == "" || ui->txt_end->text() == "" || ui->txt_tel->text() == "")
    {
        QMessageBox::warning(this, "ERRO", "Preencha todos os campos antes de editar o cliente");
    }
    else
    {
        QString nome_cliente=ui->txt_nome->text();
        QString endereco=ui->txt_end->text();
        QString telefone=ui->txt_tel->text();
        QSqlQuery query;
        query.prepare("update tb_clientes set nome_cliente='"+nome_cliente+"',end_cliente='"+endereco+"',telefone_cliente='"+telefone+"' where id_cliente="+QString::number(id_cliente));
        if(query.exec())
        {
            this->close();
            ger_cli::alt=true;
        }
        else
            QMessageBox::warning(this, "ERRO", "Erro ao atualizar dados do cliente");
    }
}
