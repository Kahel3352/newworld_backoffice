#include "connexionwindow.h"
#include "ui_connexionwindow.h"
#include <QSqlQuery>
#include <QCryptographicHash>

ConnexionWindow::ConnexionWindow(QSqlDatabase* db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnexionWindow)
{
    qDebug()<<"ConnexionWindow::ConnexionWindow(QWidget *parent) :QDialog(parent),ui(new Ui::ConnexionWindow)";
    ui->setupUi(this);

    this->db = db;

    //on lie les slots on boutons
    connect(ui->pushButtonOk, SIGNAL(clicked()), this, SLOT(clickOk()));
    connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(clickCancel()));
}

ConnexionWindow::~ConnexionWindow()
{
    delete ui;
}

QString ConnexionWindow::getLogin()
{
    qDebug()<<"QString ConnexionWindow::getLogin()";
    return employe;
}

//quand on clic sur ok
void ConnexionWindow::clickOk()
{
    qDebug()<<"void ConnexionWindow::clickOk()";
    QSqlQuery query;
    query.prepare("SELECT Employe.* FROM Employe WHERE nom=? AND prenom=? AND mdp=password(?)");
    query.addBindValue(ui->lineEditNom->text());
    query.addBindValue(ui->lineEditPrenom->text());
    query.addBindValue(ui->lineEditMdp->text());
    if(query.exec())
    {
        if(query.size()>0)
        {
            employe = ui->lineEditPrenom->text()+" "+ui->lineEditNom->text();
            accept();
        }
        else
        {
            ui->labelNom->setStyleSheet("color: red");
            ui->labelPrenom->setStyleSheet("color: red");
            ui->labelMdp->setStyleSheet("color: red");
        }
    }
    else
        qDebug()<<"La requête ne s'execute pas";
}

//quand on click sur annuler
void ConnexionWindow::clickCancel()
{
    qDebug()<<"void ConnexionWindow::clickCancel()";
    //on renvoie rejected
    reject();
}
