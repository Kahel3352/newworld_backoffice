#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
#include "connexionwindow.h"


/**
 * @brief Retourne un QSqlDatabase initialisé avec l'adresse de la base de données, sont nom, le login et le mot de passe
 */
QSqlDatabase initDatabase();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db = initDatabase();
    db.open();
    ConnexionWindow connexionWindow(&db);

    //si la connexionWindow renvoie accepted
    if(connexionWindow.exec()==QDialog::Accepted)
    {
        //on créer la mainWindow en lui passant la fenêtre de connexion
        MainWindow w(&connexionWindow);
        w.show();

        return a.exec();
    }
    //sinon on retourne un code erreur
    else
    {
        return -1;
    }

    db.close();
}

QSqlDatabase initDatabase()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL3");
    db.setHostName("localhost");
    db.setDatabaseName("nw");
    db.setUserName("mvanlerberghe");
    db.setPassword("ini01");
    return db;
}
