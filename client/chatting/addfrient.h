#ifndef ADDFRIENT_H
#define ADDFRIENT_H

#include <QWidget>

namespace Ui {
class addfrient;
}

class addfrient : public QWidget
{
    Q_OBJECT

public:
    explicit addfrient(QWidget *parent = nullptr);
    ~addfrient();

private slots:
    void on_backBtn_clicked();

    void on_cancelBtn_clicked();

    void on_confirmBtn_clicked();

private:
    Ui::addfrient *ui;
};

#endif // ADDFRIENT_H
