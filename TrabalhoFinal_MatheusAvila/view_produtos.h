#ifndef VIEW_PRODUTOS_H
#define VIEW_PRODUTOS_H

#include <QDialog>

namespace Ui {
class view_produtos;
}

class view_produtos : public QDialog
{
    Q_OBJECT

public:
    explicit view_produtos(QWidget *parent = nullptr);
    ~view_produtos();

private:
    Ui::view_produtos *ui;
};

#endif // VIEW_PRODUTOS_H
