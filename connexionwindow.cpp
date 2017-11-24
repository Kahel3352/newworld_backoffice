#include "connexionwindow.h"
#include "ui_connexionwindow.h"
#include <QSqlQuery>
#include <QCryptographicHash>

ConnexionWindow::ConnexionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnexionWindow)
{
    qDebug()<<"ConnexionWindow::ConnexionWindow(QWidget *parent) :QDialog(parent),ui(new Ui::ConnexionWindow)";
    ui->setupUi(this);
    //on lie les slots on boutons
    connect(ui->pushButtonOk, SIGNAL(clicked()), this, SLOT(clickOk()));
    connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(clickCancel()));

    //on ouvre la base de donnée
    if(!connectDatabase())
    {
        qDebug()<<"Connexion à la bdd échouée";
        qDebug()<<db.lastError();
    }
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
    QSqlQuery query;
    query.prepare("SELECT employe.* FROM employe WHERE nom=? AND prenom=? AND mdp=?");
    query.addBindValue(ui->lineEditNom->text());
    query.addBindValue(ui->lineEditPrenom->text());
    query.addBindValue(QCryptographicHash::hash("test"),QCryptographicHash::Md5);
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
}

//quand on click sur annuler
void ConnexionWindow::clickCancel()
{
    //on renvoie rejected
    reject();
}


bool ConnexionWindow::connectDatabase()
{
    qDebug()<<"bool ConnexionWindow::connectDatabase()";
    db = QSqlDatabase::addDatabase("QMYSQL3");
    db.setHostName("localhost");
    db.setDatabaseName("nw");
    db.setUserName("mvanlerberghe");
    db.setPassword("ini01");
    return db.open();
}
