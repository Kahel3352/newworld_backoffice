#include "mainwindow.h"
#include "ui_mainwindow.h"
QString REPERTOIREDESIMAGES="/home/mvanlerberghe/public_html/2.5/img/variete/";

MainWindow::MainWindow(ConnexionWindow *connexionWindow, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug()<<"MainWindow::MainWindow(ConnexionWindow *connexionWindow, QWidget *parent)";
    ui->setupUi(this);
    ui->labelEmploye->setText(connexionWindow->getLogin());

    //on initialise le QTableWidget des varietés
    initTableVarietes();

    //on donne une valeur "nulle" a currentVariete
    currentVariete = -1;
}

MainWindow::~MainWindow()
{
    qDebug()<<"MainWindow::~MainWindow()";
    delete ui;
}

void MainWindow::clearVarieteForm()
{
    ui->lineEditVarieteNom->clear();
    ui->comboBoxVarieteProduit->clear();
    ui->textEditVarieteDescription->clear();
}

void MainWindow::initTableVarietes()
{
    qDebug()<<"void MainWindow::initTableVarietes()";
    //on prépare la requête
    QString txtReq = "SELECT idVariete, nom FROM Variete WHERE valide != true";
    QSqlQuery query;

    //on récupère la taille du tableau
    int tableVarieteRowCount = ui->tableVarietes->rowCount();

    //on cache la colonne qui contient les id
    ui->tableVarietes->hideColumn(0);

    //on lance la requête
    if(query.exec(txtReq))
    {
        while(query.next())
        {
            tableVarieteRowCount++;
            ui->tableVarietes->setRowCount(tableVarieteRowCount);
            ui->tableVarietes->setItem(tableVarieteRowCount-1, 0, new QTableWidgetItem(query.value("idVariete").toString()));
            ui->tableVarietes->setItem(tableVarieteRowCount-1, 1, new QTableWidgetItem(query.value("nom").toString()));
        }
    }
    else
        qDebug()<<txtReq<<" n'a pu s'executer";
}

void MainWindow::on_tableVarietes_clicked(const QModelIndex &index)
{
    currentVariete = index.row();
    qDebug()<<"void MainWindow::on_tableVarietes_clicked(const QModelIndex &index)";
    QSqlQuery queryVariete;
    queryVariete.prepare("SELECT nom, description, libelle, image FROM Variete INNER JOIN Produit on Variete.idProduit = Produit.idProduit WHERE idVariete=?");
    queryVariete.addBindValue(ui->tableVarietes->item(index.row(), 0)->text().toInt());
    if(queryVariete.exec())
    {
        ui->comboBoxVarieteProduit->clear();
        queryVariete.next();
        qDebug()<<queryVariete.value("nom").toString()<<" selectionné";
        ui->lineEditVarieteNom->setText(queryVariete.value("nom").toString());
        ui->textEditVarieteDescription->setText(queryVariete.value("description").toString());
        QString fileName=REPERTOIREDESIMAGES +queryVariete.value("image").toString();
        qDebug()<<fileName;
        ui->labelImage->setPixmap(QPixmap(fileName).scaled(QSize(150, 150)));

        QSqlQuery queryProduits;
        QString strQueryProduits("SELECT libelle FROM Produit");
        if(queryProduits.exec(strQueryProduits))
        {
            while (queryProduits.next())
            {
                ui->comboBoxVarieteProduit->addItem(queryProduits.value("libelle").toString());
            }

            ui->comboBoxVarieteProduit->setCurrentText(queryVariete.value("libelle").toString());
        }
        else
            qDebug()<<strQueryProduits<<" n'a pu s'executer";

    }
    else
        qDebug()<<"SELECT nom, description FROM Variete WHERE idVariete=?"<<" ne s'execute pas";
}

void MainWindow::on_pushButtonVarieteAccepter_clicked()
{
    QSqlQuery query;
    query.prepare("UPDATE Variete SET valide = true WHERE idVariete=?");
    query.addBindValue(ui->tableVarietes->item(currentVariete, 0)->text());
    if(query.exec())
    {
        qDebug()<<ui->tableVarietes->item(currentVariete, 1)->text()<<" validé";
    }

    ui->tableVarietes->removeRow(currentVariete);
}

void MainWindow::on_pushButtonVarieteRefuser_clicked()
{
    QSqlQuery query;
    query.prepare("DELETE FROM Variete WHERE idVariete=?");
    query.addBindValue(ui->tableVarietes->item(currentVariete, 0)->text());
    if(query.exec())
    {
        qDebug()<<ui->tableVarietes->item(currentVariete, 1)->text()<<" à été refusé";
    }

    ui->tableVarietes->removeRow(currentVariete);
}

void MainWindow::on_pushButtonVarieteAnnuler_clicked()
{
    //on vide le formulaire
    clearVarieteForm();

    //on désélectionne la variete
    this->currentVariete = -1;
    ui->tableVarietes->reset();

}
