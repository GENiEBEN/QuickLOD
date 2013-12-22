#include "gui.h"
#include "ui_gui.h"
#include <QUrl>
#include <QString>
#include <QSettings>
#include <QStringList>
#include <QDesktopServices>
#include <QStyleFactory>
#include <QProcess>
#include <QCoreApplication>


//Browse registry for all LODAdj keys and change them all
void set_amd_lod(QString value){
    QString regpath = "HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Video";
    QSettings sets(regpath, QSettings::NativeFormat);
    QStringList keys = sets.allKeys();
    QStringList foo_l; QStringList boo_l;QString foo;

    for (int i=0;i<keys.count();i++){
        if (keys.value(i).contains("LODAdj")){
            foo_l << regpath + "\\" + keys.at(i);
        }
    }
    for (int i=0;i<foo_l.count();i++){foo = foo_l.at(i);foo.replace("/","\\",Qt::CaseInsensitive);foo.replace("\\LODAdj","",Qt::CaseInsensitive);boo_l << foo;}
    for (int i=0;i<boo_l.count();i++){QSettings boo_s(boo_l.at(i),QSettings::NativeFormat);boo_s.setValue("LODAdj",value);}
}

gui::gui(QWidget *parent) :QWidget(parent),ui(new Ui::gui){
    ui->setupUi(this);


    //Set Custom Theme
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(darkPalette);
    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");

    //Get Current LOD
    QSettings sets("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Video", QSettings::NativeFormat);
    QStringList keys = sets.allKeys();
    QStringList foo_l; QStringList boo_l;QString foo;

    for (int i=0;i<keys.count();i++){//find all LOD keys (if multiple cards/drivers)
        if (keys.value(i).contains("LODAdj")){
            foo_l << "HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Video\\" + keys.at(i);
        }
    }
    for (int i=0;i<foo_l.count();i++){//create a list with all registry LOD paths found
        foo = foo_l.at(i);
        foo.replace("/","\\",Qt::CaseInsensitive);
        foo.replace("\\LODAdj","",Qt::CaseInsensitive);
        boo_l << foo;
    }

    for (int j=0; j<boo_l.count();j++){//get value from each registry LOD path; only last is visible in GUI
        QSettings lodadj(boo_l.at(j), QSettings::NativeFormat);
        ui->value_0->setText(QString("Current LOD: %1").arg(lodadj.value("LODAdj").toString()));
    }
    //Show value of sliders in GUI
    ui->value_1->setText(QString::number(ui->slider_1->value() * 0.25));
    ui->value_2->setText(QString::number(ui->slider_2->value() * 0.25));
    ui->value_3->setText(QString::number(ui->slider_3->value() * 0.25));
    ui->value_4->setText(QString::number(ui->slider_4->value() * 0.25));
    ui->value_5->setText(QString::number(ui->slider_5->value() * 0.25));
}

gui::~gui()
{
    delete ui;
}

void gui::on_slider_1_valueChanged(int value)
{
    ui->value_1->setText(QString::number(value * 0.25));
}

void gui::on_slider_2_valueChanged(int value)
{
    ui->value_2->setText(QString::number(value* 0.25));
}

void gui::on_slider_3_valueChanged(int value)
{
    ui->value_3->setText(QString::number(value * 0.25));
}

void gui::on_slider_4_valueChanged(int value)
{
    ui->value_4->setText(QString::number(value * 0.25));
}

void gui::on_slider_5_valueChanged(int value)
{
    ui->value_5->setText(QString::number(value* 0.25));
}

void gui::on_github_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/GENiEBEN/quick-lod"));
}

void gui::on_tabWidget_currentChanged(int index)
{
    switch (index){
        case 1: {
        ui->table_AboutModules->setColumnWidth(1,70);
        ui->table_AboutModules->horizontalHeader()->setStretchLastSection(1);
        }
    }
}

void gui::on_button_1_clicked()
{
    set_amd_lod(ui->value_1->text());
    ui->value_0->setText(QString("Current LOD: %1").arg(ui->value_1->text()));
}

void gui::on_button_2_clicked()
{
    set_amd_lod(ui->value_2->text());
    ui->value_0->setText(QString("Current LOD: %1").arg(ui->value_2->text()));
}

void gui::on_button_3_clicked()
{
    set_amd_lod(ui->value_3->text());
    ui->value_0->setText(QString("Current LOD: %1").arg(ui->value_3->text()));
}

void gui::on_button_4_clicked()
{
    set_amd_lod(ui->value_4->text());
    ui->value_0->setText(QString("Current LOD: %1").arg(ui->value_4->text()));
}

void gui::on_button_5_clicked()
{
    set_amd_lod(ui->value_5->text());
    ui->value_0->setText(QString("Current LOD: %1").arg(ui->value_5->text()));
}

void gui::on_Start_clicked()
{
    QSettings reg("GENiEBEN","QuickLOD");
    reg.setValue("AMD_1", ui->value_1->text());
    reg.setValue("AMD_2", ui->value_2->text());
    reg.setValue("AMD_3", ui->value_3->text());
    reg.setValue("AMD_4", ui->value_4->text());
    reg.setValue("AMD_5", ui->value_5->text());

    QProcess hotkeys;
    hotkeys.startDetached("quicklod-hotkeys.exe");
    qApp->quit();
}
