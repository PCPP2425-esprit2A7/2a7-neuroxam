#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    materielWidget = new materielwindow();
    ui->stackedWidget->addWidget(materielWidget);

    ui->stackedWidget->setCurrentWidget(ui->homeWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset_button_color(){
    switch(current_section){

    case 0:
        ui->homeButton->setStyleSheet("border-radius:20px;"
                                      "background-color:#226597;"
                                      "color:white;"
                                      );
        break;
    case 1:
        ui->employeButton->setStyleSheet("border-radius:20px;"
                                      "background-color:#226597;"
                                      "color:white;"
                                      );
        break;
    case 2:
        ui->centreButton->setStyleSheet("border-radius:20px;"
                                      "background-color:#226597;"
                                      "color:white;"
                                      );
        break;
    case 3:
        ui->examButton->setStyleSheet("border-radius:20px;"
                                      "background-color:#226597;"
                                      "color:white;"
                                      );
        break;

    case 4:
        ui->etudiantButton->setStyleSheet("border-radius:20px;"
                                      "background-color:#226597;"
                                      "color:white;"
                                      );
        break;

    case 5:
        ui->materielButton->setStyleSheet("border-radius:20px;"
                                      "background-color:#226597;"
                                      "color:white;"
                                      );
        break;
    case 6:
        ui->formationButton->setStyleSheet("border-radius:20px;"
                                      "background-color:#226597;"
                                      "color:white;"
                                      );
        break;
    }
}

void MainWindow::on_homeButton_clicked()
{
    reset_button_color();
    current_section = 0;
    ui->stackedWidget->setCurrentWidget(ui->homeWidget);
    ui->homeButton->setStyleSheet("border-radius:20px;"
                                  "background-color:#FF4444;"
                                  "color:white;"
                                  );
}

void MainWindow::on_materielButton_clicked()
{
    reset_button_color();
    current_section = 5;
    ui->stackedWidget->setCurrentWidget(materielWidget);
    ui->materielButton->setStyleSheet("border-radius:20px;"
                                  "background-color:#FF4444;"
                                  "color:white;"
                                  );
}



void MainWindow::on_centreButton_clicked()
{
    reset_button_color();
    current_section = 2;
    ui->centreButton->setStyleSheet("border-radius:20px;"
                                  "background-color:#FF4444;"
                                  "color:white;"
                                  );
}


void MainWindow::on_examButton_clicked()
{
    reset_button_color();
    current_section = 3;
    ui->examButton->setStyleSheet("border-radius:20px;"
                                 "background-color:#FF4444;"
                                "color:white;"
                                  );
}


void MainWindow::on_disconnectButton_clicked()
{
    emit disconnected();  // Notify main.cpp to relaunch login
    this->close();
}


void MainWindow::on_employeButton_clicked()
{
    reset_button_color();
    current_section = 1;
    ui->employeButton->setStyleSheet("border-radius:20px;"
                                  "background-color:#FF4444;"
                                  "color:white;"
                                  );
}


void MainWindow::on_formationButton_clicked()
{
    reset_button_color();
    current_section = 6;
    ui->formationButton->setStyleSheet("border-radius:20px;"
                                     "background-color:#FF4444;"
                                     "color:white;"
                                     );
}

