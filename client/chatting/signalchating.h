#ifndef SIGNALCHATING_H
#define SIGNALCHATING_H

#include <QWidget>

namespace Ui {
class signalChating;
}

class signalChating : public QWidget
{
    Q_OBJECT

public:
    explicit signalChating(QWidget *parent = nullptr);
    ~signalChating();
private:
    QColor color;

private slots:
    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_boldBtn_clicked(bool checked);

    void on_slopeBtn_clicked(bool checked);

    void on_underlineBtn_clicked(bool checked);

    void on_setColorBtn_clicked();

    void on_preserveBtn_clicked();

    void on_clearBtn_clicked();

    void on_sendBtn_clicked();

    void on_exitBtn_clicked();

private:
    Ui::signalChating *ui;
};

#endif // SIGNALCHATING_H
