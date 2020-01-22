#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QDialog>
#include "mainwindow.h"
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QFile>
#include <QDate>
#include <QSqlError>
#include <QSqlDriver>
#include "encryptionhandler.h"

namespace Ui {
class authentication;
}

class authentication : public QDialog
{
    Q_OBJECT

public:
    explicit authentication(QWidget *parent = 0);
    ~authentication();
    int getUserNum(void);
    int getPress(void);
    int buttonPressed;
    QString getUserDescription(void);
    bool frozen;
    bool isAcceptedTrueOrFalseValue;
    bool isAccepted(void);
    void writeToLog(QString name, QString data);
    QSqlDatabase db;




private:
    Ui::authentication *ui;


private slots:
    void accept(void);
    void reject(void);
    void testDBListener(void);




};

#endif // AUTHENTICATION_H
