#ifndef CREATGROUP_H
#define CREATGROUP_H

#include <QWidget>

namespace Ui {
class creatGroup;
}

class creatGroup : public QWidget
{
    Q_OBJECT

public:
    explicit creatGroup(QWidget *parent = nullptr);
    ~creatGroup();

private slots:
    void on_backBtn_clicked();

    void on_creatBtn_clicked();

private:
    Ui::creatGroup *ui;
};

#endif // CREATGROUP_H
