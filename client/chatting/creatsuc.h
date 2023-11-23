#ifndef CREATSUC_H
#define CREATSUC_H

#include <QWidget>

namespace Ui {
class creatSuc;
}

class creatSuc : public QWidget
{
    Q_OBJECT

public:
    explicit creatSuc(QWidget *parent = nullptr);
    ~creatSuc();

private slots:
    void on_backBtn_clicked();

private:
    Ui::creatSuc *ui;
};

#endif // CREATSUC_H
