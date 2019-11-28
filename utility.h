#ifndef TEST_UTILITY_H
#define TEST_UTILITY_H

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


int rozmiar_cfg_generalnego=5;
void bd2_wyswietl();
int bd2_reload();
bool bd2_add_user(std::string nazwa,std::string sciezka);
bool bd2_remove_user(std::string nazwa_user);
bool bd2_rename_user(std::string nazwa);
bool bd2_zapisz_do_pliku();
void cfg_gen_reload();
void cfg_gen_policz();
void cfg_gen_wyswietl();
void cfg_gen_zapisz_do_pliku();
bool cfg_gen_dodaj_sciezke_steam_csgo();
bool cfg_gen_dodaj_sciezke_steam();
void load_backup(std::string nazwa_backup);
bool movepliki(int wybor,int liczkonta);
int listowanie_folderow(std::string listowanie_folderow_path,std::string ustawienie,int dlugosc_ciagu,bool wyswietlic);  //(nazwa,"",0) == bez filtrow
std::string odczytaj_nazwe_konta(std::string sciezka);
void znajdz_nazwe_konta(bool wyswietl);
int znajdz_konto_po_nazwie(std::string nazwa_konta);
void exportuj_pliki();
void create_backup(std::string nazwa_backup);
bool zapisz_celowink(std::string nazwa_uzytkownika,std::string nazwa_kopii);
bool wczytaj_celownik(std::string nazwa_kopii,std::string nazwa_uzytkownika);
bool reload_all();
std::string odczytaj_nazwe_user_z_vdf(std::string sciezka);
bool patch_nazwy_ponad_ascii();

std::string wersja_KantonLPM = "v3.1.1";
std::string wersja_premium = "premium";

struct bd2_struct
{
    std::string nazwa;
    std::string sciezka;
};
struct config_programu
{
    std::string nazwa;
    std::string wartosc;
};

bd2_struct bd2[20]; // max kont = 10;
config_programu cfg[10]; //ile opcji moze byc w configu

struct listowanie_katalogow_struct{
    std::string listowanie_katalogow_nazwa;
    int listowanie_katalogow_numer_katalogu;
};

struct wyszukiwanie_nazwy_konta_struct{
    std::string nazwa_konta_steam;
    std::string id_steam;
};
wyszukiwanie_nazwy_konta_struct wyszukiwanie_nazwy_konta[15];
listowanie_katalogow_struct list_kat[100];


int liczkonta;
int licz_ile_w_cfg;
std::string pathappdata;
std::string path_pulpit;
std::string steam_folder;
std::string path_pulpit_konfigcs;
std::string path_config;
std::string pathcsgo_main;
std::string pathdane;
std::string pathftp_main;
std::string pathhasla_main;
std::string steam_csgo_folder;
std::string wersja_programu;
std::string sciezka_do_folderu_z_gra;

void stworz_sciezki() {

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



    pathappdata += getenv("AppData"); // sciezka do appdata
    path_pulpit_konfigcs += cfg[1].wartosc;
    wersja_programu = cfg[4].wartosc;
    path_pulpit = cfg[1].wartosc;
    steam_folder = cfg[2].wartosc;
    steam_csgo_folder = cfg[3].wartosc;
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

    cfg[0].nazwa="config_glowny";
    cfg[1].nazwa="path_pulpit";
    cfg[2].nazwa="path_steam";
    cfg[3].nazwa="path_steam_csgo";
    cfg[4].nazwa="wersja_programu";

}

std::string pathdodajconfig(int wybor,bd2_struct* bd2)
{
    std::string pathdodajconfigstr = bd2[wybor].sciezka;
    pathdodajconfigstr += "/config.cfg";
    return pathdodajconfigstr;
}

std::string pathdodajvideo(int wybor,bd2_struct* bd2)
{
    std::string pathdodajvideostr = bd2[wybor].sciezka;
    pathdodajvideostr += "/video.txt";
    return pathdodajvideostr;
}

bool movepliki(int wybor,int liczkonta)
{
    int bladtmp=1;
    //std::cout<<"Przenoszenie z "<<bd2[wybor].nazwa<<std::endl;
    int tmpwybor = wybor;
    tmpwybor++;

    while(tmpwybor<liczkonta){
        std::string path1c = pathdodajconfig(wybor,bd2);
        std::string path1v = pathdodajvideo(wybor,bd2);

        std::string path2c = pathdodajconfig(tmpwybor,bd2);
        std::string path2v = pathdodajvideo(tmpwybor,bd2);

        if((CopyFileA(path1c.c_str(), path2c.c_str(), FALSE))==0){
            //std::cout<<"Nie udalo sie skopiowac pliku, kod bledu: "<<GetLastError()<<std::endl;
            return false;
        }
        if((CopyFileA(path1v.c_str(), path2v.c_str(), FALSE))==0){
            //std::cout<<"Nie udalo sie skopiowac pliku, kod bledu: "<<GetLastError()<<std::endl;
            return false;
        }
        tmpwybor++;
    }

    tmpwybor = wybor;
    tmpwybor--;
    while(tmpwybor>0){
        std::string path1c = pathdodajconfig(wybor,bd2);
        std::string path1v = pathdodajvideo(wybor,bd2);

        std::string path2c = pathdodajconfig(tmpwybor,bd2);
        std::string path2v = pathdodajvideo(tmpwybor,bd2);

        if((CopyFileA(path1c.c_str(), path2c.c_str(), FALSE))==0){
            //std::cout<<"Nie udalo sie skopiowac pliku, kod bledu: "<<GetLastError()<<std::endl;
            return false;
            bladtmp = 3;
        }
        if((CopyFileA(path1v.c_str(), path2v.c_str(), FALSE))==0){
            //std::cout<<"Nie udalo sie skopiowac pliku, kod bledu: "<<GetLastError()<<std::endl;
            return false;
            bladtmp = 3;
        }
        tmpwybor--;
    }
    //if(bladtmp ==3) std::cout<<"Nie udalo sie skopiowac plikow,"<<std::endl;
    //else std::cout<<"Kopiowanie plikow z "<<bd2[wybor].nazwa<<" zakonczone"<<std::endl;
    return true;
}




void cfg_gen_reload() {
    std::string path_config_tmp = path_config;
    path_config_tmp += "\\config.cfg";
    if ((GetFileAttributesA(path_config_tmp.c_str())) != INVALID_FILE_ATTRIBUTES) {

        std::ifstream infile(path_config_tmp);
        std::string line;
        int numer=0,i=0;
        while (std::getline(infile, line))
        {
            i=0;
            cfg[numer].nazwa="";
            cfg[numer].wartosc="";
            for(i;i<line.length();i++){
                if(line[i]==' '){
                    i++;
                    break;
                }
                else cfg[numer].nazwa+=line[i];
            }
            for(i;i<line.length();i++){
                cfg[numer].wartosc+=line[i];
            }
            numer++;
        }
        infile.clear();
        licz_ile_w_cfg=numer;
    }

}

int bd2_reload(){


    int liczkonta_tmp=1;
    std::ifstream infile(pathdane);
    std::string line;
    std::getline(infile, line);
    while (std::getline(infile, line))
    {
        bd2[liczkonta_tmp].nazwa=line;
        std::getline(infile, line);
        bd2[liczkonta_tmp].sciezka = line;
        liczkonta_tmp++;
    }

    liczkonta=liczkonta_tmp;
    return liczkonta_tmp;
}

void cfg_gen_wyswietl(){
    std::string path_config_tmp = path_config;
    path_config_tmp += "\\config.cfg";
    std::cout<<std::endl;
    std::cout<<"Z pliku: "<<std::endl;
    if ((GetFileAttributesA(path_config_tmp.c_str())) != INVALID_FILE_ATTRIBUTES) {

        std::ifstream infile(path_config_tmp);
        std::string line;
        while (std::getline(infile, line))
        {
            std::cout<<line<<std::endl;
        }
        infile.clear();
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"z pamieci: "<<std::endl;
    for (int i=0;i<licz_ile_w_cfg;i++){
        std::cout<<cfg[i].nazwa<<" "<<cfg[i].wartosc<<std::endl;
    }
}
void cfg_gen_policz(){
    std::string path_config_tmp = path_config;
    path_config_tmp += "\\config.cfg";
    if ((GetFileAttributesA(path_config_tmp.c_str())) != INVALID_FILE_ATTRIBUTES) {

        std::ifstream infile(path_config_tmp);
        std::string line;
        int numer=0;
        while (std::getline(infile, line))
        {
            numer++;
        }
        infile.close();
        licz_ile_w_cfg=numer;
    }

}
void cfg_gen_zapisz_do_pliku(){


    std::string path_config_tmp = path_config;
    path_config_tmp += "\\config.cfg";
    cfg_gen_policz();

    std::cout<<"modyfikowanie cfg glownego"<<std::endl;
    system("cls");

    if ((GetFileAttributesA(path_config_tmp.c_str())) != INVALID_FILE_ATTRIBUTES){
        FILE *fp_upgrade;
        if ((fp_upgrade = fopen(path_config_tmp.c_str(), "w")) != NULL)
        {

            for (int i = 0; i < rozmiar_cfg_generalnego; i++)
            {
                fprintf(fp_upgrade, "%s ", cfg[i].nazwa.c_str());
                if(cfg[i].wartosc!="")fprintf(fp_upgrade, "%s\n", cfg[i].wartosc.c_str());
                else fprintf(fp_upgrade, "brak_danych\n");
            }
            fclose(fp_upgrade);
            stworz_sciezki();
            cfg_gen_policz();
            cfg_gen_reload();
            stworz_sciezki();
        }
        else {
            std::cout << "Nie udalo sie otworzyc pliku config, zmiany nie zostaly zachowane! \n" << std::endl;
            system("pause");
        }
    }

}

int listowanie_folderow(std::string listowanie_folderow_path,std::string ustawienie,int dlugosc_ciagu,bool wyswietlic) {  //(nazwa,"",0) == bez filtrow
    int wyliczanie = 0;
    DIR *dir;
    struct dirent *ent;
    std::string listowanie_tmp;
    std::string listowanie_tmp_2;
    if ((dir = opendir(listowanie_folderow_path.c_str())) != NULL) {
/* print all the files and directories within directory */
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
/* could not open directory */
        perror("");
        return EXIT_FAILURE;
    }
}


bool bd2_add_user(std::string nazwa,std::string sciezka){


    if ((GetFileAttributesA(sciezka.c_str())) == INVALID_FILE_ATTRIBUTES) {
        std::cout<<"Podana sciezka jest niepoprawna!"<<std::endl;
        system("pause");
        return false;
    }

    for(int i=0;i<nazwa.length();i++){
        if((int)nazwa[i]>255 || (int)nazwa[i]<=0){
            std::cout<<"nazwa "<<nazwa<<" zawiera niedozwolone znaki, podaj inna nazwe lub 0 any wyjsc"<<std::endl;
            std::getline(std::cin, nazwa);
            if(nazwa=="0")return false;
            else break;
        }
    }

    for (int i = 0; i < liczkonta; i++) {
        if (nazwa == bd2[i].nazwa) {
            std::cout << "Konto o podanej nazwie juz istnieje! Zmiany nie zostana wprowadzone" << std::endl;
            system("pause");
            return false;
        }
        if (sciezka == bd2[i].sciezka) {
            std::cout << "To konto zostalo juz dodane!Zmiany nie zostana wprowadzone " << std::endl;
            system("pause");
            return false;
        }
    }



    bd2[liczkonta].nazwa = nazwa;
    bd2[liczkonta].sciezka = sciezka;
    liczkonta+=1;


    if(bd2_zapisz_do_pliku()){
        std::cout<<"Uzytkownik "<<bd2[liczkonta].nazwa<<" zostal dodany!"<<std::endl;
        system("pause");
        return true;
    }
    else {
        std::cout<<"Wystapil blad!Zmiany nie zostaly zachowane!"<<std::endl;
        system("pause");
        return false;
    }

}


std::string odczytaj_nazwe_konta(std::string sciezka){
    std::string odczytaj_nazwe_konta_sciezka = steam_folder;
    odczytaj_nazwe_konta_sciezka+="\\userdata\\";
    odczytaj_nazwe_konta_sciezka+=sciezka;
    odczytaj_nazwe_konta_sciezka+="\\730\\local\\cfg\\config.cfg";
    std::string bufor;


    FILE *plik_config_konta_steam;
    if ((plik_config_konta_steam = fopen(odczytaj_nazwe_konta_sciezka.c_str(), "r")) != NULL){

        while ((fscanf(plik_config_konta_steam,"%s",bufor.c_str()))!=EOF){
            if (bufor[0]=='n' && bufor[1]=='a' && bufor[2]=='m' && bufor[3]=='e'){
                fscanf(plik_config_konta_steam,"%s",bufor.c_str());
                fclose(plik_config_konta_steam);
                return bufor.c_str();
            }
        }
    }
    else {
        std::cout << "Nie udalo sie otworzyc pliku "<<odczytaj_nazwe_konta_sciezka.c_str()<<"\n" << std::endl;
        return "Blad odczytu";
    }
    return "Blad";
}



void znajdz_nazwe_konta(bool wyswietl){
    stworz_sciezki();
    std::string sciezka_do_profilu_tmp = steam_folder;
    sciezka_do_profilu_tmp+="\\userdata";
    int ile_folderow = listowanie_folderow(sciezka_do_profilu_tmp,"",0,false);
    for(int i = 1 ; i<=ile_folderow;i++){
        wyszukiwanie_nazwy_konta[i].nazwa_konta_steam = odczytaj_nazwe_konta(list_kat[i].listowanie_katalogow_nazwa);
        wyszukiwanie_nazwy_konta[i].id_steam = list_kat[i].listowanie_katalogow_nazwa;
        if(wyswietl)std::cout<<"("<<i<<") "<<wyszukiwanie_nazwy_konta[i].nazwa_konta_steam.c_str()<<" Id steam: "<<wyszukiwanie_nazwy_konta[i].id_steam.c_str()<<std::endl;
    }
}

void bd2_wyswietl(){


    std::ifstream infile(pathdane);
    std::string line;
    std::getline(infile, line);
    while (std::getline(infile, line))
    {
        std::cout<<line<<" ";
        std::getline(infile, line);
        std::cout<<line<<std::endl;
    }
}

int znajdz_konto_po_nazwie(std::string nazwa_konta){
    for(int i=1;i<liczkonta;i++){
        if (bd2[i].nazwa == nazwa_konta)return i;
    }
    return 0;
}

void exportuj_pliki(){
    std::string path_przenies_na_pulpit = cfg[1].wartosc;
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
    else std::cout << "Plik skopiowany pomyslnie" << std::endl;

    /*
    std::string path_backupcfg = path_przenies_na_pulpit_csgo;
    path_backupcfg +="\\backup";
    if ((GetFileAttributesA(path_backupcfg.c_str())) == INVALID_FILE_ATTRIBUTES) {
        CreateDirectoryA(path_backupcfg.c_str(), 0);
        std::cout << "Folder config zostal utworzony" << std::endl;
    }
    int policz_foldery = listowanie_folderow(path_backupcfg,"",0,false);
    std::string tmp_path_backup;
    for (int i=1;i<=policz_foldery;i++){
        tmp_path_backup=path_backupcfg;
        tmp_path_backup+="\\";
        tmp_path_backup+=list_kat[i].listowanie_katalogow_nazwa;
        if ((GetFileAttributesA(tmp_path_backup.c_str())) == INVALID_FILE_ATTRIBUTES) {
            CreateDirectoryA(tmp_path_backup.c_str(), 0);
            CopyFileA(pathdane.c_str(), path_pulpit_konfigcs_dane.c_str(), FALSE);
        }
    }
    */

}

void create_backup(std::string nazwa_backup){

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
    std::string pathkopiabackup;
    for(int i=1;i<liczkonta;i++) {
        pathkopiabackup="";
        pathkopiabackup = pathkopia.c_str();
        pathkopiabackup += "\\";
        pathkopiabackup += bd2[i].nazwa;
        if ((GetFileAttributesA(pathkopiabackup.c_str())) == INVALID_FILE_ATTRIBUTES) {
            CreateDirectoryA(pathkopiabackup.c_str(), 0);
            std::cout << "Folder " << pathkopiabackup.c_str() << " zostal utworzony"
                      << std::endl;
        }
        std::string path2v = pathkopiabackup.c_str();
        std::string path2c = pathkopiabackup.c_str();
        path2c += "/config.cfg";
        path2v += "/video.txt";

        std::string path1c = pathdodajconfig(i, bd2);
        std::string path1v = pathdodajvideo(i, bd2);

        if ((CopyFileA(path1c.c_str(), path2c.c_str(), FALSE)) == 0) {
            std::cout << "Nie udalo sie skopiowac pliku, kod bledu: " << GetLastError() << std::endl;
        } else
            std::cout << "Plik " << path1c.c_str() << " skopiowany pomyslnie" << std::endl;
        if ((CopyFileA(path1v.c_str(), path2v.c_str(), FALSE)) == 0) {
            std::cout << "Nie udalo sie skopiowac pliku, kod bledu: " << GetLastError() << std::endl;
        } else
            std::cout << "Plik " << path1v.c_str() << " skopiowany pomyslnie" << std::endl;
    }
    system("pause");

}

void load_backup(std::string nazwa_backup){

    std::string pathkopia = pathcsgo_main;
    pathkopia += "\\backup\\";
    pathkopia+=nazwa_backup;
    if ((GetFileAttributesA(pathkopia.c_str())) == INVALID_FILE_ATTRIBUTES) {
        std::cout << "Nie istnieje kopia zapasowa dla tego konta " << pathkopia.c_str() << std::endl;
        return;
    }


    std::string pathkopiabackup;
    for(int i=1;i<liczkonta;i++) {
        pathkopiabackup="";
        pathkopiabackup = pathkopia.c_str();
        pathkopiabackup += "\\";
        pathkopiabackup += bd2[i].nazwa;

        if ((GetFileAttributesA(pathkopiabackup.c_str())) == INVALID_FILE_ATTRIBUTES) {
            CreateDirectoryA(pathkopiabackup.c_str(), 0);
        }

        std::string path1v = pathkopiabackup.c_str();
        std::string path1c = pathkopiabackup.c_str();
        path1c += "\\config.cfg";
        path1v += "\\video.txt";

        std::string path2c = pathdodajconfig(i, bd2);
        std::string path2v = pathdodajvideo(i, bd2);

        if ((CopyFileA(path1c.c_str(), path2c.c_str(), FALSE)) == 0) {
            std::cout << "Nie udalo sie skopiowac pliku, kod bledu: " << GetLastError() << std::endl;
        } else
            std::cout << "Plik " << path1c.c_str() << " wczytany pomyslnie" << std::endl;
        if ((CopyFileA(path1v.c_str(), path2v.c_str(), FALSE)) == 0) {
            std::cout << "Nie udalo sie skopiowac pliku, kod bledu: " << GetLastError() << std::endl;
        } else
            std::cout << "Plik " << path1v.c_str() << " wczytany pomyslnie" << std::endl;
    }
    system("pause");
}

bool bd2_remove_user(std::string nazwa_user){
    int numer_konta = znajdz_konto_po_nazwie(nazwa_user);
    if (numer_konta==0){
        std::cout<<"Konto o podanej nazwie nie istnieje!"<<std::endl;
        system("pause");
        return false;
    }
    for(int i=numer_konta;i<liczkonta-1;i++){
        bd2[i].nazwa = bd2[i+1].nazwa;
        bd2[i].sciezka = bd2[i+1].sciezka;
    }
    bd2[liczkonta-1].nazwa="";
    bd2[liczkonta-1].sciezka="";
    liczkonta-=1;
    if(bd2_zapisz_do_pliku()){
        bd2_reload();
        std::cout<<"Uzytkownik zostal usuniety!"<<std::endl;
        system("pause");
        return true;
    }
    else{
        std::cout << "Nie udalo sie otworzyc pliku dane_csgo, zmiany nie zostaly zachowane! \n" << std::endl;
        bd2_reload();
        system("pause");
        return false;
    }
}

bool bd2_zapisz_do_pliku(){

    std::cout<<"Modyfikowanie bd2"<<std::endl;
    system("cls");

    if ((GetFileAttributesA(pathdane.c_str())) != INVALID_FILE_ATTRIBUTES){
        FILE *fp_upgrade;
        if ((fp_upgrade = fopen(pathdane.c_str(), "w")) != NULL)
        {
            fprintf(fp_upgrade, "konta_steam \n");
            for (int i = 1; i < liczkonta; i++)
            {
                fprintf(fp_upgrade, "%s\n", bd2[i].nazwa.c_str());
                fprintf(fp_upgrade, "%s\n", bd2[i].sciezka.c_str());
            }
            fclose(fp_upgrade);
            std::cout<<"Zmiany zostaly wprowadzone!"<<std::endl;
            return true;
        }
        else {
            std::cout << "Nie udalo sie otworzyc pliku dane_csgo, zmiany nie zostaly zachowane! \n" << std::endl;
            system("pause");
            return false;
        }
    }
    else {
        system("cls");
        std::cout<<"Plik dane_csgo nie istnieje!Zmiany nie zostaly zachowane!"<<std::endl;
        system("pasue");
        return false;
    }
}

bool cfg_gen_dodaj_sciezke_steam(){

    std::string ustawienia_sciezka_tmp;
    std::cout<<"(1) Podaj sciezke do folderu steam: "<<std::endl;
    std::cout<<"np: C:\\Steam"<<std::endl;
    ustawienia_sciezka_tmp="";
    std::getline(std::cin, ustawienia_sciezka_tmp);
    if ((GetFileAttributesA(ustawienia_sciezka_tmp.c_str())) != INVALID_FILE_ATTRIBUTES){
        cfg[2].wartosc=ustawienia_sciezka_tmp;
        stworz_sciezki();
        cfg_gen_zapisz_do_pliku();
        std::cout<<"Sciezka do folderu steam zostala dodana!"<<std::endl;
        system("pause");
        return true;
    }
    else {
        std::cout<<"Sciezka do folderu steam nie jest poprawna!"<<std::endl;
        system("pause");
        return false;
    }

}


bool zapisz_celowink(std::string nazwa_uzytkownika,std::string nazwa_kopii){
    int user_id = znajdz_konto_po_nazwie(nazwa_uzytkownika);
    std::string sciezka_config = bd2[user_id].sciezka;
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



bool wczytaj_celownik(std::string nazwa_kopii,std::string nazwa_uzytkownika){



    struct crosshair_struct{
        std::string nazwa;
        std::string wartosc;
    };

    crosshair_struct crosshair[23];
    int licznik_crosshair=0;



    //ustawienie sciezek
    int user_id = znajdz_konto_po_nazwie(nazwa_uzytkownika);
    std::string sciezka_config = bd2[user_id].sciezka;
    sciezka_config += "\\config.cfg";

    std::string sciezka_kopia = pathcsgo_main;
    sciezka_kopia += "\\crosshair_backup\\";
    sciezka_kopia += nazwa_kopii;
    sciezka_kopia +="\\crosshair.cfg";

    std::string sciezka_file_temp = bd2[user_id].sciezka;
    sciezka_file_temp += "\\kanton_temp_file.cfg";




    if ((GetFileAttributesA(sciezka_kopia.c_str())) == INVALID_FILE_ATTRIBUTES) {
        std::cout<<"Kopia o podanej nazwie nie istnieje!";
        system("pause");
        return false;
    }



    FILE *fp_path_kopia;
    FILE *fp_temp;


    //wczytanie kopii do pamieci
    if((fp_path_kopia=fopen(sciezka_config.c_str(),"w"))!=NULL){
        while((fscanf(fp_path_kopia, "%s", crosshair[licznik_crosshair].nazwa.c_str()))!=EOF) {
            fscanf(fp_path_kopia, "%s", crosshair[licznik_crosshair].wartosc.c_str());
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
                if (line_sprawdz_czy_cross == crosshair[i].nazwa){
                    fprintf(fp_temp,"%s %s\n",crosshair[i].nazwa.c_str(),crosshair[i].wartosc.c_str());
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



    std::string zmiana_nazwy =  bd2[user_id].sciezka;
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
bool usun_celownik(std::string nazwa_kopii){
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


bool cfg_gen_dodaj_sciezke_steam_csgo(){

    std::string ustawienia_sciezka_tmp;
    std::cout<<"(2) Podaj sciezke do folderu steam gdzie zainstalowany jest csgo: "<<std::endl;
    std::cout<<"np: C:\\steamlibrary"<<std::endl;
    std::cout<<"Jezeli csgo jest zainstalowany na tym samym dysku co program Steam ponownie wpisz poprzednio podana sciezke"<<std::endl;
    if(cfg[2].wartosc!="brak_danych")std::cout<<"( "<<cfg[2].wartosc<<" )"<<std::endl;
    ustawienia_sciezka_tmp="";
    std::getline(std::cin, ustawienia_sciezka_tmp);
    if ((GetFileAttributesA(ustawienia_sciezka_tmp.c_str())) != INVALID_FILE_ATTRIBUTES){
        cfg[3].wartosc=ustawienia_sciezka_tmp;
        stworz_sciezki();
        cfg_gen_zapisz_do_pliku();
        std::cout<<"Sciezka do folderu steam z csgo zostala dodana!"<<std::endl;
        system("pause");
        return true;
    }
    else {
        std::cout<<"Sciezka do folderu steam csgo nie jest poprawna!"<<std::endl;
        system("pause");
        return false;
    }

}

bool reload_all(){
    stworz_sciezki();
    //std::cout<<"sciezki stworzone!"<<std::endl;
    liczkonta = bd2_reload();
    //std::cout<<"Konta policzone!"<<std::endl;
    cfg_gen_reload();
    cfg_gen_policz();
    //std::cout<<"Konfig glowny wczytany!"<<std::endl;
    if(cfg[0].wartosc != wersja_KantonLPM){
        cfg[0].wartosc=wersja_KantonLPM;
        cfg_gen_zapisz_do_pliku();
    }
    return true;
}


std::string odczytaj_nazwe_user_z_vdf(std::string sciezka){
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

bool bd2_rename_user(std::string nazwa){
    int id_konta = znajdz_konto_po_nazwie(nazwa);
    if (id_konta==0){
        std::cout<<"Konto o podanej nazwie nie istnieje! Zmiany nie zostaly zachowane!"<<std::endl;
        system("sleep");
        return false;
    }

    std::cout<<"Podaj nowa nazwe: "<<std::endl;
    std::string nowa_nazwa;
    std::getline(std::cin,nowa_nazwa);

    int id_konta_check = znajdz_konto_po_nazwie(nazwa);
    if (id_konta_check==0){
        std::cout<<"Konto o podanej nazwie juz istnieje! Zmiany nie zostaly zachowane!"<<std::endl;
        system("pause");
        return false;
    }

    bd2[id_konta].nazwa = nowa_nazwa;
    if(bd2_zapisz_do_pliku()){
        std::cout<<"Nowa nazwa zostala zapisana!"<<std::endl;
        reload_all();
        return true;
    }
    else {
        perror("");
        return false;
    }
}

bool patch_nazwy_ponad_ascii(){
    std::string nazwa;
    for(int j =0;j<liczkonta;j++) {
        for (int i = 0; i < bd2[j].nazwa.length(); i++) {
            if ((int) bd2[j].nazwa[i] > 255 || (int) bd2[j].nazwa[i] <= 0) {
                std::cout << "nazwa " << bd2[j].nazwa << " zawiera niedozwolone znaki, podaj inna nazwe lub 0 any wyjsc (zmieniona zostanie nazwa w programie nie w steam)"<< std::endl;
                std::getline(std::cin, nazwa);
                if (nazwa == "0")return false;
                else break;
            }
        }
    }
    return true;
}




#endif //TEST_UTILITY_H
