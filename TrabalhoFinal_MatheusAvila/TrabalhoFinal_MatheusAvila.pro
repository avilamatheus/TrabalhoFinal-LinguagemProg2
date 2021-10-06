QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_adms.cpp \
    add_clientes.cpp \
    add_new.cpp \
    add_new_gestao.cpp \
    add_produto.cpp \
    edit_adm.cpp \
    edit_cli.cpp \
    edit_prod.cpp \
    edit_venda.cpp \
    edit_venda_gestao.cpp \
    ger_cli.cpp \
    ger_prod.cpp \
    gestao_adms.cpp \
    gestao_edit_v.cpp \
    gestao_vendas.cpp \
    login.cpp \
    main.cpp \
    novavenda.cpp \
    principal.cpp \
    vendas_clientes.cpp \
    view_produtos.cpp

HEADERS += \
    Conexao.h \
    add_adms.h \
    add_clientes.h \
    add_new.h \
    add_new_gestao.h \
    add_produto.h \
    edit_adm.h \
    edit_cli.h \
    edit_prod.h \
    edit_venda.h \
    edit_venda_gestao.h \
    ger_cli.h \
    ger_prod.h \
    gestao_adms.h \
    gestao_edit_v.h \
    gestao_vendas.h \
    login.h \
    novavenda.h \
    principal.h \
    vendas_clientes.h \
    view_produtos.h

FORMS += \
    add_adms.ui \
    add_clientes.ui \
    add_new.ui \
    add_new_gestao.ui \
    add_produto.ui \
    edit_adm.ui \
    edit_cli.ui \
    edit_prod.ui \
    edit_venda.ui \
    edit_venda_gestao.ui \
    ger_cli.ui \
    ger_prod.ui \
    gestao_adms.ui \
    gestao_edit_v.ui \
    gestao_vendas.ui \
    login.ui \
    novavenda.ui \
    principal.ui \
    vendas_clientes.ui \
    view_produtos.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
