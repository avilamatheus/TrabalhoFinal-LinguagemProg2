#include "ger_prod.h"
#include "ui_ger_prod.h"
#include "edit_prod.h"
bool ger_prod::alt;
ger_prod::ger_prod(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ger_prod)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("../TrabalhoFinal_MatheusAvila/imgs/logo.png"));
    setWindowTitle("Gerenciar Produtos - Scrap Sweet");
    if(!con.abrir())
    {
        QMessageBox::warning(this, "ERRO", "Erro ao abrir o banco de dados");
    }
    else
    {
        QSqlQuery query;
        query.prepare("select * from tb_produtos");
        if(query.exec())
        {
            int cont=0;
            ui->tw_produtos->setColumnCount(3);
            while(query.next())
            {
                ui->tw_produtos->insertRow(cont);
                ui->tw_produtos->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tw_produtos->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tw_produtos->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
                ui->tw_produtos->item(cont,0)->setTextAlignment(Qt::AlignCenter);
                ui->tw_produtos->item(cont,1)->setTextAlignment(Qt::AlignCenter);
                ui->tw_produtos->item(cont,2)->setTextAlignment(Qt::AlignCenter);
                ui->tw_produtos->setRowHeight(cont, 20);
                cont++;
            }
            ui->tw_produtos->setColumnWidth(0, 5);
            ui->tw_produtos->setColumnWidth(1, 200);

            QStringList cabecalhos={"Código", "Produto", "Valor"};
            ui->tw_produtos->setHorizontalHeaderLabels(cabecalhos);
            ui->tw_produtos->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tw_produtos->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tw_produtos->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
            ui->tw_produtos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tw_produtos->verticalHeader()->setVisible(false);

        }
        else
            QMessageBox::warning(this, "ERRO", "Erro ao listar produtos");
    }
}

ger_prod::~ger_prod()
{
    delete ui;
    con.fechar();
}

void ger_prod::on_btn_excluir_clicked()
{

    if(ui->tw_produtos->currentRow() < 0)
    {
        QMessageBox::warning(this, "ERRO", "Selecione um produto primeiro");
    }
    else
    {
        QMessageBox::StandardButton op=QMessageBox::question(this, "Excluir", "Deseja mesmo excluir esse produto?", QMessageBox::Yes|QMessageBox::No);
        if(op==QMessageBox::Yes)
        {
            int linha=ui->tw_produtos->currentRow();
            int id=ui->tw_produtos->item(linha, 0)->text().toInt();
            QSqlQuery query;
            query.prepare("delete from tb_produtos where id_produto="+QString::number(id));
            if(query.exec())
            {
                ui->tw_produtos->removeRow(linha);
                QMessageBox::information(this, "", "Produto excluido");
            }
            else
                QMessageBox::warning(this, "ERRO", "Erro ao excluir Produto");
            }
        }
}

void ger_prod::on_btn_editar_clicked()
{
    if(ui->tw_produtos->currentRow() < 0)
    {
        QMessageBox::warning(this, "ERRO", "Selecione um produto primeiro");
    }
    else
    {
    int linha = ui->tw_produtos->currentRow();
    int id=ui->tw_produtos->item(linha,0)->text().toInt();
    edit_prod f_editar(this, id);
    f_editar.exec();
    if(alt)
    {
    QSqlQuery query;
    query.prepare("select * from tb_produtos");
    if(query.exec())
    {
        while(ui->tw_produtos->rowCount() > 0)
        {
            ui->tw_produtos->removeRow(0);
        }
        int cont=0;
        ui->tw_produtos->setColumnCount(3);
        while(query.next())
        {
            ui->tw_produtos->insertRow(cont);
            ui->tw_produtos->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tw_produtos->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tw_produtos->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tw_produtos->item(cont,0)->setTextAlignment(Qt::AlignCenter);
            ui->tw_produtos->item(cont,1)->setTextAlignment(Qt::AlignCenter);
            ui->tw_produtos->item(cont,2)->setTextAlignment(Qt::AlignCenter);
            ui->tw_produtos->setRowHeight(cont, 20);
            cont++;
        }
    }
    }
}
}

void ger_prod::on_btn_filtrar_clicked()
{
    QString busca;
    while(ui->tw_produtos->rowCount() > 0)
    {
        ui->tw_produtos->removeRow(0);
    }
    if(ui->txt_filtrar->text()=="")
    {
        if(ui->rb_cod->isChecked())
        {
            busca="select id_produto,produto,valor from tb_produtos order by id_produto";
        }
        else
            busca="select id_produto,produto,valor from tb_produtos order by produto";
    }
    else
    {
        if(ui->rb_cod->isChecked())
        {
            busca="select id_produto,produto,valor from tb_produtos where id_produto="+ui->txt_filtrar->text()+" order by id_produto";
        }
        else
            busca="select id_produto,produto,valor from tb_produtos where produto like '%"+ui->txt_filtrar->text()+"%' order by produto";
    }
    int cont=0;
    QSqlQuery query;
    query.prepare(busca);
    if(query.exec())
    {
        while(query.next())
        {
            ui->tw_produtos->insertRow(cont);
            ui->tw_produtos->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tw_produtos->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tw_produtos->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tw_produtos->item(cont,0)->setTextAlignment(Qt::AlignCenter);
            ui->tw_produtos->item(cont,1)->setTextAlignment(Qt::AlignCenter);
            ui->tw_produtos->item(cont,2)->setTextAlignment(Qt::AlignCenter);
            ui->tw_produtos->setRowHeight(cont, 20);
            cont++;
        }
    }

}
