#ifndef CRAETGROUPNAME_H
#define CRAETGROUPNAME_H

#include <QWidget>

namespace Ui {
class craetGroupName;
}

class craetGroupName : public QWidget
{
    Q_OBJECT

public:
    explicit craetGroupName(QWidget *parent = nullptr,QVector<QString>name={});
    ~craetGroupName();
public:
    QVector<QString>choosedName;

private slots:
    void on_confirmBtn_clicked();

private:
    Ui::craetGroupName *ui;
};

#endif // CRAETGROUPNAME_H
