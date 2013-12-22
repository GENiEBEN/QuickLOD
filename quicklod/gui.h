#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QString>

extern void set_amd_lod(QString value);

namespace Ui {
class gui;
}

class gui : public QWidget
{
    Q_OBJECT

public:
    explicit gui(QWidget *parent = 0);
    ~gui();

private slots:
    void on_slider_1_valueChanged(int value);

    void on_slider_2_valueChanged(int value);

    void on_slider_3_valueChanged(int value);

    void on_slider_4_valueChanged(int value);

    void on_slider_5_valueChanged(int value);

    void on_github_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_button_1_clicked();

    void on_button_2_clicked();

    void on_button_3_clicked();

    void on_button_4_clicked();

    void on_button_5_clicked();

    void on_Start_clicked();

private:
    Ui::gui *ui;
};




#endif // GUI_H
