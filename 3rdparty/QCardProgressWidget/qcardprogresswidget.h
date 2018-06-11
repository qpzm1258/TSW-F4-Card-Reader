#ifndef QCARDPROGRESSWIDGET_H
#define QCARDPROGRESSWIDGET_H
#include <QDialog>
#include <QLineEdit>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "qcardprogresswidget_global.h"

namespace Ui {
class QCardProgressWidget;
}

class QCARDPROGRESSWIDGETSHARED_EXPORT QCardProgressWidget : public QDialog
{
    Q_OBJECT

public:
    QCardProgressWidget(QWidget *parent = 0);
    void SetNameAndCode(QString _name,QString _code);
    ~QCardProgressWidget();
private:
    Ui::QCardProgressWidget *ui;
    void ChangeLineEditBGColor(QLineEdit* lineEdit,QString type);
    void DecodeJson(QString jsonStr);
    void DecodeBank(QString code);
    void DecodeCity(QString code);
    QString name;
    QString code;

public slots:
    void GetJsonZFromNetwork(QNetworkReply *reply);
};

#endif // QCARDPROGRESSWIDGET_H
