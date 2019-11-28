#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "steam_user_list.h"
#include "steam_user_list_notindatabase.h"
#include "get_string.h"
#include "getwidestring.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include "utility_v2.h"
#include "instalacja.h"
#include "instalacja_programu.h"
#include "show_password.h"


inline int rozmiar_buttons_disabled = 7;
inline int rozmiar_buttons_enabled =31;
//list_buttons[i]->setStyleSheet(":hover{background:#ffffff}");

inline void ui_set_color_scheme(QPushButton* list_buttons[],bool is_button_enabled,QString color_scheme){
    int rozmiar_buttons;
    if(is_button_enabled)rozmiar_buttons=rozmiar_buttons_enabled;
    else rozmiar_buttons=rozmiar_buttons_disabled;
    for(int i=0;i<rozmiar_buttons;i++){
        if(!is_button_enabled)list_buttons[i]->setEnabled(false);
        list_buttons[i]->setStyleSheet(color_scheme);
    }
}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0); // tab SYNC zawsze pierwszy


    if ((GetFileAttributesA(pathappdata.c_str())) == INVALID_FILE_ATTRIBUTES) {  //sprawdzenie czy program zainstalowany
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Program not installed", "Kanton LPM is not yet installed, do you want to install it now?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            instalacja();
        } else exit(0);
    }



    QPushButton* list_buttons_enabled[rozmiar_buttons_enabled];
    QPushButton* list_buttons_disabled[rozmiar_buttons_disabled];

    list_buttons_disabled[0] = ui->pushButton_21;
    list_buttons_disabled[1] = ui->pushButton_97;
    list_buttons_disabled[2] = ui->pushButton_18;
    list_buttons_disabled[3] = ui->pushButton_15;
    list_buttons_disabled[4] = ui->pushButton_25;
    list_buttons_disabled[5] = ui->pushButton_19;
    list_buttons_disabled[6] = ui->pushButton_17;






    list_buttons_enabled[0] = ui->pushButton;
    list_buttons_enabled[1] = ui->pushButton_2;
    list_buttons_enabled[2] = ui->pushButton_4;
    list_buttons_enabled[3] = ui->pushButton_37;
    list_buttons_enabled[4] = ui->pushButton_38;
    list_buttons_enabled[5] = ui->pushButton_40;
    list_buttons_enabled[6] = ui->pushButton_10;
    list_buttons_enabled[7] = ui->pushButton_13;
    list_buttons_enabled[8] = ui->pushButton_41;
    list_buttons_enabled[9] = ui->pushButton_7;
    list_buttons_enabled[10] = ui->pushButton_22;
    list_buttons_enabled[11] = ui->pushButton_39;
    list_buttons_enabled[12] = ui->pushButton_24;
    list_buttons_enabled[13] = ui->pushButton_26;
    list_buttons_enabled[14] = ui->pushButton_11;
    list_buttons_enabled[15] = ui->pushButton_5;
    list_buttons_enabled[16] = ui->pushButton_6;
    list_buttons_enabled[17] = ui->pushButton_9;
    list_buttons_enabled[18] = ui->pushButton_95;
    list_buttons_enabled[19] = ui->pushButton_3;
    list_buttons_enabled[20] = ui->pushButton_12;
    list_buttons_enabled[21] = ui->pushButton_14;
    list_buttons_enabled[22] = ui->pushButton_99;
    list_buttons_enabled[23] = ui->pushButton_100;
    list_buttons_enabled[24] = ui->pushButton_101;
    list_buttons_enabled[25] = ui->pushButton_20;
    list_buttons_enabled[26] = ui->pushButton_98;
    list_buttons_enabled[27] = ui->pushButton_23;
    list_buttons_enabled[28] = ui->pushButton_16;
    list_buttons_enabled[29] = ui->pushButton_94;
    list_buttons_enabled[30] = ui->pushButton_96;


    //ui->pushButton->setStyleSheet("border:1px solid #090909;");


    if(lpm_config->cfg[5].value=="Light" || lpm_config->cfg[5].value == "brak_danych"){
        ui->pushButton_6->setText("Turn ON dark mode");
        ui_set_color_scheme(list_buttons_disabled,false,ui_buttons_color_light);
    }

    if(lpm_config->cfg[5].value=="Dark"){
        ui->pushButton_6->setText("Turn OFF dark mode");
        this->setStyleSheet(ui_color_scheme_dark);
        ui_set_color_scheme(list_buttons_disabled,false,ui_buttons_color_dark);
    }




    std::string wersja_kanton_lpm = "Kanton LPM ";
    wersja_kanton_lpm += wersja_KantonLPM;
    QWidget::setWindowTitle(wersja_kanton_lpm.c_str());






    if(lpm_config->cfg[6].value == "brak_danych" || lpm_config->cfg[6].value == "true"){
        ui->pushButton_20->setText("Password Authentication: ON");
    }
    else ui->pushButton_20->setText("Password Authentication: OFF");


    std::string favourites_button_set_text="";
    if(lpm_config->cfg[7].value != "brak_danych"){
        favourites_button_set_text="";
        favourites_button_set_text+=" Sync with - ";
        favourites_button_set_text+=lpm_config->cfg[7].value;
        ui->pushButton_3->setText(favourites_button_set_text.c_str());
        ui->pushButton_99->setEnabled(true);
    }
    else ui->pushButton_99->setEnabled(false);

    if(lpm_config->cfg[8].value != "brak_danych"){
        favourites_button_set_text="";
        favourites_button_set_text+=" Sync with - ";
        favourites_button_set_text+=lpm_config->cfg[8].value;
        ui->pushButton_12->setText(favourites_button_set_text.c_str());
        ui->pushButton_100->setEnabled(true);
    }
    else ui->pushButton_100->setEnabled(false);

    if(lpm_config->cfg[9].value != "brak_danych"){
        favourites_button_set_text="";
        favourites_button_set_text+=" Sync with - ";
        favourites_button_set_text+=lpm_config->cfg[9].value;
        ui->pushButton_14->setText(favourites_button_set_text.c_str());
        ui->pushButton_101->setEnabled(true);
    }
    else ui->pushButton_101->setEnabled(false);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() //config sync
{
    steam_user_list_current_label="Select the source account";
    Steam_User_List steam_user_list;
    steam_user_list.setModal(true);
    steam_user_list.exec();

    if(steam_user_list.return_value=="")return;

    std::string nazwa_konta = steam_user_list_get_username_from_string(steam_user_list.return_value);

    int numer_konta = lpm_users->find_account_by_name(nazwa_konta);
    bool sukces = lpm_users->sync_files(numer_konta, lpm_users->used_slots);

    if(sukces){
        QMessageBox::information(this,"Succes","Cfg files moved! To apply Launch Options to all accounts you need to restart/relog to steam!");
        steam_user_list.return_value = "";
    }
    else{
        QMessageBox::critical(this,"Error!","Error! Cannot move cfg files! ");
        steam_user_list.return_value = "";
    }
}

void MainWindow::on_pushButton_37_clicked() //user show all users
{
    steam_user_list_current_label="All saved accounts";
    Steam_User_List steam_user_list;
    steam_user_list.setModal(true);
    steam_user_list.exec();
}

void MainWindow::on_pushButton_38_clicked() //user add user
{
    Steam_User_List_NotInDataBase steam_user_list_notindatabase;
    steam_user_list_notindatabase.setModal(true);
    steam_user_list_notindatabase.exec();

    for (int n=0;n<lpm_users->used_slots+1;n++){
        if(lpm_users->bd2[n].path == steam_user_list_notindatabase.return_value_sciezka){
            //std::cout<<" (Already in database)  "<<std::endl;
            return;
        }
    }
    if(lpm_users->add_user(steam_user_list_notindatabase.return_value_nazwa,steam_user_list_notindatabase.return_value_sciezka)){
        QMessageBox::information(this,"Succes","User added to favorites");
    }
    else {
        QMessageBox::critical(this,"Error!","Error! Cannot add user to favorites!");
    }
}

void MainWindow::on_pushButton_40_clicked() //user remove user
{
    steam_user_list_current_label="Select the user to remove";
    Steam_User_List steam_user_list;
    steam_user_list.setModal(true);
    steam_user_list.exec();

    if(steam_user_list.return_value == ""){
        return;
    }
    std::string nazwa_konta = steam_user_list_get_username_from_string(steam_user_list.return_value);
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Deleting user", "Are you sure you want to remove this user from favorites?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        if(lpm_users->remove_user(nazwa_konta)){
             QMessageBox::information(this,"Succes","User removed from favorites");
        }
        else {
            QMessageBox::critical(this,"Error!","Error! Something went wrong, cannot remove user from favorites!");
        }
    } else return;

}

void MainWindow::on_pushButton_4_clicked()
{
    Instalacja_Programu instalacja_programu;
    instalacja_programu.setModal(true);
    instalacja_programu.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    std::string path_tmp_cfg = lpm_config->cfg[3].value;
    path_tmp_cfg+=sciezka_do_folderu_z_gra;
    ShellExecuteA(0, "explore", path_tmp_cfg.c_str(), NULL, NULL, SW_SHOW);
}

void MainWindow::on_pushButton_10_clicked()
{
    std::string path_backup = pathcsgo_main;
    path_backup+="\\backup";
    ShellExecuteA(0, "explore", path_backup.c_str(), NULL, NULL, SW_SHOW);
}

void MainWindow::on_pushButton_13_clicked()
{
    steam_user_list_current_label="Select an account";
    Steam_User_List steam_user_list;
    steam_user_list.setModal(true);
    steam_user_list.exec();
    if (steam_user_list.return_value == ""){
        return;
    }

    std::string nazwa_konta = steam_user_list_get_username_from_string(steam_user_list.return_value);
    int numer_konta = lpm_users->find_account_by_name(nazwa_konta);
    ShellExecuteA(0, "explore", lpm_users->bd2[numer_konta].path.c_str(), NULL, NULL, SW_SHOW); //otwieranie lokalizacji
}

void MainWindow::on_pushButton_41_clicked() //user rename
{
    steam_user_list_current_label="Select a user to rename";
    Steam_User_List steam_user_list;
    steam_user_list.setModal(true);
    steam_user_list.exec();
    if (steam_user_list.return_value == ""){
        return;
    }
    std::string nazwa_konta = steam_user_list_get_username_from_string(steam_user_list.return_value);


    get_string_current_label_text = "Enter the new name";
    Get_String get_string;
    get_string.setModal(true);
    get_string.exec();

    if(get_string.input_from_lineEdit == ""){
        QMessageBox::information(this,"Operation cancelled","No changes were made");
        return;
    }

    if(lpm_users->rename_user(nazwa_konta,get_string.input_from_lineEdit)){
        QMessageBox::information(this,"Succes","User renamed!");
    }
    else{
        QMessageBox::critical(this,"Error!","Error! Something went wrong, cannot rename user!");
    }
}

void MainWindow::on_pushButton_7_clicked() //backup create
{
    get_string_current_label_text = "Chose a name for your new backup";
    Get_String get_string;
    get_string.setModal(true);
    get_string.exec();

    if(create_backup(get_string.input_from_lineEdit)){
        QMessageBox::information(this,"Succes","Backup created!");
    }
    else{
        QMessageBox::critical(this,"Error!","Error! Something went wrong, cannot create backup!");
    }
}

void MainWindow::on_pushButton_22_clicked() //open backup
{
    std::string path_backup = pathcsgo_main;
    path_backup+="\\backup";
    ShellExecuteA(0, "explore", path_backup.c_str(), NULL, NULL, SW_SHOW);
}


void MainWindow::on_pushButton_39_clicked() //user export files
{
    steam_user_list_current_label="Select an account";
    Steam_User_List steam_user_list;
    steam_user_list.setModal(true);
    steam_user_list.exec();
    if (steam_user_list.return_value == ""){
        return;
    }
    std::string nazwa_konta = steam_user_list_get_username_from_string(steam_user_list.return_value);

    bool error=false;


    int numer_konta = lpm_users->find_account_by_name(nazwa_konta);
    QString file_name = QFileDialog::getExistingDirectory(this,"Select destination","C://");
    if(file_name.toUtf8().constData()==""){
        return;
    }

    std::string sciezka_user_cfg = lpm_users->bd2[numer_konta].path;
    sciezka_user_cfg+="\\config.cfg";
    std::string sciezka_user_video = lpm_users->bd2[numer_konta].path;
    sciezka_user_video+="\\video.txt";

    std::string sciezka_docelowa = file_name.toUtf8().constData();
    sciezka_docelowa += "\\KantonLPM\\";
    sciezka_docelowa += lpm_users->bd2[numer_konta].name;

    if ((GetFileAttributesA(sciezka_docelowa.c_str())) == INVALID_FILE_ATTRIBUTES) {
        CreateDirectoryA(sciezka_docelowa.c_str(), 0);
    }
   sciezka_docelowa+="\\config.cfg";

    if ((CopyFileA(sciezka_user_cfg.c_str(), sciezka_docelowa.c_str(), FALSE)) == 0) {
        std::cout << "Nie udalo sie skopiowac pliku, kod bledu: " << GetLastError() << std::endl;
        error = true;
        QMessageBox::critical(this,"Error!","Error! Something went wrong, cannot copy config.cfg file!");
    } else std::cout << "Plik " << sciezka_user_cfg.c_str() << " skopiowany pomyslnie" << std::endl;

    sciezka_docelowa = file_name.toUtf8().constData();
    sciezka_docelowa += "\\KantonLPM\\";
    sciezka_docelowa += lpm_users->bd2[numer_konta].name;
    sciezka_docelowa += "\\video.txt";




    if ((CopyFileA(sciezka_user_video.c_str(), sciezka_docelowa.c_str(), FALSE)) == 0) {
        std::cout << "Nie udalo sie skopiowac pliku, kod bledu: " << GetLastError() << std::endl;
        error = true;
        QMessageBox::critical(this,"Error!","Error! Something went wrong, cannot copy video.txt file!");
    } else std::cout << "Plik " << sciezka_user_video.c_str() << " skopiowany pomyslnie" << std::endl;

    if(error==false){
        QMessageBox::information(this,"Succes","Files moved!");
    }
}


bool authentication(){
    get_string_current_label_text = "Enter Acces Password";
    hide_entry=true;
    Get_String get_string;
    get_string.setModal(true);
    get_string.exec();
    hide_entry=false;
    return compare_passwords(get_string.input_from_lineEdit);
}


void MainWindow::on_pushButton_24_clicked() //password set acces password
{

    if(lpm_password->pswd[0].password != "password_not_found"){
        if(!authentication()){
            QMessageBox::critical(this,"Error!","Error! Incorrect Acces Password!");
            return;
        }
    }
    get_string_current_label_text = "Enter your new Acces Password";
    Get_String get_string;
    get_string.setModal(true);
    get_string.exec();

    if(get_string.input_from_lineEdit==""){
        QMessageBox::critical(this,"Error!","Error! Something went wrong, cannot set acces password!");
        return;
    }
    else {
        long int new_acces_password[500];
        rsa_encrypt(get_string.input_from_lineEdit,new_acces_password);

        std::string access_password="";
        for(int i=0;new_acces_password[i]!=-1;i++){
            access_password+= std::to_string(new_acces_password[i]);
            access_password+= ' ';
        }
        access_password+="-1";
        lpm_password->pswd[0].password ="";
        lpm_password->pswd[0].password = access_password;
        lpm_password->save_to_file();
        lpm_password->reload();
    }
}

void MainWindow::on_pushButton_9_clicked() //password add password
{

    if(!Session_Password_Authentication){
        if(!authentication()){
            QMessageBox::critical(this,"Error!","Incorrect Password");
            return;
        }
        else Session_Password_Authentication=true;
    }



    GetWideString get_wide_string;
    get_wide_string.setModal(true);
    get_wide_string.exec();

    lpm_password->reload();
    if(get_wide_string.nazwa=="" || get_wide_string.login == "" || get_wide_string.password == ""){
        QMessageBox::information(this,"Abort","Operation aborted by user.");
        return;
    }

    bool nazwa_juz_istnieje=false;
    for(int i=0;i<=lpm_password->rozmiar_pswd;i++){
        if(compare_strings(get_wide_string.nazwa,lpm_password->pswd[i].name)){
            nazwa_juz_istnieje=true;
            QMessageBox::information(this,"Error","Name already used, please select another name");
            break;
        }
    }



    while(nazwa_juz_istnieje){

        nazwa_juz_istnieje=false;

        GetWideString get_wide_string;
        get_wide_string.setModal(true);
        get_wide_string.exec();

        lpm_password->reload();
        if(get_wide_string.nazwa=="" || get_wide_string.login == "" || get_wide_string.password == ""){
            QMessageBox::information(this,"Abort","Operation aborted by user.");
            return;
        }


        for(int i=0;i<=lpm_password->rozmiar_pswd;i++){
            if(compare_strings(get_wide_string.nazwa,lpm_password->pswd[i].name)){
                nazwa_juz_istnieje=true;
                QMessageBox::information(this,"Error","Name already used, please select another name");
                break;
            }
        }
    }




    // szyfrowanie login
    std::string user_login = get_wide_string.login;
    long int int_login_encr[500];
    rsa_encrypt(user_login,int_login_encr);
    std::string user_login_encr="";
    for(int i=0;int_login_encr[i]!=-1;i++){
        user_login_encr+= std::to_string(int_login_encr[i]);
        user_login_encr+= ' ';
    }
    user_login_encr+="-1";

    //szyfrowanie haslo
    std::string user_password = get_wide_string.password;
    long int int_password_encr[500];
    rsa_encrypt(user_password,int_password_encr);
    std::string user_password_encr="";
    for(int i=0;int_password_encr[i]!=-1;i++){
        user_password_encr+= std::to_string(int_password_encr[i]);
        user_password_encr+= ' ';
    }
    user_password_encr+="-1";


    lpm_password->rozmiar_pswd+=1;
    lpm_password->pswd[lpm_password->rozmiar_pswd].name = get_wide_string.nazwa;
    lpm_password->pswd[lpm_password->rozmiar_pswd].login = "";
    lpm_password->pswd[lpm_password->rozmiar_pswd].login = user_login_encr;
    lpm_password->pswd[lpm_password->rozmiar_pswd].password = "";
    lpm_password->pswd[lpm_password->rozmiar_pswd].password += user_password_encr;


    if(lpm_password->save_to_file()){
        QMessageBox::information(this,"Succes","Password Saved!");
    }
    else{
        QMessageBox::critical(this,"Error!","Error! Something went wrong, cannot add password!");
    }


}

void MainWindow::on_pushButton_26_clicked() //show password
{

    if(!Session_Password_Authentication){
        if(!authentication()){
            QMessageBox::critical(this,"Error!","Incorrect Password");
            return;
        }
        else Session_Password_Authentication=true;
    }

    show_password_current_button_label="Copy password to clipboard";
    show_password_current_button_2_label="Copy login to clipboard";
    bool_copy_to_clipboard=true;
    Show_Password show_password;
    show_password.setModal(true);
    show_password.exec();
    copy_login_to_clipboard=false;
    copy_password_to_clipboard=false;

}

void MainWindow::on_pushButton_11_clicked() //delete password
{
    if(!Session_Password_Authentication){
        if(!authentication()){
            QMessageBox::critical(this,"Error!","Incorrect Password");
            return;
        }
        else Session_Password_Authentication=true;
    }

    show_password_current_button_label="Confirm selection";
    show_password_current_button_2_label="";
    bool_copy_to_clipboard=false;
    Show_Password show_password;
    show_password.setModal(true);
    show_password.exec();

    if(show_password.show_password_return==""){
        QMessageBox::information(this,"Abort","Operation aborted by user.");
        return;
    }
    std::string nazwa_konta=get_name_from_string(show_password.show_password_return);

    int numer_konta_do_usuniecia = lpm_password->find_user_by_name(nazwa_konta);
    if(numer_konta_do_usuniecia==-1){
        QMessageBox::critical(this,"Error!","Something went wrong, cannot remove password");
        return;
    }
    else{
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Remove password", "Are you sure you want to remove this password?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            if(lpm_password->remove_user(numer_konta_do_usuniecia)){
                QMessageBox::information(this,"Succes","Password removed!");
                return;
            }
        } else exit(0);
    }



}

void MainWindow::on_pushButton_5_clicked()  //Export LPM Config
{
    QString file_name="";
    QFileDialog explorer;
    file_name = explorer.getExistingDirectory(this,"Select your steamapps folder","C://");
    if(file_name.isNull()){
        QMessageBox::information(this,"Operation aborted","Operation aborted by user!");
        return;
    }
    if(export_files(file_name.toUtf8().constData())){
        QMessageBox::information(this,"Succes","Files moved!");
    }
    else{
        QMessageBox::critical(this,"Error!","Error! Something went wrong, cannot export files!");
    }
}

void MainWindow::on_pushButton_3_clicked() //Favorites slot 1
{
    if(lpm_config->cfg[7].value == "brak_danych"){

        steam_user_list_current_label="Select an account to add";
        Steam_User_List steam_user_list;
        steam_user_list.setModal(true);
        steam_user_list.exec();
        if (steam_user_list.return_value == ""){
            QMessageBox::information(this,"Operation aborted!","Operation aborted by user");
            return;
        }
        std::string nazwa_konta = steam_user_list_get_username_from_string(steam_user_list.return_value);
        lpm_config->cfg[7].value = nazwa_konta;
        lpm_config->save_to_file();
        lpm_config->reload();
        restart_programu();
    }


    bool sukces = lpm_users->sync_files(lpm_users->find_account_by_name(lpm_config->cfg[7].value), lpm_users->used_slots);
    if(sukces){
        QMessageBox::information(this,"Succes","Cfg files synced!");
    }
    else{
        QMessageBox::critical(this,"Error!","Error! Cannot sync cfg files! ");
    }

}

void MainWindow::on_pushButton_12_clicked() //Favorites slot 2
{

    if(lpm_config->cfg[8].value == "brak_danych"){

        steam_user_list_current_label="Select an account to add";
        Steam_User_List steam_user_list;
        steam_user_list.setModal(true);
        steam_user_list.exec();
        if (steam_user_list.return_value == ""){
            QMessageBox::information(this,"Operation aborted!","Operation aborted by user");
            return;
        }
        std::string nazwa_konta = steam_user_list_get_username_from_string(steam_user_list.return_value);
        lpm_config->cfg[8].value = nazwa_konta;
        lpm_config->save_to_file();
        lpm_config->reload();
        restart_programu();
    }

    bool sukces = lpm_users->sync_files(lpm_users->find_account_by_name(lpm_config->cfg[8].value), lpm_users->used_slots);
    if(sukces){
        QMessageBox::information(this,"Succes","Cfg files synced!");
    }
    else{
        QMessageBox::critical(this,"Error!","Error! Cannot sync cfg files! ");
    }

}

void MainWindow::on_pushButton_14_clicked() //Favorites slot 3
{

    if(lpm_config->cfg[9].value == "brak_danych"){

        steam_user_list_current_label="Select an account to add";
        Steam_User_List steam_user_list;
        steam_user_list.setModal(true);
        steam_user_list.exec();
        if (steam_user_list.return_value == ""){
            QMessageBox::information(this,"Operation aborted!","Operation aborted by user");
            return;
        }
        std::string nazwa_konta = steam_user_list_get_username_from_string(steam_user_list.return_value);
        lpm_config->cfg[9].value = nazwa_konta;
        lpm_config->save_to_file();
        lpm_config->reload();
        restart_programu();
    }

    bool sukces = lpm_users->sync_files(lpm_users->find_account_by_name(lpm_config->cfg[9].value), lpm_users->used_slots);
    if(sukces){
        QMessageBox::information(this,"Succes","Cfg files synced!");
    }
    else{
        QMessageBox::critical(this,"Error!","Error! Cannot sync cfg files! ");
    }

}

void MainWindow::on_pushButton_15_clicked() //Favorites slot 4
{

}

void MainWindow::on_pushButton_6_clicked()
{
    if(lpm_config->cfg[5].value == "Light" || lpm_config->cfg[5].value == "brak_danych"){
        lpm_config->cfg[5].value = "Dark";
        QMessageBox::information(this,"Succes","Color scheme changed to Dark. Changes will take place after restart");
    }
    else if(lpm_config->cfg[5].value == "Dark"){
        lpm_config->cfg[5].value = "Light";
        QMessageBox::information(this,"Succes","Color scheme changed to Light. Changes will take place after restart");
    }
    lpm_config->save_to_file();
    lpm_config->reload();

    restart_programu();

}

void MainWindow::on_pushButton_23_clicked() // remove backup
{
    std::string path_backup = pathcsgo_main;
    path_backup += "\\backup";
    QString file_name = QFileDialog::getExistingDirectory(this,"Select backup",path_backup.c_str());
    if(file_name.isNull()){
        QMessageBox::information(this,"Operation aborted!","Operation aborted by user!");
        return;
    }

    std::string nazwa_kopii="";
    std::string z_file_name = file_name.toStdString();

    for(int i=path_backup.length()+1;i<z_file_name.length();i++){
        nazwa_kopii+=z_file_name[i];
    }
    path_backup+="\\";
    path_backup+=nazwa_kopii;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete Backup?", "Are you sure you want to delete this backup?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {

        int ile_katalogow = listowanie_folderow(path_backup,"",0,false);
        std::string tmp;
        std::string tmp_2;
        for(int i=0;i<=ile_katalogow;i++){

            tmp=path_backup;
            tmp+="\\";
            tmp+=list_kat[i].listowanie_katalogow_nazwa;
            tmp+="\\config.cfg";

            tmp_2=path_backup;
            tmp_2+="\\";
            tmp_2+=list_kat[i].listowanie_katalogow_nazwa;
            tmp_2+="\\video.txt";

            remove(tmp.c_str());
            remove(tmp_2.c_str());

            tmp=path_backup;
            tmp+="\\";
            tmp+=list_kat[i].listowanie_katalogow_nazwa;

            RemoveDirectoryA(tmp.c_str());
        }
        RemoveDirectoryA(path_backup.c_str());

        if ((GetFileAttributesA(path_backup.c_str())) == INVALID_FILE_ATTRIBUTES) {
            QMessageBox::information(this,"Succes","Backup removed!");
            return;
        }
        else{
            QMessageBox::information(this,"Operation failed","Something went wrong, operation failed!");
            return;
        }



    } else {
        QMessageBox::information(this,"Operation aborted","Operation aborted by user!");
        return;
    }

}



void MainWindow::on_pushButton_8_clicked() //load backup
{
    std::string path_backup = pathcsgo_main;
    path_backup += "\\backup";
    QString file_name = QFileDialog::getExistingDirectory(this,"Select backup",path_backup.c_str());
    if(file_name.isNull()){
        QMessageBox::information(this,"Operation aborted!","Operation aborted by user!");
        return;
    }
    std::string nazwa_backup="";
    std::string sciezka = file_name.toStdString();
    for(int i=path_backup.length()+1;i<sciezka.length();i++){
        nazwa_backup+=sciezka[i];
    }
    if(load_backup(nazwa_backup)){
        QMessageBox::information(this,"Succes","Backup loaded!");
    }
}

void MainWindow::on_pushButton_16_clicked()
{
    ShellExecuteA(0, "explore", pathappdata.c_str(), NULL, NULL, SW_SHOW);
}

void MainWindow::on_pushButton_17_clicked()
{

}

void MainWindow::on_pushButton_21_clicked()
{

}

void MainWindow::on_pushButton_25_clicked()
{

}

void MainWindow::on_pushButton_20_clicked()  //password require authentication
{
    if(!Session_Password_Authentication){
        if(!authentication()){
            QMessageBox::critical(this,"Error!","Incorrect Password");
            return;
        }
        else Session_Password_Authentication=true;
    }

    if(lpm_config->cfg[6].value == "brak_danych" || lpm_config->cfg[6].value == "true"){

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Turn Password Authentication off?", "Are you sure you want to turn off Password Authentication?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            lpm_config->cfg[6].value = "false";
            lpm_config->save_to_file();
            lpm_config->reload();
            QMessageBox::information(this,"Succes","Password Authentication is now OFF");
            restart_programu();
        } else {
            QMessageBox::information(this,"Operation aborted","Operation aborted by user!");
            return;
        }
    }
    else if (lpm_config->cfg[6].value == "false") {

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Turn Password Authentication on?", "Are you sure you want to turn on Password Authentication?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            lpm_config->cfg[6].value = "true";
            lpm_config->save_to_file();
            lpm_config->reload();
            QMessageBox::information(this,"Succes","Password Authentication is now ON");
            restart_programu();
        } else {
            QMessageBox::information(this,"Operation aborted","Operation aborted by user!");
            return;
        }

    }

}

void MainWindow::on_pushButton_19_clicked()
{

}

void MainWindow::on_pushButton_18_clicked()
{

}

void MainWindow::on_pushButton_customContextMenuRequested(const QPoint &pos)
{

}

void MainWindow::on_pushButton_95_clicked() // move custom cfg file
{
    steam_user_list_current_label="Select the source account";
    Steam_User_List steam_user_list;
    steam_user_list.setModal(true);
    steam_user_list.exec();
    if (steam_user_list.return_value == ""){
        QMessageBox::information(this,"Operation cancelled","Operation aborted by user. No changes were made");
        return;
    }

    std::string nazwa_konta = steam_user_list_get_username_from_string(steam_user_list.return_value);
    int numer_konta = lpm_users->find_account_by_name(nazwa_konta);

    std::string sciezka;
    sciezka = lpm_users->bd2[numer_konta].path;


    QString file_path="";
    QFileDialog explorer;
    file_path = explorer.getOpenFileName(this,"Select a file",sciezka.c_str(),tr("Text Files (*.cfg)"));
    if(file_path.isNull()){
        QMessageBox::critical(this,"Error!","Error! Something went wrong, cannot move the file!");
        return;
    }
    std::string file_name="";
    int dlugosc_sciezki = sciezka.length();
    sciezka = file_path.toUtf8().constData();

    for(int i = dlugosc_sciezki+1;i<sciezka.length();i++){
        file_name+=sciezka[i];
    }

    std::cout<<"sciezka: "<<std::endl;
    std::cout<<sciezka<<std::endl;
    if(move_custom_file_to_csgo_folder(sciezka,file_name)){
        QMessageBox::information(this,"Succes","Files moved!");
    }
    else{
        QMessageBox::critical(this,"Error!","Error! Something went wrong, cannot copy the file!");
    }
}

void MainWindow::on_pushButton_98_clicked() // crosshair backup
{

    /* Choose account and name */
    steam_user_list_current_label="Select the source account";
    Steam_User_List steam_user_list;
    steam_user_list.setModal(true);
    steam_user_list.exec();

    if (steam_user_list.return_value == ""){
        QMessageBox::information(this,"Operation cancelled","Operation aborted by user. No changes were made");
        return;
    }

    std::string user_name = steam_user_list_get_username_from_string(steam_user_list.return_value);

    get_string_current_label_text = "Enter a name for your new crosshair backup";
    Get_String get_string;
    get_string.setModal(true);
    get_string.exec();

    if(get_string.input_from_lineEdit == ""){
        QMessageBox::information(this,"Operation cancelled","No changes were made");
        return;
    }
    /* END Choose account and name */

    if(save_crosshair(user_name,get_string.input_from_lineEdit)){
        QMessageBox::information(this,"Succes","Crosshair backup created!");
    }
    else{
        QMessageBox::critical(this,"Error!","Error! Something went wrong, cannot create crosshair backup!");
    }

}

void MainWindow::on_pushButton_97_clicked()
{

}

void MainWindow::on_pushButton_94_clicked() //show crosshair backup
{
    std::string open_path = pathappdata;
    open_path +="\\CSGO\\crosshair_backup";
    ShellExecuteA(0, "explore", open_path.c_str(), NULL, NULL, SW_SHOW);
}

void MainWindow::on_pushButton_96_clicked()
{

    steam_user_list_current_label="Select the source account";
    Steam_User_List steam_user_list;
    steam_user_list.setModal(true);
    steam_user_list.exec();

    if (steam_user_list.return_value == ""){
        QMessageBox::information(this,"Operation cancelled","Operation aborted by user. No changes were made");
        return;
    }

    std::string nazwa = steam_user_list_get_username_from_string(steam_user_list.return_value);


    std::string path_to_localconfig = lpm_config->cfg[2].value;
    path_to_localconfig += "\\userdata\\";
    path_to_localconfig += get_steam_folder_id_from_path(lpm_users->bd2[lpm_users->find_account_by_name(nazwa)].path);
    path_to_localconfig += "\\config\\localconfig.vdf";
    std::string launch_options = vdf_read_launch_options(path_to_localconfig);



    if(launch_options == "Error! Launch options not found!"){
        QMessageBox::critical(this,"Error!","Error! Something went wrong, cannot retrieve launch options!");
        return;
    }

    std::string copy_to_clipboard_tmp = launch_options;
    copy_to_clipboard_tmp+="\n Copy to clipboard?";

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Succes!", QString::fromStdString(copy_to_clipboard_tmp), QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        copy_to_clipboard(launch_options);
    }

}

void MainWindow::on_pushButton_99_clicked()
{
    if(lpm_config->cfg[7].value != "brak_danych"){

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Clear favourite slot", "Are you sure you want to clear this slot?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            lpm_config->cfg[7].value = "brak_danych";
            lpm_config->save_to_file();
            lpm_config->reload();
            restart_programu();
        } else {
            QMessageBox::information(this,"Operation aborted","Operation aborted by user!");
            return;
        }
    }
}

void MainWindow::on_pushButton_100_clicked()
{
    if(lpm_config->cfg[8].value != "brak_danych"){

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Clear favourite slot", "Are you sure you want to clear this slot?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            lpm_config->cfg[8].value = "brak_danych";
            lpm_config->save_to_file();
            lpm_config->reload();
            restart_programu();
        } else {
            QMessageBox::information(this,"Operation aborted","Operation aborted by user!");
            return;
        }
    }
}

void MainWindow::on_pushButton_101_clicked()
{
    if(lpm_config->cfg[9].value != "brak_danych"){

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Clear favourite slot", "Are you sure you want to clear this slot?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            lpm_config->cfg[9].value = "brak_danych";
            lpm_config->save_to_file();
            lpm_config->reload();
            restart_programu();
        } else {
            QMessageBox::information(this,"Operation aborted","Operation aborted by user!");
            return;
        }
    }
}
