#include "gestao_vendas.h"
#include "ui_gestao_vendas.h"
#include <QPrinter>
#include <QPainter>
#include <QDesktopServices>


gestao_vendas::gestao_vendas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestao_vendas)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("../TrabalhoFinal_MatheusAvila/imgs/logo.png"));
    setWindowTitle("Histórico de Vendas - Scrap Sweet");
    ui->de_f->setDate(QDate::currentDate());
    ui->tw_clientes->horizontalHeader()->setVisible(true);
    ui->tw_clientes->verticalHeader()->setVisible(false);
    ui->tw_clientes->setColumnCount(4);
    QStringList a={"ID Cliente","Nome Cliente","Endereço Cliente","Telefone Cliente"};
    ui->tw_clientes->setHorizontalHeaderLabels(a);
    ui->tw_clientes->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tw_clientes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tw_clientes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_clientes->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tw_prod_v->horizontalHeader()->setVisible(true);
    ui->tw_prod_v->verticalHeader()->setVisible(false);
    ui->tw_prod_v->setColumnCount(4);
    QStringList b={"Produto","Quantidade","Valor Uni.","Valor Tot."};
    ui->tw_prod_v->setHorizontalHeaderLabels(b);
    ui->tw_prod_v->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tw_prod_v->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tw_prod_v->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_prod_v->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tw_vendas->horizontalHeader()->setVisible(true);
    ui->tw_vendas->verticalHeader()->setVisible(false);
    ui->tw_vendas->setColumnCount(9);
    QStringList c={"ID Pedido","Data da Venda","Hora da Venda","Valor Total","Metodo de Pag.","Data de Entrega","Observações", "ID Cliente", "Adm responsável"};
    ui->tw_vendas->setHorizontalHeaderLabels(c);
    ui->tw_vendas->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tw_vendas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tw_vendas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_vendas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    if(!con.abrir())
    {
        QMessageBox::warning(this, "ERRO", "Erro ao abrir o banco de dados");
    }
    else
    {
    int cont=0;
    QSqlQuery query;
    query.prepare("select * from tb_pedidos order by id_venda desc");
    if(query.exec())
    {
    while(query.next())
    {
        ui->tw_vendas->insertRow(cont);
        ui->tw_vendas->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tw_vendas->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tw_vendas->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tw_vendas->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
        ui->tw_vendas->setItem(cont,4,new QTableWidgetItem(query.value(4).toString()));
        ui->tw_vendas->setItem(cont,5,new QTableWidgetItem(query.value(5).toString()));
        ui->tw_vendas->setItem(cont,6,new QTableWidgetItem(query.value(6).toString()));
        ui->tw_vendas->setItem(cont,7,new QTableWidgetItem(query.value(7).toString()));
        ui->tw_vendas->setItem(cont,8,new QTableWidgetItem(query.value(8).toString()));
        ui->tw_vendas->item(cont,0)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,1)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,2)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,3)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,4)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,5)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,6)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,7)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,8)->setTextAlignment(Qt::AlignCenter);
        cont++;
    }
    }
    }
}

gestao_vendas::~gestao_vendas()
{
    delete ui;
    con.fechar();
}

void gestao_vendas::on_tw_vendas_itemSelectionChanged()
{
    if(ui->tw_vendas->currentRow() > -1)
    {
    ui->tw_prod_v->setRowCount(0);
    ui->tw_clientes->setRowCount(0);
    int cont=0;
    QSqlQuery query;
    query.prepare("select produto,qtd,valor_un,valor_total from tb_produtosvendidos where id_venda="+ui->tw_vendas->item(ui->tw_vendas->currentRow(),0)->text());
    if(query.exec())
    {
        while(query.next())
        {
            ui->tw_prod_v->insertRow(cont);
            ui->tw_prod_v->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tw_prod_v->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tw_prod_v->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tw_prod_v->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tw_prod_v->item(cont,0)->setTextAlignment(Qt::AlignCenter);
            ui->tw_prod_v->item(cont,1)->setTextAlignment(Qt::AlignCenter);
            ui->tw_prod_v->item(cont,2)->setTextAlignment(Qt::AlignCenter);
            ui->tw_prod_v->item(cont,3)->setTextAlignment(Qt::AlignCenter);
            cont++;
        }
    }
    int cont1=0;
    QSqlQuery query1;
    query1.prepare("select * from tb_clientes where id_cliente="+ui->tw_vendas->item(ui->tw_vendas->currentRow(),7)->text());
    if(query1.exec())
    {
        while(query1.next())
        {
            ui->tw_clientes->insertRow(cont1);
            ui->tw_clientes->setItem(cont1,0,new QTableWidgetItem(query1.value(0).toString()));
            ui->tw_clientes->setItem(cont1,1,new QTableWidgetItem(query1.value(1).toString()));
            ui->tw_clientes->setItem(cont1,2,new QTableWidgetItem(query1.value(2).toString()));
            ui->tw_clientes->setItem(cont1,3,new QTableWidgetItem(query1.value(3).toString()));
            ui->tw_clientes->item(cont1,0)->setTextAlignment(Qt::AlignCenter);
            ui->tw_clientes->item(cont1,1)->setTextAlignment(Qt::AlignCenter);
            ui->tw_clientes->item(cont1,2)->setTextAlignment(Qt::AlignCenter);
            ui->tw_clientes->item(cont1,3)->setTextAlignment(Qt::AlignCenter);
            cont1++;
        }
    }
    }
}



void gestao_vendas::on_btn_filtrar_clicked()
{
    ui->tw_vendas->setRowCount(0);
    ui->tw_clientes->setRowCount(0);
    ui->tw_prod_v->setRowCount(0);
    QString data_inicial = ui->de_ini->text();
    QString data_final = ui->de_f->text();
    qDebug() << "Da String " << data_inicial;
    qDebug() << "Da String " << data_final;
    QDate dataini = QDate::fromString(data_inicial, "dd/MM/yyyy");
    QDate datafinal = QDate::fromString(data_final, "dd/MM/yyyy");
    qDebug() << "Da Date " << dataini;
    qDebug() << "Da Date " << datafinal;
    qint64 iniju = dataini.toJulianDay();
    qint64 finalju = datafinal.toJulianDay();
    qDebug() << iniju;
    qDebug() << finalju;

    int cont=0;
    QSqlQuery query;
    query.prepare("select * from tb_pedidos where julianDate between "+QString::number(iniju)+" and "+QString::number(finalju)+" order by id_venda desc");
    if(query.exec())
    {
    while(query.next())
    {
        ui->tw_vendas->insertRow(cont);
        ui->tw_vendas->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tw_vendas->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tw_vendas->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tw_vendas->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
        ui->tw_vendas->setItem(cont,4,new QTableWidgetItem(query.value(4).toString()));
        ui->tw_vendas->setItem(cont,5,new QTableWidgetItem(query.value(5).toString()));
        ui->tw_vendas->setItem(cont,6,new QTableWidgetItem(query.value(6).toString()));
        ui->tw_vendas->setItem(cont,7,new QTableWidgetItem(query.value(7).toString()));
        ui->tw_vendas->setItem(cont,8,new QTableWidgetItem(query.value(8).toString()));
        ui->tw_vendas->item(cont,0)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,1)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,2)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,3)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,4)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,5)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,6)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,7)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,8)->setTextAlignment(Qt::AlignCenter);
        cont++;
    }
    }
}

void gestao_vendas::on_btn_all_clicked()
{
    ui->tw_vendas->setRowCount(0);
    ui->tw_clientes->setRowCount(0);
    ui->tw_prod_v->setRowCount(0);
    int cont=0;
    QSqlQuery query;
    query.prepare("select * from tb_pedidos order by id_venda desc");
    if(query.exec())
    {
    while(query.next())
    {
        ui->tw_vendas->insertRow(cont);
        ui->tw_vendas->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tw_vendas->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tw_vendas->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tw_vendas->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
        ui->tw_vendas->setItem(cont,4,new QTableWidgetItem(query.value(4).toString()));
        ui->tw_vendas->setItem(cont,5,new QTableWidgetItem(query.value(5).toString()));
        ui->tw_vendas->setItem(cont,6,new QTableWidgetItem(query.value(6).toString()));
        ui->tw_vendas->setItem(cont,7,new QTableWidgetItem(query.value(7).toString()));
        ui->tw_vendas->setItem(cont,8,new QTableWidgetItem(query.value(8).toString()));
        ui->tw_vendas->item(cont,0)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,1)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,2)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,3)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,4)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,5)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,6)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,7)->setTextAlignment(Qt::AlignCenter);
        ui->tw_vendas->item(cont,8)->setTextAlignment(Qt::AlignCenter);
        cont++;
    }
    }
}

void gestao_vendas::on_btn_pdf_clicked()
{
    if(ui->tw_vendas->currentRow()>-1)
    {
    int numprod = ui->tw_prod_v->rowCount();

    QString local=+"../TrabalhoFinal_MatheusAvila/pdf/"+ui->tw_vendas->item(ui->tw_vendas->currentRow(),0)->text()+"_vendas.pdf";
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(local);
    QPainter painter;
    painter.begin(&printer);
    painter.drawPixmap(650,-25,QPixmap("../TrabalhoFinal_MatheusAvila/imgs/logomenor.png"));
    painter.drawText(25,40,"Número da venda: "+ui->tw_vendas->item(ui->tw_vendas->currentRow(),0)->text());
    painter.drawText(25,60,"Data da venda: "+ui->tw_vendas->item(ui->tw_vendas->currentRow(),1)->text());
    painter.drawText(25,80,"Hora da venda: "+ui->tw_vendas->item(ui->tw_vendas->currentRow(),2)->text());
    painter.drawText(25,100,"Observações:");
    painter.drawText(25,120,ui->tw_vendas->item(ui->tw_vendas->currentRow(),6)->text());
    painter.drawText(225,40,"Método de pagamento: "+ui->tw_vendas->item(ui->tw_vendas->currentRow(),4)->text());
    painter.drawText(425,40,"Admin Responsavel: "+ui->tw_vendas->item(ui->tw_vendas->currentRow(),8)->text());
    painter.drawText(225,60,"Data de Entrega: "+ui->tw_vendas->item(ui->tw_vendas->currentRow(),5)->text());
    painter.drawText(225,80,"Valor Total: R$ "+ui->tw_vendas->item(ui->tw_vendas->currentRow(),3)->text());
    painter.drawText(25,150,"Nome Cliente: "+ui->tw_clientes->item(0,1)->text());
    painter.drawText(25,170,"Endereço Cliente: "+ui->tw_clientes->item(0,2)->text());
    painter.drawText(25,190,"Telefone Cliente: "+ui->tw_clientes->item(0,3)->text());
    painter.drawText(25,220,"Itens do pedido:");
    painter.drawText(25,240,"---------------------------------------");
    if(numprod < 9)
    {
    int linha=260;
    int salto=20;
    for(int i=0;i<numprod;i++)
    {
        painter.drawText(25,linha,"Produto: "+ui->tw_prod_v->item(i,0)->text());
        linha+=salto;
        painter.drawText(25,linha,"Quantidade: "+ui->tw_prod_v->item(i,1)->text());
        linha+=salto;
        painter.drawText(25,linha,"Valor Unitário: R$ "+ui->tw_prod_v->item(i,2)->text());
        linha+=salto;
        painter.drawText(25,linha,"Valor Total: R$ "+ui->tw_prod_v->item(i,3)->text());
        linha+=salto;
        painter.drawText(25,linha,"---------------------------------------");
        linha+=salto;
    }
    }
    if(numprod > 8)
    {
        int linha=260;
        int salto=20;
        int res = numprod;
        for(int i=0;i<8;i++)
        {
            painter.drawText(25,linha,"Produto: "+ui->tw_prod_v->item(i,0)->text());
            linha+=salto;
            painter.drawText(25,linha,"Quantidade: "+ui->tw_prod_v->item(i,1)->text());
            linha+=salto;
            painter.drawText(25,linha,"Valor Unitário: R$ "+ui->tw_prod_v->item(i,2)->text());
            linha+=salto;
            painter.drawText(25,linha,"Valor Total: R$ "+ui->tw_prod_v->item(i,3)->text());
            linha+=salto;
            painter.drawText(25,linha,"---------------------------------------");
            linha+=salto;
            res--;
        }
        linha=260;
        if(res<9)
        {
            painter.drawText(275,240,"---------------------------------------");
            for(int i=8;i<numprod;i++)
            {
                painter.drawText(275,linha,"Produto: "+ui->tw_prod_v->item(i,0)->text());
                linha+=salto;
                painter.drawText(275,linha,"Quantidade: "+ui->tw_prod_v->item(i,1)->text());
                linha+=salto;
                painter.drawText(275,linha,"Valor Unitário: R$ "+ui->tw_prod_v->item(i,2)->text());
                linha+=salto;
                painter.drawText(275,linha,"Valor Total: R$ "+ui->tw_prod_v->item(i,3)->text());
                linha+=salto;
                painter.drawText(275,linha,"---------------------------------------");
                linha+=salto;
            }
        }
        linha=260;
        if(res>9)
        {
            painter.drawText(275,240,"---------------------------------------");
            for(int i=8;i<16;i++)
            {
                painter.drawText(275,linha,"Produto: "+ui->tw_prod_v->item(i,0)->text());
                linha+=salto;
                painter.drawText(275,linha,"Quantidade: "+ui->tw_prod_v->item(i,1)->text());
                linha+=salto;
                painter.drawText(275,linha,"Valor Unitário: R$ "+ui->tw_prod_v->item(i,2)->text());
                linha+=salto;
                painter.drawText(275,linha,"Valor Total: R$ "+ui->tw_prod_v->item(i,3)->text());
                linha+=salto;
                painter.drawText(275,linha,"---------------------------------------");
                linha+=salto;
            }
            linha=260;
            painter.drawText(525,240,"---------------------------------------");
            for(int i=16;i<numprod;i++)
            {
                painter.drawText(525,linha,"Produto: "+ui->tw_prod_v->item(i,0)->text());
                linha+=salto;
                painter.drawText(525,linha,"Quantidade: "+ui->tw_prod_v->item(i,1)->text());
                linha+=salto;
                painter.drawText(525,linha,"Valor Unitário: R$ "+ui->tw_prod_v->item(i,2)->text());
                linha+=salto;
                painter.drawText(525,linha,"Valor Total: R$ "+ui->tw_prod_v->item(i,3)->text());
                linha+=salto;
                painter.drawText(525,linha,"---------------------------------------");
                linha+=salto;
            }
        }
        }
    painter.end();
    QMessageBox::information(this, "PDF", "PDF Salvo com sucesso.");
    QDesktopServices::openUrl(QUrl("file:"+local));
    }
    else
        QMessageBox::warning(this, "ERRO", "Selecione um pedido primeiro.");
}

void gestao_vendas::on_btn_excluir_clicked()
{

    if(ui->tw_vendas->currentRow() < 0)
    {
        QMessageBox::warning(this, "ERRO", "Selecione uma venda primeiro");
    }
    else
    {
        QMessageBox::StandardButton op=QMessageBox::question(this, "Excluir", "Deseja mesmo excluir essa venda?", QMessageBox::Yes|QMessageBox::No);
        if(op==QMessageBox::Yes)
        {
            int linha=ui->tw_vendas->currentRow();
            int id=ui->tw_vendas->item(linha, 0)->text().toInt();
            QSqlQuery query;
            QSqlQuery query1;
            query.prepare("delete from tb_pedidos where id_venda="+QString::number(id));
            query1.prepare("delete from tb_produtosvendidos where id_venda="+QString::number(id));
            if(query.exec())
            {
                ui->tw_vendas->removeRow(linha);
                ui->tw_clientes->setRowCount(0);
                ui->tw_prod_v->setRowCount(0);
                if(query1.exec())
                {
                    QMessageBox::information(this, "", "Venda excluida");
                }
            }
            else
               QMessageBox::information(this, "", "Erro ao excluir venda");
        }
}
}

void gestao_vendas::on_btn_edit_clicked()
{
    if(ui->tw_vendas->currentRow() < 0)
    {
        QMessageBox::warning(this, "ERRO", "Selecione uma venda primeiro");
    }
    else
    {
        int linha = ui->tw_vendas->currentRow();
        int id=ui->tw_vendas->item(linha,0)->text().toInt();
        gestao_edit_v edit(this, id);
        edit.exec();
        ui->tw_vendas->setRowCount(0);
        ui->tw_clientes->setRowCount(0);
        ui->tw_prod_v->setRowCount(0);
        int cont=0;
        QSqlQuery query;
        query.prepare("select * from tb_pedidos order by id_venda desc");
        if(query.exec())
        {
        while(query.next())
        {
            ui->tw_vendas->insertRow(cont);
            ui->tw_vendas->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tw_vendas->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tw_vendas->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tw_vendas->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tw_vendas->setItem(cont,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tw_vendas->setItem(cont,5,new QTableWidgetItem(query.value(5).toString()));
            ui->tw_vendas->setItem(cont,6,new QTableWidgetItem(query.value(6).toString()));
            ui->tw_vendas->setItem(cont,7,new QTableWidgetItem(query.value(7).toString()));
            ui->tw_vendas->setItem(cont,8,new QTableWidgetItem(query.value(8).toString()));
            ui->tw_vendas->item(cont,0)->setTextAlignment(Qt::AlignCenter);
            ui->tw_vendas->item(cont,1)->setTextAlignment(Qt::AlignCenter);
            ui->tw_vendas->item(cont,2)->setTextAlignment(Qt::AlignCenter);
            ui->tw_vendas->item(cont,3)->setTextAlignment(Qt::AlignCenter);
            ui->tw_vendas->item(cont,4)->setTextAlignment(Qt::AlignCenter);
            ui->tw_vendas->item(cont,5)->setTextAlignment(Qt::AlignCenter);
            ui->tw_vendas->item(cont,6)->setTextAlignment(Qt::AlignCenter);
            ui->tw_vendas->item(cont,7)->setTextAlignment(Qt::AlignCenter);
            ui->tw_vendas->item(cont,8)->setTextAlignment(Qt::AlignCenter);
            cont++;
        }
        }
    }

}
