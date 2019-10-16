#ifndef QUOTEDBMANAGER_H
#define QUOTEDBMANAGER_H

#include <stdlib.h>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>


typedef struct quote{

        QString date, name, compName,address1, address2, city,state,email,phone1,phone2,fax,custom1,custom2,notes;
        int quoteNum, salesP, platSize, carriage, knee, logTurner, logDeck,setWorks, extraTrailerValue, cantTurnValue,customPrice1,customPrice2,sawSpecs,status,linear,handled;
        bool horiz, vert, topSaw, feedJoy,hdOutfeed, sawdustChain, pulleyTrailer, trailer52, extraTrailer,cantTurn,hamDog,extraAxle;
    } Quote; //QuoteForStruct



class QuoteDbManager
{
public:
    QuoteDbManager(void);\
    int getNumQuotes(void);
    Quote getQuote(int );
    void buildQuote(Quote);
    void start(void);


private:
    QSqlDatabase db;
    bool mySql;








};

#endif // QUOTEDBMANAGER_H
