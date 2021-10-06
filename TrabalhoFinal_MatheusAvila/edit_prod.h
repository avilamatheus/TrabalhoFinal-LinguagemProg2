#ifndef EDIT_PROD_H
#define EDIT_PROD_H

#include <QDialog>

namespace Ui {
class edit_prod;
}

class edit_prod : public QDialog
{
    Q_OBJECT

public:
    explicit edit_prod(QWidget *parent = nullptr, int id=0);
    ~edit_prod();

private slots:
    void on_btn_gravar_clicked();

private:
    Ui::edit_prod *ui;
};

#endif // EDIT_PROD_H
