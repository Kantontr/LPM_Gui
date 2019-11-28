#include "show_password.h"
#include "ui_show_password.h"
#include "utility_v2.h"

Show_Password::Show_Password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Show_Password)
{
    ui->setupUi(this);


    if(lpm_config->cfg[5].value=="Dark"){
        this->setStyleSheet(ui_color_scheme_dark);;
    }

    if(bool_copy_to_clipboard==true){
        ui->pushButton_3->setEnabled(true);
    }
    else ui->pushButton_3->setEnabled(false);

    ui->pushButton->setText(QString::fromStdString(show_password_current_button_label));
    ui->pushButton_3->setText(QString::fromStdString(show_password_current_button_2_label));

    lpm_password->reload();
    std::string show_password_tmp="";
    for(int i = 1;i<=lpm_password->rozmiar_pswd;i++){
        show_password_tmp="";
        show_password_tmp = "Name: ";
        show_password_tmp+=lpm_password->pswd[i].name;
        show_password_tmp+=" || login: ";
        show_password_tmp+=rsa_decrypt(lpm_password->pswd[i].login);
        show_password_tmp+="  || password: ";
        show_password_tmp+=rsa_decrypt(lpm_password->pswd[i].password);
        ui->listWidget->addItem(show_password_tmp.c_str());
        //std::cout<<"nazwa: "<<pswd[i].name.c_str()<<" | login: "<<rsa_decrypt(pswd[i].login).c_str()<<" | haslo: "<<rsa_decrypt(pswd[i].password).c_str()<<std::endl;
    }



}

Show_Password::~Show_Password()
{
    delete ui;
}

void Show_Password::on_pushButton_2_clicked()
{
    Show_Password::close();
}




void Show_Password::on_pushButton_clicked() //copy to clipboard or delete
{
    show_password_return = ui->listWidget->currentItem()->text().toStdString();
    if(bool_copy_to_clipboard==true){
        std::string password=get_password_from_string(show_password_return);
        copy_login_to_clipboard=true;
        copy_to_clipboard(password);
        if(copy_login_to_clipboard && copy_password_to_clipboard){
            Show_Password::close();
        }
    }
    else Show_Password::close();
}

void Show_Password::on_pushButton_3_clicked()
{
    show_password_return = ui->listWidget->currentItem()->text().toStdString();
    if(bool_copy_to_clipboard==true){
        std::string login=get_login_from_string(show_password_return);
        copy_password_to_clipboard=true;
        copy_to_clipboard(login);
        if(copy_login_to_clipboard && copy_password_to_clipboard){
            Show_Password::close();
        }
    }
    else Show_Password::close();

}
