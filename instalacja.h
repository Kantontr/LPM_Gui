//
// Created by kanto on 15.12.2018.
//

#include <QMessageBox>

#ifndef CLION_KANTONPROGRAMV3_INSTALACJA_PROGRAMU_H
#define CLION_KANTONPROGRAMV3_INSTALACJA_PROGRAMU_H


#include "utility_v2.h"

inline std::string znajdz_sciezke_steam();

inline std::string znajdz_sciezke_csgo();

inline std::string znajdz_scieze_steam_z_rejestru();

inline std::string znajdz_scieze_csgo_z_pliku(std::string tmp_sciezka_csgo);

inline int instalacja() { //0 bez bledu , 1 nie ma steam , 2 nie ma csgo, 3 nie ma obu , 4 inne

    std::string path_appdata_instal = getenv("AppData");
    path_appdata_instal += "\\KantonLPM";

    if ((GetFileAttributesA(path_appdata_instal.c_str())) == INVALID_FILE_ATTRIBUTES) {
        CreateDirectoryA(path_appdata_instal.c_str(), 0);
        std::cout << "Folder KantonLPM zostal utworzony w " << path_appdata_instal << std::endl;
    }

    std::string pathappdata_config = path_appdata_instal;
    pathappdata_config += "\\config";
    if ((GetFileAttributesA(pathappdata_config.c_str())) == INVALID_FILE_ATTRIBUTES) {
        CreateDirectoryA(pathappdata_config.c_str(), 0);
        std::string pathappdata_config_cfg = pathappdata_config;
        pathappdata_config_cfg += "\\config.cfg";
        FILE *fp_create_cfg;
        if ((fp_create_cfg = fopen(pathappdata_config_cfg.c_str(), "w")) != NULL) {
            fprintf(fp_create_cfg, "config_glowny %s\n", wersja_KantonLPM.c_str());
            fprintf(fp_create_cfg, "path_pulpit brak_danych\n");
            fprintf(fp_create_cfg, "steam_folder brak_danych\n");
            fprintf(fp_create_cfg, "path_steam_csgo brak_danych\n");
            fprintf(fp_create_cfg, "wersja_programu standard");
            fclose(fp_create_cfg);
        }

        printf("Plik zostal utworzony! \n");
        std::cout << "Folder KantonLPM/Config zostal utworzony" << std::endl;
    }
    stworz_sciezki();
    lpm_config->save_to_file();

    std::string pathcsgo_main = path_appdata_instal;
    pathcsgo_main += "//CSGO";

    while (true) {
        system("cls");

        if ((GetFileAttributesA(pathcsgo_main.c_str())) == INVALID_FILE_ATTRIBUTES) {
            CreateDirectoryA(pathcsgo_main.c_str(), 0);
            std::cout << "Folder KantonLPM/CSGO zostal utworzony" << std::endl;
            FILE *fp;
            fp = fopen(pathdane.c_str(), "w");
            fprintf(fp, "Konta_Steam");
            fclose(fp);
        }
        bool dodaj_sciezke_steam_bool = false;
        bool dodaj_sciezke_steam_csgo_bool = false;

        std::string tmp_sciezka_steam;
        std::string tmp_sciezka_csgo;

        /*znajdz sciezke do steam */
        tmp_sciezka_steam = znajdz_scieze_steam_z_rejestru();
        if ((GetFileAttributesA(tmp_sciezka_steam.c_str())) != INVALID_FILE_ATTRIBUTES) {

            lpm_config->cfg[2].value = tmp_sciezka_steam;
            dodaj_sciezke_steam_bool = true;
            std::cout<<"znaleziono sciezke steam! "<<tmp_sciezka_steam<<std::endl;

            std::string csgo_na_tym_samym_dysku = tmp_sciezka_steam;
            csgo_na_tym_samym_dysku += "\\steamapps\\common\\Counter-Strike Global Offensive";

            if ((GetFileAttributesA(csgo_na_tym_samym_dysku.c_str())) != INVALID_FILE_ATTRIBUTES){
                lpm_config->cfg[3].value = tmp_sciezka_steam;
                dodaj_sciezke_steam_csgo_bool = true;
                std::cout<<"znaleziono sciezke steamapps! "<<tmp_sciezka_steam<<std::endl;
            }
        }

        if (!dodaj_sciezke_steam_bool) {
            tmp_sciezka_steam = znajdz_sciezke_steam();
            if (tmp_sciezka_steam != "blad") {
                dodaj_sciezke_steam_bool = true;
                lpm_config->cfg[2].value = tmp_sciezka_steam;

                std::string csgo_na_tym_samym_dysku = tmp_sciezka_steam;
                csgo_na_tym_samym_dysku += "\\steamapps\\common\\Counter-Strike Global Offensive";

                if ((GetFileAttributesA(csgo_na_tym_samym_dysku.c_str())) != INVALID_FILE_ATTRIBUTES){
                    lpm_config->cfg[3].value = tmp_sciezka_steam;
                    dodaj_sciezke_steam_csgo_bool = true;
                }
            }
        }




        /*znajdz sciezke do steamapps */
        if (!dodaj_sciezke_steam_csgo_bool) {
            tmp_sciezka_csgo = znajdz_scieze_csgo_z_pliku(tmp_sciezka_csgo);
            std::string tmp_wariant1 = tmp_sciezka_csgo;
            std::string tmp_wariant2 = tmp_sciezka_csgo;
            tmp_wariant1 += "\\steamapps\\common\\Counter-Strike Global Offensive";
            tmp_wariant2 += "\\common\\Counter-Strike Global Offensive";

            if ((((GetFileAttributesA(tmp_wariant1.c_str())) != INVALID_FILE_ATTRIBUTES)) || ((GetFileAttributesA(tmp_wariant2.c_str())) != INVALID_FILE_ATTRIBUTES)) {
                lpm_config->cfg[3].value = tmp_sciezka_csgo;
                dodaj_sciezke_steam_csgo_bool = true;
            }
        }

        if (!dodaj_sciezke_steam_csgo_bool) {
            tmp_sciezka_csgo = znajdz_sciezke_csgo();
            if (tmp_sciezka_csgo != "blad") {
                dodaj_sciezke_steam_csgo_bool = true;
                lpm_config->cfg[3].value = tmp_sciezka_csgo;
            }
        }

        if(dodaj_sciezke_steam_csgo_bool && dodaj_sciezke_steam_bool){
            lpm_config->save_to_file();
            reload_all();
            return 0;
        }


        /* automatyczne wyszukiwanie fail */

        std::string ustawienia_sciezka_tmp;
        lpm_config->save_to_file();
        reload_all();
        if (dodaj_sciezke_steam_bool && dodaj_sciezke_steam_csgo_bool)return 0;
        if (dodaj_sciezke_steam_bool == false) return 1;
        if (dodaj_sciezke_steam_csgo_bool == false) return 2;
        if (!dodaj_sciezke_steam_bool && !dodaj_sciezke_steam_csgo_bool)return 3;
        return 4;
    }
}

inline std::string znajdz_sciezke_steam() {

    std::string tmp_sciezka = "C:\\Program Files\\Steam\\userdata";
    if ((GetFileAttributesA(tmp_sciezka.c_str())) != INVALID_FILE_ATTRIBUTES) {
        return "C:\\Program Files\\Steam";
    }
    tmp_sciezka = "C:\\Program Files (x86)\\Steam\\userdata";
    if ((GetFileAttributesA(tmp_sciezka.c_str())) != INVALID_FILE_ATTRIBUTES) {
        return "C:\\Program Files (x86)\\Steam";
    }
    tmp_sciezka = "D:\\Program Files\\Steam\\userdata";
    if ((GetFileAttributesA(tmp_sciezka.c_str())) != INVALID_FILE_ATTRIBUTES) {
        return "D:\\Program Files\\Steam";
    }
    tmp_sciezka = "D:\\Program Files (x86)\\Steam\\userdata";
    if ((GetFileAttributesA(tmp_sciezka.c_str())) != INVALID_FILE_ATTRIBUTES) {
        return "D:\\Program Files (x86)\\Steam";
    }
    tmp_sciezka = "C:\\Programy\\Steam\\userdata";
    if ((GetFileAttributesA(tmp_sciezka.c_str())) != INVALID_FILE_ATTRIBUTES) {
        return "C:\\Programy\\Steam";
    }
    tmp_sciezka = "E:\\Program Files\\Steam\\userdata";
    if ((GetFileAttributesA(tmp_sciezka.c_str())) != INVALID_FILE_ATTRIBUTES) {
        return "E:\\Program Files\\Steam";
    }
    tmp_sciezka = "E:\\Program Files (x86)\\Steam\\userdata";
    if ((GetFileAttributesA(tmp_sciezka.c_str())) != INVALID_FILE_ATTRIBUTES) {
        return "E:\\Program Files (x86)\\Steam";
    }
    return "blad";
}


inline std::string znajdz_scieze_steam_z_rejestru() {
    HKEY hkSoftware;
    LONG result;
    result = RegOpenKeyExA(HKEY_CURRENT_USER, "software\\valve\\steam", 0, KEY_ALL_ACCESS, &hkSoftware);
    //if( result == ERROR_SUCCESS )

    char buf[60];
    DWORD dwBufSize = 20;
    DWORD dwRegsz = REG_SZ;
    result = RegQueryValueExA(hkSoftware, "steampath", NULL, &dwRegsz, (LPBYTE) buf, &dwBufSize);
    if (result == ERROR_SUCCESS) {
        return buf;
    } else {
        std::cout << "blad" << std::endl;
    }
    return "blad";
}


inline std::string znajdz_scieze_csgo_z_pliku(std::string tmp_sciezka_csgo) {

    tmp_sciezka_csgo+="\\config\\config.vdf";
    std::ifstream infile(tmp_sciezka_csgo);
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
                if (tmp=="BaseInstallFolder_1"){
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


inline std::string znajdz_sciezke_csgo() {

    std::string tmp_sciezka = "C:\\Program Files\\Steam\\steamapps\\common\\Counter-Strike Global Offensive";
    if ((GetFileAttributesA(tmp_sciezka.c_str())) != INVALID_FILE_ATTRIBUTES) {
        return "C:\\Program Files\\Steam";
    }
    tmp_sciezka = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Counter-Strike Global Offensive";
    if ((GetFileAttributesA(tmp_sciezka.c_str())) != INVALID_FILE_ATTRIBUTES) {
        return "C:\\Program Files (x86)\\Steam";
    }
    tmp_sciezka = "D:\\Program Files\\Steam\\steamapps\\common\\Counter-Strike Global Offensive";
    if ((GetFileAttributesA(tmp_sciezka.c_str())) != INVALID_FILE_ATTRIBUTES) {
        return "D:\\Program Files\\Steam";
    }
    tmp_sciezka = "D:\\Program Files (x86)\\Steam\\steamapps\\common\\Counter-Strike Global Offensive";
    if ((GetFileAttributesA(tmp_sciezka.c_str())) != INVALID_FILE_ATTRIBUTES) {
        return "D:\\Program Files (x86)\\Steam";
    }
    tmp_sciezka = "C:\\Programy\\Steam\\steamapps\\common\\Counter-Strike Global Offensive";
    if ((GetFileAttributesA(tmp_sciezka.c_str())) != INVALID_FILE_ATTRIBUTES) {
        return "C:\\Programy\\Steam";
    }
    tmp_sciezka = "E:\\Program Files\\Steam\\steamapps\\common\\Counter-Strike Global Offensive";
    if ((GetFileAttributesA(tmp_sciezka.c_str())) != INVALID_FILE_ATTRIBUTES) {
        return "E:\\Program Files\\Steam";
    }
    tmp_sciezka = "E:\\Program Files (x86)\\Steam\\steamapps\\common\\Counter-Strike Global Offensive";
    if ((GetFileAttributesA(tmp_sciezka.c_str())) != INVALID_FILE_ATTRIBUTES) {
        return "E:\\Program Files (x86)\\Steam";
    }
    return "blad";
}


#endif //CLION_KANTONPROGRAMV3_INSTALACJA_PROGRAMU_H
