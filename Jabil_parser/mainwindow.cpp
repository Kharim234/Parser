#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include "parser_files.h"
#include <QTextStream>

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

QStringList MainWindow::parse_for_limits(QString String_with_limits, QStringList Limits_to_parse){
    Parser_files internal_parser;
    QStringList Limits_to_show;
    for(int i  = 0; i < Limits_to_parse.size(); i++){
        internal_parser.Parse_string(Limits_to_parse.at(i), String_with_limits);
        Limits_to_show.append(internal_parser.Get_parsed_string());
    }
    return Limits_to_show;
}

void MainWindow::parse_for_limits_and_show_them(QString String_with_limits, QStringList Limits_to_parse){
    QStringList Limits_to_show;
    Limits_to_show = this->parse_for_limits(String_with_limits, Limits_to_parse);
    show_string_list_in_one_line(Limits_to_show);
}

void MainWindow::parse_for_limits_and_show_them_minitab(QString String_with_limits, QStringList Limits_to_parse){
    QStringList Limits_to_show;
    Limits_to_show = this->parse_for_limits(String_with_limits, Limits_to_parse);
    for(int i  = 0; i < Limits_to_parse.size(); i++){
        if(Limits_to_parse.at(i) == "upper"){
        }
        if(Limits_to_parse.at(i) == "lower"){
        }



    }


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
QString MainWindow::Read_file(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select log files"), "/home/jana", tr("Log files (*.xdcf *.*)"));
    ui->textBrowser->clear();
    m_Parse_file_path.clear();

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        ui->textBrowser->append("File read error");
        return "";
    }
    m_Parse_file_path += fileName;

    QString Text_in_file = file.readAll();
    file.close();
    return Text_in_file;

}
void MainWindow::on_pushButton_Parse_File_clicked()
{


    Parser_files external_parser, internal_parser;
    int file_index;
    QString Parsed_string;

    QString Text_in_file = this->Read_file();
    if(Text_in_file.length() == 0){
        return;
    }

    QStringList Limits_to_parse = {"designator","subDesignator","upper", "nominal", "lower"};
    QString external_XML_mark_string_to_parse = "limits";

    if(external_parser.Parse_string(external_XML_mark_string_to_parse,Text_in_file) > 0){
        show_string_list_in_one_line(Limits_to_parse);
    }else{
        ui->textBrowser->append("Not found any limits");
        return;
    }

    do{
        file_index = external_parser.Parse_string(external_XML_mark_string_to_parse,Text_in_file);
        Parsed_string = external_parser.Get_parsed_string();
        Text_in_file.remove(0, file_index);

        if(file_index >= 0){
          Parsed_string = external_parser.Get_parsed_string();
          this->parse_for_limits_and_show_them(Parsed_string, Limits_to_parse);
        }

    }while(file_index>=0);

}

void MainWindow::on_pushButton_Save_File_clicked()
{

//    QString fileName = QFileDialog::getOpenFileName(this,
//        tr("Save file"), "/home/jana", tr("save as (*.csv)"));
    QString Parse_file_path_with_changed_ending, Parse_file_path = m_Parse_file_path;
    if(Parse_file_path.length()>0){
        Parse_file_path_with_changed_ending = (Parse_file_path.split(".")).at(0);
        Parse_file_path_with_changed_ending +=  ".csv";
    }else{
       Parse_file_path_with_changed_ending = "/home/untitled.csv";
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               Parse_file_path_with_changed_ending,
                               tr("CSV file (*.csv)"));

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        //ui->textBrowser->clear();
        //ui->textBrowser->append("Error - save file");
        return;
    }
    QTextStream out(&file);
    out << ui->textBrowser->toPlainText();

}

QString MainWindow::Check_and_replace(QString string_to_find, QString string_to_replace, QString primary_string){
    int index;
    QString replaced_string;
    index = primary_string.indexOf(string_to_find);
    replaced_string = primary_string;
    if(index != -1){
     replaced_string.replace(index,string_to_find.length(), string_to_replace);
    }

    return replaced_string;
}

void MainWindow::on_pushButton_Parse_File_for_Minitab_clicked()
{
    Parser_files external_parser, internal_parser;
    int file_index;
    QString Parsed_string;

    QString Text_in_file = this->Read_file();
    if(Text_in_file.length() == 0){
        return;
    }

    //QStringList Limits_to_parse = {"subDesignator","upper","lower"};
    QString external_XML_mark_string_to_parse = "limits";

    if(external_parser.Parse_string(external_XML_mark_string_to_parse,Text_in_file) <= 0){
        ui->textBrowser->append("Not found any limits");
        return;
    }



    do{
        file_index = external_parser.Parse_string(external_XML_mark_string_to_parse,Text_in_file);
        Parsed_string = external_parser.Get_parsed_string();
        Text_in_file.remove(0, file_index);

        if(file_index >= 0){
            ui->textBrowser->append("XCapa;");
            ui->textBrowser->append("   Baseline;");

            internal_parser.Parse_string("subDesignator", Parsed_string);
            ui->textBrowser->append("   RSubgroups  " + internal_parser.Get_parsed_string() + ";");

            internal_parser.Parse_string("lower", Parsed_string);
            QString parsed_string = internal_parser.Get_parsed_string();
            parsed_string = Check_and_replace(".",",",parsed_string);
            ui->textBrowser->append("   LSpec  " + parsed_string + ";");

            internal_parser.Parse_string("upper", Parsed_string);
            parsed_string = internal_parser.Get_parsed_string();
            parsed_string = Check_and_replace(".",",",parsed_string);
            ui->textBrowser->append("   USpec  " + parsed_string + ".");
        }

    }while(file_index>=0);
    ui->textBrowser->append("XWORD");
}
