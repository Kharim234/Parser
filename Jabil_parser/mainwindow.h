#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Parse_File_clicked();


    void on_pushButton_Save_File_clicked();

    void on_pushButton_Parse_File_for_Minitab_clicked();

private:
    Ui::MainWindow *ui;
    void parse_for_limits_and_show_them(QString String_with_limits, QStringList Limits_to_parse);
    void show_string_list_in_one_line(QStringList List);
    QString m_Parse_file_path;
    QString Read_file(void);
    QStringList parse_for_limits(QString String_with_limits, QStringList Limits_to_parse);
    void parse_for_limits_and_show_them_minitab(QString String_with_limits, QStringList Limits_to_parse);
    QString Check_and_replace(QString string_to_find, QString string_to_replace, QString primary_string);
};
#endif // MAINWINDOW_H

