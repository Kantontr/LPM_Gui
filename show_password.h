#ifndef SHOW_PASSWORD_H
#define SHOW_PASSWORD_H

#include <QDialog>

inline std::string show_password_current_button_label;
inline std::string show_password_current_button_2_label;
inline bool bool_copy_to_clipboard;
namespace Ui {
class Show_Password;
}

class Show_Password : public QDialog
{
    Q_OBJECT

public:
    std::string show_password_return;
    explicit Show_Password(QWidget *parent = nullptr);
    ~Show_Password();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Show_Password *ui;
};

#endif // SHOW_PASSWORD_H
