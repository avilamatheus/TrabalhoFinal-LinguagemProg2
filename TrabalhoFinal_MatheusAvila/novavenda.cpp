#include "novavenda.h"
#include "ui_novavenda.h"
#include "edit_venda.h"
#include "add_new.h"
#include "view_produtos.h"
#include "principal.h"
QString novavenda::g_prod;
QString novavenda::g_qtd;
QString novavenda::g_vu;
QString novavenda::g_vt;
bool novavenda::alt;
bool novavenda::add;

novavenda::novavenda(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::novavenda)
{
    ui->setupUi(this);
    setWindowTitle("Nova Venda - Scrap Sweet");
    setWindowIcon(QIcon("../TrabalhoFinal_MatheusAvila/imgs/logo.png"));
    if(!con.abrir())
    {
        QMessageBox::warning(this, "ERRO", "Erro ao abrir o banco de dados");
    }
    ui->tw_prod->setColumnCount(5);
    ui->tw_prod->setColumnWidth(0,50);
    ui->tw_prod->setColumnWidth(1,150);
    ui->tw_prod->setColumnWidth(2,50);
    ui->tw_prod->setColumnWidth(3,50);
    ui->tw_prod->setColumnWidth(4,50);
    QStringList cabecalho={"ID Produto", "Nome", "Valor Uni.", "Qtd", "Valor Total"};
    ui->tw_prod->setHorizontalHeaderLabels(cabecalho);
    ui->tw_prod->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_prod->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_prod->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tw_prod->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tw_prod->verticalHeader()->setVisible(false);

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

        QStringList cabecalhos={"ID Cliente","Nome Cliente","Endereço Cliente","Telefone Cliente"};
        ui->tw_clientes->setHorizontalHeaderLabels(cabecalhos);
        ui->tw_clientes->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tw_clientes->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_clientes->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tw_clientes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tw_clientes->verticalHeader()->setVisible(false);
    }
}


novavenda::~novavenda()
{
    delete ui;
}

void novavenda::on_txt_cod_returnPressed()
{
    QSqlQuery query;
    QString id=ui->txt_cod->text();
    float valtot;
    int cont = 0;
    query.prepare("select * from tb_produtos where id_produto="+id);
    if(query.exec())
    {
        if(query.first())
        {
        ui->tw_prod->insertRow(cont);
        ui->tw_prod->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tw_prod->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tw_prod->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tw_prod->setItem(cont,3,new QTableWidgetItem(ui->txt_qtd->text()));
        valtot=ui->txt_qtd->text().toFloat()*query.value(2).toFloat();
        ui->tw_prod->setItem(cont,4,new QTableWidgetItem(QString::number(valtot)));
        ui->tw_prod->setRowHeight(cont,20);
        ui->tw_prod->item(cont,0)->setTextAlignment(Qt::AlignCenter);
        ui->tw_prod->item(cont,1)->setTextAlignment(Qt::AlignCenter);
        ui->tw_prod->item(cont,2)->setTextAlignment(Qt::AlignCenter);
        ui->tw_prod->item(cont,3)->setTextAlignment(Qt::AlignCenter);
        ui->tw_prod->item(cont,4)->setTextAlignment(Qt::AlignCenter);
        cont++;
        ui->lb_tot->setText("R$ "+QString::number(total(ui->tw_prod, 4)));
        }
        else
            QMessageBox::warning(this, "ERRO", "Produto não encontrado");
        resetar();
    }
    else
        QMessageBox::warning(this, "ERRO", "Erro ao inserir um novo produto");
}

void novavenda::resetar()
{
    ui->txt_cod->clear();
    ui->txt_qtd->setText("1");
    ui->txt_cod->setFocus();
}
float novavenda::total(QTableWidget *tw, int coluna)
{
    int linhas;
    float total=0;
    linhas=tw->rowCount();
    for(int i=0;i<linhas;i++)
    {
        total+=tw->item(i,coluna)->text().toFloat();
    }
    return total;
}

void novavenda::on_btn_excluir_clicked()
{
    if(ui->tw_prod->currentRow() < 0)
        {
            QMessageBox::warning(this, "ERRO", "Selecione um produto primeiro");
        }
    else
        {
            QMessageBox::StandardButton op=QMessageBox::question(this, "Excluir", "Deseja mesmo excluir esse produto?", QMessageBox::Yes|QMessageBox::No);
            if(op==QMessageBox::Yes)
            {
                ui->tw_prod->removeRow(ui->tw_prod->currentRow());
                ui->lb_tot->setText("R$ "+QString::number(total(ui->tw_prod, 4)));
                cont--;
            }
        }

}


void novavenda::on_btn_editar_clicked()
{
    if(ui->tw_prod->currentRow() < 0)
        {
            QMessageBox::warning(this, "ERRO", "Selecione um produto primeiro");
        }
    else
        {
           int linha=ui->tw_prod->currentRow();
           g_prod=ui->tw_prod->item(linha, 1)->text();
           g_qtd=ui->tw_prod->item(linha, 3)->text();
           g_vu=ui->tw_prod->item(linha, 2)->text();
           edit_venda f_edit;
           f_edit.exec();
           if(alt)
           {
               ui->tw_prod->item(linha,2)->setText(g_vu);
               ui->tw_prod->item(linha,3)->setText(g_qtd);
               ui->tw_prod->item(linha,4)->setText(g_vt);
               ui->lb_tot->setText("R$ "+QString::number(total(ui->tw_prod, 4)));
           }
        }

}

void novavenda::on_btn_finalizar_clicked()
{
    if(ui->tw_clientes->currentRow() < 0)
    {
        QMessageBox::warning(this, "ERRO", "Selecione um cliente primeiro");
    }
    else
    {
    if(ui->tw_prod->rowCount()>0)
    {
        int idVenda;
        QString id_cliente = ui->tw_clientes->item(ui->tw_clientes->currentRow(),0)->text();
        QString msgFimVenda;
        float ValorTotal=total(ui->tw_prod, 4);
        QString data=QDate::currentDate().toString("dd/MM/yyyy");
        QString hora=QTime::currentTime().toString("hh:mm:ss");
        qint64 ju = QDate::currentDate().toJulianDay();
        QString pag=ui->txt_pag->text();
        QString dataentrega=ui->txt_dataentrega->text();
        QString obs=ui->txt_obs->text();
        QString adm = principal::nome_adm;
        if(dataentrega=="" || obs == "" || pag == "")
            QMessageBox::warning(this, "ERRO", "Preencha os campos antes de finalizar a venda");
        else
        {
        QSqlQuery query;
        query.prepare("insert into tb_pedidos (data_venda,hora_venda,valor_total,metodo_pag,data_entrega,obs_venda,id_cliente,adm_resp,julianDate) values('"+data+"','"+hora+"',"+QString::number(ValorTotal)+",'"+pag+"','"+dataentrega+"','"+obs+"','"+id_cliente+"','"+adm+"',"+QString::number(ju)+")");
        if(!query.exec())
        {
            QMessageBox::warning(this, "ERRO", "Erro ao processar venda");
        }
        else
        {
            query.prepare("select id_venda from tb_pedidos order by id_venda desc limit 1");
            query.exec();
            query.first();
            idVenda=query.value(0).toInt();
            int t_linhas=ui->tw_prod->rowCount();
            int linha=0;
            while(linha<t_linhas)
            {
                QString prod=ui->tw_prod->item(linha,1)->text();
                QString qtd=ui->tw_prod->item(linha,3)->text();
                QString v_u=ui->tw_prod->item(linha,2)->text();
                QString v_t=ui->tw_prod->item(linha,4)->text();
                query.prepare("insert into tb_produtosvendidos (id_venda,produto,qtd,valor_un,valor_total)values("+QString::number(idVenda)+",'"+prod+"',"+qtd+","+v_u+","+v_t+")");
                query.exec();
                linha++;
            }
            msgFimVenda="ID Venda: "+QString::number(idVenda)+"\nValor Total: R$"+QString::number(ValorTotal);
            QMessageBox::information(this, "Venda Concluida",msgFimVenda);
            close();
        }
    }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Não existem produtos nessa venda");
    }
    }
}

void novavenda::on_btn_filtrar_clicked()
{
    QString busca;
    while(ui->tw_clientes->rowCount() > 0)
    {
        ui->tw_clientes->removeRow(0);
    }
    if(ui->txt_filtrar->text()=="")
    {
        if(ui->rb_cod->isChecked())
        {
            busca="select id_cliente,nome_cliente,end_cliente,telefone_cliente from tb_clientes order by id_cliente";
        }
        else
            busca="select id_cliente,nome_cliente,end_cliente,telefone_cliente from tb_clientes order by nome_cliente";
    }
    else
    {
        if(ui->rb_cod->isChecked())
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

void novavenda::on_pushButton_4_clicked()
{
    view_produtos f_produtos;
    f_produtos.exec();
}

void novavenda::on_add_new_cliente_clicked()
{
    add_new f_add;
    f_add.exec();
    if(add)
    {
        QSqlQuery query;
        query.prepare("select * from tb_clientes");
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
