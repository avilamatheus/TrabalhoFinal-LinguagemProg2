#ifndef ADD_PRODUTO_H
#define ADD_PRODUTO_H
#include "Conexao.h"
#include <QDialog>
#include <QMessageBox>

namespace Ui {
class add_produto;
}

class add_produto : public QDialog
{
    Q_OBJECT

public:
    explicit add_produto(QWidget *parent = nullptr);
    ~add_produto();
    Conexao con;

private slots:
    void on_btn_salvar_clicked();

    void on_btn_cancelar_clicked();

private:
    Ui::add_produto *ui;
};

#endif // ADD_PRODUTO_H
