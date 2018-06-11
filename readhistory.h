#ifndef READHISTORY_H
#define READHISTORY_H

#include <QDialog>

namespace Ui {
class ReadHistory;
}

class ReadHistory : public QDialog
{
    Q_OBJECT

public:
    explicit ReadHistory(QWidget *parent = 0);
    ~ReadHistory();

private:
    Ui::ReadHistory *ui;
};

#endif // READHISTORY_H
