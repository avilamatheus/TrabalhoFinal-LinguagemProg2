#include "add_adms.h"
#include "ui_add_adms.h"
#include <QMessageBox>
add_adms::add_adms(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_adms)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("../TrabalhoFinal_MatheusAvila/imgs/logo.png"));
    setWindowTitle("Adicionar Novo Admin - Scrap Sweet");
    ui->txt_nome->setFocus();
    con.abrir();
}

add_adms::~add_adms()
{
    delete ui;
    con.fechar();
}

void add_adms::on_btn_salvar_clicked()
{
    QString nome=ui->txt_nome->text();
    QString user=ui->txt_user->text();
    QString senha=ui->txt_senha->text();
    bool samename=false;
    bool sameuser=false;
    if(nome == "" || user == "" || senha == "")
        QMessageBox::warning(this, "ERRO", "Por favor preencha todos os campos.");
    else
    {
    if(nome=="Admin" || nome=="admin")
    {
        QMessageBox::warning(this, "ERRO", "Esse nome é reservado para o Admin principal.");
    }
    else
    {
    if(user=="Admin" || user=="admin")
            QMessageBox::warning(this, "ERRO", "Esse username é reservado para o Admin principal.");
    else
    {
    QSqlQuery query;
    query.prepare("select * from tb_admins where nome_adm='"+nome+"'");
    query.exec();
    if(query.first())
       samename=true;
    QSqlQuery query1;
    query1.prepare("select * from tb_admins where username_adm='"+user+"'");
    query1.exec();
    if(query1.first())
             sameuser=true;
    if(samename == false && sameuser == false)
    {
        QSqlQuery query;
        query.prepare("insert into tb_admins (nome_adm,username_adm,senha_adm) values('"+nome+"','"+user+"','"+senha+"')");
        if(!query.exec())
        {
            QMessageBox::warning(this, "ERRO", "Erro ao inserir Admin");
        }
        else
        {
            QMessageBox::information(this, "Admin", "Admin inserido com sucesso");
            this->close();
        }
    }
    else
        QMessageBox::warning(this, "ERRO", "Já existe um adm com esse nome e username");
}
}
}
}
