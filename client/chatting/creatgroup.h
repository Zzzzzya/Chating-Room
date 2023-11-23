#ifndef CREATGROUP_H
#define CREATGROUP_H

#include <QWidget>
#include<QVector>
#include<QListWidgetItem>

namespace Ui {
class creatGroup;
}

class creatGroup : public QWidget
{
    Q_OBJECT

public:
    explicit creatGroup(QWidget *parent = nullptr);
    void showMessage(QVector<QString> &onlineperson);
    void showNum(int cnt);
    void clickedName(int cnt);
    QVector<QString>choosedName;
    QVector<QListWidgetItem*>selectedItem;
    ~creatGroup();

private slots:
    void on_backBtn_clicked();

    void on_creatBtn_clicked();

private:
    Ui::creatGroup *ui;
};

#endif // CREATGROUP_H
