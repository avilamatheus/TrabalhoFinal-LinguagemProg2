#ifndef GESTAO_EDIT_V_H
#define GESTAO_EDIT_V_H

#include <QDialog>
#include <QTableWidget>
namespace Ui {
class gestao_edit_v;
}

class gestao_edit_v : public QDialog
{
    Q_OBJECT

public:
    explicit gestao_edit_v(QWidget *parent = nullptr, int id=0);
    ~gestao_edit_v();
    int cont;
    void resetar();
    float total(QTableWidget *tw, int coluna);
    static QString g_prod, g_qtd, g_vu, g_vt;
    static bool alt;
    static bool add;

private slots:
    void on_pushButton_4_clicked();

    void on_txt_cod_returnPressed();

    void on_btn_excluir_clicked();

    void on_btn_editar_clicked();

    void on_btn_filtrar_clicked();

    void on_add_new_cliente_clicked();

    void on_btn_finalizar_clicked();

private:
    Ui::gestao_edit_v *ui;
};

#endif // GESTAO_EDIT_V_H
