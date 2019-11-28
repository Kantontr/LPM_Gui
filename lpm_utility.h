#ifndef LPM_UTILITY_H
#define LPM_UTILITY_H
#include <iostream>
#include <windef.h>
#include <afxres.h>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <Windows.h>
#include <ShellAPI.h>
#include <ShlObj.h>
#include <direct.h>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <string>
#include<cmath>
#include <QMessageBox>
#include <sys/types.h>
#include <sys/stat.h>



class LPM_CONFIG{
public:
    int config_size;
    int used_slots;

    struct config_programu
    {
        std::string name;
        std::string value;
    };
    config_programu *cfg;

    LPM_CONFIG(int int_config_size){
        config_size = int_config_size;
        cfg = new config_programu[config_size];
        reload();
    }

    void save_to_file();
    bool add_steam_csgo_path();
    bool add_steam_path();
    void reload();
    void count();
};

class LPM_PASSWORD{
    public:

    int rozmiar_pswd=1;

    struct passwords
    {
        std::string name;
        std::string login;
        std::string password;
    };
    passwords pswd[100]; //ile hasel mozna dodac


    bool reload();
    bool save_to_file();
    int find_user_by_name(std::string nazwa_konta);
    bool remove_user(int konto_do_usuniecia);

};


class LPM_USERS{
    public:

    int used_slots;

    struct bd2_struct
    {
        std::string name;
        std::string path;
    };

    bd2_struct bd2[20]; // max kont = 20;

    bool add_user(std::string nazwa,std::string sciezka);
    int reload();
    bool remove_user(std::string nazwa_user);
    bool save_to_file();
    bool rename_user(std::string nazwa,std::string nowa_nazwa);
    int find_account_by_name(std::string nazwa_konta);
    std::string read_account_name(std::string sciezka);
    bool sync_files(int wybor,int used_slots);

};

inline LPM_CONFIG *lpm_config = new LPM_CONFIG(10);
inline LPM_PASSWORD *lpm_password = new LPM_PASSWORD;
inline LPM_USERS *lpm_users = new LPM_USERS;


struct listowanie_katalogow_struct{
    std::string listowanie_katalogow_nazwa;
    int listowanie_katalogow_numer_katalogu;
};

struct wyszukiwanie_nazwy_konta_struct{
    std::string nazwa_konta_steam;
    std::string id_steam;
};

inline wyszukiwanie_nazwy_konta_struct wyszukiwanie_nazwy_konta[15];
inline listowanie_katalogow_struct list_kat[100];


inline std::string wersja_KantonLPM = "beta v1.6";
inline std::string wersja_premium = "standard";
inline std::string pathappdata;
inline std::string path_pulpit;
inline std::string steam_folder;
inline std::string path_pulpit_konfigcs;
inline std::string path_config;
inline std::string pathcsgo_main;
inline std::string pathdane;
inline std::string pathftp_main;
inline std::string pathhasla_main;
inline std::string steam_csgo_folder;
inline std::string wersja_programu;
inline std::string sciezka_do_folderu_z_gra;
inline std::string path_hasla_plik;

inline bool copy_login_to_clipboard=false;
inline bool copy_password_to_clipboard=false;
inline bool Session_Password_Authentication=false;

inline QString ui_buttons_color_dark = "color: gray; background-color: #171717;";
inline QString ui_color_scheme_dark = "color: white; background-color: #232323;";
inline QString ui_buttons_color_light = "color: white; background-color: #B5B5B5;";

inline std::string get_steam_folder_id_from_path(std::string input);
inline bool vdf_save_launch_options(std::string file_path,std::string launch_options);
inline std::string vdf_read_launch_options(std::string file_path);

inline void stworz_sciezki() {

    pathappdata = "";
    path_pulpit= "";
    steam_folder= "";
    path_pulpit_konfigcs= "";
    path_config= "";
    pathcsgo_main= "";
    pathdane= "";
    pathftp_main= "";
    pathhasla_main= "";
    steam_csgo_folder= "";
    wersja_programu= "";
    sciezka_do_folderu_z_gra="\\steamapps\\common\\Counter-Strike Global Offensive\\csgo\\cfg";


    pathappdata += getenv("AppData");
    path_pulpit_konfigcs += lpm_config->cfg[1].value;
    wersja_programu = lpm_config->cfg[4].value;
    path_pulpit = lpm_config->cfg[1].value;
    steam_folder = lpm_config->cfg[2].value;
    steam_csgo_folder = lpm_config->cfg[3].value;
    pathappdata += "\\KantonLPM";
    pathftp_main += pathappdata;
    pathhasla_main += pathappdata;
    pathcsgo_main += pathappdata;
    pathcsgo_main += "\\CSGO";
    pathdane += pathcsgo_main;
    path_config += pathappdata;
    path_config += "\\config";
    path_pulpit_konfigcs += "\\konfigcs";
    pathhasla_main += "\\Hasla";
    pathftp_main += "\\FTP";
    pathdane += "\\dane_csgo.cfg";
    path_hasla_plik = pathhasla_main;
    path_hasla_plik += "\\pswd.cfg";

    lpm_config->cfg[0].name="config_glowny";
    lpm_config->cfg[1].name="path_pulpit";
    lpm_config->cfg[2].name="path_steam";
    lpm_config->cfg[3].name="path_steam_csgo";
    lpm_config->cfg[4].name="wersja_programu";
    lpm_config->cfg[5].name="UI_Color_Scheme";
    lpm_config->cfg[6].name="Require_Authentication";
    lpm_config->cfg[7].name="Favourites_Slot_1";
    lpm_config->cfg[8].name="Favourites_Slot_2";
    lpm_config->cfg[9].name="Favourites_Slot_3";

}



inline void decimal_to_binary(long int op1,long int aOp[]){
    long int result, i = 0;
    do{
        result = op1 % 2;
        op1 /= 2;
        aOp[i] = result;
        i++;
    }while(op1 > 0);
}

inline long int modular_exponentiation(long int a,long int b,long int n){
    long int *bb;
    long int count = 0, c = 0, d = 1, i;

    count = (long int) (log(b)/log(2)) + 1;

    bb = (long int *) malloc(sizeof(long int*) * count);
    decimal_to_binary(b, bb);

    for (i = count - 1; i >= 0; i--) {
        c = 2 * c;
        d = (d*d) % n;
        if (bb[i] == 1) {
            c = c + 1;
            d = (d*a) % n;
        }
    }
    return d;
}


inline void rsa_encrypt(std::string msg,long int msg_encrypted[]){
    int p, q, n, e;
    p =197;
    q=89;
    n = p*q;
    e = 71;

    int i =0;
    for(i=0;i<msg.length();i++){
        msg_encrypted[i] = modular_exponentiation((int)msg[i],e,n);
    }
    msg_encrypted[i]=-1;
}

inline std::string rsa_decrypt(std::string msg_encrypted){

    std::string msg_decrypted = "";
    std::string int_temp="";
    long int rsa_msg_encrypted[500];
    int licznik_rsa_msg=0;
    int string_length = msg_encrypted.length();


    for(int i=0;i<string_length;i++){
        if(msg_encrypted[i]==' '){
            rsa_msg_encrypted[licznik_rsa_msg] = stoi(int_temp);
            int_temp="";
            licznik_rsa_msg++;
        }
        else int_temp+=msg_encrypted[i];
    }
    rsa_msg_encrypted[licznik_rsa_msg]=-1;


    int p, q, n,d;
    p =197;
    q=89;
    n = p*q;
    d = 13847;

    int i=0;
    for(i=0;rsa_msg_encrypted[i]!=-1;i++){
        msg_decrypted += modular_exponentiation(rsa_msg_encrypted[i],d,n);
    }
    return msg_decrypted;
}


inline  std::string pathdodajconfig(int wybor)
{
    std::string pathdodajconfigstr = lpm_users->bd2[wybor].path;
    pathdodajconfigstr += "/config.cfg";
    return pathdodajconfigstr;
}

inline  std::string pathdodajvideo(int wybor)
{
    std::string pathdodajvideostr = lpm_users->bd2[wybor].path;
    pathdodajvideostr += "/video.txt";
    return pathdodajvideostr;
}



inline  int listowanie_folderow(std::string listowanie_folderow_path,std::string ustawienie,int dlugosc_ciagu,bool wyswietlic) {  //(nazwa,"",0) == bez filtrow
    int wyliczanie = 0;
    DIR *dir;
    struct dirent *ent;
    std::string listowanie_tmp;
    std::string listowanie_tmp_2;
    if ((dir = opendir(listowanie_folderow_path.c_str())) != NULL) {

        while ((ent = readdir(dir)) != NULL) {
            if (ustawienie == ""){
                if(wyliczanie>=2){
                    list_kat[wyliczanie-1].listowanie_katalogow_nazwa = ent->d_name;
                    list_kat[wyliczanie-1].listowanie_katalogow_numer_katalogu = wyliczanie;
                    if(wyswietlic)printf("(%d) %s\n", wyliczanie-1, list_kat[wyliczanie-1].listowanie_katalogow_nazwa.c_str());
                }
                wyliczanie++;
            }
            else {
                listowanie_tmp = ent->d_name;
                if(listowanie_tmp.length()>5){
                    listowanie_tmp_2="";
                    listowanie_tmp_2.insert(0,listowanie_tmp,listowanie_tmp.length()-(dlugosc_ciagu),dlugosc_ciagu);
                    if((listowanie_tmp_2==ustawienie)){
                        wyliczanie++;
                        list_kat[wyliczanie].listowanie_katalogow_nazwa = ent->d_name;
                        list_kat[wyliczanie].listowanie_katalogow_numer_katalogu = wyliczanie;
                        if(wyswietlic)printf("(%d) %s\n", wyliczanie, list_kat[wyliczanie].listowanie_katalogow_nazwa.c_str());
                    }
                }
            }
        }
        closedir(dir);
        return wyliczanie-2;
    } else {
        perror("");
        return EXIT_FAILURE;
    }
}




inline bool export_files(std::string sciezka_docelowa){

    std::string path_przenies_na_pulpit = sciezka_docelowa;
    path_przenies_na_pulpit+="\\KantonLPM";
    if ((GetFileAttributesA(path_przenies_na_pulpit.c_str())) == INVALID_FILE_ATTRIBUTES) {
        CreateDirectoryA(path_przenies_na_pulpit.c_str(), 0);
        std::cout << "Folder KantonLPM zostal utworzony na pulpicie" << std::endl;
    }

    std::string path_przenies_na_pulpit_config = path_przenies_na_pulpit;
    path_przenies_na_pulpit_config+="\\config";
    if ((GetFileAttributesA(path_przenies_na_pulpit_config.c_str())) == INVALID_FILE_ATTRIBUTES) {
        CreateDirectoryA(path_przenies_na_pulpit_config.c_str(), 0);
        std::cout << "Folder config zostal utworzony" << std::endl;
    }
    path_przenies_na_pulpit_config += "\\config.cfg";
    std::string path_cfg = path_config;
    path_cfg += "\\config.cfg";
    CopyFileA(path_cfg.c_str(), path_przenies_na_pulpit_config.c_str(), FALSE);


    std::string path_przenies_na_pulpit_csgo = path_przenies_na_pulpit;
    path_przenies_na_pulpit_csgo+="\\CSGO";
    if ((GetFileAttributesA(path_przenies_na_pulpit_csgo.c_str())) == INVALID_FILE_ATTRIBUTES) {
        CreateDirectoryA(path_przenies_na_pulpit_csgo.c_str(), 0);
        std::cout << "Folder CSGO zostal utworzony" << std::endl;
    }



    std::string path_pulpit_konfigcs_dane = path_przenies_na_pulpit_csgo;
    path_pulpit_konfigcs_dane += "/dane_csgo.cfg";
    CopyFileA(pathdane.c_str(), path_pulpit_konfigcs_dane.c_str(), FALSE);
    if ((GetFileAttributesA(path_pulpit_konfigcs_dane.c_str())) == INVALID_FILE_ATTRIBUTES) {
        std::cout << "Wystapil blad" << std::endl;
    }

    std::string path_przenies_na_pulpit_hasla = path_przenies_na_pulpit;
    path_przenies_na_pulpit_hasla+="\\Hasla";
    if ((GetFileAttributesA(path_przenies_na_pulpit_hasla.c_str())) == INVALID_FILE_ATTRIBUTES) {
        CreateDirectoryA(path_przenies_na_pulpit_hasla.c_str(), 0);
        std::cout << "Folder Hasla zostal utworzony" << std::endl;
    }
    path_przenies_na_pulpit_hasla+="\\pswd.cfg";
    std::cout<<"przenosze z "<<path_hasla_plik<<" do : "<<path_pulpit_konfigcs_dane;
    CopyFileA(path_hasla_plik.c_str(), path_przenies_na_pulpit_hasla.c_str(), FALSE);

    return true;



}

inline  bool create_backup(std::string nazwa_backup){

    std::string pathkopia = pathcsgo_main;
    pathkopia += "\\backup";
    if ((GetFileAttributesA(pathkopia.c_str())) == INVALID_FILE_ATTRIBUTES) {
        CreateDirectoryA(pathkopia.c_str(), 0);
        std::cout << "Folder backup zostal utworzony w " << pathkopia.c_str() << std::endl;
    }
    pathkopia+="\\";
    pathkopia+=nazwa_backup;
    if ((GetFileAttributesA(pathkopia.c_str())) == INVALID_FILE_ATTRIBUTES) {
        CreateDirectoryA(pathkopia.c_str(), 0);
        std::cout << "Folder "<<nazwa_backup<<" zostal utworzony w " << pathkopia.c_str() << std::endl;
    }
    else{
        return false; //jezeli kopia o tej nazwie juz jest
    }

    std::string pathkopiabackup;
    for(int i=1;i<lpm_users->used_slots;i++) {
        pathkopiabackup="";
        pathkopiabackup = pathkopia.c_str();
        pathkopiabackup += "\\";
        pathkopiabackup += get_steam_folder_id_from_path(lpm_users->bd2[i].path);
        std::cout<<pathkopiabackup<<std::endl;
        if ((GetFileAttributesA(pathkopiabackup.c_str())) == INVALID_FILE_ATTRIBUTES) {
            CreateDirectoryA(pathkopiabackup.c_str(), 0);
            std::cout << "Folder " << pathkopiabackup.c_str() << " zostal utworzony"
                      << std::endl;
        }
        std::string path2v = pathkopiabackup.c_str();
        std::string path2c = pathkopiabackup.c_str();
        path2c += "/config.cfg";
        path2v += "/video.txt";

        std::string path1c = pathdodajconfig(i);
        std::string path1v = pathdodajvideo(i);

        if ((CopyFileA(path1c.c_str(), path2c.c_str(), FALSE)) == 0) {
            std::cout << "Nie udalo sie skopiowac pliku, kod bledu: " << GetLastError() << std::endl;
            return false;
        } else
            std::cout << "Plik " << path1c.c_str() << " skopiowany pomyslnie" << std::endl;
        if ((CopyFileA(path1v.c_str(), path2v.c_str(), FALSE)) == 0) {
            std::cout << "Nie udalo sie skopiowac pliku, kod bledu: " << GetLastError() << std::endl;
            return false;
        } else
            std::cout << "Plik " << path1v.c_str() << " skopiowany pomyslnie" << std::endl;
    }
    return true;
}

inline bool load_backup(std::string nazwa_backup){

    std::string pathkopia = pathcsgo_main;
    pathkopia += "\\backup\\";
    pathkopia+=nazwa_backup;
    if ((GetFileAttributesA(pathkopia.c_str())) == INVALID_FILE_ATTRIBUTES) {
        std::cout << "Nie istnieje kopia zapasowa dla tego konta " << pathkopia.c_str() << std::endl;
        return false;
    }


    int ile_katalogow = listowanie_folderow(pathkopia,"",0,false);

    std::string sciezka_tmp = pathkopia;
    std::string sciezka_tmp_2;
    for(int i=0;i<ile_katalogow;i++){
        for(int j=1;j<=lpm_users->used_slots;j++){
            if(get_steam_folder_id_from_path(lpm_users->bd2[j].path) == list_kat[i].listowanie_katalogow_nazwa){

                sciezka_tmp = pathkopia;
                sciezka_tmp+="\\";
                sciezka_tmp += list_kat[i].listowanie_katalogow_nazwa;
                sciezka_tmp += "\\";
                sciezka_tmp += "\\config.cfg";

                sciezka_tmp_2 = lpm_users->bd2[j].path;
                sciezka_tmp_2 += "\\config.cfg";

                if ((CopyFileA(sciezka_tmp.c_str(), sciezka_tmp_2.c_str(), FALSE)) == 0) {
                    std::cout << "Nie udalo sie skopiowac pliku, kod bledu: " <<std::endl;
                    perror("");
                } else std::cout << "Plik " << sciezka_tmp.c_str() << " skopiowany pomyslnie" << std::endl;



                sciezka_tmp = pathkopia;
                sciezka_tmp+="\\";
                sciezka_tmp += list_kat[i].listowanie_katalogow_nazwa;
                sciezka_tmp += "\\";
                sciezka_tmp += "\\video.txt";

                sciezka_tmp_2 = lpm_users->bd2[j].path;
                sciezka_tmp_2 += "\\video.txt";

                if ((CopyFileA(sciezka_tmp.c_str(), sciezka_tmp_2.c_str(), FALSE)) == 0) {
                    std::cout << "Nie udalo sie skopiowac pliku, kod bledu: " <<std::endl;
                    perror("");
                } else std::cout << "Plik " << sciezka_tmp.c_str() << " skopiowany pomyslnie" << std::endl;

                break;
            }
        }
    }

    return true;

}


inline  bool save_crosshair(std::string nazwa_uzytkownika,std::string nazwa_kopii){
    int user_id = lpm_users->find_account_by_name(nazwa_uzytkownika);
    std::string sciezka_config = lpm_users->bd2[user_id].path;
    sciezka_config += "\\config.cfg";
    std::ifstream infile(sciezka_config);
    std::string pathkopia = pathcsgo_main;
    pathkopia += "\\crosshair_backup";
    if ((GetFileAttributesA(pathkopia.c_str())) == INVALID_FILE_ATTRIBUTES) {
        CreateDirectoryA(pathkopia.c_str(), 0);
    }
    pathkopia += "\\";
    pathkopia += nazwa_kopii;
    if ((GetFileAttributesA(pathkopia.c_str())) != INVALID_FILE_ATTRIBUTES){
        std::cout<<"Kopia o podanej nazwie juz istnieje! Czy chcesz nadpisac? (y/n)"<<std::endl;
        char pytanie;
        std::cin>>pytanie;
        if (pytanie != 'y')return false;
    }
    if ((GetFileAttributesA(pathkopia.c_str())) == INVALID_FILE_ATTRIBUTES) {
        CreateDirectoryA(pathkopia.c_str(), 0);
    }
    std::cout << "Folder crosshair_backup zostal utworzony w " << pathkopia.c_str() << std::endl;
    pathkopia += "\\crosshair.cfg";
    FILE *fp_create_cfg;
    if((fp_create_cfg=fopen(pathkopia.c_str(),"w"))!=NULL){
        std::string line;
        std::getline(infile, line);
        while (std::getline(infile, line))
        {
            if(line.length() > 10 && (line[0] == 'c' && line[1] == 'l' && line[2] == '_' && line[3] == 'c' && line[4] == 'r' && line[5] == 'o' && line[6] == 's' && line[7] == 's')){
                fprintf(fp_create_cfg,"%s\n",line.c_str());
            }
        }
        fclose(fp_create_cfg);
        infile.clear();
        return true;
    }
    return false;
}



inline bool load_crosshair(std::string nazwa_kopii,std::string nazwa_uzytkownika){

    struct crosshair_struct{
        std::string name;
        std::string value;
    };

    crosshair_struct crosshair[23];
    int licznik_crosshair=0;

    //ustawienie sciezek
    int user_id = lpm_users->find_account_by_name(nazwa_uzytkownika);
    std::string sciezka_config = lpm_users->bd2[user_id].path;
    sciezka_config += "\\config.cfg";

    std::string sciezka_kopia = pathcsgo_main;
    sciezka_kopia += "\\crosshair_backup\\";
    sciezka_kopia += nazwa_kopii;
    sciezka_kopia +="\\crosshair.cfg";

    std::string sciezka_file_temp = lpm_users->bd2[user_id].path;
    sciezka_file_temp += "\\kanton_temp_file.cfg";




    if ((GetFileAttributesA(sciezka_kopia.c_str())) == INVALID_FILE_ATTRIBUTES) {
        std::cout<<"Kopia o podanej nazwie nie istnieje!";

        return false;
    }



    FILE *fp_path_kopia;
    FILE *fp_temp;


    //wczytanie kopii do pamieci
    if((fp_path_kopia=fopen(sciezka_config.c_str(),"w"))!=NULL){
        while((fscanf(fp_path_kopia, "%s", crosshair[licznik_crosshair].name.c_str()))!=EOF) {
            fscanf(fp_path_kopia, "%s", crosshair[licznik_crosshair].value.c_str());
            licznik_crosshair++;
        }
        fclose(fp_path_kopia);
    }



    std::ifstream infile(sciezka_config);
    std::string line;
    std::string line_sprawdz_czy_cross;
    int m;
    fp_temp=fopen(sciezka_file_temp.c_str(),"a");
    while (std::getline(infile, line))
    {
        line_sprawdz_czy_cross = "";
        for (int j = 0;j<13;j++){
            line_sprawdz_czy_cross+=line[j];
        }

        if (line_sprawdz_czy_cross == "cl_crosshair"){
            line_sprawdz_czy_cross = "";
            m = 0;
            while (line[m]!= ' '){
                line_sprawdz_czy_cross+=line[m];
            }
            for (int i=0;i<licznik_crosshair;i++){
                if (line_sprawdz_czy_cross == crosshair[i].name){
                    fprintf(fp_temp,"%s %s\n",crosshair[i].name.c_str(),crosshair[i].value.c_str());
                    break;
                }
            }
        }
        else {
            fprintf(fp_temp,"%s\n",line.c_str());
        }
    }
    fclose(fp_temp);
    infile.close();
    infile.clear();



    std::string zmiana_nazwy =  lpm_users->bd2[user_id].path;
    zmiana_nazwy += "\\config(kopia).cfg";
    std::cout<<sciezka_config<<std::endl;
    std::cout<<zmiana_nazwy<<std::endl;
    std::cout<<sciezka_file_temp<<std::endl;
    std::cout<<sciezka_config<<std::endl;

    if ((GetFileAttributesA(zmiana_nazwy.c_str())) != INVALID_FILE_ATTRIBUTES) {
        remove(zmiana_nazwy.c_str());
    }

    int value = rename(sciezka_config.c_str(),zmiana_nazwy.c_str());
    if(!value)
    {
        printf("%s", "File name changed successfully \n");
    }
    else
    {
        perror("Error");
    }
    value = rename(sciezka_file_temp.c_str(),sciezka_config.c_str());
    if(!value)
    {
        printf("%s", "File name changed successfully \n");
    }
    else
    {
        perror("Error");
    }
    return true;
}


inline bool delete_crosshair(std::string nazwa_kopii){
    std::string sciezka_kopia = pathcsgo_main;
    sciezka_kopia += "\\crosshair_backup\\";
    sciezka_kopia += nazwa_kopii;
    sciezka_kopia +="\\crosshair.cfg";
    if ((GetFileAttributesA(sciezka_kopia.c_str())) != INVALID_FILE_ATTRIBUTES){
        remove (sciezka_kopia.c_str());
        sciezka_kopia = pathcsgo_main;
        sciezka_kopia += "\\crosshair_backup\\";
        sciezka_kopia += nazwa_kopii;
        RemoveDirectoryA(sciezka_kopia.c_str());
        return true;
    }
    else{
        perror("");
        return false;
    }
}

inline  bool reload_all(){
    stworz_sciezki();
    lpm_users->reload();
    lpm_config->reload();
    lpm_password->reload();
    if(lpm_config->cfg[0].value != wersja_KantonLPM){
        lpm_config->cfg[0].value=wersja_KantonLPM;
        lpm_config->save_to_file();
    }
    return true;
}


inline std::string read_username_from_vdf(std::string sciezka){
    std::ifstream infile(sciezka);
    std::string line;
    std::string tmp;

    while (std::getline(infile, line))
    {
        tmp="";
        for (int i=0;i<line.length()-1;i++){
            if(line[i]=='\"'){
                i++;
                while(line[i]!='\"'){
                    tmp+=line[i];
                    i++;
                }
                if (tmp=="PersonaName"){
                    int counter=0;
                    int m=0;
                    tmp="";
                    while(counter<3){
                        if(line[m]=='\"')counter++;
                        m++;
                    }
                    while(line[m]!='\"'){
                        tmp+=line[m];
                        m++;
                    }
                    return tmp;
                }
            }
        }
    }
    return "Nie znaleziono!";
}



inline bool compare_passwords(std::string password){
    lpm_password->reload();
    if(password=="")return false;
    long int VF_int[500];
    long int VF_saved[500];
    rsa_encrypt(password,VF_int);
    int licz =0;
    std::string int_to_string_temp="";
    for(int i=0;i<lpm_password->pswd[0].password.length()-1;i++){
        if(lpm_password->pswd[0].password[i]==' '){
            VF_saved[licz] = stoi(int_to_string_temp);
            int_to_string_temp="";
            licz++;
        }
        else{
            int_to_string_temp += lpm_password->pswd[0].password[i];
        }
    }
    VF_saved[licz]=-1;

    if(sizeof(VF_int)/sizeof (long int) == sizeof(VF_saved)/sizeof (long int)){
        for(int i=0;VF_int[i]!=-1;i++){
            if(VF_int[i] != VF_saved[i])return false;
        }
        return true;
    }
    else return false;
}



inline void copy_to_clipboard(std::string message){
    const size_t len = strlen(message.c_str()) + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem),message.c_str(), len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}

inline bool compare_strings(std::string tekst_1,std::string tekst_2){
    if(tekst_1.length() != tekst_2.length()){
        return false;
    }
    for(int i=0;i<tekst_1.length();i++){
        if(tekst_1[i] != tekst_2[i]){
            return false;
        }
    }
    return true;
}


inline std::string get_login_from_string(std::string input){
    std::string login = "";
    int max,min;


    for(int i=5;i<input.length();i++){ // 5 bo 1 znaki to Name:
        if(input[i]==' ' && input[i+1]=='|' && input[i+2]=='|' && input[i+3]==' ' && input[i+4]=='l' && input[i+5]=='o' && input[i+6]=='g' && input[i+7]=='i' && input[i+8]=='n' & input[i+9]==':'){
            min = i+11;
            break;
        }
    }


    for(int j=min;j<input.length();j++){
        if(input[j]==' ' && input[j+1]=='|' && input[j+2]=='|' && input[j+3]==' ' && input[j+4]=='p' && input[j+5]=='a' && input[j+6]=='s' && input[j+7]=='s' && input[j+8]=='w' && input[j+9]=='o' && input[j+10]=='r' && input[j+11]=='d' && input[j+12]==':'){
            max = j;
            break;
        }
    }


    for(int j=min;j<max-1;j++){
        login+=input[j];
    }
    return login;
}

inline std::string get_password_from_string(std::string input){
    std::string password="";
    for(int i=0;i<input.length();i++){
        if(input[i]==' ' && input[i+1]=='|' && input[i+2]=='|' && input[i+3]==' ' && input[i+4]=='p' && input[i+5]=='a' && input[i+6]=='s' && input[i+7]=='s' && input[i+8]=='w' && input[i+9]=='o' && input[i+10]=='r' && input[i+11]=='d' && input[i+12]==':'){
            i=i+14;
            for(i;i<input.length();i++){
                password+=input[i];
            }
            return password;
        }
    }
}

inline std::string get_name_from_string(std::string input){
    std::string nazwa_konta = "";
    for(int i=5;i<input.length();i++){ // 5 bo 1 znaki to Name:
        if(input[i]==' ' && input[i+1]=='|' && input[i+2]=='|' && input[i+3]==' ' && input[i+4]=='l' && input[i+5]=='o' && input[i+6]=='g' && input[i+7]=='i' && input[i+8]=='n' & input[i+9]==':'){
            for(int j=6;j<i;j++){
                nazwa_konta+=input[j];
            }
            return nazwa_konta;
        }
    }
}

inline std::string get_file_modification_date(std::string filepath){

    char timeStr[ 100 ] = "";
    struct stat buf;
    time_t ltime;
    char datebuf [9];
    char timebuf [9];
    std::string sciezka_bd2=filepath;
    sciezka_bd2+="\\config.cfg";
    if (!stat(filepath.c_str(), &buf))
    {
        strftime(timeStr, 100, "%d-%m-%Y %H:%M:%S", localtime( &buf.st_mtime));
        std::stringstream ss;
        ss << timeStr;
        std::string ts = ss.str();
        return ts;
    }
    else return " not_found";


}

inline std::string steam_user_list_get_username_from_string(std::string input){
    std::string return_nazwa="";
    for (int i=0;i<input.length()-40;i++){
        return_nazwa+=input[i];
    }
    return return_nazwa;
}

inline bool move_custom_file_to_csgo_folder(std::string path,std::string file_name){
    std::string sciezka_docelowa = lpm_config->cfg[3].value;
    sciezka_docelowa+=sciezka_do_folderu_z_gra;
    sciezka_docelowa+="\\";
    sciezka_docelowa+=file_name;
    if((CopyFileA(path.c_str(), sciezka_docelowa.c_str(), FALSE))==0){
        //std::cout<<"Nie udalo sie skopiowac pliku, kod bledu: "<<GetLastError()<<std::endl;
        return false;
    }
    else return true;
}

inline void restart_programu(){
    std::string restart = pathappdata;
    restart+="\\bin\\LPM_GUI.exe";
    ShellExecuteA(NULL, "open", restart.c_str(), NULL, NULL, SW_SHOWDEFAULT);
    exit(0);
}

inline std::string get_steam_folder_id_from_path(std::string input){
    std::string return_value="";
    int min=input.length()-15;
    while(input[min]!='\\'){
        min--;
    }
    for(int i=min+1;i<(input.length()-14);i++){
        return_value+=input[i];
    }
    return return_value;
}

inline std::string vdf_read_launch_options(std::string file_path){
    std::ifstream vdf_file("C:\\Programy\\Steam\\userdata\\60074252\\config\\localconfig.vdf");
    std::string line;
    std::string return_value = "";
    std::getline(vdf_file,line);
    while(getline(vdf_file,line)){
        if(line == "					\"730\""){
            std::getline(vdf_file,line);
            while(std::getline(vdf_file,line)){
                int j=0;
                for(j;line[j]!='"';j++);
                if(line[j] == '"' && line[j+1] == 'L' && line[j+2] == 'a' && line[j+3] == 'u' && line[j+4] == 'n' && line[j+5] == 'c' && line[j+6] == 'h' && line[j+7] == 'O' && line[j+8] == 'p' && line[j+9] == 't' && line[j+10] == 'i' && line[j+11] == 'o' && line[j+12] == 'n' && line[j+13] == 's'){
                    int i=j+15;
                    while(i<line.length() && line[i]!='"'){
                        i++;
                    }
                    i+=1;
                    for(i;i<line.length()-1;i++){
                        return_value+=line[i];
                    }
                    return return_value;
                }
            }
        }

    }
    return "Error! Launch options not found!";
}

inline bool vdf_save_launch_options(std::string file_path,std::string launch_options){

    std::ifstream vdf_file(file_path);
    std::string line;
    std::string new_value = "";

    std::string tmp_directory =pathcsgo_main;
    tmp_directory+="\\temp";


    if ((GetFileAttributesA(tmp_directory.c_str())) == INVALID_FILE_ATTRIBUTES) {
        CreateDirectoryA(tmp_directory.c_str(), 0);
    }

    tmp_directory+="\\vdf_temp.vdf";

    std::ofstream copy_file(tmp_directory);

    while(getline(vdf_file,line)){
        if(line == "					\"730\""){
            copy_file <<line<<std::endl;
            std::getline(vdf_file,line);
            copy_file <<line<<std::endl;
            int j=0;
            int sign_counter=0;
            int i=0;
            while(std::getline(vdf_file,line)){
                j=0;
                for(j;line[j]!='"';j++);
                if(line[j] == '"' && line[j+1] == 'L' && line[j+2] == 'a' && line[j+3] == 'u' && line[j+4] == 'n' && line[j+5] == 'c' && line[j+6] == 'h' && line[j+7] == 'O' && line[j+8] == 'p' && line[j+9] == 't' && line[j+10] == 'i' && line[j+11] == 'o' && line[j+12] == 'n' && line[j+13] == 's'){
                    sign_counter=0;
                    i=0;
                    for(int i=0;sign_counter<=2;i++){
                        new_value+=line[i];
                        if(line[i]=='"'){
                            sign_counter++;
                        }
                    }
                    new_value+=launch_options;
                    new_value+='"';
                    copy_file <<new_value<<std::endl;
                }
                else copy_file <<line<<std::endl;
            }
        }
        else {
         copy_file <<line<<std::endl;
        }
    }

    if((CopyFileA(tmp_directory.c_str(), file_path.c_str(), FALSE))==0){
        return false;
    }
    remove(tmp_directory.c_str());
    tmp_directory =pathcsgo_main;
    tmp_directory+="\\temp";
    RemoveDirectoryA(tmp_directory.c_str());
    return true;

}

#endif // LPM_UTILITY_H
