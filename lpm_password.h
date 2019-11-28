#ifndef LPM_PASSWORD_H
#define LPM_PASSWORD_H
#include "lpm_utility.h"

inline bool LPM_PASSWORD::reload(){

    if ((GetFileAttributesA(path_hasla_plik.c_str())) != INVALID_FILE_ATTRIBUTES) {

        std::ifstream infile(path_hasla_plik);
        std::string line;
        int i=1;
        std::getline(infile, line);
        pswd[0].password = line;
        while (std::getline(infile, line))
        {
            pswd[i].name = line;
            if(std::getline(infile, line)){
                pswd[i].login = line;
                if(std::getline(infile, line)){
                    pswd[i].password = line;
                }
            }
            i++;
        }
        infile.clear();
        rozmiar_pswd=i-1;
    }
}



inline bool LPM_PASSWORD::save_to_file(){


   std::cout<<"modyfikowanie pswd"<<std::endl;

    if ((GetFileAttributesA(path_hasla_plik.c_str())) != INVALID_FILE_ATTRIBUTES){

        if(pswd[0].password == ""){
            pswd[0].password = "password_not_defined";
        }
        std::ofstream plik_hasla;
        plik_hasla.open(path_hasla_plik.c_str());
        plik_hasla << pswd[0].password.c_str()<<std::endl;


        for (int i = 1; i <= rozmiar_pswd; i++)
        {
            std::cout<<"pswd zapisz do pliku "<<i<<" nazwa: "<<pswd[i].name.c_str()<<" login: "<<pswd[i].login.c_str()<<" password: "<<pswd[i].password.c_str()<<std::endl;
            plik_hasla<<pswd[i].name<<std::endl<<pswd[i].login<<std::endl<<pswd[i].password<<std::endl;
        }
        plik_hasla.close();
        reload();
        return true;



    }

}

inline int LPM_PASSWORD::find_user_by_name(std::string nazwa_konta){
    int konto_do_usuniecia=-1;
    for(int i=1;i<=rozmiar_pswd;i++){
        std::cout<<"porownanie z: "<<pswd[i].name.c_str()<<std::endl;
        if(compare_strings(pswd[i].name,nazwa_konta)){
            return i;
        }
    }
    return -1;;
}

inline bool LPM_PASSWORD::remove_user(int konto_do_usuniecia){

    if(konto_do_usuniecia!=-1){
        for(int i=konto_do_usuniecia;i<rozmiar_pswd;i++){
            if(i+1<=rozmiar_pswd){
                pswd[i].name=pswd[i+1].name;
                pswd[i].login=pswd[i+1].login;
                pswd[i].password=pswd[i+1].password;
            }
        }
        rozmiar_pswd-=1;
    }
    save_to_file();
    reload();
    return true;
}

#endif // LPM_PASSWORD_H
