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



private:
    Ui::authentication *ui;
    QSqlDatabase db;

private slots:
    void accept(void);
    void reject(void);


};

#endif // AUTHENTICATION_H
