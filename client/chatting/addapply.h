#ifndef ADDAPPLY_H
#define ADDAPPLY_H

#include <QWidget>

namespace Ui {
class addApply;
}

class addApply : public QWidget
{
    Q_OBJECT

public:
    explicit addApply(QWidget *parent = nullptr);
    void editMessage(QString &name);
    ~addApply();

private slots:
    void on_backBtn_clicked();

    void on_cancelBtn_clicked();

    void on_confirmBtn_clicked();

private:
    Ui::addApply *ui;
};

#endif // ADDAPPLY_H
