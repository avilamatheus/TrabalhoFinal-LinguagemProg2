#ifndef NOVAVENDA_H
#define NOVAVENDA_H
#include "Conexao.h"
#include <QDialog>
#include <QMessageBox>
#include <QTableWidget>

namespace Ui {
class novavenda;
}

class novavenda : public QDialog
{
    Q_OBJECT

public:
    explicit novavenda(QWidget *parent = nullptr);
    ~novavenda();
    Conexao con;
    int cont;
    void resetar();
    float total(QTableWidget *tw, int coluna);
    static QString g_prod, g_qtd, g_vu, g_vt;
    static bool alt;
    static bool add;

private slots:
    void on_txt_cod_returnPressed();

    void on_btn_excluir_clicked();

    void on_btn_editar_clicked();

    void on_btn_finalizar_clicked();

    void on_btn_filtrar_clicked();

    void on_pushButton_4_clicked();

    void on_add_new_cliente_clicked();

private:
    Ui::novavenda *ui;
};

#endif // NOVAVENDA_H
