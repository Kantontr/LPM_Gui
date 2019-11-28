#include "steam_user_list.h"
#include "ui_steam_user_list.h"
#include <QMessageBox>
#include "utility_v2.h"

Steam_User_List::Steam_User_List(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Steam_User_List)
{
    ui->setupUi(this);

    if(lpm_config->cfg[5].value=="Dark"){
        this->setStyleSheet(ui_color_scheme_dark);;
    }

    ui->label->setText(QString::fromStdString(steam_user_list_current_label));
    reload_all();
    std::string nazwa_plus_data;
    for (int i=1;i<lpm_users->used_slots;i++){
        nazwa_plus_data=lpm_users->bd2[i].name;
        nazwa_plus_data += "  ||  last modified: ";

        nazwa_plus_data += get_file_modification_date(lpm_users->bd2[i].path);
        ui->listWidget->addItem(nazwa_plus_data.c_str());

    }
}

Steam_User_List::~Steam_User_List()
{
    delete ui;
}

void Steam_User_List::on_pushButton_clicked()
{
    return_value = ui->listWidget->currentItem()->text().toUtf8().constData();
    Steam_User_List::close();
}

void Steam_User_List::on_pushButton_2_clicked()
{
    return_value = "";
    Steam_User_List::close();
    return;
}
