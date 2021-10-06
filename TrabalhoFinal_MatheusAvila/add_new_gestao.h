#ifndef ADD_NEW_GESTAO_H
#define ADD_NEW_GESTAO_H

#include <QDialog>

namespace Ui {
class add_new_gestao;
}

class add_new_gestao : public QDialog
{
    Q_OBJECT

public:
    explicit add_new_gestao(QWidget *parent = nullptr);
    ~add_new_gestao();

private slots:
    void on_btn_salvar_clicked();

private:
    Ui::add_new_gestao *ui;
};

#endif // ADD_NEW_GESTAO_H
