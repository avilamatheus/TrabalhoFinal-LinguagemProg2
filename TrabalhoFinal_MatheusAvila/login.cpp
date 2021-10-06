#include "login.h"
#include "ui_login.h"
#include "principal.h"
#include <QMessageBox>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setWindowTitle("Login - Scrap Sweet");
    setWindowIcon(QIcon("../TrabalhoFinal_MatheusAvila/imgs/logo.png"));
}

login::~login()
{
    delete ui;
}

void login::on_btn_logar_clicked()
{
    if(!con.abrir())
    {
        QMessageBox::warning(this, "ERRO", "Erro ao abrir banco de dados");
    }
    else
     {
        QString username,senha;
        username=ui->txt_username->text();
        senha=ui->txt_senha->text();
        QSqlQuery query;
        query.prepare("select * from tb_admins where username_adm='"+username+"' and senha_adm='"+senha+"'");
        query.exec();
        if(query.first())
        {
            if(query.value(1).toString()!="")
            {
                principal::logado=true;
                principal::nome_adm=query.value(1).toString();
                principal::id_adm=query.value(0).toInt();
                QMessageBox::information(this, "LOGIN", "Login realizado com sucesso");
                con.fechar();
                close();
            }
        }
        else
           QMessageBox::warning(this, "ERRO", "Username e Senha incorretos");
       }
}

void login::on_btn_cancelar_clicked()
{
    principal::logado=false;
    close();
}
