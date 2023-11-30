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
    explicit craetGroupName(QWidget *parent = nullptr,QStringList name={});
    ~craetGroupName();
public:
    QStringList choosedName;

private slots:
    void on_confirmBtn_clicked();

signals:
    void confirmBtnClicked(const QString &my_name,const QString &groupName,const QStringList &name);

private:
    Ui::craetGroupName *ui;
};

#endif // CRAETGROUPNAME_H
