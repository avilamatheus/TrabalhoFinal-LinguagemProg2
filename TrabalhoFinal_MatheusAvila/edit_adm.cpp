#include "edit_adm.h"
#include "ui_edit_adm.h"
#include "Conexao.h"
#include <QMessageBox>
#include "gestao_adms.h"
#include "principal.h"

static int id_adm;

QString nome_original;
QString user_original;

edit_adm::edit_adm(QWidget *parent, int id) :
    QDialog(parent),
    ui(new Ui::edit_adm)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("../TrabalhoFinal_MatheusAvila/imgs/logo.png"));
    setWindowTitle("Editar Adm - Scrap Sweet");
    id_adm = id;
    QSqlQuery query;
    query.prepare("select * from tb_admins where id_adm="+QString::number(id_adm));
    if(query.exec())
    {
        query.first();
        ui->txt_nome->setText(query.value(1).toString());
        ui->txt_user->setText(query.value(2).toString());
        ui->txt_senha->setText(query.value(3).toString());
        nome_original = query.value(1).toString();
        user_original = query.value(2).toString();
    }

}

edit_adm::~edit_adm()
{
    delete ui;
}

void edit_adm::on_btn_salvar_clicked()
{
    QString senha=ui->txt_senha->text();
    if(id_adm==1)
    {
        QSqlQuery query;
        query.prepare("update tb_admins set senha_adm='"+senha+"' where id_adm="+QString::number(id_adm));
        if(query.exec())
        {
            this->close();
            gestao_adms::alt=true;
        }
    }
    else
    {
    if(senha == "")
    {
        QMessageBox::warning(this, "ERRO", "Preencha todos os campos antes de editar o adm");
    }
    else
    {
            QSqlQuery query;
            query.prepare("update tb_admins set senha_adm='"+senha+"' where id_adm="+QString::number(id_adm));
            if(query.exec())
            {
                this->close();
                gestao_adms::alt=true;
            }
            else
                QMessageBox::warning(this, "ERRO", "Erro ao atualizar dados do admin");
        }
    }
}
