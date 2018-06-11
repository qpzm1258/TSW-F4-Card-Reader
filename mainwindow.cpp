#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windows.h"
#include "pathdefine.h"
#include <QMessageBox>
#include <QFile>
#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>
#include <QRect>
#include <QPrintPreviewDialog>
#include <QSysInfo>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include <QFileDialog>
//#include "sicardstatus.h"
#include "3rdparty/QCardProgressWidget/qcardprogresswidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //QFile license("c:/termb.lic");
    //if(!license.exists())
    //{
    //   //QFile::copy(QCoreApplication::applicationDirPath()  + "/termb.lic","c:/termb.lic");
    //    if(!QFile::copy(QCoreApplication::applicationDirPath()  + "/termb.lic","c:/termb.lic"))
    //    {
    //        QMessageBox::critical(this,tr("Error"),tr("Can not copy the license file!"));
    //        this->close();
    //    }
    //}
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());  //这种最好。
    ConnectSQL();
    ui->mainToolBar->setHidden(true);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(ReadIdCard()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(ClearIDZone()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(OpenPrintPreview()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(ReadSiCard()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(ClearSIZone()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(OpenSiCardStatus()));
    //ui->lineEdit->setReadOnly(true);
    //ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
    ui->lineEdit_4->setReadOnly(true);
    ui->lineEdit_5->setReadOnly(true);
    ui->lineEdit_6->setReadOnly(true);
    ui->lineEdit_7->setReadOnly(true);
    ui->lineEdit_8->setReadOnly(true);
    ui->lineEdit_9->setReadOnly(true);
    ui->lineEdit_10->setReadOnly(true);
    ui->lineEdit_11->setReadOnly(true);
    ui->lineEdit_12->setReadOnly(true);
    ui->lineEdit_13->setReadOnly(true);
    ui->lineEdit_14->setReadOnly(true);
    ui->lineEdit_15->setReadOnly(true);
    ui->lineEdit_16->setReadOnly(true);
    ui->lineEdit_17->setReadOnly(true);
    ui->textEdit->setReadOnly(true);
    ui->textEdit_2->setReadOnly(true);
}

int MainWindow::DecMesg(unsigned char *uchRespond, unsigned char * uchPHMsg, int len1, int len2,
                char * Name, std::string *Gender, char * Folk,
                char *BirthDay, char * Code, char * Address,
                char *Agency, char * ExpireStart, char* ExpireEnd)
{
    const char * gfolk[] = {
        "汉",
        "蒙古",
        "回",
        "藏",
        "维吾尔",
        "苗",
        "彝",
        "壮",
        "布依",
        "朝鲜",
        "满",
        "侗",
        "瑶",
        "白",
        "土家",
        "哈尼",
        "哈萨克",
        "傣",
        "黎",
        "傈僳",
        "佤",
        "畲",
        "高山",
        "拉祜",
        "水",
        "东乡",
        "纳西",
        "景颇",
        "柯尔克孜",
        "土",
        "达斡尔",
        "仫佬",
        "羌",
        "布朗",
        "撒拉",
        "毛南",
        "仡佬",
        "锡伯",
        "阿昌",
        "普米",
        "塔吉克",
        "怒",
        "乌孜别克",
        "俄罗斯",
        "鄂温克",
        "德昂",
        "保安",
        "裕固",
        "京",
        "塔塔尔",
        "独龙",
        "鄂伦春",
        "赫哲",
        "门巴",
        "珞巴",
        "基诺",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "其他",
        "芒人",
        "摩梭人",
        "革家人",
        "穿青人",
        "入籍",
        "其他族"
    };

    //int type = 1;
    int i;

    //FILE * fp = fopen(filewlt, "wb+");
    //if (!fp)return 0;
    //if ((unsigned)len2 != fwrite((void *)uchPHMsg, 1, len2, fp)) {
    //    fclose(fp);
    //    return 0;
    //}
    //fclose(fp);
    //if (Dewlt(filewlt) != 1)
    //{
    //	return 0;
    //}
    unsigned char * pChar = uchRespond;
    //int offset = 0;

    memset(Name, 0, 31);
    WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pChar,
        15, Name, 30, NULL, NULL);
    for (i = 29; i>0; i--)
    {
        if (Name[i] == 0x20)
            Name[i] = 0x0;
        else
            break;
    }
    pChar += 30;
    //sex
    //memset(Gender, 0, 4 );
    if (*pChar == 0x31)
        *Gender = "男";
    else
        *Gender = "女";
    pChar += 2;
    //folk
    char _folk[4];
    memset(_folk, 0, 4);
    WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pChar, 2, _folk, 2, NULL, NULL);
    const char * pfolk = gfolk[atoi(_folk) - 1];
    memset(Folk, 0, 10);
    memcpy((void*)Folk, (void*)pfolk, strlen(pfolk));
    pChar += 4;

    //birth
    memset(BirthDay, 0, 9);
    WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pChar, 8, BirthDay, 8, NULL, NULL);
    pChar += 16;

    //addr
    memset(Address, 0, 71);
    WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pChar, 35, Address, 70, NULL, NULL);
    for (i = 0; i<69; i++)
    {
        if (Address[i] == 0x20)
            Address[i] = 0x0;
    }
    pChar += 70;

    memset(Code, 0, 19);
    WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pChar, 18, Code, 18, NULL, NULL);
    pChar += 36;

    memset(Agency, 0, 31);
    WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pChar, 15, Agency, 30, NULL, NULL);
    pChar += 30;

    //2005-7-18 针对有效期截至日期问题（有长期表示方式）
    memset(ExpireStart, 0, 9);
    WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pChar, 8, ExpireStart, 8, NULL, NULL);
    pChar += 16;

    //有效期截至日期
    memset(ExpireEnd, 0, 9);
    WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pChar, 8, ExpireEnd, 8, NULL, NULL);
    return 1;
}

int MainWindow::ReadIdCard()
{
    ClearIDZone();

    HINSTANCE HDLL2;
    HDLL2=LoadLibrary(TEXT("F4_MDS.dll"));

    if (HDLL2 == NULL)
    {
        QMessageBox::critical(this,tr("Error"),tr("Can not load F4_MDS.dll!"));
        return -1;
        //return -1;
    }
    char dev_Name[5] = { 'U','S','B' };
    long usb2 = 0;
    typedef long(WINAPI *open_com2)(char*);
    open_com2 GetReadHandle = (open_com2)GetProcAddress(HDLL2, "com_open");
    //GetReadHandle = (open_com2)GetProcAddress(HDLL2, "com_open");
    //if(GetReadHandle!= NULL)
    //{
    //    QMessageBox::critical(this,tr("Error"),tr("Can not load functions!"));
    //    return -1;
    //}

    usb2 = GetReadHandle(dev_Name);
        //long a =usb;
        //m_hDeviceHandle = (HANDLE)usb;
    if (usb2 < 0)
    {
        QMessageBox::critical(this,tr("Error"),tr("Can not connect card reader!"));
        return -1;
    }

    typedef long(WINAPI *GetSAMStatus)(long);
    GetSAMStatus getSAMStatus;
    getSAMStatus=(GetSAMStatus)GetProcAddress(HDLL2, "Syn_Find_IDCard");
    if(getSAMStatus(usb2)!=0)
    {
        QMessageBox::critical(this,tr("Error"),tr("Can not find id card!"));
        return -1;
    }

    typedef long(WINAPI *SelectIDCard)(long);
    SelectIDCard SelectCard;
    SelectCard = (SelectIDCard)GetProcAddress(HDLL2, "Syn_Select_IDCard");
    if(SelectCard(usb2)!=0)
    {
        QMessageBox::critical(this,tr("Error"),tr("Can not select id card!"));
        return -1;
    }

    typedef long(WINAPI *ReadCard)(long, unsigned char*, unsigned char*);
    ReadCard Reader = (ReadCard)GetProcAddress(HDLL2, "Syn_Read_BaseMsg");

    unsigned char pucCHMsg[256] = { 0x00 };
    unsigned char pucPHMsg[1024] = { 0x00 };

    //std::cout << Reader(usb2, pucCHMsg, pucPHMsg) << std::endl;
    //std::cout << pucCHMsg << std::endl;
    if (Reader(usb2, pucCHMsg, pucPHMsg) == 0)
    {
        char a[31];
        //char b[4];
        std::string b;
        char c[10];
        char d[9];
        char e[19];
        char f[71];
        char g[31];
        char h[9];
        char i[9];
        if(DecMesg(pucCHMsg, pucPHMsg, 256, 1024, a, &b, c, d, e, f, g, h, i)!=1)
        {
            QMessageBox::critical(this,tr("Error"),tr("Can not read the message!"));
            return -1;
        }

        long  (WINAPI *pSaveCardJPG)(unsigned char * pucCHMsg, unsigned int puiCHMsgLen, unsigned char * pucPHMsg, unsigned int  puiPHMsgLen, char * front, char *back);
        HINSTANCE hMyDll = LoadLibrary(TEXT("SavePhoto.dll"));
        pSaveCardJPG = (long (WINAPI *)(unsigned char * pucCHMsg, unsigned int 	puiCHMsgLen, unsigned char * pucPHMsg, unsigned int  puiPHMsgLen, char * front, char * back))GetProcAddress(hMyDll, "SaveCard2JPG");
        if (pSaveCardJPG != NULL)
        {
            char front[] = "1.jpg";
            char back[] = "2.jpg";
            char * p1 = front;
            char * p2 = back;
            if(pSaveCardJPG(pucCHMsg, 256, pucPHMsg, 1024, p1, p2)!=1)
            {
                QMessageBox::critical(this,tr("Error"),tr("Can not create image!"));
                return -1;
            }
            FreeLibrary(hMyDll);
        }
        ui->lineEdit->setText(QString::fromLocal8Bit(a).replace(" ",""));
        ui->lineEdit_2->setText(QString::fromLocal8Bit(e).replace(" ",""));
        ui->lineEdit_3->setText(QString::fromUtf8(b.data()).replace(" ",""));
        ui->lineEdit_4->setText(QString::fromStdString(c).replace(" ",""));
        ui->lineEdit_5->setText(QString::fromLocal8Bit(d).replace(" ",""));
        ui->textEdit->setText(QString::fromLocal8Bit(f).replace(" ",""));
        ui->textEdit_2->setText(QString::fromLocal8Bit(g).replace(" ",""));
        ui->lineEdit_8->setText(QString::fromLocal8Bit(h).replace(" ",""));
        ui->lineEdit_9->setText(QString::fromLocal8Bit(i).replace(" ",""));
        QFile transactorSFZfront(QCoreApplication::applicationDirPath()  + "/1.jpg");
        QFile transactorSFZback(QCoreApplication::applicationDirPath()  + "/2.jpg");

        if(transactorSFZfront.exists() && transactorSFZback.exists())
        {
            QPixmap front;

            QPixmap back;

            if(back.load(QCoreApplication::applicationDirPath()  + "/2.jpg")&&front.load(QCoreApplication::applicationDirPath()  + "/1.jpg"))
            {
                QPixmap* idImage=new QPixmap(front.width(),front.height()*2);
                QPainter  painter(idImage);
                painter.drawPixmap(0,0,front.width(),front.height(),front);
                painter.drawPixmap(0,back.height()+1,back.width(),back.height(),back);
                        //idImage->save("idimage.jpg");
                transactorSFZfront.remove();
                transactorSFZback.remove();
                ui->label->setPixmap(*idImage);
            }
        }
        QDateTime q_expdate=QDateTime::fromString(ui->lineEdit_9->text(),"yyyyMMdd");
        if(q_expdate.isValid())
        {
            QDateTime exp=q_expdate.addDays(1).addMSecs(-1);
            if(exp<QDateTime::currentDateTime())
            {
                QMessageBox::warning(this,tr("Warning"),tr("ID card expired!"),QMessageBox::Ok);
            }
        }

        QByteArray pucCHMsgBin=QByteArray::fromRawData(reinterpret_cast<char*>(pucCHMsg), 256);
        QByteArray pucPHMsgBin=QByteArray::fromRawData(reinterpret_cast<char*>(pucPHMsg), 1024);
        QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");

        database.setDatabaseName("History.db");
        database.setUserName("nnsi");
        database.setPassword("nnsi213");

        if(database.open())
        {
            QSqlQuery sql_query;
            bool ret = sql_query.exec("CREATE TABLE IF NOT EXISTS IDCard(\
            ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,\
            Name TEXT NOT NULL,\
            Code TEXT NOT NULL,\
            UchPHMsg BLOB NOT NULL,\
            uchRespond BLOB NOT NULL,\
            Time TEXT NOT NULL\
            );");

            QSqlQuery query(database);
            QString strDt = QDateTime::currentDateTime().toString(DATETIME_FORMAT);
            QString strSql = "INSERT INTO IDCard (Name,Code,UchPHMsg,uchRespond,Time) VALUES (?,?,?,?,?)";
            query.prepare(strSql);
            query.bindValue(0, QString::fromLocal8Bit(a).replace(" ",""));
            query.bindValue(1, QString::fromLocal8Bit(e).replace(" ",""));
            query.bindValue(2, pucPHMsgBin,QSql::Binary);
            query.bindValue(3, pucCHMsgBin,QSql::Binary);
            query.bindValue(4,strDt);
            ret = query.exec();

            if(!ret)
            {
                QMessageBox::critical(this,tr("Error"),tr("Can not create tables!")+database.lastError().text());
                database.close();
                return ret;
            }
            database.close();
            return true;
        }
        else
        {
             QMessageBox::critical(this,tr("Error"),tr("Can not connect database!"));
             return false;
        }
    }
    else
    {
        QMessageBox::critical(this,tr("Error"),tr("Can not read the ID card!"));
        return -1;
    }
    return 0;
}

void MainWindow::ClearIDZone()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    ui->label->clear();
}

void MainWindow::OpenPrintPreview()
{

    if(ui->label->pixmap()==nullptr||ui->label->pixmap()->isNull())
    {
        QMessageBox::critical(this,tr("Error"),tr("Please read the id card first!"));
        return;
    }
    if(QSysInfo::productVersion().contains("xp",Qt::CaseInsensitive))
    {
        if(QMessageBox::information(this,tr("Error"),tr("Can not print the ID card image in Windows XP!Do you save this image?"),QMessageBox::Ok|QMessageBox::Cancel)==QMessageBox::Ok)
        {
            QString fileName;
            fileName = QFileDialog::getSaveFileName(this,
                tr("Save Image"), "", tr("Image File (*.jpg)"));

            if (!fileName.isNull())
            {
                   ui->label->pixmap()->save(fileName,"jpg");             //fileName是文件名
            }
        }


        return;
    }
    QPrinter printer(QPrinter::HighResolution);
        //自定义纸张大小
    printer.setPageSize(QPrinter::Custom);  /* 数据显示至预览界面 */
    //printer.setPaperSize(QSize(328,408),QPrinter::Point);
    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, SIGNAL(paintRequested(QPrinter *)),this,SLOT(printPreviewSlot(QPrinter *)));
    preview.exec(); /* 等待预览界面退出 */
}

void MainWindow::printPreviewSlot(QPrinter *printerPixmap)
{
    printerPixmap->setOrientation(QPrinter::Portrait);
    //获取界面的图片
    QPixmap pixmap = ui->label->pixmap()->scaled(328*6.2,408*6.2);
    QPainter painterPixmap(this);
    painterPixmap.begin(printerPixmap);
    //QRect rect = painterPixmap.viewport();
    //int x = rect.width() / pixmap.width();
    //int y = rect.height() / pixmap.height();
    //painterPixmap.scale(x, y);
    painterPixmap.drawPixmap(0, 0, pixmap);
    painterPixmap.end();
}

void MainWindow::ReadSiCard()
{
    ClearSIZone();
    HINSTANCE hinstance;
    //BOOL fFreeResult = false;
    hinstance = LoadLibrary(TEXT("SICARD.dll"));
    if (hinstance == NULL)
    {
        QMessageBox::critical(this,tr("Error"),tr("Can not load SICARD.dll!"));
        return;
        //return -1;
    }

    if(PowerOnAndRestCpuCard()!=0)
    {
        FreeLibrary(hinstance);
        return;
    }

    typedef long (WINAPI *ReadSiCard)(bool bCheckPin, char* pRegion, char* pCardtype, char* pVersion,
        char* Issueid, char* Issuedate, char* expdate, char* pCardno,
        char* pIdno, char* pName, char* pSex, char* nation, char* birthaddress,
        char* pBirth, char* pErrmsg);
    ReadSiCard GetSiCard;
    //bool fRunTimeLinkSucess = false;
    GetSiCard = (ReadSiCard)GetProcAddress(hinstance, "ICC_Reader_GetSICardInfo");

    if (GetSiCard == NULL)
    {
        QMessageBox::critical(this,tr("Error"),tr("Can not load functions!"));
        FreeLibrary(hinstance);
        return;
    }

     bool bCheckPin = false;
     char pRegion[6];
     char pCardtype[25];
     char pVersion[10];
     char Issueid[50];
     char Issuedate[25];
     char expdate[20];
     char pCardno[10];
     char pIdno[25];
     char pName[10];
     char pSex[10];
     char nation[10];
     char birthaddress[255];
     char pBirth[255];
     char pErrmsg[255];

     if(0!=GetSiCard(bCheckPin, pRegion, pCardtype, pVersion, Issueid,
                 Issuedate, expdate, pCardno, pIdno, pName, pSex, nation, birthaddress,
                 pBirth, pErrmsg))
     {
         QMessageBox::critical(this,tr("Error"),tr("Can not read the SI card!"));
         FreeLibrary(hinstance);
         return;
     }

     ui->lineEdit_6->setText(QString::fromLocal8Bit(pName).replace(" ",""));
     ui->lineEdit_15->setText(QString::fromLocal8Bit(pIdno).replace(" ",""));
     ui->lineEdit_16->setText(QString::fromLocal8Bit(pSex).replace(" ",""));
     ui->lineEdit_14->setText(QString::fromLocal8Bit(nation).replace(" ",""));
     ui->lineEdit_17->setText(QString::fromLocal8Bit(pCardno).replace(" ",""));
     ui->lineEdit_7->setText(QString::fromLocal8Bit(pRegion).replace(" ","").left(6));
     ui->lineEdit_10->setText(QString::fromLocal8Bit(pCardtype).replace(" ",""));
     ui->lineEdit_11->setText(QString::fromLocal8Bit(pVersion).replace(" ",""));
     ui->lineEdit_12->setText(QString::fromLocal8Bit(Issuedate).replace(" ",""));
     ui->lineEdit_13->setText(QString::fromLocal8Bit(expdate).replace(" ",""));

     QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");

     database.setDatabaseName("History.db");
     database.setUserName("nnsi");
     database.setPassword("nnsi213");

     if(database.open())
     {
         QSqlQuery sql_query;
         bool ret = sql_query.exec("CREATE TABLE IF NOT EXISTS SICard(\
                 ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,\
                 Name TEXT NOT NULL,\
                 Code TEXT NOT NULL,\
                 CardNo TEXT NOT NULL,\
                 Region TEXT,\
                 CardType TEXT,\
                 Version TEXT,\
                 ValidFrom TEXT,\
                 ExpDate TEXT,\
                 Sex TEXT,\
                 Nation TEXT,\
                 Time TEXT NOT NULL\
                 );");

         QSqlQuery query(database);
         QString strDt = QDateTime::currentDateTime().toString(DATETIME_FORMAT);
         QString strSql = "INSERT INTO SICard (Name,Code,CardNo,Region,CardType,Version,ValidFrom,ExpDate,Sex,Nation,Time) VALUES (?,?,?,?,?,?,?,?,?,?,?)";
         query.prepare(strSql);
         query.bindValue(0, QString::fromLocal8Bit(pName).replace(" ",""));
         query.bindValue(1, QString::fromLocal8Bit(pIdno).replace(" ",""));
         query.bindValue(2, QString::fromLocal8Bit(pCardno).replace(" ",""));
         query.bindValue(3, QString::fromLocal8Bit(pRegion).replace(" ","").left(6));
         query.bindValue(4, QString::fromLocal8Bit(pCardtype).replace(" ",""));
         query.bindValue(5, QString::fromLocal8Bit(pVersion).replace(" ",""));
         query.bindValue(6, QString::fromLocal8Bit(Issuedate).replace(" ",""));
         query.bindValue(7, QString::fromLocal8Bit(expdate).replace(" ",""));
         query.bindValue(8, QString::fromLocal8Bit(pSex).replace(" ",""));
         query.bindValue(9, QString::fromLocal8Bit(nation).replace(" ",""));
         query.bindValue(10,strDt);
         ret = query.exec();

         if(!ret)
         {
             QMessageBox::critical(this,tr("Error"),tr("Can not create tables!")+database.lastError().text());
             database.close();
             return;
         }
         database.close();
         return;
     }
     else
     {
          QMessageBox::critical(this,tr("Error"),tr("Can not connect database!"));
          return;
     }
}

long MainWindow::PowerOnAndRestCpuCard()
{
    char dev_Name[5] = { 'U','S','B' };
    // HINSTANCE HDLL;
    HINSTANCE HDLL2 = LoadLibraryA("F4_MDS.dll");
    long usb2 = 0;
    typedef long(WINAPI *open_com2)(char*);
    if (HDLL2 == NULL)
    {
        QMessageBox::critical(this,tr("Error"),tr("Can not load F4_MDS.dll!"));
        return -2;
        //return -1;
    }
    open_com2 ICC_Reader_Open2;
    ICC_Reader_Open2 = (open_com2)GetProcAddress(HDLL2, "ICC_Reader_Open");
    usb2 = ICC_Reader_Open2(dev_Name);
    //long a =usb;
    //m_hDeviceHandle = (HANDLE)usb;
    if (usb2 < 0)
    {
        QMessageBox::critical(this,tr("Error"),tr("Can not connect card reader!"));
        return -3;
        //return IFD_UnConnected;
    }
    else
    {
        typedef long(WINAPI *power_on2)(long, unsigned char, unsigned char*);
        typedef long(WINAPI *logic_select)(HANDLE, unsigned char);
        long len, ret1;
        unsigned char buf1[100];
        power_on2  ICC_Reader_PowerOn2;
        ICC_Reader_PowerOn2 = (power_on2)GetProcAddress(HDLL2, "ICC_Reader_PowerOn");
        len = ICC_Reader_PowerOn2(usb2, 0x01, buf1);
        logic_select   Logic_Type_Select1;
        Logic_Type_Select1 = (logic_select)GetProcAddress(HDLL2, "icc_type_set");
        if (len == -1)
        {

            ret1 = Logic_Type_Select1((HANDLE)usb2, 0x02);
            if (ret1 == -2)
            {
                QMessageBox::critical(this,tr("Error"),tr("Can not find the SI card!"));
                return -4;
            }
        }
        return 0;
    }
}

void MainWindow::ClearSIZone()
{
    ui->lineEdit_6->clear();
    ui->lineEdit_15->clear();
    ui->lineEdit_16->clear();
    ui->lineEdit_14->clear();
    ui->lineEdit_17->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_10->clear();
    ui->lineEdit_11->clear();
    ui->lineEdit_12->clear();
    ui->lineEdit_13->clear();
}

bool MainWindow::ConnectSQL()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");

    database.setDatabaseName("History.db");
    database.setUserName("nnsi");
    database.setPassword("nnsi213");

    if(database.open())
    {
        QSqlQuery sql_query;
        bool ret = sql_query.exec("CREATE TABLE IF NOT EXISTS IDCard(\
        ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,\
        Name TEXT NOT NULL,\
        Code TEXT NOT NULL,\
        UchPHMsg BLOB NOT NULL,\
        uchRespond BLOB NOT NULL,\
        Time TEXT NOT NULL\
        );");

        ret = sql_query.exec("CREATE TABLE IF NOT EXISTS SICard(\
                ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,\
                Name TEXT NOT NULL,\
                Code TEXT NOT NULL,\
                CardNo TEXT NOT NULL,\
                Region TEXT,\
                CardType TEXT,\
                Version TEXT,\
                ValidFrom TEXT,\
                ExpDate TEXT,\
                Sex TEXT,\
                Nation TEXT,\
                Time TEXT NOT NULL\
                );");


        if(!ret)
        {
            QMessageBox::critical(this,tr("Error"),tr("Can not create tables!")+database.lastError().text());
            database.close();
            return ret;
        }
        database.close();
        return true;
    }
    else
    {
         QMessageBox::critical(this,tr("Error"),tr("Can not connect database!"));
         return false;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenSiCardStatus()
{
    if(ui->lineEdit->text().isEmpty()||ui->lineEdit_2->text().isEmpty()
            ||ui->lineEdit->text().isNull()||ui->lineEdit_2->text().isNull())
    {
        QMessageBox::critical(this,tr("Error"),tr("Please read the id card first!"));
        return;
    }
    //SiCardStatus *dlg=new SiCardStatus();
    QCardProgressWidget *dlg=new QCardProgressWidget();
    dlg->SetNameAndCode(ui->lineEdit->text(),ui->lineEdit_2->text());

    dlg->exec();
}
