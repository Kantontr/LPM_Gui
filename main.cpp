#include "mainwindow.h"
#include <QApplication>
#include "utility_v2.h"
#include "instalacja.h"

inline bool update_1_5(){
    std::cout<<"applying patch v1.5"<<std::endl;
        lpm_config->used_slots=10;
        lpm_config->save_to_file();
        lpm_config->reload();
}



int main(int argc, char *argv[])
{


    reload_all(); //wczytanie ustawien


    if ((GetFileAttributesA(pathcsgo_main.c_str())) == INVALID_FILE_ATTRIBUTES) { //czy zainstalowany
        instalacja();
    }

    /*patch password manager (v1.4)*/
    if ((GetFileAttributesA(pathhasla_main.c_str())) == INVALID_FILE_ATTRIBUTES) {
        CreateDirectoryA(pathhasla_main.c_str(), 0);
    }

    if ((GetFileAttributesA(path_hasla_plik.c_str())) == INVALID_FILE_ATTRIBUTES) {
        FILE *fp_create_hasla_plik;
        if ((fp_create_hasla_plik = fopen(path_hasla_plik.c_str(), "w")) != NULL)
        {
                fprintf(fp_create_hasla_plik, "password_not_found");
        }
        else {
            std::cout << "Nie udalo sie otworzyc pliku pswd, zmiany nie zostaly zachowane! \n" << std::endl;
        }
    }
    /* END patch password manager (v1.4)*/

      if(lpm_config->used_slots<10)update_1_5();
      /* password authentication*/
      if(lpm_config->cfg[6].value=="false"){
          Session_Password_Authentication=true;
      }


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

