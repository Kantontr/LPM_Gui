#include "steam_user_list_notindatabase.h"
#include "ui_steam_user_list_notindatabase.h"
#include "utility_v2.h"
#include <QMessageBox>


Steam_User_List_NotInDataBase::Steam_User_List_NotInDataBase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Steam_User_List_NotInDataBase)
{
    ui->setupUi(this);

    if(lpm_config->cfg[5].value=="Dark"){
        this->setStyleSheet(ui_color_scheme_dark);;
    }

    reload_all();

    std::string sciezka_wlasna;
    std::string sciezka = lpm_config->cfg[2].value;
    sciezka += "\\userdata";
    std::string sciezka_wlasna_tmp;
    int wyliczanie = listowanie_folderow(sciezka,"",0,false);
    bool konto_dodane=false;
    std::string nazwa_konta_juz_w_bazie;

    for (int i=1;i<=wyliczanie;i++){
        sciezka_wlasna=sciezka;
        sciezka_wlasna+="\\";
        sciezka_wlasna+=list_kat[i].listowanie_katalogow_nazwa;
        sciezka_wlasna+="\\config\\localconfig.vdf";

        konto_dodane=false;
        sciezka_wlasna_tmp = sciezka;
        sciezka_wlasna_tmp += "\\";
        sciezka_wlasna_tmp += list_kat[i].listowanie_katalogow_nazwa;
        sciezka_wlasna_tmp+="\\730\\local\\cfg";

        for (int n=0;n<lpm_users->used_slots+1;n++){
            if(lpm_users->bd2[n].path == sciezka_wlasna_tmp){
                konto_dodane=true;
                std::cout<<"Konto juz dodane"<<sciezka_wlasna_tmp<<std::endl;
                break;
            }
        }
        if(!konto_dodane){
            ui->listWidget->addItem(read_username_from_vdf(sciezka_wlasna).c_str());
        }
        else {
            nazwa_konta_juz_w_bazie = read_username_from_vdf(sciezka_wlasna);
            nazwa_konta_juz_w_bazie += " (Already in favorites)";
            ui->listWidget->addItem(nazwa_konta_juz_w_bazie.c_str());
        }
    }
}

Steam_User_List_NotInDataBase::~Steam_User_List_NotInDataBase()
{
    delete ui;
}

void Steam_User_List_NotInDataBase::on_pushButton_clicked() //User not in database confirm
{
    return_value_nazwa = ui->listWidget->currentItem()->text().toUtf8().constData(); //nazwa konta
    std::cout<<"Dodano nazwa: "<<return_value_nazwa<<std::endl;

    std::string sciezka_wlasna;
    std::string sciezka = lpm_config->cfg[2].value;
    sciezka += "\\userdata";
    std::string sciezka_wlasna_tmp;
    int wyliczanie = listowanie_folderow(sciezka,"",0,false);
    bool konto_dodane=false;
    std::string nazwa_konta_juz_w_bazie;
    for (int i=1;i<=wyliczanie;i++){
        sciezka_wlasna=sciezka;
        sciezka_wlasna+="\\";
        sciezka_wlasna+=list_kat[i].listowanie_katalogow_nazwa;
        sciezka_wlasna+="\\config\\localconfig.vdf";

        if(read_username_from_vdf(sciezka_wlasna).c_str() == return_value_nazwa){
            sciezka_wlasna=sciezka;
            sciezka_wlasna+="\\";
            sciezka_wlasna+=list_kat[i].listowanie_katalogow_nazwa;
            sciezka_wlasna+="\\730\\local\\cfg";
            return_value_sciezka = sciezka_wlasna;  //sciezka
            std::cout<<"Dodano sciezke: "<<return_value_sciezka<<std::endl;
            delete ui;
            Steam_User_List_NotInDataBase::close();
            return;
        }

    }
    QMessageBox::critical(this,"Error!","Error! Cannot add user to favorites (User already exists!)");

}

void Steam_User_List_NotInDataBase::on_pushButton_2_clicked() //user add user back
{
    Steam_User_List_NotInDataBase::close();
}
