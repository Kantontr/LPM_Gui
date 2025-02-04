#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_37_clicked();

    void on_pushButton_38_clicked();

    void on_pushButton_40_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_41_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_39_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_95_clicked();

    void on_pushButton_98_clicked();

    void on_pushButton_97_clicked();

    void on_pushButton_94_clicked();

    void on_pushButton_96_clicked();

    void on_pushButton_99_clicked();

    void on_pushButton_100_clicked();

    void on_pushButton_101_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
