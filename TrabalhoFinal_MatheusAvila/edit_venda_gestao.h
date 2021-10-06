#ifndef EDIT_VENDA_GESTAO_H
#define EDIT_VENDA_GESTAO_H

#include <QDialog>

namespace Ui {
class edit_venda_gestao;
}

class edit_venda_gestao : public QDialog
{
    Q_OBJECT

public:
    explicit edit_venda_gestao(QWidget *parent = nullptr);
    ~edit_venda_gestao();

private slots:
    void on_btn_salvar_clicked();

    void on_btn_cancelar_clicked();

private:
    Ui::edit_venda_gestao *ui;
};

#endif // EDIT_VENDA_GESTAO_H
