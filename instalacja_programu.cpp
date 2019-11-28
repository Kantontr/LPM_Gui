#include "instalacja_programu.h"
#include "ui_instalacja_programu.h"
#include <QFileDialog>
#include <QMessageBox>
#include "instalacja.h"
#include "utility_v2.h"

Instalacja_Programu::Instalacja_Programu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Instalacja_Programu)
{
    ui->setupUi(this);

    if(lpm_config->cfg[5].value=="Dark"){
        this->setStyleSheet("color: white; background-color: #232323;");;
    }


}

Instalacja_Programu::~Instalacja_Programu()
{
    delete ui;
}

void Instalacja_Programu::on_pushButton_clicked()
{
    instalacja_kod_bledu = instalacja();
    bool bool_instalacja_steam = true;
    bool bool_instalacja_steam_csgo = true;
    if (instalacja_kod_bledu==0){
        Instalacja_Programu::close();
        return;
    }
    else if(instalacja_kod_bledu==1 || instalacja_kod_bledu==3){
        bool_instalacja_steam = false;
    }
    else if(instalacja_kod_bledu==2 || instalacja_kod_bledu==3){
        bool_instalacja_steam = false;
    }

    while (!bool_instalacja_steam){
    QString file_name = QFileDialog::getExistingDirectory(this,"Select your steamapps folder","C://");
    lpm_config->cfg[2].value = file_name.toUtf8().constData();
    bool_instalacja_steam = lpm_config->add_steam_path();
    }

    while (!bool_instalacja_steam_csgo){
    QString file_name = QFileDialog::getExistingDirectory(this,"Select your steamapps folder","C://");
    lpm_config->cfg[3].value = file_name.toUtf8().constData();
    bool_instalacja_steam_csgo = lpm_config->add_steam_csgo_path();
    }


}
