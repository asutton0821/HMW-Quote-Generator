#include "quotepdfmanager.h"



/*
 *
 * This class handles the generation of a PDF quote.
 * It grabs the information and total price from the other
 * classes in this project.
 *
 * The class makes sure that a saveLocation variable is initialized. It does this
 * by first checking to see if the file "saveLocation" exists, and if not, it creates
 * it and fills it with the default save location (/home/{USER}/Desktop/hmw)/ Otherwise,
 * if there is a custom save location, it will load this.
 *
 *
 * The save location can be changed from the "File" menu.
 */


quotePDFManager::quotePDFManager(QObject *parent) :
    QObject(parent)
{

   // saveLocation = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+"/hmwquotes";
    QFile file("saveLocation");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Save File Doesn't Exist";
    }
    if(QFileInfo(file).exists()){
      //  qDebug()<< "Save file exists";
        QTextStream in(&file);
        int line = 0;
        while(!in.atEnd()){
            if(line == 0){
            saveLocation = in.readLine();
           // qDebug() << "Found in file: " << saveLocation;
            line++;
            }
            else{
                break;
            }

        }
        file.close();

    }
    else{
        saveLocation = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        //qDebug() << "Creating a new file";
            if(file.open(QIODevice::ReadWrite)){
                QTextStream stream(&file);
                stream << saveLocation << endl;
            }
           // qDebug() << "File created";
            file.close();

    }



                QSqlQuery qu;
        qu.exec("SELECT quoteNum FROM quoteTable WHERE name = 'statusBox' AND value = 'Open'");
        qu.last();

        int numberOfOpenQuotes = qu.at() + 1;

        if(numberOfOpenQuotes < 0 ){
            qDebug() << "No open quotes.";
            numberOfOpenQuotes = 1;
        }

        qDebug() << "number of open quotes = " << numberOfOpenQuotes;
        qDebug() << "Completion date: " << QDate::currentDate().addDays(21 * numberOfOpenQuotes);

        compDate = QDate::currentDate().addDays(21 * numberOfOpenQuotes);




}

/*
 *
 * Prints the detailed page (all the info following the quote) after a page break.
 *
 *
 */


QString quotePDFManager::detailPage(Quote q){
    QString lengthPhrase;
    QSqlQuery qu;

    qu.exec("SELECT * FROM quoteTable WHERE name = 'platform40RadioButton' AND quoteNum = "+QString::number(q.quoteNum));
    if(qu.last()){
        qu.exec("SELECT * FROM quoteTable WHERE name = 'carriageKneesSpinBox' AND quoteNum = "+QString::number(q.quoteNum));
        qu.last();
        lengthPhrase+=""+QString::number(qu.value(3).toInt())+" Headblock trailer is 40 Ft. plus the deck overhang (3.5 ft.) during transport = total 43.5 ft.";
    }
    qu.exec("SELECT * FROM quoteTable WHERE name = 'platform48RadioButton' AND quoteNum = "+QString::number(q.quoteNum));
    if(qu.last()){
        qu.exec("SELECT * FROM quoteTable WHERE name = 'carriageKneesSpinBox' AND quoteNum = "+QString::number(q.quoteNum));
        qu.last();
        lengthPhrase+=""+QString::number(qu.value(3).toInt())+" Headblock trailer is 48 Ft. plus the deck overhang (3.5 ft.) during transport = total 51.5 ft.";
    }
    qu.exec("SELECT * FROM quoteTable WHERE name = 'platform52RadioButton' AND quoteNum = "+QString::number(q.quoteNum));
    if(qu.last()){
        qu.exec("SELECT * FROM quoteTable WHERE name = 'carriageKneesSpinBox' AND quoteNum = "+QString::number(q.quoteNum));
        qu.last();
        lengthPhrase+=""+QString::number(qu.value(3).toInt())+" Headblock trailer is 52 Ft. plus the deck overhang (3.5 ft.) during transport = total 55.5 ft.";
    }
    qu.exec("SELECT * FROM quoteTable WHERE name = 'platform60RadioButton' AND quoteNum = "+QString::number(q.quoteNum));
    if(qu.last()){
        qu.exec("SELECT * FROM quoteTable WHERE name = 'carriageKneesSpinBox' AND quoteNum = "+QString::number(q.quoteNum));
        qu.last();
        lengthPhrase+=""+QString::number(qu.value(3).toInt())+" Headblock trailer is 60 Ft. plus the deck overhang (3.5 ft.) during transport = total 63.5 ft.";
    }
    QString html = "<html><font size=4 face='Times New Roman'><br /><br />Additional Equipment required to operate sawmill<br />Saw Blade<br />Air Compressor<br />Power - diesel or electric motor<br/>Pulleys and Bushings & Belts for connecting motor to mandrel</font><font size=4 face='Times New Roman'> <br /><br /><br />When the sawmill is completed and before you pick it up, we suggest that you come here so that we can go over general operation, maintenance and safety of the sawmill with you. We'll let you know a date when the mill is near to completion (see quote for estimated date). <br />Transporting the sawmill will require the following:<br /><br />LENGTH: "+lengthPhrase+"<br />HEIGHT: Approximately 12 Ft.<br />WEIGHT: Not overweight. Weight on axle is approximately 17,500 lbs.<br />WIDTH: <u>OVERWIDE LOAD - PERMITS REQUIRED. 13Ft. 6 In.</u><br /><br />Driver will need:<br />2 Wide load signs<br />2 Chains (to tie log deck down for transport)<br />6 Red flags<br />Bill of Lading<br /><br /><br />If you do not have a trucking company there to use, you can try:<br /> TRAILER TRANSIT*           800-423-3647 - Bob (nationwide)<br />JIMMY T WOOD*       901-358-9599 - Daniel (Memphis, TN)<br />L & O TRUCKING*      901-942-4991 (Memphis, TN)<br /> * These have hauled our sawmills in the past.</font></html>";
    return html;
}

/* This functions finds the values in the array.
 *
 * VERY DEPRECATED.
 */
/*
bool quotePDFManager::findInArray(QString array[100], QString value, int index){
    for(int i=0; i<index;i++){
        if(array[i].compare(value) ==0){
           // qDebug() << "FOUND IN ARRAY!! " << value;
            //qDebug() << "found " << value;
            return true;
        }
    }
    return false;
} */


bool quotePDFManager::findInArray(QList<QString> array, QString value, int index){
    for(int i=0; i<index;i++){
        if(array[i].compare(value) ==0){
            //qDebug() << "FOUND IN ARRAY!! " << value;
            //qDebug() << "found " << value;
            return true;
        }
    }
    return false;
}

/*
 *
 *
 * This is the base layout for quotePDF manager. This handles the
 * "Options" page and the logic behind it is simple:
 * if a certain platform size is selected and an upgrade is added,
 * then grab that option, grab the price, and add it to the list.
 *
 * For future use, this function is basically dynamic.
 * Throw your value into the database, along with a description and price,
 * and it will grab automatically using the If Statements from the MainWindow.cpp.
 *
 * Please make sure when adding a new checkbox, that you add it to the connections file that
 * is stored on the desktop.
 *
 * The PDF generator can automatically detect a spinbox by making sure that the value is greater than 0. If it is,
 * then it will account for there being a spinbox or some other type of object, and give you the appropriate price on that.
 *
 *
 * Note: uses a table to align everything correctly.
 *
 */


QString quotePDFManager::getOptions(Quote q,int quoteNum, QList<QString> array, int index){
    QSqlQuery query;
    quoteDBPriceManager qP;
    QString str = "";

    if(findInArray(array,"mill40",index) && findInArray(array,"threeStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'LD3Over2';");
        //query.exec("SELECT LD3Over2 FROM quoteItems");
        query.last();
        int price = query.value(2).toInt();
        QLocale l = QLocale::system();
        QString s = l.toString(price);
        str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+"</td><td align='right' style='padding-right:0px style='padding-left:0px'><b>$ "+s+"</b></td></tr>";
    }
    if(findInArray(array,"mill48",index) && findInArray(array,"fourStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'LD4Over3';");
        //query.exec("SELECT LD4Over3 FROM quoteItems");
        query.last();
        int price = query.value(2).toInt();
        QLocale l = QLocale::system();
        QString s = l.toString(price);
        str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+"</td><td align='right' style='padding-right:0px style='padding-left:0px'><b>$ "+s+"</b></td></tr>";
    }
    if(findInArray(array,"mill52",index) && findInArray(array,"fourStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'LD4Over3';");
        //query.exec("SELECT LD4Over3 FROM quoteItems");
        query.last();
        int price = query.value(2).toInt();
        QLocale l = QLocale::system();
        QString s = l.toString(price);
        str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+"</td><td align='right' style='padding-right:0px style='padding-left:0px'><b>$ "+s+"</b></td></tr>";
    }

    //No log deck options:

    if(findInArray(array,"mill40",index) && findInArray(array,"noStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD2';");
        //query.exec("SELECT noLD2 FROM quoteItems");
        query.last();
        int price = query.value(2).toInt();
        QLocale l = QLocale::system();
        QString s = l.toString(price);
        str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+"</td><td align='right' style='padding-right:0px style='padding-left:0px'><b>-$ "+s+"</b></td></tr>";
    }
    if(findInArray(array,"mill48",index) && findInArray(array,"noStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD3';");
        //query.exec("SELECT noLD3 FROM quoteItems");
        query.last();
        int price = query.value(2).toInt();
        QLocale l = QLocale::system();
        QString s = l.toString(price);
        str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+"</td><td align='right' style='padding-right:0px style='padding-left:0px'><b>-$ "+s+"</b></td></tr>";

    }
    if(findInArray(array,"mill52",index) && findInArray(array,"noStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD3';");
        //query.exec("SELECT noLD3 FROM quoteItems");
        query.last();
        int price = query.value(2).toInt();
        QLocale l = QLocale::system();
        QString s = l.toString(price);
        str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+"</td><td align='right' style='padding-right:0px style='padding-left:0px'><b>-$ "+s+"</b></td></tr>";

    }
    if(findInArray(array,"mill60",index) && findInArray(array,"noStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD4';");
        //query.exec("SELECT noLD4 FROM quoteItems");
        query.last();
        int price = query.value(2).toInt();
        QLocale l = QLocale::system();
        QString s = l.toString(price);
        str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+"</td><td align='right' style='padding-right:0px style='padding-left:0px'><b>-$ "+s+"</b></td></tr>";

    }





    for(int i = 0; i<index;i++){
        QRegExp re("\\d*");
        query.exec("SELECT * FROM quoteTable WHERE quoteNum = " + QString::number(quoteNum) + " AND connectionName = '"+array.at(i)+"'");
        if(query.last() && query.value(3).toInt() > 1 && re.exactMatch(query.value(3).toString())){
            if(findOverride(array.at(i),quoteNum)){
                    int value = query.value(3).toInt();
                    query.exec("SELECT * FROM quoteItems WHERE name = '"+array.at(i)+"';");
                    query.last();
                    query.exec("SELECT * FROM quoteItems WHERE name = '"+array.at(i)+"'");
                    query.last();
                    QString name = query.value(1).toString();
                    query.exec("SELECT * FROM quoteItems WHERE name = '"+array.at(i)+"';");
                    query.last();
                    str+="<tr><td style='padding-left:25px'>"+name+" x "+QString::number(value)+":</td><td align='right' ><b>NO CHARGE</b></td></tr>";
            }
            if(array.at(i) == "wheelSize"){
                int value = query.value(3).toInt();
                if(value == 12){
                    int totalValue = 1000; //dollars
                    query.exec("SELECT * FROM quoteItems WHERE name = '"+array.at(i)+"'");
                    query.last();
                    QString name = query.value(1).toString();
                    QLocale l = QLocale::system();
                    QString s = l.toString(totalValue);
                    str+="<tr><td style='padding-left:25px'>"+name+":</td><td align='right' ><b>$ "+s+"</b></td></tr>";
                }
                else if(value == 14){
                    int totalValue = 1500; //dollars
                    query.exec("SELECT * FROM quoteItems WHERE name = '"+array.at(i)+"'");
                    query.last();
                    QString name = query.value(1).toString();
                    QLocale l = QLocale::system();
                    QString s = l.toString(totalValue);
                    str+="<tr><td style='padding-left:25px'>"+name+":</td><td align='right' ><b>$ "+s+"</b></td></tr>";
                }


             }
            else{
                int value = query.value(3).toInt();
                query.exec("SELECT * FROM quoteItems WHERE name = '"+array.at(i)+"';");
                query.last();
                int totalValue = query.value(2).toInt() * value;
                query.exec("SELECT * FROM quoteItems WHERE name = '"+array.at(i)+"'");
                query.last();
                QString name = query.value(1).toString();
                QLocale l = QLocale::system();
                QString s = l.toString(totalValue);
                str+="<tr><td style='padding-left:25px'>"+name+" x "+QString::number(value)+":</td><td align='right' ><b>$ "+s+"</b></td></tr>";
            }

        }


        else if(findOverride(array.at(i),quoteNum)){
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array.at(i)+"';");
            query.last();
            str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+":</td><td align='right' ><b>NO CHARGE</b></td></tr>";
        }

      else{
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array.at(i)+"';"); //find all the things that are marked... grab their prices
           // qDebug() << array[i];
            if(query.last()){
                int price = query.value(2).toInt();
                QLocale l = QLocale::system();
                QString s = l.toString(price);
                str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+"</td><td align='right' ><b>$ "+s+"</b></td></tr>";

            }
      }
    }
    if(q.custom1 != "" && q.custom1 != " "){
        //qDebug() << "FOUND CUSTOM!";
        if(q.customPrice1 == 0){
            str+="<tr><td style='padding-left:25px'>"+q.custom1+": </td><td align='right' ><b>NO CHARGE</b></td></tr>";
        }
        else{
       // str+=""+q.custom1+": <b>$" + QString::number(q.customPrice1)+ "</b><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
        int price = q.customPrice1;
        QLocale l = QLocale::system();
        QString s = l.toString(price);
        str+="<tr><td style='padding-left:25px'>"+q.custom1+": </td><td align='right' ><b>$ "+s+"</b></td></tr>";
        }
    }
    if(q.custom2 != "" && q.custom2 != " "){
        //qDebug() << "FOUND CUSTOM2";
        if(q.customPrice2 == 0){
            str+="<tr><td style='padding-left:25px'>"+q.custom2+": </td><td align='right' ><b>NO CHARGE</b></td></tr>";
        }
        else{
       //str+=""+q.custom2+": <b>$" + QString::number(q.customPrice2)+ "</b><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
        int price = q.customPrice2;
        QLocale l = QLocale::system();
        QString s = l.toString(price);
        str+="<tr><td style='padding-left:25px'>"+q.custom2+": </td><td align='right' ><b>$ "+s+"</b></td></tr>";
        }
    }
       //Checks to make sure that options exist.
       if(str.compare("") == 0){
               return str;
        }

       //int price = qP.priceQuote(q);
       int price = totalPrice;
       QLocale l = QLocale::system();
       QString s = l.toString(price);
       // qDebug() << "Str: " << str;
    return "<table width='100%'><font size=4 face='Times New Roman'><tr> <th align='left'><b>OPTIONS:</b></th></tr>"+str+"</table><br /><hr><br /><table width='100%'><font size=4 face='Times New Roman'><tr><td style='padding-left:100px'><b>HEAVY WEIGHT SAWMILL TOTAL W/ OPTIONS: </b></td><td align='right'><b>$ "+s+"</b></td></tr></table>";

}

/*
 *
 * Get options from the quote form using an array.
 *
 * Very deprecated
 */

/*
QString quotePDFManager::getOptions(Quote q,int quoteNum, QString array[100], int index){
    QSqlQuery query;
    quoteDBPriceManager qP;
    QString str = "";

    if(findInArray(array,"mill40",index) && findInArray(array,"threeStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'LD3Over2';");
        //query.exec("SELECT LD3Over2 FROM quoteItems");
        query.last();
        int price = query.value(2).toInt();
        QLocale l = QLocale::system();
        QString s = l.toString(price);
        str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+"</td><td align='right' style='padding-right:0px style='padding-left:0px'><b>$ "+s+"</b></td></tr>";
    }
    if(findInArray(array,"mill48",index) && findInArray(array,"fourStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'LD4Over3';");
        //query.exec("SELECT LD4Over3 FROM quoteItems");
        query.last();
        int price = query.value(2).toInt();
        QLocale l = QLocale::system();
        QString s = l.toString(price);
        str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+"</td><td align='right' style='padding-right:0px style='padding-left:0px'><b>$ "+s+"</b></td></tr>";
    }

    //No log deck options:

    if(findInArray(array,"mill40",index) && findInArray(array,"noStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD2';");
        //query.exec("SELECT noLD2 FROM quoteItems");
        query.last();
        int price = query.value(2).toInt();
        QLocale l = QLocale::system();
        QString s = l.toString(price);
        str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+"</td><td align='right' style='padding-right:0px style='padding-left:0px'><b>-$ "+s+"</b></td></tr>";
    }
    if(findInArray(array,"mill48",index) && findInArray(array,"noStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD3';");
        //query.exec("SELECT noLD3 FROM quoteItems");
        query.last();
        int price = query.value(2).toInt();
        QLocale l = QLocale::system();
        QString s = l.toString(price);
        str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+"</td><td align='right' style='padding-right:0px style='padding-left:0px'><b>-$ "+s+"</b></td></tr>";

    }
    if(findInArray(array,"mill60",index) && findInArray(array,"noStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD4';");
        //query.exec("SELECT noLD4 FROM quoteItems");
        query.last();
        int price = query.value(2).toInt();
        QLocale l = QLocale::system();
        QString s = l.toString(price);
        str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+"</td><td align='right' style='padding-right:0px style='padding-left:0px'><b>-$ "+s+"</b></td></tr>";

    }





    for(int i = 0; i<index;i++){




        if(array[i] == "cantTurner"){
            query.exec("SELECT * FROM quoteTable WHERE quoteNum = " + QString::number(quoteNum) + " AND connectionName = 'cantTurner'");
            query.last();
            int value = query.value(3).toInt(); //the number of canturners in the spin box
           // qDebug() << "PDF value is " << value;
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
            query.last();
            int totalValue = query.value(2).toInt() * value;
          //  qDebug() << "Total Cant Price PDF" << totalValue;
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"'");
            query.last();
            QString name = query.value(1).toString();
            QLocale l = QLocale::system();
            QString s = l.toString(totalValue);
            str+="<tr><td style='padding-left:25px'>"+name+" x "+QString::number(value)+":</td><td align='right' ><b>$ "+s+"</b></td></tr>";

        }
        if(array[i] == "brownsville"){
            query.exec("SELECT * FROM quoteTable WHERE quoteNum = " + QString::number(quoteNum) + " AND connectionName = 'brownsville'");
            query.last();
            int value = query.value(3).toInt(); //the number of brownsville in the spin box
           // qDebug() << "PDF value is " << value;
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
            query.last();
            int totalValue = query.value(2).toInt() * value;
          //  qDebug() << "Total Cant Price PDF" << totalValue;
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"'");
            query.last();
            QString name = query.value(1).toString();
            QLocale l = QLocale::system();
            QString s = l.toString(totalValue);
            str+="<tr><td style='padding-left:25px'>"+name+" x "+QString::number(value)+":</td><td align='right' ><b>$ "+s+"</b></td></tr>";

        }
        if(array[i] == "cantPushOff"){
            query.exec("SELECT * FROM quoteTable WHERE quoteNum = " + QString::number(quoteNum) + " AND connectionName = 'cantPushOff'");
            query.last();
            int value = query.value(3).toInt(); //the number of cantPushOff in the spin box
           // qDebug() << "PDF value is " << value;
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
            query.last();
            int totalValue = query.value(2).toInt() * value;
          //  qDebug() << "Total Cant Price PDF" << totalValue;
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"'");
            query.last();
            QString name = query.value(1).toString();
            QLocale l = QLocale::system();
            QString s = l.toString(totalValue);
            str+="<tr><td style='padding-left:25px'>"+name+" x "+QString::number(value)+":</td><td align='right' ><b>$ "+s+"</b></td></tr>";

        }
        else if(array[i] == "extraTrailer"){
            // qDebug() << "trailerLeg";
             query.exec("SELECT * FROM quoteTable WHERE quoteNum = " + QString::number(quoteNum) + " AND connectionName = 'extraTrailer'");
             query.last();
             int value = query.value(3).toInt(); //the number of canturners in the spin box
           //  qDebug() << "PDF value is " << value;
             query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
             query.last();
             int totalValue = query.value(2).toInt() * value;
           //  qDebug() << "Total Trailer Price PDF" << totalValue;
             query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"'");
             query.last();
             QString name = query.value(1).toString();
             QLocale l = QLocale::system();
             QString s = l.toString(totalValue);
             str+="<tr><td style='padding-left:25px'>"+name+" x "+QString::number(value)+":</td><td align='right' ><b>$ "+s+"</b></td></tr>";
             //qDebug() << totalPrice << endl;

         }





        else if(array[i] == "cantTurners" && findOverride("actionCant_Turners")){
                query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
                query.last();
                str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+":</td><td align='right' ><b>NO CHARGE</b></td></tr>";


            }
       else if(array[i] == "hamDog" && findOverride("actionHam_Dog")){
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
            query.last();
            str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+":</td><td align='right' ><b>NO CHARGE</b></td></tr>";

            }
       else if(array[i] == "pulley36" && findOverride("36_Pulley_And_Bushing")){
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
            query.last();
            str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+":</td><td align='right' ><b>NO CHARGE</b></td></tr>";

            }
        else  if(array[i] == "hdOutfeed" && findOverride("actionHD_Outfeed_Belt")){
              query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
              query.last();
              str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+":</td><td align='right' ><b>NO CHARGE</b></td></tr>";

            }
       else if(array[i] == "sawDustChain" && findOverride("actionSawdust_Chain")){
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
            query.last();
            str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+":</td><td align='right' ><b>NO CHARGE</b></td></tr>";

            }
       else if(array[i] == "vertEdg" && findOverride("actionVertical_Edger")){
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
            query.last();
            str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+":</td><td align='right' ><b>NO CHARGE</b></td></tr>";

            }
        else if(array[i] == "feedJoyStick" && findOverride("actionFeed_Joystick")){
             query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
             query.last();
             str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+":</td><td align='right' ><b>NO CHARGE</b></td></tr>";

            }
       else if(array[i] == "topSaw" && findOverride("actionTop_Saw")){
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
            query.last();
            str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+":</td><td align='right' ><b>NO CHARGE</b></td></tr>";

            }
        else if(array[i] == "trailerLeg" && findOverride("actionTrailer_Leg")){
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
            query.last();
            str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+":</td><td align='right' ><b>NO CHARGE</b></td></tr>";

            }
       else if(array[i] == "trailer52" && findOverride("action52_Trailer")){
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
            query.last();
            str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+":</td><td align='right' ><b>NO CHARGE</b></td></tr>";

            }
       else  if(array[i] == "linearCarriage" && findOverride("actionLinear")){
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
            query.last();
            str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+":</td><td align='right' ><b>NO CHARGE</b></td></tr>";

            }


      else{
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';"); //find all the things that are marked... grab their prices
           // qDebug() << array[i];
            if(query.last()){
                int price = query.value(2).toInt();
                QLocale l = QLocale::system();
                QString s = l.toString(price);
                str+="<tr><td style='padding-left:25px'>"+query.value(1).toString()+"</td><td align='right' ><b>$ "+s+"</b></td></tr>";
            }
      }



//qDebug() << "QUOTE: " << q.quoteNum << " custom: " << q.custom1;
    }
    if(q.custom1 != "" && q.custom1 != " "){
        //qDebug() << "FOUND CUSTOM!";
        if(q.customPrice1 == 0){
            str+="<tr><td style='padding-left:25px'>"+q.custom1+": </td><td align='right' ><b>NO CHARGE</b></td></tr>";
        }
        else{
       // str+=""+q.custom1+": <b>$" + QString::number(q.customPrice1)+ "</b><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
        int price = q.customPrice1;
        QLocale l = QLocale::system();
        QString s = l.toString(price);
        str+="<tr><td style='padding-left:25px'>"+q.custom1+": </td><td align='right' ><b>$ "+s+"</b></td></tr>";
        }
    }
    if(q.custom2 != "" && q.custom2 != " "){
        //qDebug() << "FOUND CUSTOM2";
        if(q.customPrice2 == 0){
            str+="<tr><td style='padding-left:25px'>"+q.custom2+": </td><td align='right' ><b>NO CHARGE</b></td></tr>";
        }
        else{
       //str+=""+q.custom2+": <b>$" + QString::number(q.customPrice2)+ "</b><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
        int price = q.customPrice2;
        QLocale l = QLocale::system();
        QString s = l.toString(price);
        str+="<tr><td style='padding-left:25px'>"+q.custom2+": </td><td align='right' ><b>$ "+s+"</b></td></tr>";
        }
    }
       //Checks to make sure that options exist.
       if(str.compare("") == 0){
               return str;
        }

       //int price = qP.priceQuote(q);
       int price = totalPrice;
       QLocale l = QLocale::system();
       QString s = l.toString(price);
       // qDebug() << "Str: " << str;
    return "<table width='100%'><font size=4 face='Times New Roman'><tr> <th align='left'><b>OPTIONS:</b></th></tr>"+str+"</table><br /><hr><br /><table width='100%'><font size=4 face='Times New Roman'><tr><td style='padding-left:100px'><b>HEAVY WEIGHT SAWMILL TOTAL W/ OPTIONS: </b></td><td align='right'><b>$ "+s+"</b></td></tr></table>";

}
 */

/*
 *
 * This is the new, enhanced way to get the quoted mill using the
 * database and the connections array. Index specifies the
 * number of objects in the array at the current time of use.
 *
 *
 *
 */

QString quotePDFManager::getQuotedMill(QList<QString> array, int index){
        QString carType;
        int lD, platPrice,platSize,knees;
        QSqlQuery query;

        if(findInArray(array,"challengerCarriage",index)){
            carType = carType = "CHALLENGER Carriage: 36&quot;";
        }
        else if(findInArray(array,"magnumCarriage",index)){
             carType = "MAGNUM LT Carriage: 40&quot;";
        }
        /*
        if(q.carriage == 1){
            carType = "CHALLENGER Carriage: 36&quot;";
        }
        if(q.carriage == 2){
            carType = "MAGNUM LT Carriage: 40&quot;";
        } */

        if(findInArray(array,"mill48",index) && findInArray(array,"challengerCarriage",index)){
            lD = 3;
            platSize = 48;
            knees = 3;
            query.exec("SELECT * FROM quoteItems WHERE name = 'mill48Chal';");
            query.last();
            platPrice = query.value(2).toInt();
            //qDebug() << platPrice;
        }
        if(findInArray(array,"mill40",index) && findInArray(array,"challengerCarriage",index)){
            lD =2;
            platSize = 40;
            knees = 2;
            query.exec("SELECT * FROM quoteItems WHERE name = 'mill40Chal';");
            query.last();
            platPrice = query.value(2).toInt();
        }
        if(findInArray(array,"mill60",index) && findInArray(array,"challengerCarriage",index)){
            lD = 4;
            platSize = 60;
            knees = 4;
            query.exec("SELECT * FROM quoteItems WHERE name = 'mill60Chal';");
            query.last();
            platPrice = query.value(2).toInt();
        }
        if(findInArray(array,"mill48",index) && findInArray(array,"magnumCarriage",index)){
            lD =3;
            platSize = 48;
            knees = 3;
            query.exec("SELECT * FROM quoteItems WHERE name = 'mill48LT';");
            query.last();
            platPrice = query.value(2).toInt();
        }
        if(findInArray(array,"mill40",index) && findInArray(array,"magnumCarriage",index)){
            lD = 2;
            platSize = 40;
            knees = 2;
            query.exec("SELECT * FROM quoteItems WHERE name = 'mill40LT';");
            query.last();
            platPrice = query.value(2).toInt();
        }
        if(findInArray(array,"mill60",index) && findInArray(array,"magnumCarriage",index)){
            lD = 4;
            platSize = 60;
            knees = 4;
            query.exec("SELECT * FROM quoteItems WHERE name = 'mill60LT';");
            query.last();
            platPrice = query.value(2).toInt();
        }

        if(findInArray(array,"mill52",index) && findInArray(array,"challengerCarriage",index)){
            lD = 3;
            platSize = 52;
            knees = 3;
            query.exec("SELECT * FROM quoteItems WHERE name = 'mill52Chal';");
            query.last();
            platPrice = query.value(2).toInt();
            //qDebug() << platPrice;
        }
        if(findInArray(array,"mill52",index) && findInArray(array,"magnumCarriage",index)){
            lD =3;
            platSize = 52;
            knees = 3;
            query.exec("SELECT * FROM quoteItems WHERE name = 'mill52LT';");
            query.last();
            platPrice = query.value(2).toInt();
        }



        quoteDBPriceManager qPrice;

        int price = platPrice;
        QLocale l = QLocale::system();
        QString s = l.toString(price);

       //QString priceOfMill = "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>HEAVY WEIGHT SAWMILL TOTAL &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$ "+s+"</b>";

        QString priceOfMill = "<table width='100%'><font size=4 face='Times New Roman'><tr><td style='padding-left:100px'><b>HEAVY WEIGHT SAWMILL TOTAL: </b></td><td align='right'><b>$ "+s+"</b></td></tr></table>";

        QString string =  "<font size=4 face='Times New Roman'>One (1) Hurdle Heavy Weight Automatic Sawmill on a "+QString::number(platSize)+" Ft. Three Beam Platform(12&quot; 30# Beams)<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QString::number(knees)+" Headblock "+carType+" knee openings, 29&quot; dog openings,<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Variable Tapering, Extra Heavy Duty Tong Dogs<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;CAM Setworks<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Husk Frame Assembly with Offbearer Belt to end of mill<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Sawyer's Cab with Door, Insulation & Air Conditioner<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;555 Series Feed<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Standard Chain Log Turner<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QString::number(lD)+" Strand Log Deck"+priceOfMill+"<br /></p></p></p>";
        return string;
}


/*
 *
 * Handles the actual printing of the PDF. This starts off
 * by grabbing the client info and sales person info from the
 * quote struct, and adds it to the quote PDF. It checks to
 * see if notes, address, city, etc exist and if so, adds them
 * to the working PDF.
 *
 * This will automatically open the PDF once generated.
 * The user will be prompted if a required field isn't filled
 * in.
 *
 */
void quotePDFManager::print(int quoteNum,Quote q, QList<QString> array, int index){
    QString ops = getOptions(q,quoteNum,array,index);
    QString salesP;
    QSqlQuery qu;
    QString addressBox;

    //
    qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'salesP' AND quoteNum = "+QString::number(quoteNum));
    if(qu.last()){
        salesP = qu.value(3).toString();
    }
    else{
        salesP = "";
    }
    QString addressLine;
    QString addressLine2;

    qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'address1' AND quoteNum = "+QString::number(quoteNum));
        if(qu.last()){
             addressLine = qu.value(3).toString();
        }
        else{
            addressLine = "";
        }


    qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'address2' AND quoteNum = "+QString::number(quoteNum));
    if(qu.last()){
        addressLine2 = qu.value(3).toString();
    }
    else{
        addressLine2 = "";
    }
    if(addressLine.compare("") != 0 && addressLine2.compare("") != 0){
        addressBox+=""+addressLine+"<br />"+addressLine2;
    }
    else{
        addressBox = addressLine;
    }

    QString phoneBox;
    QString phone1;
    QString phone2;

    qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'phone1' AND quoteNum = "+QString::number(quoteNum));
    if(qu.last()){
         phone1 = "Phone (Primary): "+qu.value(3).toString();
    }
    else{
        phone1 = "";
    }
    qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'phone2' AND quoteNum = "+QString::number(quoteNum));
    if(qu.last()){
        phone2 = "Phone (Secondary): "+qu.value(3).toString();
    }
    else{
        phone2 = "";
    }

    if(phone2.compare("") !=0 && phone1.compare("") != 0){
        phoneBox+=""+phone1+"<br />"+phone2;

    }
    else{
        phoneBox+=phone1;
    }



    qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'notes' AND quoteNum = "+QString::number(quoteNum));
    //qu.last();
    QString noteBox;
    if(qu.last() && qu.value(3).toString() != "" && qu.value(3).toString() != " " ){
        noteBox = "<b>Notes: </b><br />"+qu.value(3).toString()+"<br />";
    }
    else{
        noteBox = "";
    }
    QString compName;
    QString topBoxString;
    qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'compName' AND quoteNum = "+QString::number(quoteNum));
    if(qu.last()){
     compName = qu.value(3).toString();
    }
    else{
         compName = "";
    }

    if(compName != "" && compName != " "){
        topBoxString+=""+compName+"<br />";
    }



    if(addressBox != " " && addressBox != ""){
        topBoxString+=""+addressBox+"<br />";
    }

    QString city;
    qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'city' AND quoteNum = "+QString::number(quoteNum));
    if(qu.last()){
        city = qu.value(3).toString();
    }
    else{
        city = "";
    }

    if(city != "" && city != " "){
        topBoxString+=""+city+"";
    }

    QString states;
    qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'states' AND quoteNum = "+QString::number(quoteNum));
    if(qu.last()){
        states = ", "+qu.value(3).toString();
    }
    else{
        states = "";
    }

        topBoxString+=""+states+"<br />";



    if(phone1 != "" && phone1 != " "){
        topBoxString+=""+phoneBox+"<br />";
    }
    QString email;
    qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'email' AND quoteNum = "+QString::number(quoteNum));
    if(qu.last()){
        email = "Email: " + qu.value(3).toString();
    }
    else{
        email = "";
    }

    if(email != "" && email != " "){
        topBoxString+=""+email+"<br />";
    }

    QString fax;
    qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'fax' AND quoteNum = "+QString::number(quoteNum));
    if(qu.last()){
         fax = "Fax: "+ qu.value(3).toString();
    }
    else{
        fax = "";
    }
    if(fax != "" && fax != " "){
        topBoxString+=""+fax+"<br />";
    }
    topBoxString+="<br />";

    QString defaultQuoteString;

       int saw = 575;
    qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'sawSpeed' AND quoteNum ="+QString::number(quoteNum));
    if(qu.last()){
        saw = qu.value(3).toInt();
    }

    /*
     * Changed completion to delivery... may need to change back in the future.
     *
     */

    defaultQuoteString = "<br />The sawmill is designed to run "+QString::number(saw)+"rpm at the mandrel. <br />This quote is valid for thirty (30) days.<br/>Expected delivery date: "+getCompletionDate().toString("MM/dd/yyyy")+". 10% Deposit Required. <br />Balance of sawmill will be due prior to shipping.<br />FOB- Hurdle Machine Works, Inc., Moscow, TN - FREIGHT COLLECT<br />";




            ;


   QString html = "<html><font size=4 face='Times New Roman'><div align=right>"+q.date+"</div><div align=right>Quote: "+QString::number(q.quoteNum)+"</div><div align=right>"+salesP+"</div><img src = :/img/img/hurdle.jpg width=700 height=150 align='right'/><hr noshade><br />"+q.name+"<br />"+topBoxString+""
           +getQuotedMill(array,index)+""+ops+ "<br /><div style=\"page-break-after:always !important;\"></div>" +noteBox+
           "" +defaultQuoteString+""+detailPage(q)+"<font size=4 face='Times New Roman'></html>"

            ;





    QTextDocument document;
    document.setHtml(html);
   // qDebug() << saveLocation;
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);


    //hmwquotes
    if((saveLocation.compare(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+"") == 0)  && !QDir(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)).exists()){
        QDir().mkdir(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+"");
        //qDebug() << "Created folder hmw";
    }
    else{
      //  qDebug() << "Save location is now: " << saveLocation;
    }



    QString fileName = saveLocation+"/Quote"+QString::number(quoteNum)+".pdf";
    printer.setOutputFileName(fileName);
    printer.newPage();
    document.print(&printer);

    QDesktopServices::openUrl(QUrl("file:///"+fileName));





}

/*
 *
 * This updates the save directory of the quotes.
 * Default location is saved to the desktop.
 *
 *
 */

void quotePDFManager::updateLocation(QString fileName){
    saveLocation = fileName;
    //qDebug() << "New save location updated to: " << saveLocation << endl;
    QFile file("saveLocation");
    file.remove();
    if(file.open(QIODevice::ReadWrite)){
        QTextStream stream(&file);
        stream << saveLocation << endl;
    }
    file.close();

}

/*
 *
 * Gets the current completion date and returns it.
 *
 *
 */

QDate quotePDFManager::getCompletionDate(){
    QSqlQuery qu;
    qu.exec("SELECT quoteNum FROM quoteTable WHERE name = 'statusBox' AND value = 'Closed'");
    qu.last();

    int numberOfOpenQuotes = qu.at() + 1;

    if(numberOfOpenQuotes < 0 ){
        qDebug() << "No open quotes.";
        numberOfOpenQuotes = 1;
    }

    qDebug() << "number of open quotes = " << numberOfOpenQuotes;
    qDebug() << "Delivery date: " << QDate::currentDate().addDays(21 * numberOfOpenQuotes);

    compDate = QDate::currentDate().addDays(21 * numberOfOpenQuotes);
    updateCompletionDate(compDate);

    return compDate;
}

/*
 *
 *
 * Updates the completion date file and saves it,
 * thereby preserving the completion date the user
 * chooses.
 *
 *
 */

void quotePDFManager::updateCompletionDate(QDate date){
    compDate = date;
    qDebug() << "New date updated to: " << date.toString("MM/dd/yyyy") << endl;
    checkForDateToOverlap();
}
/*
 * Checks the current completion date.
 * If the completion date <= current date - 10 days, then it adds
 * 32 more days to the completion date automatically.
 * This keeps everyting consistent.
 *
 *
 */

void quotePDFManager::checkForDateToOverlap(){

    //qDebug() << compDate.toString("MM/dd/yyyy") << QDate::currentDate().addDays(32).toString("MM/dd/yyyy") << (compDate < QDate::currentDate().addDays(10)) << endl;
    if(compDate <= QDate::currentDate().addDays(10)){
        QDate newDate = QDate::currentDate().addDays(33);
        //compDate = newDate;
        //qDebug() << newDate;
        updateCompletionDate(newDate);
    }
}

/*
 *
 * Updates the array that is sent from Price Manager.
 *
 */

void quotePDFManager::updateArray(QString arrayl[100]){
    for(int i= 0; i<length;i++){
        array[i] = arrayl[i];
    }
}

/*
 *
 *
 * Updates the length of the array to match that of price manager.
 *
 */

void quotePDFManager::updateLength(int lengthl){
    length = lengthl;
}

/*
 *
 * Finds any overrides.
 * DEPRECATED.
 *
 */

/*
bool quotePDFManager::findOverride(QString value){
    for(int i = 0; i < length + 1; i++){
        if(array[i] == value){
            return true;
        }
    }
    return false;
} */

/*
 *
 * Updated to work dynamically.
 *
 */


bool quotePDFManager::findOverride(QString value,int quoteNum){
    //qDebug() << "looking for an override of " << value << " with quoteNum of " << quoteNum;
    QSqlQuery qu;
    qu.exec("SELECT * FROM quoteOverrides WHERE quoteNum = " +QString::number(quoteNum)+ " AND connectionName = '" +value+ "'");
    if(qu.last()){
        return true;
    }
    else{
        return false;
    }
}

/*
 *
 * Updates total price
 *
 */
void quotePDFManager::updateTotalPrice(int totalPrice2){
    totalPrice = totalPrice2;

}






