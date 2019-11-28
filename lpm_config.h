#ifndef LPM_CONFIG_H
#define LPM_CONFIG_H
#include "lpm_utility.h"


inline void LPM_CONFIG::save_to_file(){


    std::string path_config_tmp = path_config;
    path_config_tmp += "\\config.cfg";


    std::cout<<"modyfikowanie cfg glownego"<<std::endl;


    if ((GetFileAttributesA(path_config_tmp.c_str())) != INVALID_FILE_ATTRIBUTES){
        FILE *fp_upgrade;
        if ((fp_upgrade = fopen(path_config_tmp.c_str(), "w")) != NULL)
        {

            for (int i = 0; i < config_size; i++)
            {
                fprintf(fp_upgrade, "%s ", cfg[i].name.c_str());
                if(cfg[i].value!="")fprintf(fp_upgrade, "%s\n", cfg[i].value.c_str());
                else fprintf(fp_upgrade, "brak_danych\n");
            }
            fclose(fp_upgrade);
            stworz_sciezki();
            count();
            reload();
            stworz_sciezki();
        }
        else {
            std::cout << "Nie udalo sie otworzyc pliku config, zmiany nie zostaly zachowane! \n" << std::endl;

        }
    }

}

inline bool LPM_CONFIG::add_steam_csgo_path(){

   std::string ustawienia_sciezka_tmp;
   std::cout<<"(2) Podaj sciezke do folderu steam gdzie zainstalowany jest csgo: "<<std::endl;
   std::cout<<"np: C:\\steamlibrary"<<std::endl;
   std::cout<<"Jezeli csgo jest zainstalowany na tym samym dysku co program Steam ponownie wpisz poprzednio podana sciezke"<<std::endl;
   if(cfg[2].value!="brak_danych")std::cout<<"( "<<cfg[2].value<<" )"<<std::endl;
   ustawienia_sciezka_tmp="";
   std::getline(std::cin, ustawienia_sciezka_tmp);
   if ((GetFileAttributesA(ustawienia_sciezka_tmp.c_str())) != INVALID_FILE_ATTRIBUTES){
       cfg[3].value=ustawienia_sciezka_tmp;
       stworz_sciezki();
       save_to_file();
       std::cout<<"Sciezka do folderu steam z csgo zostala dodana!"<<std::endl;

       return true;
   }
   else {
       std::cout<<"Sciezka do folderu steam csgo nie jest poprawna!"<<std::endl;

       return false;
   }

}

inline bool LPM_CONFIG::add_steam_path(){

    std::string ustawienia_sciezka_tmp;
    std::cout<<"(1) Podaj sciezke do folderu steam: "<<std::endl;
    std::cout<<"np: C:\\Steam"<<std::endl;
    ustawienia_sciezka_tmp="";
    std::getline(std::cin, ustawienia_sciezka_tmp);
    if ((GetFileAttributesA(ustawienia_sciezka_tmp.c_str())) != INVALID_FILE_ATTRIBUTES){
        cfg[2].value=ustawienia_sciezka_tmp;
        stworz_sciezki();
        save_to_file();
        std::cout<<"Sciezka do folderu steam zostala dodana!"<<std::endl;

        return true;
    }
    else {
        std::cout<<"Sciezka do folderu steam nie jest poprawna!"<<std::endl;

        return false;
    }

}


inline void LPM_CONFIG::reload() {
    std::string path_config_tmp = path_config;
    path_config_tmp += "\\config.cfg";
    if ((GetFileAttributesA(path_config_tmp.c_str())) != INVALID_FILE_ATTRIBUTES) {

        std::ifstream infile(path_config_tmp);
        std::string line;
        int numer=0,i=0;
        while (std::getline(infile, line))
        {
            i=0;
            cfg[numer].name="";
            cfg[numer].value="";
            for(i;i<line.length();i++){
                if(line[i]==' '){
                    i++;
                    break;
                }
                else cfg[numer].name+=line[i];
            }
            for(i;i<line.length();i++){
                cfg[numer].value+=line[i];
            }
            numer++;
        }
        infile.clear();
        used_slots=numer;
    }

}


inline void LPM_CONFIG::count(){
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
        used_slots=numer;
    }
}


#endif // LPM_CONFIG_H
