#ifndef CLION_KANTONPROGRAMV3_CONSOLE_MODE_H
#define CLION_KANTONPROGRAMV3_CONSOLE_MODE_H

#endif //CLION_KANTONPROGRAMV3_CONSOLE_MODE_H
#pragma once
#include "utility.h"
void console_mod_menu(std::string predefined_input) {
    bool console_mod_bool = true;
    std::string console_mode_input;
    int dlugosc_input;
    int ile_argumentow = 0;
    struct struct_lista_argumentow_console_mode {
        std::string argument;
    };

    while (console_mod_bool) {
        system("cls");
        ile_argumentow = 0;

        if(predefined_input.length()>2){
            console_mode_input = predefined_input;
            predefined_input="";
        }
        else{
            std::getline(std::cin, console_mode_input);
            if (console_mode_input[0] == '0')return;
        }

        dlugosc_input = console_mode_input.length();
        for (int i = 0; i < dlugosc_input; i++) {
            if (console_mode_input[i] == ' ') {
                ile_argumentow++;
            }
        }
        struct_lista_argumentow_console_mode *lista_argumentow_console_mode = new struct_lista_argumentow_console_mode[ile_argumentow+1];
        ile_argumentow=0;
        for (int i = 0; i < dlugosc_input; i++) {
            if (console_mode_input[i] != ' ') {
                lista_argumentow_console_mode[ile_argumentow].argument += console_mode_input[i];
            } else {
                ile_argumentow++;
            }
        }


        system("cls");
        std::cout << "=================" << std::endl;
        std::cout << "Console mode" << std::endl;
        std::cout << "=================" << std::endl;
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<std::endl;



        if (lista_argumentow_console_mode[0].argument == "sync") {
            for (int j = 2; j <= ile_argumentow; j++) {
                lista_argumentow_console_mode[1].argument += " ";
                lista_argumentow_console_mode[1].argument += lista_argumentow_console_mode[j].argument;
            }
            int numer_konta = znajdz_konto_po_nazwie(lista_argumentow_console_mode[1].argument);
            if (numer_konta == 0) {
                std::cout << "Konto o podanej nazwie nie istnieje! Podaj inna nazwe" << std::endl;
                system("pause");
                break;
            }
            else {
                movepliki(numer_konta, liczkonta);
                system("pause");
                return;
            }
        }

        else if (lista_argumentow_console_mode[0].argument == "open") {
            if (lista_argumentow_console_mode[1].argument=="cfg"){
                std::string path_tmp_cfg = cfg[3].wartosc;
                path_tmp_cfg+=sciezka_do_folderu_z_gra;
                ShellExecuteA(0, "explore", path_tmp_cfg.c_str(), NULL, NULL, SW_SHOW);
                return;
            }
            if (lista_argumentow_console_mode[1].argument=="backup"){
                std::string path_backup = pathcsgo_main;
                path_backup+="\\backup";
                ShellExecuteA(0, "explore", path_backup.c_str(), NULL, NULL, SW_SHOW);
                return;
            }
            for (int j = 2; j <= ile_argumentow; j++) {
                lista_argumentow_console_mode[1].argument += " ";
                lista_argumentow_console_mode[1].argument += lista_argumentow_console_mode[j].argument;
            }
            int numer_konta = znajdz_konto_po_nazwie(lista_argumentow_console_mode[1].argument);
            if ((GetFileAttributesA(bd2[numer_konta].sciezka.c_str())) == INVALID_FILE_ATTRIBUTES) {
                std::cout << "Konto o podanej nazwie nie istnieje!" << std::endl;
                system("pause");
                return;
            }
            ShellExecuteA(0, "explore", bd2[numer_konta].sciezka.c_str(), NULL, NULL, SW_SHOW); //otwieranie lokalizacji
            return;
        }


        else if (lista_argumentow_console_mode[0].argument == "export") {
            if (lista_argumentow_console_mode[1].argument == "pulpit") {
                exportuj_pliki();
                system("pause");
                return;
            }
            else {
                std::cout<<"Podano zle dane! powrot do menu"<<std::endl;
                system("pause");
            }
        }

        else if (lista_argumentow_console_mode[0].argument == "user") {

            if (lista_argumentow_console_mode[1].argument == "add") {
                if (lista_argumentow_console_mode[2].argument == "gui"){
                    std::string sciezka = cfg[2].wartosc;
                    sciezka += "\\userdata";
                    int wyliczanie = listowanie_folderow(sciezka,"",0,false);
                    std::string sciezka_wlasna;

                    std::cout<<"(0) Aby wyjsc"<<std::endl;
                    std::cout<<"Lub dodaj konto do bazy danych: "<<std::endl;

                    std::string sciezka_wlasna_tmp;
                    for (int i=1;i<=wyliczanie;i++){
                        sciezka_wlasna=sciezka;
                        sciezka_wlasna+="\\";
                        sciezka_wlasna+=list_kat[i].listowanie_katalogow_nazwa;
                        sciezka_wlasna+="\\config\\localconfig.vdf";
                        std::cout<<i<<" id: "<<list_kat[i].listowanie_katalogow_nazwa<<" nazwa: "<<odczytaj_nazwe_user_z_vdf(sciezka_wlasna);

                        bool konto_dodane=false;
                        sciezka_wlasna_tmp = sciezka;
                        sciezka_wlasna_tmp += "\\";
                        sciezka_wlasna_tmp += list_kat[i].listowanie_katalogow_nazwa;
                        sciezka_wlasna_tmp+="\\730\\local\\cfg";

                        for (int n=0;n<liczkonta+1;n++){
                            if(bd2[n].sciezka == sciezka_wlasna_tmp){
                                std::cout<<" (Juz w bazie)"<<std::endl;
                                konto_dodane=true;
                                break;
                            }
                        }
                        if(!konto_dodane){
                            std::cout<<std::endl;
                        }
                    }
                    int wybor_dodaj_konto;
                    std::cin>>wybor_dodaj_konto;
                    if (wybor_dodaj_konto==0)return;
                    if (wybor_dodaj_konto>wyliczanie)return;
                    sciezka_wlasna=sciezka;
                    sciezka_wlasna+="\\";
                    sciezka_wlasna+=list_kat[wybor_dodaj_konto].listowanie_katalogow_nazwa;
                    sciezka_wlasna_tmp = sciezka_wlasna;
                    sciezka_wlasna_tmp +="\\config\\localconfig.vdf";
                    sciezka_wlasna +="\\730\\local\\cfg";

                    bd2_add_user(odczytaj_nazwe_user_z_vdf(sciezka_wlasna_tmp),sciezka_wlasna);
                    return;
                }


                for (int j = 4; j <= ile_argumentow; j++) {
                    lista_argumentow_console_mode[3].argument += " ";
                    lista_argumentow_console_mode[3].argument += lista_argumentow_console_mode[j].argument;
                }
                lista_argumentow_console_mode[3].argument +="\\730\\local\\cfg";
                bd2_add_user(lista_argumentow_console_mode[2].argument, lista_argumentow_console_mode[3].argument);
                return;
            }
            else if (lista_argumentow_console_mode[1].argument == "remove") {
                for (int j = 3; j <= ile_argumentow; j++) {
                    lista_argumentow_console_mode[2].argument += " ";
                    lista_argumentow_console_mode[2].argument += lista_argumentow_console_mode[j].argument;
                }
                bd2_remove_user(lista_argumentow_console_mode[2].argument);
                return;
            }
            else if (lista_argumentow_console_mode[1].argument == "rename") {
                for (int j = 3; j <= ile_argumentow; j++) {
                    lista_argumentow_console_mode[2].argument += " ";
                    lista_argumentow_console_mode[2].argument += lista_argumentow_console_mode[j].argument;
                }
                bd2_rename_user(lista_argumentow_console_mode[2].argument);
                system("pause");
                return;
            }

            else {
                std::cout<<"Podano zle dane! powrot do menu"<<std::endl;
                system("pause");
            }

        }


        else if (lista_argumentow_console_mode[0].argument == "reload") {
            if(reload_all()){
                std::cout<<"Ustawienia wczytane poprawnie"<<std::endl;
                system("pause");
                return;
            }
            else {
                std::cout<<"Wystapil blad!"<<std::endl;
                perror("");
                system("pause");
                return;
            }
        }


        else if (lista_argumentow_console_mode[0].argument == "move_cfg") {
            if (ile_argumentow>=2)
            {
                for (int j = 2; j < ile_argumentow; j++) {
                    lista_argumentow_console_mode[1].argument += " ";
                    lista_argumentow_console_mode[1].argument += lista_argumentow_console_mode[j].argument;
                }
                int numer_konta = znajdz_konto_po_nazwie(lista_argumentow_console_mode[1].argument);
                std::string sciezka_zrodlo = bd2[numer_konta].sciezka;
                sciezka_zrodlo += "\\";
                sciezka_zrodlo += lista_argumentow_console_mode[ile_argumentow].argument; // nazwa pliku

                std::string sciezka_docelowa = cfg[3].wartosc;
                sciezka_docelowa+=sciezka_do_folderu_z_gra;
                sciezka_docelowa += "\\";
                sciezka_docelowa += lista_argumentow_console_mode[ile_argumentow].argument;
                if ((CopyFileA(sciezka_zrodlo.c_str(), sciezka_docelowa.c_str(), FALSE)) == 0) {
                    std::cout << "Nie udalo sie skopiowac pliku, kod bledu: " << GetLastError() << std::endl;
                    system("pause");
                } else {
                    std::cout << "Kopiowanie zakonczone powodzeniem";
                    system("pause");
                    return;
                }
            }
            else {
                std::cout<<"Podano zla liczbe argumentow!Powrot do menu"<<std::endl;
                system("pause");
            }
            return;
        }

        else if(lista_argumentow_console_mode[0].argument == "view"){
            if (lista_argumentow_console_mode[1].argument=="users"){
                for (int i=1;i<liczkonta;i++){
                    std::cout<<"Nazwa konta: "<<bd2[i].nazwa.c_str()<<std::endl;
                    std::cout<<"Sciezka: "<<bd2[i].sciezka.c_str()<<std::endl;
                }
                system("pause");
                return;
            }
            else if(lista_argumentow_console_mode[1].argument=="cfg"){
                cfg_gen_wyswietl();
                system("pause");
                return;
            }
            else {
                for (int j = 2; j <= ile_argumentow; j++) {
                    lista_argumentow_console_mode[1].argument += " ";
                    lista_argumentow_console_mode[1].argument += lista_argumentow_console_mode[j].argument;
                }
                if(bd2[znajdz_konto_po_nazwie(lista_argumentow_console_mode[1].argument)].nazwa == lista_argumentow_console_mode[1].argument) {
                    std::cout << "Nazwa konta: "
                              << bd2[znajdz_konto_po_nazwie(lista_argumentow_console_mode[1].argument)].nazwa.c_str()
                              << std::endl;
                    std::cout << "Sciezka: "
                              << bd2[znajdz_konto_po_nazwie(lista_argumentow_console_mode[1].argument)].sciezka.c_str()
                              << std::endl;
                    system("pause");
                    return;
                }
                else {
                    std::cout<<"Podano zle dane! powrot do menu"<<std::endl;
                    system("pause");
                }
            }
        }

        else if(lista_argumentow_console_mode[0].argument == "test"){
        }

        else if(lista_argumentow_console_mode[0].argument == "crosshair"){
            if(lista_argumentow_console_mode[1].argument == "save"){
                for (int j = 3; j < ile_argumentow; j++) {
                    lista_argumentow_console_mode[1].argument += " ";
                    lista_argumentow_console_mode[1].argument += lista_argumentow_console_mode[j].argument;
                }
                if (zapisz_celowink(lista_argumentow_console_mode[2].argument,lista_argumentow_console_mode[ile_argumentow].argument)){
                    std::cout<<"Kopia zostala utworzona!"<<std::endl;
                }
                else std::cout<<"Wystapil blad w tworzeniu kopii!Zmiany nie zostaly zachowane"<<std::endl;
                system("pause");
                return;
            }
            else if(lista_argumentow_console_mode[1].argument=="list"){
                std::string pathkopia_crosshair = pathcsgo_main;
                pathkopia_crosshair += "\\crosshair_backup";
                listowanie_folderow(pathkopia_crosshair,"",0,true);
                system("pause");
                return;
            }
            else if(lista_argumentow_console_mode[1].argument=="load"){
                for (int j = 4; j <= ile_argumentow; j++) {
                    lista_argumentow_console_mode[3].argument += " ";
                    lista_argumentow_console_mode[3].argument += lista_argumentow_console_mode[j].argument;
                }
                if (wczytaj_celownik(lista_argumentow_console_mode[2].argument,lista_argumentow_console_mode[3].argument)){
                    std::cout<<"Kopia zostala wczytana!"<<std::endl;
                }
                system("pause");
                return;
            }
            else if(lista_argumentow_console_mode[1].argument=="remove"){
                if (usun_celownik(lista_argumentow_console_mode[2].argument)){
                    std::cout<<"Kopia zostala usunieta!"<<std::endl;
                }
                system("pause");
                return;
            }
            return;
        }

        else if(lista_argumentow_console_mode[0].argument == "backup"){
            if(lista_argumentow_console_mode[1].argument == "create"){
                create_backup(lista_argumentow_console_mode[2].argument);
                return;
            }
            else if(lista_argumentow_console_mode[1].argument=="load"){
                load_backup(lista_argumentow_console_mode[2].argument);
                return;
            }
            else if(lista_argumentow_console_mode[1].argument=="list"){
                std::string pathkopia = pathcsgo_main;
                pathkopia += "\\backup";
                listowanie_folderow(pathkopia,"",0,true);
                system("pause");
                return;
            }
            else {
                std::cout<<"Podano zle dane! powrot do menu"<<std::endl;
                system("pause");
            }
        }

        else if (lista_argumentow_console_mode[0].argument == "man"){


            if (lista_argumentow_console_mode[1].argument=="sync"){
                std::cout<<"Funkcja synchronizujaca pliki konfiguracyjne cs go miedzy zapisanymi kontami"<<std::endl;
                std::cout<<"sync [nazwa_konta_steam]"<<std::endl;
                system("pause");
            }


            else if (lista_argumentow_console_mode[1].argument=="open"){
                std::cout<<"Funkcja otwiera folder z plikami konfiguracyjnymi lub kopiami zapasowymi "<<std::endl;
                std::cout<<"open [cfg]"<<std::endl;
                std::cout<<"open [backup]"<<std::endl;
                std::cout<<"open [nazwa_konta_steam]"<<std::endl;
                system("pause");
            }

            else if (lista_argumentow_console_mode[1].argument=="reload"){
                std::cout<<"Funkcja odswieza ustawienia "<<std::endl;
                std::cout<<"reload"<<std::endl;
                system("pause");
            }


            else if (lista_argumentow_console_mode[1].argument=="crosshair"){
                std::cout<<"Funkcja robi kopie zapasowa celownika "<<std::endl;
                std::cout<<"crosshair [save] [nazwa_konta_steam] [nazwa_kopii]"<<std::endl;
                std::cout<<"crosshair [list]"<<std::endl;
                std::cout<<"crosshair [load] [nazwa_kopii] [nazwa_konta_steam]"<<std::endl;
                std::cout<<"crosshair [remove] [nazwa_kopii]"<<std::endl;
                system("pause");
            }


            else if (lista_argumentow_console_mode[1].argument=="export"){
                std::cout<<"Funckja exportuje ustawienia do wybranej lokalizacji"<<std::endl;
                std::cout<<"export [lokalizacja_docelowa]"<<std::endl;
                std::cout<<"ex. pulpit lub C:\\..."<<std::endl;
                system("pause");
            }


            else if (lista_argumentow_console_mode[1].argument=="move_cfg"){
                std::cout<<"Funkcja przenosi plik .cfg z wybranego konta do folderu glownego csgo"<<std::endl;
                std::cout<<"move_cfg [nazwa_konta_steam] [nazwa_pliku.cfg]"<<std::endl;
                system("pause");
            }


            else if (lista_argumentow_console_mode[1].argument=="view"){
                std::cout<<"Funkcja wyswietlajaca dane podanego parametru"<<std::endl;
                std::cout<<"view [nazwa_konta]"<<std::endl;
                std::cout<<"view [users]  //wyswietl dane o wszystkich kontach steam"<<std::endl;
                std::cout<<"view [cfg] // wyswietl config glowny"<<std::endl;
                system("pause");
            }
            else if (lista_argumentow_console_mode[1].argument=="user"){
                std::cout<<"Funkcja zarzadzajaca kontami csgo"<<std::endl;
                std::cout<<"user [add] [nazwa_konta] [sciezka] //dodaje uzytkownika o podanych parametrach"<<std::endl;
                std::cout<<"np user add nazwa_konta C:\\Steam\\userdata\\60074252"<<std::endl;
                std::cout<<"user [remove] [nazwa_konta] //usuwa uzytkownika o podanych parametrach" <<std::endl;
                std::cout<<"user [add] [gui] // kreator dodawania konta. Wyswietla dostepne konta i daje mozliwosc dodania ktoregos z nich"<<std::endl;
                std::cout<<"user [rename] [stara_nazwa_konta] // zmiana nazwy pod ktora zapisane jest konto" <<std::endl;
                system("pause");
            }

            else if(lista_argumentow_console_mode[1].argument=="backup"){
                std::cout<<"Funkcja zarzadzajaca kopiami zapasowymi danych z kont csgo"<<std::endl;
                std::cout<<"backup create [nazwa_kopii] //stworz kopie plikow config.cfg i video.txt "<<std::endl;
                std::cout<<"backup load [nazwa_kopii] //wczytaj kopie plikow config.cfg i video.txt"<<std::endl;
                std::cout<<"backup list //wywietl liste kopii zapasowych"<<std::endl;
                system("pause");
            }
            else {
                std::cout<<"Podano zle dane! powrot do menu"<<std::endl;
                system("pause");
            }
        }

        else {
            std::cout<<"Podano zle dane! powrot do menu"<<std::endl;
            system("pause");
        }
        return;
    }


}
