#ifndef GROUPCHATTING_H
#define GROUPCHATTING_H

#include <QWidget>

namespace Ui {
class groupChatting;
}

class groupChatting : public QWidget
{
    Q_OBJECT

public:
    explicit groupChatting(QWidget *parent = nullptr);
    void setTableWidget(QVector<QString>&groupPerson,QVector<int>&groupPersonIsOnline);
    QString GName;
    ~groupChatting();
private:
    QColor color;

private slots:
    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_boldBtn_clicked(bool checked);

    void on_slopeBtn_clicked(bool checked);

    void on_underlineBtn_clicked(bool checked);

    void on_setColorBtn_clicked();

    void on_preserveBtn_clicked();

    void on_clearBtn_clicked();

    void on_sendBtn_clicked();

    void on_exitBtn_clicked();

private:
    Ui::groupChatting *ui;
};

#endif // GROUPCHATTING_H
