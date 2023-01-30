#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QPixmap>
#include <QFileDialog>
#include <QString>
#include <QLabel>
#include <QDebug>
#include <QThread>
#include <QTimeLine>
#include <QTime>
#include <QMessageBox>

int currentImage = 0;
QStringList images;
int mSec(83);
QTimeLine imageSequence(1000,nullptr);
int w, h;
QString folder_name;
bool noImages = false;
bool play = true;
void delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(mSec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     w = ui->imageLabel->width();
     h = ui->imageLabel->height();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::resizeEvent(QResizeEvent*)
{

    ui->imageWidget->resize(this->size().width(),this->size().height()/1.3);
    w = ui->imageWidget->width();
    h = ui->imageWidget->height();
    ui->bottomWidget->resize(this->size().width(),ui->bottomWidget->height());
    ui->imageLabel->resize(w,h);


}

void MainWindow::on_folderButton_clicked()
{
    folder_name = " ";
    folder_name = QFileDialog::getExistingDirectory(0, ("Select folder with images"), QDir::currentPath());
    //if(folder_name != " ") ui->testLabel->setText(folder_name);
    QDir directory(folder_name);
    images = directory.entryList(QStringList() << "*.jpg" << "*.png" << "*JPG" << "*jpeg", QDir::Files);
    if(images.empty()){
        QMessageBox::warning(this, "Warning", "No pictures found");
        noImages = true;

    }
    else{
        noImages = false;
    QPixmap pix(folder_name+"/"+images.at(0));
    ui->imageLabel->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->imageLabel->resize(w,h);
    }
}

void MainWindow::printNextImage (){
    if(noImages == true){
        QMessageBox::warning(this, "Warning", "No pictures found");
    }
    else{
    if((currentImage % images.size()) == 0) currentImage = 0;
    QPixmap pix(folder_name+"/"+images.at(currentImage));
    ui->imageLabel->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->imageLabel->resize(w,h);
    currentImage++;
    }
}

void MainWindow::printPrevImage(){
    if(noImages == true){
        QMessageBox::warning(this, "Warning", "No pictures found");
    }
    else{
    //qDebug() << currentImage;
    if(currentImage == -1) currentImage = images.size()-1;
    //qDebug() << currentImage;
    QPixmap pix(folder_name+"/"+images.at(currentImage));
   // qDebug() << folder_name+"/"+images.at(currentImage);
    ui->imageLabel->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->imageLabel->resize(w,h);
    currentImage--;
    }
}

void MainWindow::on_playButton_clicked()
{
    if(noImages == true){
        QMessageBox::warning(this, "Warning", "No pictures found");
    }
    else{
    if( ui->playButton->text() == "play"){
    ui->playButton->setText("stop");
    play = true;

   while(play == true){
        printNextImage();
        delay();
        if( ui->playButton->text() == "play"){
            play = false;
        }
}
   printNextImage();
}



//}
     if( ui->playButton->text() == "stop"){
         ui->playButton->setText("play");
         //play = false;
     }
    }
}

void MainWindow::on_nextButton_clicked()
{
    printNextImage();
}

void MainWindow::on_prevButton_clicked()
{
    printPrevImage();
}

void MainWindow::on_lineEdit_returnPressed()
{

    bool ok;
    int intTmp = ui->lineEdit->text().toInt(&ok);
    if(ok) {
        mSec = abs(1000/intTmp);
    } else {
        QMessageBox::warning(this, "Warning", "Typed wrong fps number");
    }


}
