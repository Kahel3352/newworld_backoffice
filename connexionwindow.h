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

public:
    explicit ConnexionWindow(QWidget *parent = 0);
    ~ConnexionWindow();
    QString getLogin();

private:
    Ui::ConnexionWindow *ui;
    bool connectDatabase();
    QSqlDatabase db;
    QString employe;

public slots:
    void clickOk();
    void clickCancel();
};

#endif // CONNEXIONWINDOW_H
