#ifndef ADD_FRIEND_H
#define ADD_FRIEND_H

#include <QWidget>

namespace Ui {
class Add_friend;
}

class Add_friend : public QWidget
{
    Q_OBJECT

public:
    explicit Add_friend(QWidget *parent = nullptr);
    ~Add_friend();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_btn_berify_clicked();

private:
    Ui::Add_friend *ui;
};

#endif // ADD_FRIEND_H
