#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "string"
#include <QPrinter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    int ReadIdCard();
    void ClearIDZone();
    void OpenPrintPreview();
    void printPreviewSlot(QPrinter *printerPixmap);
    void ReadSiCard();
    void ClearSIZone();
    void OpenSiCardStatus();

private:
    Ui::MainWindow *ui;
    int DecMesg(unsigned char *uchRespond, unsigned char * uchPHMsg, int len1, int len2,
                char * Name, std::string *Gender, char * Folk,
                char *BirthDay, char * Code, char * Address,
                char *Agency, char * ExpireStart, char* ExpireEnd);
    long PowerOnAndRestCpuCard();
    int CopyLicense();
    bool ConnectSQL();
};

#endif // MAINWINDOW_H
