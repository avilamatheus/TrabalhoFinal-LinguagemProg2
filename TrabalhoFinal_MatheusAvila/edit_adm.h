#ifndef EDIT_ADM_H
#define EDIT_ADM_H

#include <QDialog>

namespace Ui {
class edit_adm;
}

class edit_adm : public QDialog
{
    Q_OBJECT

public:
    explicit edit_adm(QWidget *parent = nullptr, int id=0);
    ~edit_adm();

private slots:
    void on_btn_salvar_clicked();

private:
    Ui::edit_adm *ui;
};

#endif // EDIT_ADM_H
