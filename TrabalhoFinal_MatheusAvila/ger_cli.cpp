#include "ger_cli.h"
#include "ui_ger_cli.h"
#include "edit_cli.h"

bool ger_cli::alt;

ger_cli::ger_cli(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ger_cli)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("../TrabalhoFinal_MatheusAvila/imgs/logo.png"));
    setWindowTitle("Gerenciar Clientes - Scrap Sweet");
        if(!con.abrir())
        {
            QMessageBox::warning(this, "ERRO", "Erro ao abrir o banco de dados");
        }
        else
        {
        QSqlQuery query;
        query.prepare("select * from tb_clientes order by nome_cliente");
        if(query.exec())
        {
            int cont=0;
            ui->tw_clientes->setColumnCount(4);
            while(query.next())
            {
                ui->tw_clientes->insertRow(cont);
                ui->tw_clientes->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tw_clientes->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tw_clientes->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
                ui->tw_clientes->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
                ui->tw_clientes->item(cont,0)->setTextAlignment(Qt::AlignCenter);
                ui->tw_clientes->item(cont,1)->setTextAlignment(Qt::AlignCenter);
                ui->tw_clientes->item(cont,2)->setTextAlignment(Qt::AlignCenter);
                ui->tw_clientes->item(cont,3)->setTextAlignment(Qt::AlignCenter);
                ui->tw_clientes->setRowHeight(cont, 20);
                cont++;
            }
            ui->tw_clientes->setColumnWidth(0, 5);
            ui->tw_clientes->setColumnWidth(1, 200);
            ui->tw_clientes->setColumnWidth(2, 350);
            ui->tw_clientes->setColumnWidth(3, 100);
            QStringList cabecalhos={"ID", "Nome", "Endereço", "Telefone"};
            ui->tw_clientes->setHorizontalHeaderLabels(cabecalhos);
            ui->tw_clientes->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tw_clientes->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tw_clientes->verticalHeader()->setVisible(false);
            ui->tw_clientes->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
            ui->tw_clientes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        }
        else
            QMessageBox::warning(this, "ERRO", "Erro ao pesquisar na tabela de clientes");
        }
}

ger_cli::~ger_cli()
{
    delete ui;
}

void ger_cli::on_btn_filtrar_clicked()
{
    QString busca;
    while(ui->tw_clientes->rowCount() > 0)
    {
        ui->tw_clientes->removeRow(0);
    }
    if(ui->txt_filtrar->text()=="")
    {
        if(ui->rb_id->isChecked())
        {
            busca="select id_cliente,nome_cliente,end_cliente,telefone_cliente from tb_clientes order by id_cliente";
        }
        else
            busca="select id_cliente,nome_cliente,end_cliente,telefone_cliente from tb_clientes order by nome_cliente";
    }
    else
    {
        if(ui->rb_id->isChecked())
        {
            busca="select id_cliente,nome_cliente,end_cliente,telefone_cliente from tb_clientes where id_cliente="+ui->txt_filtrar->text()+" order by id_cliente";
        }
        else
            busca="select id_cliente,nome_cliente,end_cliente,telefone_cliente from tb_clientes where nome_cliente like '%"+ui->txt_filtrar->text()+"%' order by nome_cliente";
    }
    int cont=0;
    QSqlQuery query;
    query.prepare(busca);
    if(query.exec())
    {
        while(query.next())
        {
            ui->tw_clientes->insertRow(cont);
            ui->tw_clientes->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tw_clientes->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tw_clientes->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tw_clientes->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tw_clientes->item(cont,0)->setTextAlignment(Qt::AlignCenter);
            ui->tw_clientes->item(cont,1)->setTextAlignment(Qt::AlignCenter);
            ui->tw_clientes->item(cont,2)->setTextAlignment(Qt::AlignCenter);
            ui->tw_clientes->item(cont,3)->setTextAlignment(Qt::AlignCenter);
            ui->tw_clientes->setRowHeight(cont, 20);
            cont++;
        }
    }
}

void ger_cli::on_btn_editar_clicked()
{
    if(ui->tw_clientes->currentRow() < 0)
    {
        QMessageBox::warning(this, "ERRO", "Selecione um cliente primeiro");
    }
    else
    {
    int linha = ui->tw_clientes->currentRow();
    int id=ui->tw_clientes->item(linha,0)->text().toInt();
    edit_cli f_edit_cli(this, id);
    f_edit_cli.exec();
    if(alt)
    {
    QSqlQuery query;
    query.prepare("select * from tb_clientes order by nome_cliente");
    if(query.exec())
    {
        while(ui->tw_clientes->rowCount() > 0)
        {
            ui->tw_clientes->removeRow(0);
        }
        int cont=0;
         ui->tw_clientes->setColumnCount(4);
        while(query.next())
        {
            ui->tw_clientes->insertRow(cont);
            ui->tw_clientes->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tw_clientes->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tw_clientes->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tw_clientes->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tw_clientes->item(cont,0)->setTextAlignment(Qt::AlignCenter);
            ui->tw_clientes->item(cont,1)->setTextAlignment(Qt::AlignCenter);
            ui->tw_clientes->item(cont,2)->setTextAlignment(Qt::AlignCenter);
            ui->tw_clientes->item(cont,3)->setTextAlignment(Qt::AlignCenter);
            ui->tw_clientes->setRowHeight(cont, 20);
            cont++;
        }
    }
    }
    }
}
