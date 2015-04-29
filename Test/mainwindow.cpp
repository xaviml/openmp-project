#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->ui->actionLoad_Image,SIGNAL(triggered()),this,SLOT(loadImages()));
    connect(this->ui->actionExit,SIGNAL(triggered()),this,SLOT(exit()));
    connect(this->ui->chooseDirectory,SIGNAL(clicked()),this,SLOT(chooseImage()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImages(){

}
void MainWindow::exit(){
    std::exit(0);
}
void MainWindow::chooseImage(){
    QString path = MainWindow::getFile();
    ui->imageinput->setText(path);
    cout <<  path.toStdString() << endl;

}
QString MainWindow::getFile(){
    return QFileDialog::getOpenFileName(this,tr("Directory"),NULL,tr("All files (*.*);;JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
}

void MainWindow::showImages(QList<QString> filesList){
    QWidget *imagesWidget = new QWidget();
    QGridLayout *grid = ui->gridLayout;


    QImage copy;
    QString tempFileName;
    QList<QImage> images;
    /*QList<QString> filesList;
    filesList << "image1.png" << "image2.png" << "image3.png";*/

    foreach(QFileInfo fileInfo, filesList){

        tempFileName = fileInfo.absoluteFilePath();
        cout << tempFileName.toStdString() << endl;
        Mat image2 = imread(tempFileName.toStdString(), CV_LOAD_IMAGE_COLOR);
        QImage image = QImage((uchar*) image2.data, image2.cols, image2.rows, image2.step, QImage::Format_RGB888);
        //QImage image(tempFileName);
        copy = image.scaled(200,200,Qt::KeepAspectRatio);
        images.append(copy);
    }
    int n = 3;
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            QPixmap p(QPixmap::fromImage(images[i]));
            QLabel *label = new QLabel(imagesWidget);
            label->setPixmap(p);
            grid->addWidget(label, i, j);
        }
    }
}