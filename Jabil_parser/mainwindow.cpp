#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include "parser_files.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::parse_for_limits_and_show_them(QString String_with_limits){
    Parser_files internal_parser;
    QStringList Limits_to_show;
    internal_parser.Parse_string("upper", String_with_limits);
    Limits_to_show.append(internal_parser.Get_parsed_string());
    internal_parser.Parse_string("nominal", String_with_limits);
    Limits_to_show.append(internal_parser.Get_parsed_string());
    internal_parser.Parse_string("lower", String_with_limits);
    Limits_to_show.append(internal_parser.Get_parsed_string());
    show_string_list_in_one_line(Limits_to_show);
}

void MainWindow::show_string_list_in_one_line(QStringList List){
    QString Whole_line;
    if(List.size() > 0){
        Whole_line = List.at(0);
    }

    for(int i = 1; i < List.size(); i++){
        Whole_line += ";" + List.at(i);

    }
    ui->textBrowser->append(Whole_line);
}
void MainWindow::on_pushButton_Parse_File_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select log files"), "/home/jana", tr("Log files (*.xdcf *.*)"));

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QByteArray Text_in_file = file.readAll();
    file.close();
    Parser_files external_parser, internal_parser;
    int file_index;
    QString Parsed_string;
    QStringList Limits_to_parse = {"upper", "nominal", "lower"};

    if(external_parser.Parse_string("limits",Text_in_file) > 0){
        show_string_list_in_one_line(Limits_to_parse);
    }

    do{
        file_index = external_parser.Parse_string("limits",Text_in_file);
        Parsed_string = external_parser.Get_parsed_string();
        Text_in_file.remove(0, file_index);

        if(file_index >= 0){
          Parsed_string = external_parser.Get_parsed_string();
          this->parse_for_limits_and_show_them(Parsed_string);
        }

    }while(file_index>=0);

}
