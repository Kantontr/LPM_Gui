#ifndef GETWIDESTRING_H
#define GETWIDESTRING_H

#include <QDialog>

namespace Ui {
class GetWideString;
}

class GetWideString : public QDialog
{
    Q_OBJECT

public:
    std::string nazwa;
    std::string login;
    std::string password;
    explicit GetWideString(QWidget *parent = nullptr);
    ~GetWideString();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_3_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_3_editingFinished();

    void on_pushButton_2_clicked();

    void on_lineEdit_2_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_destroyed();

    void on_lineEdit_2_destroyed();

    void on_lineEdit_3_destroyed();

    void on_lineEdit_returnPressed();

    void on_lineEdit_2_returnPressed();

    void on_lineEdit_3_returnPressed();

private:
    Ui::GetWideString *ui;
};

#endif // GETWIDESTRING_H
