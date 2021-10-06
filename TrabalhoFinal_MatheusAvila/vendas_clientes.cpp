#include "vendas_clientes.h"
#include "ui_vendas_clientes.h"

vendas_clientes::vendas_clientes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vendas_clientes)
{
    ui->setupUi(this);
    setWindowTitle("Vendas por Cliente - Scrap Sweet");
    setWindowIcon(QIcon("../TrabalhoFinal_MatheusAvila/imgs/logo.png"));
    if(!con.abrir())
    {
        QMessageBox::warning(this, "ERRO", "Erro ao abrir o banco de dados");
    }
    else
    {
    ui->tw_produtos->horizontalHeader()->setVisible(true);
    ui->tw_produtos->verticalHeader()->setVisible(false);
    ui->tw_produtos->setColumnCount(4);
    QStringList b={"Produto","Quantidade","Valor Unitario","Valor Total"};
    ui->tw_produtos->setHorizontalHeaderLabels(b);
    ui->tw_produtos->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tw_produtos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tw_produtos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_produtos->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tw_pedidos->horizontalHeader()->setVisible(true);
    ui->tw_pedidos->verticalHeader()->setVisible(false);
    ui->tw_pedidos->setColumnCount(8);
    QStringList c={"ID","Data da Venda","Hora da Venda","Valor Total","Metodo de Pag.","Data de Entrega","Observações", "Adm responsável"};
    ui->tw_pedidos->setHorizontalHeaderLabels(c);
    ui->tw_pedidos->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tw_pedidos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tw_pedidos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_pedidos->setEditTriggers(QAbstractItemView::NoEditTriggers);

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
        ui->tw_clientes->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tw_clientes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tw_clientes->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_clientes->verticalHeader()->setVisible(false);
    }
    }
}

vendas_clientes::~vendas_clientes()
{
    delete ui;
    con.fechar();
}
void vendas_clientes::on_tw_clientes_itemSelectionChanged()
{
    ui->tw_pedidos->setRowCount(0);
    ui->tw_produtos->setRowCount(0);
    int cont=0;
    QSqlQuery query;
    if(ui->tw_clientes->currentRow()>-1)
    {
    query.prepare("select * from tb_pedidos where id_cliente="+ui->tw_clientes->item(ui->tw_clientes->currentRow(),0)->text()+" order by id_venda desc");
    if(query.exec())
    {
        while(query.next())
        {
        ui->tw_pedidos->insertRow(cont);
        ui->tw_pedidos->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tw_pedidos->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tw_pedidos->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tw_pedidos->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
        ui->tw_pedidos->setItem(cont,4,new QTableWidgetItem(query.value(4).toString()));
        ui->tw_pedidos->setItem(cont,5,new QTableWidgetItem(query.value(5).toString()));
        ui->tw_pedidos->setItem(cont,6,new QTableWidgetItem(query.value(6).toString()));
        ui->tw_pedidos->setItem(cont,7,new QTableWidgetItem(query.value(8).toString()));
        ui->tw_pedidos->item(cont,0)->setTextAlignment(Qt::AlignCenter);
        ui->tw_pedidos->item(cont,1)->setTextAlignment(Qt::AlignCenter);
        ui->tw_pedidos->item(cont,2)->setTextAlignment(Qt::AlignCenter);
        ui->tw_pedidos->item(cont,3)->setTextAlignment(Qt::AlignCenter);
        ui->tw_pedidos->item(cont,4)->setTextAlignment(Qt::AlignCenter);
        ui->tw_pedidos->item(cont,5)->setTextAlignment(Qt::AlignCenter);
        ui->tw_pedidos->item(cont,6)->setTextAlignment(Qt::AlignCenter);
        ui->tw_pedidos->item(cont,7)->setTextAlignment(Qt::AlignCenter);

        cont++;
        }
    }
    }
 }

void vendas_clientes::on_tw_pedidos_itemSelectionChanged()
{
    if(ui->tw_pedidos->currentRow() > -1)
    {
    ui->tw_produtos->setRowCount(0);
    int cont=0;
    QSqlQuery query;
    query.prepare("select produto,qtd,valor_un,valor_total from tb_produtosvendidos where id_venda="+ui->tw_pedidos->item(ui->tw_pedidos->currentRow(),0)->text());
    if(query.exec())
    {
        while(query.next())
        {
        ui->tw_produtos->insertRow(cont);
        ui->tw_produtos->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tw_produtos->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tw_produtos->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tw_produtos->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
        cont++;
        }
    }
    }
}
void vendas_clientes::on_btn_filtrar_clicked()
{
    ui->tw_pedidos->setRowCount(0);
    ui->tw_produtos->setRowCount(0);
    ui->tw_clientes->setRowCount(0);
    QString busca;
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
