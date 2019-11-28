#ifndef LPM_STEAM_USER_H
#define LPM_STEAM_USER_H
#include "lpm_utility.h"

inline bool LPM_USERS::rename_user(std::string nazwa,std::string nowa_nazwa){
    int id_konta = find_account_by_name(nazwa);
    if (id_konta==0){
        std::cout<<"Konto o podanej nazwie nie istnieje! Zmiany nie zostaly zachowane!"<<std::endl;
        system("sleep");
        return false;
    }


    int id_konta_check = find_account_by_name(nowa_nazwa);
    if (id_konta_check!=0){
        std::cout<<"Konto o podanej nazwie juz istnieje! Zmiany nie zostaly zachowane!"<<std::endl;
        return false;
    }

    bd2[id_konta].name = nowa_nazwa;
    if(save_to_file()){
        std::cout<<"Nowa nazwa zostala zapisana!"<<std::endl;
        reload_all();
        return true;
    }
    else {
        perror("");
        return false;
    }
}


inline int LPM_USERS::reload(){


    int used_slots_tmp=1;
    std::ifstream infile(pathdane);
    std::string line;
    std::getline(infile, line);
    while (std::getline(infile, line))
    {
        bd2[used_slots_tmp].name=line;
        std::getline(infile, line);
        bd2[used_slots_tmp].path = line;
        used_slots_tmp++;
    }

    used_slots=used_slots_tmp;
    return used_slots_tmp;
}


inline bool LPM_USERS::remove_user(std::string nazwa_user){
    int numer_konta = find_account_by_name(nazwa_user);
    if (numer_konta==0){
        std::cout<<"Konto o podanej nazwie "<<nazwa_user<<" nie istnieje!"<<std::endl;
        return false;
    }
    for(int i=numer_konta;i<used_slots-1;i++){
        bd2[i].name = bd2[i+1].name;
        bd2[i].path = bd2[i+1].path;
    }
    bd2[used_slots-1].name="";
    bd2[used_slots-1].path="";
    used_slots-=1;
    if(save_to_file()){
        reload();
        std::cout<<"Uzytkownik zostal usuniety!"<<std::endl;
        return true;
    }
    else{
        std::cout << "Nie udalo sie otworzyc pliku dane_csgo, zmiany nie zostaly zachowane! \n" << std::endl;
        reload();
        return false;
    }
}

inline  bool LPM_USERS::save_to_file(){

    std::cout<<"Modyfikowanie bd2"<<std::endl;
    system("cls");

    if ((GetFileAttributesA(pathdane.c_str())) != INVALID_FILE_ATTRIBUTES){
        FILE *fp_upgrade;
        if ((fp_upgrade = fopen(pathdane.c_str(), "w")) != NULL)
        {
            fprintf(fp_upgrade, "konta_steam \n");
            for (int i = 1; i < used_slots; i++)
            {
                fprintf(fp_upgrade, "%s\n", bd2[i].name.c_str());
                fprintf(fp_upgrade, "%s\n", bd2[i].path.c_str());
            }
            fclose(fp_upgrade);
            std::cout<<"Zmiany zostaly wprowadzone!"<<std::endl;
            return true;
        }
        else {
            std::cout << "Nie udalo sie otworzyc pliku dane_csgo, zmiany nie zostaly zachowane! \n" << std::endl;
            ;
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


inline bool LPM_USERS::add_user(std::string nazwa,std::string sciezka){


    if ((GetFileAttributesA(sciezka.c_str())) == INVALID_FILE_ATTRIBUTES) {
        std::cout<<"Podana sciezka jest niepoprawna!"<<std::endl;
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

    for (int i = 0; i < used_slots; i++) {
        if (nazwa == bd2[i].name) {
            std::cout << "Konto o podanej nazwie juz istnieje! Zmiany nie zostana wprowadzone" << std::endl;
            return false;
        }
        if (sciezka == bd2[i].path) {
            std::cout << "To konto zostalo juz dodane!Zmiany nie zostana wprowadzone " << std::endl;
            return false;
        }
    }



    bd2[used_slots].name = nazwa;
    bd2[used_slots].path = sciezka;
    used_slots+=1;


    if(save_to_file()){
        std::cout<<"Uzytkownik "<<bd2[used_slots].name<<" zostal dodany!"<<std::endl;
        return true;
    }
    else {
        std::cout<<"Wystapil blad!Zmiany nie zostaly zachowane!"<<std::endl;
        return false;
    }

}



inline std::string LPM_USERS::read_account_name(std::string sciezka){
    std::string read_account_name_sciezka = steam_folder;
    read_account_name_sciezka+="\\userdata\\";
    read_account_name_sciezka+=sciezka;
    read_account_name_sciezka+="\\730\\local\\cfg\\config.cfg";
    std::string bufor;


    FILE *plik_config_konta_steam;
    if ((plik_config_konta_steam = fopen(read_account_name_sciezka.c_str(), "r")) != NULL){

        while ((fscanf(plik_config_konta_steam,"%s",bufor.c_str()))!=EOF){
            if (bufor[0]=='n' && bufor[1]=='a' && bufor[2]=='m' && bufor[3]=='e'){
                fscanf(plik_config_konta_steam,"%s",bufor.c_str());
                fclose(plik_config_konta_steam);
                return bufor.c_str();
            }
        }
    }
    else {
        std::cout << "Nie udalo sie otworzyc pliku "<<read_account_name_sciezka.c_str()<<"\n" << std::endl;
        return "Blad odczytu";
    }
    return "Blad";
}


inline int LPM_USERS::find_account_by_name(std::string nazwa_konta){
    for(int i=1;i<used_slots;i++){
        if (bd2[i].name == nazwa_konta)return i;
    }
    return 0;
}


inline bool LPM_USERS::sync_files(int wybor,int used_slots)
{
    int tmpwybor = wybor;
    tmpwybor++;

    std::string path_to_localconfig = lpm_config->cfg[2].value;
    path_to_localconfig += "\\userdata\\";
    path_to_localconfig += get_steam_folder_id_from_path(lpm_users->bd2[wybor].path);
    path_to_localconfig += "\\config\\localconfig.vdf";
    std::string launch_options = vdf_read_launch_options(path_to_localconfig);


    while(tmpwybor<lpm_users->used_slots){
        std::string path1c = pathdodajconfig(wybor);
        std::string path1v = pathdodajvideo(wybor);

        std::string path2c = pathdodajconfig(tmpwybor);
        std::string path2v = pathdodajvideo(tmpwybor);

        if((CopyFileA(path1c.c_str(), path2c.c_str(), FALSE))==0){
            return false;
        }
        if((CopyFileA(path1v.c_str(), path2v.c_str(), FALSE))==0){
            return false;
        }


        path_to_localconfig = lpm_config->cfg[2].value;
        path_to_localconfig +="\\userdata\\";
        path_to_localconfig += get_steam_folder_id_from_path(lpm_users->bd2[tmpwybor].path);
        path_to_localconfig += "\\config\\localconfig.vdf";
        vdf_save_launch_options(path_to_localconfig,launch_options);


        tmpwybor++;
    }

    tmpwybor = wybor;
    tmpwybor--;
    while(tmpwybor>0){
        std::string path1c = pathdodajconfig(wybor);
        std::string path1v = pathdodajvideo(wybor);

        std::string path2c = pathdodajconfig(tmpwybor);
        std::string path2v = pathdodajvideo(tmpwybor);

        if((CopyFileA(path1c.c_str(), path2c.c_str(), FALSE))==0){
            return false;
        }
        if((CopyFileA(path1v.c_str(), path2v.c_str(), FALSE))==0){
            return false;
        }
        tmpwybor--;
    }
    return true;
}
#endif // LPM_STEAM_USER_H
