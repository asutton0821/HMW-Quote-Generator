
#ifndef QUOTEPDFMANAGER_H
#define QUOTEPDFMANAGER_H


#include "quotedbpricemanager.h"
#include "quotedbmanager.h"
#include <QObject>
#include <QStandardPaths>
#include <QFile>
#include <QDate>
#include <QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include <QTextDocument>
#include <QPdfWriter>
#include <QPainter>
#include <QMargins>
#include <QStandardPaths>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include <QRegExp>


class quotePDFManager : public QObject
{
    Q_OBJECT
public:
    explicit quotePDFManager(QObject *parent = 0);
    QString saveLocation;
    QDate compDate;



signals:

private:
    QString array[100];
    int length;
    int totalPrice;

public slots:
    void print(int,Quote,QList<QString>, int, QString);
    void updateLocation(QString);
    void updateCompletionDate(QDate);
    QDate getCompletionDate(void);
    void checkForDateToOverlap(void);
    void updateArray(QString arrayl[100]);
    void updateLength(int );
    //bool findOverride(QString ); //This function is deprecated. Do not use.
    void updateTotalPrice(int);
    QString detailPage(Quote);
    QString getOptions(Quote, int , QList<QString> array, int );
    //QString getOptions(Quote, int , QString array[100], int ) <-This function is deprecated. Do not use.
    //bool findInArray(QString array[100], QString value, int index); <- This function is deprecated. Do not use.
    bool findInArray(QList<QString> array, QString value, int index);
    QString getQuotedMill(QList<QString> array, int index, int quoteNum);
    bool findOverride(QString overrideValue, int quoteNum);



};

#endif // QUOTEPDFMANAGER_H
