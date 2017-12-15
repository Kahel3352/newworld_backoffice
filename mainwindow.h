#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connexionwindow.h"
#include <QBitmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(ConnexionWindow* connexionWindow, QWidget *parent = 0);
    ~MainWindow();


private slots:
    /**
     * @brief remet le formulaire de saisi des variétés à zéro
     */
    void clearVarieteForm();

    /**
     * @brief remplis le tableau avec les valeurs de la bdd
     */
    void initTableVarietes();

    /**
     * @brief selectionne une
     */
    void on_tableVarietes_clicked(const QModelIndex &index);

    /**
     * @brief accepte une proposition de variete
     */
    void on_pushButtonVarieteAccepter_clicked();

    /**
     * @brief refuse une proposition de variete
     */
    void on_pushButtonVarieteRefuser_clicked();

    /**
     * @brief annule les modifications
     */
    void on_pushButtonVarieteAnnuler_clicked();

private:
    Ui::MainWindow *ui;

    /**
     * @brief variete en cours d'édition dans le tableau
     */
    int currentVariete;
};

#endif // MAINWINDOW_H
