#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(ConnexionWindow *connexionWindow, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->labelEmploye->setText(connexionWindow->getLogin());
}

MainWindow::~MainWindow()
{
    delete ui;
}
