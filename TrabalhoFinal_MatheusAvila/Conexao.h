#ifndef CONEXAO_H
#define CONEXAO_H
#include <QtSql>

class Conexao
{
public:
    QSqlDatabase bancoDeDados;
    Conexao()
    {
        bancoDeDados=QSqlDatabase::addDatabase("QSQLITE");
    }
    void fechar()
    {
        bancoDeDados.removeDatabase("QSQLITE");
        bancoDeDados.close();
    }
    bool abrir()
    {
        bancoDeDados.setDatabaseName("../TrabalhoFinal_MatheusAvila/database/database_g.db");
        if(!bancoDeDados.open())
        {
            return false;
        }
        else
        {
            bancoDeDados.open();
            return true;
        }
    }
    bool aberto()
    {
        if(bancoDeDados.isOpen())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
   };

#endif // CONEXAO_H
