#include <QDialog>
#ifndef STEAM_USER_LIST_H
#define STEAM_USER_LIST_H
inline std::string steam_user_list_current_label;
namespace Ui {
class Steam_User_List;
}

class Steam_User_List : public QDialog
{
    Q_OBJECT

public:
    std::string return_value;
    explicit Steam_User_List(QWidget *parent = nullptr);
    ~Steam_User_List();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Steam_User_List *ui;
};

#endif // STEAM_USER_LIST_H
