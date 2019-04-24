#include "quotedbmanager.h"


#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QFile>
#include <QDate>
#include <QSqlError>
#include <QApplication>
#include <QMessageBox>


/*
 *
 * This is the main class for QuoteDbManager.
 * It will allow the database to be opened and
 * then get the list of tables.
 *
 *
 *
 */

QuoteDbManager::QuoteDbManager(void)
{



mySql = true;



}

void QuoteDbManager::start(){
    /*
    if(mySql == false){
   QFile::exists("quotedatabase.sqlite");
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/colson/quotedatabase.sqlite");
    bool opened = db.open();
    db.tables();

   // qDebug() << getNumQuotes();
    }

    else{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("quotedatabase");
    db.setHostName("localhost1"); //CHANGE THIS WHEN DEPLOYING
    db.setPassword("password");
    db.setUserName("root");

   qDebug() << "Database open? : " << db.open();

    }

    if(db.open() == false){
        qDebug() << "Database does not exist. Fatal error has occured";
        //QMessageBox::critical(this,"Fatal Error","A fatal error has occured (100): No connection to the database was found.");
       // QMessageBox::critical(this,"No Connection","No connection to database. Errno: 100");
        qApp->exit(100);
        }
*/


}


/*
 * This function returns the number of quotes in the
 * database. Because a database always starts out at
 * -1 for an empty database, we must return 1 to the
 * quote generator to start it off at quote number 1.
 * Otherwise, for each number of quotes that are in
 * the database, we must return that number + 2.
 * For instance, if there are 3 quotes in the database,
 * then the database has index 0, 1, and 2. We must return
 * the integer 4, which is what the quote generator will show
 * in its quote number box.
 *
 *
 */


int QuoteDbManager::getNumQuotes(){

   QSqlQuery query;
    query.exec("SELECT * FROM quotes");
    query.last();
  //qDebug() << "Quotes: " << query.at() + 1;

    if(query.at() > 0){
       return query.at() + 2;
    }
    if(query.at() == 0){
        return query.at() + 2;
    }


    return 1;

}




/*
 *
 * Thus function gets a quote from the specified quote number,
 * assuming that the quoteNumber is greater than 0 and returns those
 * values in a struct.
 *
 *
 */
Quote QuoteDbManager::getQuote(int quoteNumber){
    Quote q;

    if(quoteNumber > 0){
        /*

                QString date, name, compName,address1, address2, city,state,email,phone1,phone2,fax,custom1,custom2,notes;
                int quoteNum, salesP, platSize, carriage, knee, logTurner, logDeck,setWorks, extraTrailerValue, cantTurnValue,customPrice1,customPrice2,sawSpecs,status,linear;
                bool horiz, vert, topSaw, feedJoy,hdOutfeed, sawdustChain, pulleyTrailer, trailer52, extraTrailer,cantTurn,hamDog,extraAxle;


        */

        QSqlQuery query;
         query.exec("SELECT * FROM quotes WHERE quoteNum = "+ QString::number(quoteNumber)); //grab the quoteNumber we want.
        // qDebug() << query.lastError().text();
        query.next();
        q.date = query.value(0).toString();
       // qDebug() << q.date;
        q.name = query.value(1).toString();
       /* q.compName = query.value(2).toString();
        q.address1 = query.value(3).toString();
        q.address2 = query.value(4).toString();
        q.city = query.value(5).toString();
        q.state = query.value(6).toString();
        q.email = query.value(7).toString();
        q.phone1 = query.value(8).toString();
        q.phone2 = query.value(9).toString();
        q.fax = query.value(10).toString();
        q.custom1 = query.value(11).toString();
        q.custom2 = query.value(12).toString();
       q.notes = query.value(13).toString();
       */ q.quoteNum = query.value(2).toInt();
        q.customPrice1 = query.value(6).toInt();
        q.customPrice2 = query.value(7).toInt();
        q.custom1 = query.value(4).toString();
        q.custom2 = query.value(5).toString();
       /* q.salesP = query.value(15).toInt();
        q.platSize = query.value(16).toInt();
        q.carriage = query.value(17).toInt();
        q.knee = query.value(18).toInt();
        q.logTurner = query.value(19).toInt();
        q.logDeck = query.value(20).toInt();
        q.setWorks = query.value(21).toInt();
        q.extraTrailerValue = query.value(22).toInt();
        q.cantTurnValue = query.value(23).toInt();
        q.customPrice1 = query.value(24).toInt();
        q.customPrice2 = query.value(25).toInt();
        q.sawSpecs = query.value(26).toInt();
        q.horiz = query.value(27).toBool();
        q.vert = query.value(28).toBool();
        q.topSaw = query.value(29).toBool();
        q.feedJoy = query.value(30).toBool();
        q.hdOutfeed = query.value(31).toBool();
        q.sawdustChain = query.value(32).toBool();
        q.pulleyTrailer = query.value(33).toBool();
        q.trailer52 = query.value(34).toBool();
        q.extraTrailer = query.value(35).toBool();
        q.cantTurn = query.value(36).toBool();
        q.hamDog = query.value(37).toBool();
        q.extraAxle = query.value(38).toBool();
        q.status = query.value(39).toInt();
        q.linear = query.value(40).toInt();
       */ q.handled = query.value(3).toInt();
      //  q.compName = query.value(39).toBool();
       // q.compName = query.value(40).toBool();

 //   qDebug() << "Quote built";

    return q;


    }




}

/*
 * This function builds the quote based on a corresponding struct.
 * Once the struct is sent from the main program,
 * then the buildQuote() function will then store it into
 * the database. It first determines whether the quote
 * will be inserted or updated (based on how current the
 * quote number is) and then will manipulate the fields
 * in the database.
 */


void QuoteDbManager::buildQuote(Quote q){

    QSqlQuery qu;

    if(q.quoteNum == getNumQuotes()){
   // qu.prepare("INSERT INTO quotes VALUES (:quoteDate, :name, :compName, :address1, :address2, :city, :states, :email, :phone1, :phone2, :fax, :custom1, :custom2, :notes, :quoteNum, :salesP, :platSize, :carriage, :knee, :logTurner, :logDeck, :setWorks, :extraTrailerValue, :cantTurnValue, :customPrice1, :customPrice2, :sawSpecs, :horiz, :vert, :topSaw, :feedJoy, :hdOutFeed, :sawdustChain, :pulleyTrailer, :trailer52, :extraTrailer, :cantTurn, :hamDog, :extraAxle, :statusQuote, :linearCarriage, :handled) ");
    qu.prepare("INSERT INTO quotes VALUES (:quoteDate, :name, :quoteNum, :handled,:custom1,:custom2,:customPrice1,:customPrice2) ");

    }

    else if(q.quoteNum < getNumQuotes()){
        //qDebug() << "Entered";
        //qu.prepare("UPDATE quotes SET quoteDate=:quoteDate, name=:name,compName=:compName,address1=:address1,address2=:address2,city=:city,states=:states,email=:email,phone1=:phone1,phone2=:phone2,fax=:fax,custom1=:custom1,custom2=:custom2,notes=:notes,salesP=:salesP,platSize=:platSize,carriage=:carriage,knee=:knee,logTurner=:logTurner,logDeck=:logDeck,setWorks=:setWorks,extraTrailerValue=:extraTrailerValue,cantTurnValue=:cantTurnValue,customPrice1=:customPrice1,customPrice2=:customPrice2,sawSpecs=:sawSpecs,horiz=:horiz,vert=:vert,topSaw=:topSaw,feedJoy=:feedJoy,hdOutFeed=:hdOutFeed,sawdustChain=:sawdustChain,pulleyTrailer=:pulleyTrailer,trailer52=:trailer52,extraTrailer=:extraTrailer,cantTurn=:cantTurn,hamDog=:hamDog,extraAxle=:extraAxle,statusQuote=:statusQuote,linearCarriage=:linearCarriage, handled=:handled WHERE quoteNum=:quoteNum");
        qu.prepare("UPDATE quotes SET quoteDate=:quoteDate, name=:name,handled=:handled,quoteNum=:quoteNum,custom1=:custom1,custom2=:custom2,customPrice1=:customPrice1,customPrice2=:customPrice2 WHERE quoteNum=:quoteNum");

    }

    //bind values to quote struct
    qu.bindValue(":quoteDate",q.date);
    qu.bindValue(":name",q.name);
    qu.bindValue(":quoteNum",q.quoteNum);
    qu.bindValue(":handled",q.handled);
    qu.bindValue(":custom1",q.custom1);
    qu.bindValue(":custom2",q.custom2);
    qu.bindValue(":customPrice1",q.customPrice1);
    qu.bindValue(":customPrice2",q.customPrice2);
    qu.exec();// << qu.lastError().text();
  //  qDebug() << "Quote inserted into table!";




}


