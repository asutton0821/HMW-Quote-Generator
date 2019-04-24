#ifndef QUOTEDBPRICEMANAGER_H
#define QUOTEDBPRICEMANAGER_H


#include <stdlib.h>
#include <stdio.h>
#include "quotedbmanager.h"
#include "quotepdfmanager.h"
#include <QRegExp>

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QFile>
#include <QDate>
#include <QSqlError>


class quoteDBPriceManager
{
public:
    quoteDBPriceManager(void );
    int priceQuote(Quote );
    void addOverridesToArray(QString ,int );
    bool findOverride(QString);
    void printArray(void);
    QString * getArray(void);
    int getTotalPrice(void);
    void removeFromArray(QString);
    int priceQuote(Quote , QString array[100], int );
    bool findInArray(QString array[100], QString value, int index);
    bool findInArray(QList<QString> array, QString value, int index);
    int priceQuote(Quote q, QString array[100], int index, int quoteNum);
    int priceQuote(Quote q,QList<QString> array, int index, int quoteNum);
    void resetOverrideArray(void);
    void processDynamicOverrides(QString overrideValue,int quoteNum);
    bool findOverride(QString overrideValue, int quoteNum);


private:
    QString array[100];
    int arrayLength;
    int totalPrice;

};

#endif // QUOTEDBPRICEMANAGER_H
