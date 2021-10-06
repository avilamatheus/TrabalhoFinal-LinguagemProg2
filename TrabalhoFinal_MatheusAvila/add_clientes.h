#ifndef ADD_CLIENTES_H
#define ADD_CLIENTES_H

#include <QDialog>
#include <QMessageBox>
#include "Conexao.h"

namespace Ui {
class add_clientes;
}

class add_clientes : public QDialog
{
    Q_OBJECT

public:
    explicit add_clientes(QWidget *parent = nullptr);
    ~add_clientes();
    Conexao con;

private slots:
    void on_btn_gravar_clicked();

private:
    Ui::add_clientes *ui;
};

#endif // ADD_CLIENTES_H
