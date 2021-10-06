#include "principal.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    principal w;
    w.show();
    w.setWindowIcon(QIcon("../TrabalhoFinal_MatheusAvila/imgs/logo.png"));
    return a.exec();
}
