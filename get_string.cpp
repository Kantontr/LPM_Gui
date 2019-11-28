#include "get_string.h"
#include "ui_get_string.h"
#include "utility_v2.h"


Get_String::Get_String(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Get_String)
{
    ui->setupUi(this);

    if(lpm_config->cfg[5].value=="Dark"){
        this->setStyleSheet(ui_color_scheme_dark);
   }

    ui->label->setText(QString::fromStdString(get_string_current_label_text));
    if(hide_entry)ui->lineEdit->setEchoMode(QLineEdit::Password);
}

Get_String::~Get_String()
{
    delete ui;
}

void Get_String::on_pushButton_clicked()
{
    input_from_lineEdit = ui->lineEdit->text().toUtf8().constData();
    Get_String::close();
    return;
}

void Get_String::on_pushButton_2_clicked()
{
    input_from_lineEdit="";
    Get_String::close();
}
