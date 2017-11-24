#include "mainwindow.h"
#include <QApplication>
#include "connexionwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConnexionWindow connexionWindow;

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
}
