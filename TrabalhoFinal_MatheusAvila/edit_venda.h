#ifndef EDIT_VENDA_H
#define EDIT_VENDA_H

#include <QDialog>

namespace Ui {
class edit_venda;
}

class edit_venda : public QDialog
{
    Q_OBJECT

public:
    explicit edit_venda(QWidget *parent = nullptr);
    ~edit_venda();

private slots:
    void on_btn_salvar_clicked();

    void on_btn_cancelar_clicked();

private:
    Ui::edit_venda *ui;
};

#endif // EDIT_VENDA_H
