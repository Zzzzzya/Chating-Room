#ifndef SET_GROUP_H
#define SET_GROUP_H

#include <QWidget>

namespace Ui {
class Set_group;
}

class Set_group : public QWidget
{
    Q_OBJECT

public:
    explicit Set_group(QWidget *parent = nullptr);
    ~Set_group();

private slots:
    void on_btn_group_clicked();

    void on_btn_setgroup_clicked();

private:
    Ui::Set_group *ui;
};

#endif // SET_GROUP_H
