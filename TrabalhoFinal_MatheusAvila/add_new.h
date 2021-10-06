#ifndef ADD_NEW_H
#define ADD_NEW_H

#include <QDialog>

namespace Ui {
class add_new;
}

class add_new : public QDialog
{
    Q_OBJECT

public:
    explicit add_new(QWidget *parent = nullptr);
    ~add_new();

private slots:
    void on_btn_salvar_clicked();

private:
    Ui::add_new *ui;
};

#endif // ADD_NEW_H
