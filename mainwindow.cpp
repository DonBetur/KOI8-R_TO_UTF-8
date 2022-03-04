#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextDecoder>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QTextStream>
#include <QDesktopServices>


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

void MainWindow::on_Clear_clicked()
{
    ui->koiText->clear();
    ui->utfText->clear();
    ui->FileLine->clear();
    ui->FileLineOut->clear();
}

void MainWindow::on_KtU_clicked()
{
    QString koi=ui->koiText->toPlainText();
    QTextEncoder* encoder = QTextCodec::codecForName("KOI8-R")->makeEncoder();
    QTextDecoder* decoder = QTextCodec::codecForName("UTF-8")->makeDecoder();
    ui->koiText->setText(koi);
    QByteArray outputData = encoder->fromUnicode(koi);
    QString utf = decoder->toUnicode(outputData,outputData.length());
    ui->utfText->setText(utf);
}

void MainWindow::on_SaveFile_clicked()
{
    QString filerasp = QFileDialog::getSaveFileName(0, "Open Dialog", "", "*.txt");
    ui->FileLineOut->setText(filerasp);
    QString filePath = ui->FileLineOut->text();
    QFile fileOut(filePath);
    if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
       {
           QTextStream stream(&fileOut);
           QString output = ui->utfText->toPlainText();
           stream << output;
           fileOut.close();
       }
}

void MainWindow::on_OpenFile_clicked()
{
    QString filerasp = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.txt");
    ui->FileLine->setText(filerasp);
    QString filePath = ui->FileLine->text();   
    QFile fileIn(filerasp);
    QString outp;
    ui -> utfText->clear();
   if(fileIn.open(QIODevice::ReadOnly|QIODevice::Text))
   {
       QTextStream stream(&fileIn);
       QString line;
       do {
           line = stream.readLine();
           outp.append(line);
       }
       while(!line.isNull());
       fileIn.close();
   }
       ui->koiText->setText(outp);
}
