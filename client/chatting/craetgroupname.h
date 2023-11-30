#ifndef CRAETGROUPNAME_H
#define CRAETGROUPNAME_H
#include"mysocket.h"

#include <QWidget>

namespace Ui {
class craetGroupName;
}

class craetGroupName : public QWidget
{
    Q_OBJECT

public:
    explicit craetGroupName(QWidget *parent = nullptr,QStringList name={});
    ~craetGroupName();
public:
    QStringList choosedName;
    MySocket *mysock;

private slots:
    void on_confirmBtn_clicked();

private:
    Ui::craetGroupName *ui;
};

#endif // CRAETGROUPNAME_H
