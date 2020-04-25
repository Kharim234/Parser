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


private:
    Ui::MainWindow *ui;
    void parse_for_limits_and_show_them(QString String_with_limits);
    void show_string_list_in_one_line(QStringList List);
};
#endif // MAINWINDOW_H
