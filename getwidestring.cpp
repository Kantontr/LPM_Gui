#include "getwidestring.h"
#include "ui_getwidestring.h"
#include "utility_v2.h"

GetWideString::GetWideString(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetWideString)
{
    ui->setupUi(this);

    if(lpm_config->cfg[5].value=="Dark"){
        this->setStyleSheet(ui_color_scheme_dark);;
   }

}

GetWideString::~GetWideString()
{
    delete ui;
}

void GetWideString::on_pushButton_clicked() //accept
{

    nazwa = ui->lineEdit->text().toStdString();
    login = ui->lineEdit_2->text().toStdString();
    password = ui->lineEdit_3->text().toStdString();
    GetWideString::close();
    return;

}

void GetWideString::on_pushButton_2_clicked() //cancel
{
    nazwa = "";
    login = "";
    password = "";

    GetWideString::close();
    return;
}

void GetWideString::on_lineEdit_editingFinished()
{

}

void GetWideString::on_lineEdit_2_editingFinished()
{

}


void GetWideString::on_lineEdit_3_editingFinished()
{

}


void GetWideString::on_lineEdit_2_cursorPositionChanged(int arg1, int arg2) // bo zjebalem
{

}

void GetWideString::on_lineEdit_3_cursorPositionChanged(int arg1, int arg2) //bo zjebalem
{

}

void GetWideString::on_lineEdit_destroyed()
{

}

void GetWideString::on_lineEdit_2_destroyed()
{

}

void GetWideString::on_lineEdit_3_destroyed()
{

}

void GetWideString::on_lineEdit_returnPressed()
{

}

void GetWideString::on_lineEdit_2_returnPressed()
{

}

void GetWideString::on_lineEdit_3_returnPressed()
{

}
