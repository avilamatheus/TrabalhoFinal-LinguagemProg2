#ifndef ADD_ADMS_H
#define ADD_ADMS_H

#include <QDialog>
#include "Conexao.h"
namespace Ui {
class add_adms;
}

class add_adms : public QDialog
{
    Q_OBJECT

public:
    explicit add_adms(QWidget *parent = nullptr);
    ~add_adms();
    Conexao con;

private slots:
    void on_btn_salvar_clicked();

private:
    Ui::add_adms *ui;
};

#endif // ADD_ADMS_H
