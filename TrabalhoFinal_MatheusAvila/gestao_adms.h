#ifndef GESTAO_ADMS_H
#define GESTAO_ADMS_H

#include <QDialog>
#include "Conexao.h"
namespace Ui {
class gestao_adms;
}

class gestao_adms : public QDialog
{
    Q_OBJECT

public:
    explicit gestao_adms(QWidget *parent = nullptr);
    ~gestao_adms();
    Conexao con;
    static bool alt;

private slots:
    void on_btn_excluir_clicked();

    void on_btn_edit_clicked();

private:
    Ui::gestao_adms *ui;
};

#endif // GESTAO_ADMS_H
