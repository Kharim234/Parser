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


void MainWindow::on_pushButton_Parse_File_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select log files"), "/home/jana", tr("Log files (*.xdcf *.*)"));

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QByteArray Text_in_file = file.readAll();
    file.close();
    Parser_files external_parser;
    external_parser.Parse_string("limits",Text_in_file);

    ui->textBrowser->append(external_parser.Get_parsed_string());
}
