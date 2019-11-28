#ifndef INSTALACJA_PROGRAMU_H
#define INSTALACJA_PROGRAMU_H

#include <QDialog>

namespace Ui {
class Instalacja_Programu;
}

class Instalacja_Programu : public QDialog
{
    Q_OBJECT

public:
    int instalacja_kod_bledu;
    explicit Instalacja_Programu(QWidget *parent = nullptr);
    ~Instalacja_Programu();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Instalacja_Programu *ui;
};

#endif // INSTALACJA_PROGRAMU_H
