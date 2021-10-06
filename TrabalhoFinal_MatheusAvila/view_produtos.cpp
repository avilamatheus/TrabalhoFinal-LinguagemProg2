#include "view_produtos.h"
#include "ui_view_produtos.h"
#include "novavenda.h"

view_produtos::view_produtos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::view_produtos)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("../TrabalhoFinal_MatheusAvila/imgs/logo.png"));
    setWindowTitle("Exibir Produtos - Scrap Sweet");
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

        QStringList cabecalhos={"ID", "Produto", "Valor"};
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

view_produtos::~view_produtos()
{
    delete ui;
}
