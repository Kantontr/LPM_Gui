#ifndef STEAM_USER_LIST_NOTINDATABASE_H
#define STEAM_USER_LIST_NOTINDATABASE_H

#include <QDialog>

namespace Ui {
class Steam_User_List_NotInDataBase;
}

class Steam_User_List_NotInDataBase : public QDialog
{
    Q_OBJECT

public:
    std::string return_value_nazwa;
    std::string return_value_sciezka;
    explicit Steam_User_List_NotInDataBase(QWidget *parent = nullptr);
    ~Steam_User_List_NotInDataBase();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Steam_User_List_NotInDataBase *ui;
};

#endif // STEAM_USER_LIST_NOTINDATABASE_H
