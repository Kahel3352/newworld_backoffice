#ifndef CONNEXIONWINDOW_H
#define CONNEXIONWINDOW_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class ConnexionWindow;
}

class ConnexionWindow : public QDialog
{
    Q_OBJECT

    /**
     * @class Gère la connexion à la fenêtre principale
     */

public:
    explicit ConnexionWindow(QWidget *parent = 0);
    ~ConnexionWindow();


    /**
     * @brief Retourne le patronyme de l'employé qui a réussi à se connecter
     */
    QString getLogin();

private:
    Ui::ConnexionWindow *ui;
    bool connectDatabase();
    QSqlDatabase db;

    /**
     * @brief Patronyme de l'employé qui a réussi à se connecter
     */
    QString employe;

public slots:
    void clickOk();
    void clickCancel();
};

#endif // CONNEXIONWINDOW_H
