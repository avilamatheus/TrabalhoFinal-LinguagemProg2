#include "gestao_adms.h"
#include "ui_gestao_adms.h"
#include <QMessageBox>
#include "principal.h"
#include "edit_adm.h"

bool gestao_adms::alt;

gestao_adms::gestao_adms(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestao_adms)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("../TrabalhoFinal_MatheusAvila/imgs/logo.png"));
    setWindowTitle("Gerenciar Administradores - Scrap Sweet");
    if(principal::id_adm==1)
    {
        ui->btn_excluir->setEnabled(true);
    }
    else
        ui->btn_excluir->setEnabled(false);
    con.abrir();
    if(!con.abrir())
    {
        QMessageBox::warning(this, "ERRO", "Erro ao abrir o banco de dados");
    }
    else
    {
    QSqlQuery query;
    query.prepare("select * from tb_admins order by nome_adm");
    if(query.exec())
    {
        int cont=0;
        ui->tw_adm->setColumnCount(3);
        while(query.next())
        {
            ui->tw_adm->insertRow(cont);
            ui->tw_adm->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tw_adm->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tw_adm->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tw_adm->item(cont,0)->setTextAlignment(Qt::AlignCenter);
            ui->tw_adm->item(cont,1)->setTextAlignment(Qt::AlignCenter);
            ui->tw_adm->item(cont,2)->setTextAlignment(Qt::AlignCenter);
            ui->tw_adm->setRowHeight(cont, 20);
            cont++;
        }
        ui->tw_adm->setColumnWidth(0, 5);
        ui->tw_adm->setColumnWidth(1, 200);
        ui->tw_adm->setColumnWidth(2, 350);
        QStringList cabecalhos={"ID", "Nome", "Username"};
        ui->tw_adm->setHorizontalHeaderLabels(cabecalhos);
        ui->tw_adm->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tw_adm->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_adm->verticalHeader()->setVisible(false);
        ui->tw_adm->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tw_adm->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    }
    else
        QMessageBox::warning(this, "ERRO", "Erro ao listar a tabela de administradores");
    }
}

gestao_adms::~gestao_adms()
{
    delete ui;
    con.fechar();
}


void gestao_adms::on_btn_excluir_clicked()
{
    if(ui->tw_adm->currentRow() < 0)
    {
        QMessageBox::warning(this, "ERRO", "Selecione um admin primeiro");
    }
    else
    {
            int linha=ui->tw_adm->currentRow();
            int id=ui->tw_adm->item(linha, 0)->text().toInt();
             QMessageBox::StandardButton op=QMessageBox::question(this, "Excluir", "Deseja mesmo excluir esse admin?", QMessageBox::Yes|QMessageBox::No);
             if(op==QMessageBox::Yes)
            {
            QSqlQuery query;
            query.prepare("delete from tb_admins where id_adm="+QString::number(id));
            if(query.exec())
            {
                ui->tw_adm->removeRow(linha);
                QMessageBox::information(this, "", "Admin excluido com sucesso");

            }
            else
                QMessageBox::warning(this, "ERRO", "Erro ao excluir Admin");
            }
      }
 }

void gestao_adms::on_btn_edit_clicked()
{
    if(ui->tw_adm->currentRow() < 0)
    {
        QMessageBox::warning(this, "ERRO", "Selecione um admin primeiro");
    }
    else
    {
        bool same;
        bool adm;
        int linha=ui->tw_adm->currentRow();
        int id=ui->tw_adm->item(linha, 0)->text().toInt();
        int id_adm = principal::id_adm;
        if(id == id_adm)
            same=true;
        else
            same=false;
        if(id_adm==1)
            adm=true;
        else
            adm=false;
        if(same || adm)
        {
            edit_adm f_edit_adm(this, id);
            f_edit_adm.exec();
            if(alt)
            {
            QSqlQuery query;
            query.prepare("select * from tb_admins order by nome_adm");
            if(query.exec())
            {
                while(ui->tw_adm->rowCount() > 0)
                {
                    ui->tw_adm->removeRow(0);
                }
                int cont=0;
                ui->tw_adm->setColumnCount(3);
                while(query.next())
                {
                    ui->tw_adm->insertRow(cont);
                    ui->tw_adm->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
                    ui->tw_adm->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
                    ui->tw_adm->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
                    ui->tw_adm->item(cont,0)->setTextAlignment(Qt::AlignCenter);
                    ui->tw_adm->item(cont,1)->setTextAlignment(Qt::AlignCenter);
                    ui->tw_adm->item(cont,2)->setTextAlignment(Qt::AlignCenter);
                    ui->tw_adm->setRowHeight(cont, 20);
                    cont++;
                }
            }
            }
        }
        else
            QMessageBox::warning(this, "ERRO", "Você não pode editar outros Adms");
    }
}
