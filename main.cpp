#include "mainwindow.h"
#include <QApplication>
#include <QSharedmemory.h>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QSharedMemory shared("NNSI Card Reader");
    if (shared.attach())
    {
        return 0;
    }
    shared.create(1);
    QApplication a(argc, argv);
    QTranslator m_qtTranslator;
    QTranslator qCardProgressWidgetTranslator;
    m_qtTranslator.load("zh_CN.qm");
    qCardProgressWidgetTranslator.load("QCardProgressWidget_zh.qm");
    a.installTranslator(&m_qtTranslator);
    a.installTranslator(&qCardProgressWidgetTranslator);
    MainWindow w;
    w.setWindowFlags(w.windowFlags() &~ Qt::WindowMaximizeButtonHint);
    w.show();

    return a.exec();
}
