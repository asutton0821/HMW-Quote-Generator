#include "quotedbpricemanager.h"
#include <QSqlDatabase>


quoteDBPriceManager::quoteDBPriceManager(void)
{

    arrayLength = 0;



/*
 *
 * No default class option
 *
 */

}

/*
 *
 * DEPRECATED!!!!!!!!!!!!!
 * This prices out the quotes according to what is given.
 * Based on default values you have a "starting price"
 * with additions and changes added on. This gets totaled up
 * and the total gets stored in the priceQuotes database
 * for future reference.
 * This will also allow you to update previously made quotes.
 * Once you edit the quote, just hit "Ok" and the quote will
 * then be updated and saved to the database.
 */


int quoteDBPriceManager::priceQuote(Quote q){
    QSqlQuery query;
    totalPrice = 0;

if(q.platSize == 40 && q.carriage == 1){ //40 challenger
    query.exec("SELECT mill40Chal FROM qPrice");
    query.last();
    qDebug() << "40' Challenger " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;

    }
if(q.platSize == 48 && q.carriage == 1 ){ //48 challenger
    query.exec("SELECT mill48Chal FROM qPrice");
    query.last();
        qDebug() << "48' Challenger " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;

    }
if(q.platSize == 60 && q.carriage == 1 ){ //60 challenger
    query.exec("SELECT mill60Chal FROM qPrice");
    query.last();
        qDebug() << "60' Challenger " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;
    }
if(q.platSize == 40 && q.carriage == 2 ){ //40 LT
    query.exec("SELECT mill40LT FROM qPrice");
    query.last();
        qDebug() << "40' LT " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;

    }
if(q.platSize == 48 && q.carriage == 2 ){ //48 LT
    query.exec("SELECT mill48LT FROM qPrice");
    query.last();
            qDebug() << "48' LT " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;

    }
if(q.platSize == 60 && q.carriage == 2){ //60 LT
    query.exec("SELECT mill60LT FROM qPrice");
    query.last();
            qDebug() << "60' LT " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;
    }
if(q.extraAxle == true){
    if(findOverride("actionExtra_Axle_Wheels")){
        qDebug() << "Found an override!";
        totalPrice+=0;
    }
    else{
    query.exec("SELECT extraAxle FROM qPrice");
    query.last();
    qDebug() << "Extra Axle " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;
    }
}
if(q.cantTurn == true){
    if(findOverride("actionCant_Turners")){
        qDebug() << "Found an override!";
        totalPrice+=0;
    }
    else{
    int value = q.cantTurnValue; //each cant turner is 3500 * the amount of knees.
    query.exec("SELECT cantTurner FROM qPrice");
    query.last();

    int totalValue = query.value(0).toInt() * q.knee;
    qDebug() << "Cant Turner : " << value << " * knees = " << totalValue;
    totalPrice+=totalValue; //so, take the number of cant turners, multiply by number of knees, which is multiplied by 3500
    qDebug() << totalPrice << endl;
    }


}

if(q.setWorks == 3){
    query.exec("SELECT compSet FROM qPrice");
    query.last();
    qDebug() << "CompSet " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;
}
if(q.setWorks == 2){
    query.exec("SELECT nanoSet FROM qPrice");
    query.last();
    qDebug() << "NanoSet " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;
}
if(q.hamDog == true){
    if(findOverride("actionHammer_Dog")){
        qDebug() << "Found an override!";
        totalPrice+=0;
    }
    else{
    query.exec("SELECT hamDog FROM qPrice");
    query.last();
    qDebug() << "HamDog " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;
    }
}
if(q.logTurner == 2){
    query.exec("SELECT hdChain FROM qPrice");
    query.last();
    qDebug() << "HD Chain " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;
}
if(q.logTurner == 3){
    query.exec("SELECT barLog FROM qPrice");
    query.last();
    qDebug() << "Bar " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;
}
if(q.platSize == 40 && q.logDeck == 2){
    query.exec("SELECT LD3Over2 FROM qPrice");
    query.last();
    qDebug() << "Strand 3 Instead of 2 " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;
}
if(q.platSize == 48 && q.logDeck == 3){
    query.exec("SELECT LD4Over3 FROM qPrice");
    query.last();
    qDebug() << "Strand 4 instead of 3 " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;
}

//No log deck options:

if(q.platSize == 40 && q.logDeck == 4){
    query.exec("SELECT noLD2 FROM qPrice");
    query.last();
    qDebug() << "Remove LogDeck2  -" << query.value(0).toInt();
    totalPrice-=query.value(0).toInt();
    qDebug() << totalPrice << endl;
}
if(q.platSize == 48 && q.logDeck == 4){
    query.exec("SELECT noLD3 FROM qPrice");
    query.last();
    qDebug() << "Remove LogDeck3  -" << query.value(0).toInt();
    totalPrice-=query.value(0).toInt();
    qDebug() << totalPrice << endl;
}
if(q.platSize == 60 && q.logDeck == 4){
    query.exec("SELECT noLD4 FROM qPrice");
    query.last();
    qDebug() << "Remove LogDeck4 -" << query.value(0).toInt();
    totalPrice-=query.value(0).toInt();
    qDebug() << totalPrice << endl;
}
//

if(q.pulleyTrailer == true){
    if(findOverride("36_Pulley_And_Bushing")){
        qDebug() << "Found an override!";
        totalPrice+=0;
    }
    else{
    query.exec("SELECT pulley36 FROM qPrice");
    query.last();
    qDebug() << "Pulley and 36' Trailer  " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;
    }
}
if(q.hdOutfeed == true){
    if(findOverride("actionHD_Outfeed_Belt")){
        qDebug() << "Found an override!";
        totalPrice+=0;
    }
    else{
    query.exec("SELECT hdOutfeed FROM qPrice");
    query.last();
    qDebug() << "HD Out Feed " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;
    }
}
if(q.sawdustChain == true){
    if(findOverride("actionSawdust_Chain")){
        qDebug() << "Found an override!";
        totalPrice+=0;
    }
    else{
    query.exec("SELECT sawDustChain FROM qPrice");
    query.last();
    qDebug() << "Saw Dust Chain " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;
    }
}
if(q.vert == true){
    if(findOverride("actionVertical_Edger")){
        qDebug() << "Found an override!";
        totalPrice+=0;
    }
    else{
    query.exec("SELECT vertEdg FROM qPrice");
    query.last();
    qDebug() << "Vertical Edger " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;
    }
}
if(q.feedJoy == true){
    if(findOverride("actionFeed_Joystick")){
        qDebug() << "Found an override!";
        totalPrice+=0;
    }
    else{
    query.exec("SELECT feedJoyStick FROM qPrice");
    query.last();
    qDebug() << "Feed Joy Stick " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;
    }
}
if(q.topSaw == true){
    if(findOverride("actionTop_Saw")){
        qDebug() << "Found an override!";
        totalPrice+=0;
    }
    else{
    query.exec("SELECT topSaw FROM qPrice");
    query.last();
    qDebug() << "Top Saw " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;
    }
}
if(q.extraTrailer == true){
    if(findOverride("actionTrailer_Leg")){
        qDebug() << "Found an override!";
        totalPrice+=0;
    }
    else{
    query.exec("SELECT trailerLeg FROM qPrice");
    query.last();

    int total = q.extraTrailerValue * query.value(0).toInt();
    qDebug() << "Trailer Leg " << query.value(0).toInt() << " times " << q.extraTrailerValue << "equals " << total;
    totalPrice+=total;
    qDebug() << totalPrice << endl;\
    }
}
if(q.custom1 != "" && q.custom1 != " "){
    totalPrice+=q.customPrice1;
    qDebug() << "Custom Price " << q.customPrice1;
    qDebug() << totalPrice << endl;
}
if(q.custom2 != "" && q.custom2 != " " ){
    totalPrice+=q.customPrice2;
        qDebug() << "Custom Price " << q.customPrice1;
    qDebug() << totalPrice << endl;
}
/*if(q.custom3 != "" && q.custom3 != " " ){
    totalPrice+=q.customPrice3;
        qDebug() << "Custom Price " << q.customPrice1 & customPrice2;
    qDebug() << totalPrice << endl;
}*/
if(q.trailer52){
    if(findOverride("action52_Trailer")){
        qDebug() << "Found an override!";
        totalPrice+=0;
    }
    else{
    query.exec("SELECT trailer52 FROM qPrice");
    query.last();
    qDebug() << "52' Trailer " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;
    }
}
if(q.linear){
    if(findOverride("actionLinear")){
        qDebug() << "Found an override!";
        totalPrice+=0;
    }
    else{
    query.exec("SELECT linearCarriage FROM qPrice");
    //query.exec("SELECT linear FROM qPrice");
    query.last();
    qDebug() << "Linear Carriage " << query.value(0).toInt();
    totalPrice+=query.value(0).toInt();
    qDebug() << totalPrice << endl;
    }
}

printArray();
return totalPrice;
}


/*
 *
 *
 *
 *
 * Use this function over the standalone price quote method.
 * This is a much more efficient method. Allows for a database to
 * be altered and changed, and will not affect the way the program works.
 * It scans and array for items, compares with a database, grabs a description and price,
 * and presents them to the user.
 *
 * To add something new, just add it to the connections file with the name of the object "objectNameCheckBox" : "connectionNameInDatabase"
 * without spaces. Then name your object, use the HMW Database Administration tool to add the price and description,
 * and then the priceQuote function will automatically detect and use it. It will try and grab anything with a value over 0, in which
 * case it will then add the price for accordingly, and you don't have to make a new statement each time you add a new SpinBox
 *
 *
 *
 *
 *
 *
 */

int quoteDBPriceManager::priceQuote(Quote q, QString array[100], int index){
    QSqlQuery query;
    totalPrice = 0;


    QString carriageString;

    if(q.platSize == 40 && q.carriage == 1){ //40 challenger
            carriageString+="mill40Chal";
        }

    if(q.platSize == 48 && q.carriage == 1 ){ //48 challenger
        carriageString+="mill48Chal";
    }
    if(q.platSize == 60 && q.carriage == 1 ){ //60 challenger
        carriageString+="mill60Chal";
    }
    if(q.platSize == 40 && q.carriage == 2 ){ //40 LT
        carriageString+="mill40LT";

    }
    if(q.platSize == 48 && q.carriage == 2 ){ //48 LT
        carriageString+="mill48LT";
    }
    if(q.platSize == 60 && q.carriage == 2){ //60 LT
        carriageString+="mill60LT";
    }
    if(q.platSize == 52 && q.carriage == 2){ //60 LT
        carriageString+="mill52Chal";
    }
    if(q.platSize == 52 && q.carriage == 1){ //60 LT
        carriageString+="mill52Chal";
    }

    //qDebug() << "Selecting " << carriageString;
    query.exec("SELECT * FROM quoteItems WHERE name = '"+carriageString+"';");
    query.last();
    //qDebug() << query.value(0).toString();
    //qDebug() << query.value(1).toString() << ":" << query.value(2).toString();
    totalPrice+=query.value(2).toInt();
    //qDebug() << totalPrice << endl;

    if(q.platSize == 40 && q.logDeck == 2){
        query.exec("SELECT * FROM quoteItems WHERE name = 'LD3Over2';");
        //query.exec("SELECT LD3Over2 FROM quoteItems");
        query.last();
       //qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice+=query.value(2).toInt();
        //qDebug() << totalPrice << endl;
    }
    if(q.platSize == 48 && q.logDeck == 3){
        query.exec("SELECT * FROM quoteItems WHERE name = 'LD4Over3';");
        //query.exec("SELECT LD4Over3 FROM quoteItems");
        query.last();
       // qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice+=query.value(2).toInt();
        //qDebug() << totalPrice << endl;
    }

    //No log deck options:

    if(q.platSize == 40 && q.logDeck == 4){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD2';");
        //query.exec("SELECT noLD2 FROM quoteItems");
        query.last();
       // qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice-=query.value(2).toInt();
        //qDebug() << totalPrice << endl;
    }
    if(q.platSize == 48 && q.logDeck == 4){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD3';");
        //query.exec("SELECT noLD3 FROM quoteItems");
        query.last();
       // qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice-=query.value(2).toInt();
        //qDebug() << totalPrice << endl;

    }
    if(q.platSize == 60 && q.logDeck == 4){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD4';");
        //query.exec("SELECT noLD4 FROM quoteItems");
        query.last();
        //qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice-=query.value(2).toInt();
        //qDebug() << totalPrice << endl;

    }






    for(int i = 0; i<index;i++){






        //qDebug() << array[index];
        if(array[i] == "cantTurner"){
            //int value = q.cantTurnValue; //each cant turner is 3500 * the amount of knees.
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
            query.last();
            int totalValue = query.value(2).toInt() * q.knee;
            //qDebug() << "Cant Turner : " << value << " * knees = " << totalValue;
            totalPrice+=totalValue; //so, take the number of cant turners, multiply by number of knees, which is multiplied by 3500
            //qDebug() << totalPrice << endl;

        }
       else if(array[i] == "extraTrailer"){
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
            query.last();
            int total = q.extraTrailerValue * query.value(2).toInt();
            //qDebug() << query.value(1).toString() << query.value(2).toInt() << " times " << q.extraTrailerValue << "equals " << total;
            totalPrice+=total;
            //qDebug() << totalPrice << endl;

        }



        else if(array[i] == "cantTurner" && findOverride("actionCant_Turners")){
               // qDebug() << "Found an override!";
                totalPrice+=0;

            }
        else if(array[i] == "hamDog" && findOverride("actionHam_Dog")){

                //qDebug() << "Found an override!";
                totalPrice+=0;

            }
        else if(array[i] == "pulley36" && findOverride("36_Pulley_And_Bushing")){
                //qDebug() << "Found an override!";
                totalPrice+=0;

            }
         else if(array[i] == "hdOutfeed" && findOverride("actionHD_Outfeed_Belt")){
                //qDebug() << "Found an override!";
                totalPrice+=0;

            }
       else if(array[i] == "sawDustChain" && findOverride("actionSawdust_Chain")){
                //qDebug() << "Found an override!";
                totalPrice+=0;

            }
        else if(array[i] == "vertEdg" && findOverride("actionVertical_Edger")){
                //qDebug() << "Found an override!";
                totalPrice+=0;

            }
         else if(array[i] == "feedJoyStick" && findOverride("actionFeed_Joystick")){
                //qDebug() << "Found an override!";
                totalPrice+=0;

            }
        else if(array[i] == "topSaw" && findOverride("actionTop_Saw")){
                //qDebug() << "Found an override!";
                totalPrice+=0;

            }
        else if(array[i] == "trailerLeg" && findOverride("actionTrailer_Leg")){
                //qDebug() << "Found an override!";
                totalPrice+=0;

            }
        else if(array[i] == "trailer52" && findOverride("action52_Trailer")){
                //qDebug() << "Found an override!";
                totalPrice+=0;

            }
        else if(array[i] == "linearCarriage" && findOverride("actionLinear")){
                //qDebug() << "Found an override!";
                totalPrice+=0;

            }





        else{
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';"); //find all the things that are marked... grab their prices
            query.last();
           // qDebug() << query.value(1).toString() << query.value(2).toInt();
            totalPrice+=query.value(2).toInt();
            //qDebug() << totalPrice << endl;
        }


    }
    if(q.custom1 != "" && q.custom1 != " "){
        totalPrice+=q.customPrice1;
       // qDebug() << "Custom Price " << q.customPrice1;
       // qDebug() << totalPrice << endl;
    }
    if(q.custom2 != "" && q.custom2 != " " ){
        totalPrice+=q.customPrice2;
       // qDebug() << "Custom Price " << q.customPrice1;
       // qDebug() << totalPrice << endl;
    }


    return totalPrice;
}





/*
 *
 * Adds the overrides from the checkboxes
 *
 *
 */

void quoteDBPriceManager::addOverridesToArray(QString overrideValue,int length){
    array[length] = overrideValue;
    arrayLength = length;
   qDebug() << array[length];

}

/*
 * Prints the array for testing purposes
 *
 *
 */

void quoteDBPriceManager::printArray(){
    for(int i=0;i<arrayLength;i++){
        qDebug() << array[i];
    }
}
/*
 * Finds any overrides and marks them.
 * DEPRECATED
 *
 */

bool quoteDBPriceManager::findOverride(QString value){
    for(int i = 0; i < arrayLength + 1; i++){
        if(array[i] == value){
            return true;
        }
    }
    return false;
}


/*
 *Updated to use a database
 *
 */

bool quoteDBPriceManager::findOverride(QString value,int quoteNum){
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
 * Grabs the current array.
 *
 */
QString* quoteDBPriceManager::getArray(){
    return array;
}

/*
 *
 * Grabs the total price.
 *
 */

int quoteDBPriceManager::getTotalPrice(){
    return totalPrice;
}

/*
 * Removes values from the array.
 *
 *
 */

void quoteDBPriceManager::removeFromArray(QString value){
    int indexToRemove = 0;
    for(int i = 0; i<arrayLength + 1;i++){
        if(array[i] == value){
            indexToRemove = i;
        }
    }

    QString array2[100];

    for(int i = 0;i<arrayLength;i++){
        if(i != indexToRemove){
            array2[i] = array[i];
        }
    }

     memcpy(array,array2,sizeof(array));

}


/*
 * Searches in the array for a specified value. Index = the total number of elements in the array at
 * the time of searching.
 *
 * DEPRECATED
 *
 */

/*
bool quoteDBPriceManager::findInArray(QString array[100], QString value, int index){
    for(int i=0; i<index;i++){
        if(array[i].compare(value) ==0){
          //  qDebug() << "FOUND IN ARRAY!! " << value;
            //qDebug() << "found " << value;
            return true;
        }
    }
    return false;
} */
/*
 * Searches in the array for a specified value. Index = the total number of elements in the array at
 * the time of searching.
 *
 *
 */

bool quoteDBPriceManager::findInArray(QList<QString> array, QString value, int index){
    for(int i=0; i<index;i++){
        if(array.at(i).compare(value) ==0){
          //  qDebug() << "FOUND IN ARRAY!! " << value;
            //qDebug() << "found " << value;
            return true;
        }
    }
    return false;
}

/*
 * To add something new, just add it to the connections file with the name of the object "objectNameCheckBox" : "connectionNameInDatabase"
 * without spaces. Then name your object, use the HMW Database Administration tool to add the price and description,
 * and then the priceQuote function will automatically detect and use it. It will try and grab anything with a value over 0, in which
 * case it will then add the price for accordingly, and you don't have to make a new statement each time you add a new SpinBox
 *
 *
 *
 */


int quoteDBPriceManager::priceQuote(Quote q,QList<QString> array, int index, int quoteNum){
   // qDebug() << "Running priceQuote";
    QSqlQuery query;
    totalPrice = 0;


    QString carriageString;

    if(findInArray(array,"mill48",index) && findInArray(array,"challengerCarriage",index)){
        carriageString+="mill48Chal";
    }
    if(findInArray(array,"mill40",index) && findInArray(array,"challengerCarriage",index)){
        carriageString+="mill40Chal";
    }
    if(findInArray(array,"mill60",index) && findInArray(array,"challengerCarriage",index)){
        carriageString+="mill60Chal";
    }
    if(findInArray(array,"mill48",index) && findInArray(array,"magnumCarriage",index)){
        carriageString+="mill48LT";
    }
    if(findInArray(array,"mill40",index) && findInArray(array,"magnumCarriage",index)){
        carriageString+="mill40LT";
    }
    if(findInArray(array,"mill60",index) && findInArray(array,"magnumCarriage",index)){
        carriageString+="mill60LT";
    }
    if(findInArray(array,"mill52",index) && findInArray(array,"challengerCarriage",index)){
        carriageString+="mill52Chal";
    }
    if(findInArray(array,"mill52",index) && findInArray(array,"magnumCarriage",index)){
        carriageString+="mill52LT";
    }

   // qDebug() << "Selecting " << carriageString;
    query.exec("SELECT * FROM quoteItems WHERE name = '"+carriageString+"';");
    query.last();
    //qDebug() << query.value(0).toString();
    //qDebug() << query.value(1).toString() << ":" << query.value(2).toString();
    totalPrice+=query.value(2).toInt();
    //qDebug() << totalPrice << endl;


    if(findInArray(array,"mill40",index) && findInArray(array,"threeStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'LD3Over2';");
        //query.exec("SELECT LD3Over2 FROM quoteItems");
        query.last();
       //qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice+=query.value(2).toInt();
        //qDebug() << totalPrice << endl;
    }
    if(findInArray(array,"mill48",index) && findInArray(array,"fourStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'LD4Over3';");
        //query.exec("SELECT LD4Over3 FROM quoteItems");
        query.last();
       // qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice+=query.value(2).toInt();
        //qDebug() << totalPrice << endl;
    }

    if(findInArray(array,"mill52",index) && findInArray(array,"fourStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'LD4Over3';");
        //query.exec("SELECT LD4Over3 FROM quoteItems");
        query.last();
       // qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice+=query.value(2).toInt();
        //qDebug() << totalPrice << endl;
    }



    //No log deck options:

    if(findInArray(array,"mill40",index) && findInArray(array,"noStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD2';");
        //query.exec("SELECT noLD2 FROM quoteItems");
        query.last();
       // qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice-=query.value(2).toInt();
        //qDebug() << totalPrice << endl;
    }
    if(findInArray(array,"mill48",index) && findInArray(array,"noStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD3';");
        //query.exec("SELECT noLD3 FROM quoteItems");
        query.last();
       // qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice-=query.value(2).toInt();
        //qDebug() << totalPrice << endl;

    }
    if(findInArray(array,"mill60",index) && findInArray(array,"noStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD4';");
        //query.exec("SELECT noLD4 FROM quoteItems");
        query.last();
        //qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice-=query.value(2).toInt();
        //qDebug() << totalPrice << endl;

    }
    if(findInArray(array,"mill52",index) && findInArray(array,"noStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD4';");
        //query.exec("SELECT noLD4 FROM quoteItems");
        query.last();
        //qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice-=query.value(2).toInt();
        //qDebug() << totalPrice << endl;

    }





  //  qDebug() << "index is " << index;
    for(int i = 0; i<index;i++){
        QRegExp re("\\d*");

        query.exec("SELECT * FROM quoteTable WHERE quoteNum = " + QString::number(quoteNum) + " AND connectionName = '"+array.at(i)+"'");
        if(query.last() && query.value(3).toInt() > 1 && re.exactMatch(query.value(3).toString())){
            if(findOverride(array[i],quoteNum)){
                        //qDebug() << "FOUND AN OVERRIDE @ " << quoteNum << " OF " << array[i];
                        totalPrice+=0;
            }

            else{
                int value = query.value(3).toInt();
                query.exec("SELECT * FROM quoteItems WHERE name = '"+array.at(i)+"';");
                query.last();
                   qDebug() << "ITEM: " << array.at(i) << " PRICE : " << query.value(2).toInt() << " * " << value << "=" << query.value(2).toInt() * value;
                int totalValue = query.value(2).toInt() * value;
                totalPrice+=totalValue;
            }
        }

        else if(findOverride(array[i],quoteNum)){
            //qDebug() << "FOUND AN OVERRIDE @ " << quoteNum << " OF " << array[i];
            totalPrice+=0;
        }

        else if(array.at(i) == "wheelSize"){
            int value = query.value(3).toInt();
            if(value == 12){
                query.exec("SELECT * FROM quoteItems WHERE name = '"+array.at(i)+"';");
                query.last();

                int totalValue = 1000;
                totalPrice+=totalValue;
            }
            if(value == 14){
                query.exec("SELECT * FROM quoteItems WHERE name = '"+array.at(i)+"';");
                query.last();

                int totalValue = 1500;
                totalPrice+=totalValue;
            }
        }

        else{
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array.at(i)+"';"); //find all the things that are marked... grab their prices
            if(query.last()){

                qDebug() << "ITEM: " << array.at(i) << " PRICE: " << query.value(2).toInt();
                    totalPrice+=query.value(2).toInt();
         }


}

    }

      if(q.custom1 != "" && q.custom1!= " " ){
        totalPrice+=q.customPrice1;

    }

    if(q.custom2 != "" && q.custom2 != " " ){
        totalPrice+=q.customPrice2;

    }

    qDebug() << totalPrice;
    return totalPrice;
}

/*
 *
 * Runs a quick analysis of the price.
 * WARNING: may slow down program significantly if resources are low.
 *
 */

int quoteDBPriceManager::tempPriceQuote(Quote q,QList<QString> array, int index, int quoteNum){
    //qDebug() << "Running tempPriceQuote";
    QSqlQuery query;
    totalPrice = 0;


    QString carriageString;

    if(findInArray(array,"mill48",index) && findInArray(array,"challengerCarriage",index)){
        carriageString+="mill48Chal";
    }
    if(findInArray(array,"mill40",index) && findInArray(array,"challengerCarriage",index)){
        carriageString+="mill40Chal";
    }
    if(findInArray(array,"mill60",index) && findInArray(array,"challengerCarriage",index)){
        carriageString+="mill60Chal";
    }
    if(findInArray(array,"mill48",index) && findInArray(array,"magnumCarriage",index)){
        carriageString+="mill48LT";
    }
    if(findInArray(array,"mill40",index) && findInArray(array,"magnumCarriage",index)){
        carriageString+="mill40LT";
    }
    if(findInArray(array,"mill60",index) && findInArray(array,"magnumCarriage",index)){
        carriageString+="mill60LT";
    }
    if(findInArray(array,"mill52",index) && findInArray(array,"challengerCarriage",index)){
        carriageString+="mill52Chal";
    }
    if(findInArray(array,"mill52",index) && findInArray(array,"magnumCarriage",index)){
        carriageString+="mill52LT";
    }

   // qDebug() << "Selecting " << carriageString;
    query.exec("SELECT * FROM quoteItems WHERE name = '"+carriageString+"';");
    query.last();
    //qDebug() << query.value(0).toString();
    //qDebug() << query.value(1).toString() << ":" << query.value(2).toString();
    totalPrice+=query.value(2).toInt();
    //qDebug() << totalPrice << endl;


    if(findInArray(array,"mill40",index) && findInArray(array,"threeStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'LD3Over2';");
        //query.exec("SELECT LD3Over2 FROM quoteItems");
        query.last();
       //qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice+=query.value(2).toInt();
        //qDebug() << totalPrice << endl;
    }
    if(findInArray(array,"mill48",index) && findInArray(array,"fourStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'LD4Over3';");
        //query.exec("SELECT LD4Over3 FROM quoteItems");
        query.last();
       // qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice+=query.value(2).toInt();
        //qDebug() << totalPrice << endl;
    }

    if(findInArray(array,"mill52",index) && findInArray(array,"fourStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'LD4Over3';");
        //query.exec("SELECT LD4Over3 FROM quoteItems");
        query.last();
       // qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice+=query.value(2).toInt();
        //qDebug() << totalPrice << endl;
    }



    //No log deck options:

    if(findInArray(array,"mill40",index) && findInArray(array,"noStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD2';");
        //query.exec("SELECT noLD2 FROM quoteItems");
        query.last();
       // qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice-=query.value(2).toInt();
        //qDebug() << totalPrice << endl;
    }
    if(findInArray(array,"mill48",index) && findInArray(array,"noStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD3';");
        //query.exec("SELECT noLD3 FROM quoteItems");
        query.last();
       // qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice-=query.value(2).toInt();
        //qDebug() << totalPrice << endl;

    }
    if(findInArray(array,"mill60",index) && findInArray(array,"noStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD4';");
        //query.exec("SELECT noLD4 FROM quoteItems");
        query.last();
        //qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice-=query.value(2).toInt();
        //qDebug() << totalPrice << endl;

    }
    if(findInArray(array,"mill52",index) && findInArray(array,"noStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD4';");
        //query.exec("SELECT noLD4 FROM quoteItems");
        query.last();
        //qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice-=query.value(2).toInt();
        //qDebug() << totalPrice << endl;

    }





  //  qDebug() << "index is " << index;
    for(int i = 0; i<index;i++){
        QRegExp re("\\d*");

        query.exec("SELECT * FROM quoteTableTemp WHERE quoteNum = " + QString::number(quoteNum) + " AND connectionName = '"+array.at(i)+"'");
        if(query.last() && query.value(3).toInt() > 1 && re.exactMatch(query.value(3).toString())){
            if(findOverride(array[i],quoteNum)){
                        //qDebug() << "FOUND AN OVERRIDE @ " << quoteNum << " OF " << array[i];
                        totalPrice+=0;
            }
            if(array.at(i) == "wheelSize"){
                int value = query.value(3).toInt();
                if(value == 12){
                    query.exec("SELECT * FROM quoteItems WHERE name = '"+array.at(i)+"';");
                    query.last();

                    int totalValue = 1000;
                    totalPrice+=totalValue;
                }
                if(value == 14){
                    query.exec("SELECT * FROM quoteItems WHERE name = '"+array.at(i)+"';");
                    query.last();

                    int totalValue = 1500;
                    totalPrice+=totalValue;
                }





            }
            else{
                int value = query.value(3).toInt();
                query.exec("SELECT * FROM quoteItems WHERE name = '"+array.at(i)+"';");
                query.last();

                int totalValue = query.value(2).toInt() * value;
                totalPrice+=totalValue;
            }



        }

        else if(findOverride(array[i],quoteNum)){
            //qDebug() << "FOUND AN OVERRIDE @ " << quoteNum << " OF " << array[i];
            totalPrice+=0;
        }

    else{

            query.exec("SELECT * FROM quoteItems WHERE name = '"+array.at(i)+"';"); //find all the things that are marked... grab their prices
            if(query.last()){

                    totalPrice+=query.value(2).toInt();


            }


}

    }

      if(q.custom1 != "" && q.custom1!= " " ){
        totalPrice+=q.customPrice1;

    }

    if(q.custom2 != "" && q.custom2 != " " ){
        totalPrice+=q.customPrice2;

    }


    return totalPrice;
}


/*
 *
 * Prices the quotes using an array object.
 * Very DEPRECATED
 *
 */

/*
int quoteDBPriceManager::priceQuote(Quote q,QString array[100], int index, int quoteNum){
    //qDebug() << "Running priceQuote";
    QSqlQuery query;
    totalPrice = 0;


    QString carriageString;

    if(findInArray(array,"mill48",index) && findInArray(array,"challengerCarriage",index)){
        carriageString+="mill48Chal";
    }
    if(findInArray(array,"mill40",index) && findInArray(array,"challengerCarriage",index)){
        carriageString+="mill40Chal";
    }
    if(findInArray(array,"mill60",index) && findInArray(array,"challengerCarriage",index)){
        carriageString+="mill60Chal";
    }
    if(findInArray(array,"mill48",index) && findInArray(array,"magnumCarriage",index)){
        carriageString+="mill48LT";
    }
    if(findInArray(array,"mill40",index) && findInArray(array,"magnumCarriage",index)){
        carriageString+="mill40LT";
    }
    if(findInArray(array,"mill60",index) && findInArray(array,"magnumCarriage",index)){
        carriageString+="mill60LT";
    }

   // qDebug() << "Selecting " << carriageString;
    query.exec("SELECT * FROM quoteItems WHERE name = '"+carriageString+"';");
    query.last();
    //qDebug() << query.value(0).toString();
    //qDebug() << query.value(1).toString() << ":" << query.value(2).toString();
    totalPrice+=query.value(2).toInt();
    //qDebug() << totalPrice << endl;
    if(findInArray(array,"mill40",index) && findInArray(array,"threeStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'LD3Over2';");
        //query.exec("SELECT LD3Over2 FROM quoteItems");
        query.last();
       //qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice+=query.value(2).toInt();
        //qDebug() << totalPrice << endl;
    }
    if(findInArray(array,"mill48",index) && findInArray(array,"fourStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'LD4Over3';");
        //query.exec("SELECT LD4Over3 FROM quoteItems");
        query.last();
       // qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice+=query.value(2).toInt();
        //qDebug() << totalPrice << endl;
    }

    //No log deck options:

    if(findInArray(array,"mill40",index) && findInArray(array,"noStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD2';");
        //query.exec("SELECT noLD2 FROM quoteItems");
        query.last();
       // qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice-=query.value(2).toInt();
        //qDebug() << totalPrice << endl;
    }
    if(findInArray(array,"mill48",index) && findInArray(array,"noStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD3';");
        //query.exec("SELECT noLD3 FROM quoteItems");
        query.last();
       // qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice-=query.value(2).toInt();
        //qDebug() << totalPrice << endl;

    }
    if(findInArray(array,"mill60",index) && findInArray(array,"noStrand",index)){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD4';");
        //query.exec("SELECT noLD4 FROM quoteItems");
        query.last();
        //qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice-=query.value(2).toInt();
        //qDebug() << totalPrice << endl;

    }





  //  qDebug() << "index is " << index;
    for(int i = 0; i<index;i++){

        if(array[i] == "cantTurner"){
            //qDebug() << "found cant turner";
            query.exec("SELECT * FROM quoteTable WHERE quoteNum = " + QString::number(quoteNum) + " AND connectionName = 'cantTurner'");
            query.last();
            int value = query.value(3).toInt(); //the number of canturners in the spin box
            //qDebug() << "Cant Turners: " << value;
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
            query.last();
            int totalValue = query.value(2).toInt() * value;
           // qDebug() << "Total Cant Price " << totalValue;

            //qDebug() << "Cant Turner : " << value << " * knees = " << totalValue;
            totalPrice+=totalValue; //so, take the number of cant turners, multiply by number of knees, which is multiplied by 3500
            //qDebug() << totalPrice << endl;

        }
        if(array[i] == "cantPushOff"){
            //qDebug() << "found cant turner";
            query.exec("SELECT * FROM quoteTable WHERE quoteNum = " + QString::number(quoteNum) + " AND connectionName = 'cantPushOff'");
            query.last();
            int value = query.value(3).toInt(); //the number of brownsville in the spin box
            //qDebug() << "Cant Turners: " << value;
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
            query.last();
            int totalValue = query.value(2).toInt() * value;
           // qDebug() << "Total Cant Price " << totalValue;

            //qDebug() << "cantPushOff : " << value << " * knees = " << totalValue;
            totalPrice+=totalValue; //so, take the number of cant turners, multiply by number of knees, which is multiplied by 3500
            //qDebug() << totalPrice << endl;

        }

        if(array[i] == "brownsville"){
            //qDebug() << "found cant turner";
            query.exec("SELECT * FROM quoteTable WHERE quoteNum = " + QString::number(quoteNum) + " AND connectionName = 'brownsville'");
            query.last();
            int value = query.value(3).toInt(); //the number of brownsville in the spin box
            //qDebug() << "Cant Turners: " << value;
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
            query.last();
            int totalValue = query.value(2).toInt() * value;

           // qDebug() << "Total Cant Price " << totalValue;

            //qDebug() << "Brownsville : " << value << " * knees = " << totalValue;
            totalPrice+=totalValue; //so, take the number of cant turners, multiply by number of knees, which is multiplied by 3500
            //qDebug() << totalPrice << endl;

        }

       else if(array[i] == "extraTrailer"){
            //qDebug() << "trailerLeg";
            query.exec("SELECT * FROM quoteTable WHERE quoteNum = " + QString::number(quoteNum) + " AND connectionName = 'extraTrailer'");
            query.last();
            int value = query.value(3).toInt(); //the number of canturners in the spin box
            //qDebug() << "Trailer Leg: " << value;
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';");
            query.last();
            int totalValue = query.value(2).toInt() * value;
            //qDebug() << "Total Trailer Leg Price " << totalValue;
//
            //qDebug() << "Cant Turner : " << value << " * knees = " << totalValue;
            totalPrice+=totalValue; //so, take the number of cant turners, multiply by number of knees, which is multiplied by 3500
            //qDebug() << totalPrice << endl;

        }



        else if(array[i] == "cantTurners" && findOverride("actionCant_Turners")){
               // qDebug() << "Found an override!";
                totalPrice+=0;

            }
        else if(array[i] == "hamDog" && findOverride("actionHam_Dog")){

                //qDebug() << "Found an override!";
                totalPrice+=0;

            }
        else if(array[i] == "pulley36" && findOverride("36_Pulley_And_Bushing")){
                //qDebug() << "Found an override!";
                totalPrice+=0;

            }
         else if(array[i] == "hdOutfeed" && findOverride("actionHD_Outfeed_Belt")){
                //qDebug() << "Found an override!";
                totalPrice+=0;

            }
       else if(array[i] == "sawDustChain" && findOverride("actionSawdust_Chain")){
                //qDebug() << "Found an override!";
                totalPrice+=0;

            }
        else if(array[i] == "vertEdg" && findOverride("actionVertical_Edger")){
                //qDebug() << "Found an override!";
                totalPrice+=0;

            }
         else if(array[i] == "feedJoyStick" && findOverride("actionFeed_Joystick")){
                //qDebug() << "Found an override!";
                totalPrice+=0;

            }
        else if(array[i] == "topSaw" && findOverride("actionTop_Saw")){
                //qDebug() << "Found an override!";
                totalPrice+=0;

            }
        else if(array[i] == "trailerLeg" && findOverride("actionTrailer_Leg")){
                //qDebug() << "Found an override!";
                totalPrice+=0;

            }
        else if(array[i] == "trailer52" && findOverride("action52_Trailer")){
                //qDebug() << "Found an override!";
                totalPrice+=0;

            }
        else if(array[i] == "linearCarriage" && findOverride("actionLinear")){
                //qDebug() << "Found an override!";
                totalPrice+=0;

            }




    else{





           // qDebug() << " i " << i << "array[i] " << array[i];
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array[i]+"';"); //find all the things that are marked... grab their prices
            if(query.last()){
           // qDebug() << query.value(1).toString() << query.value(2).toInt();
            totalPrice+=query.value(2).toInt();

            }
            //qDebug() << totalPrice << endl;

}

    }

      if(q.custom1 != "" && q.custom1!= " " ){
        totalPrice+=q.customPrice1;
       // qDebug() << "Custom Price " << q.customPrice1;
       // qDebug() << totalPrice << endl;
    }

    if(q.custom2 != "" && q.custom2 != " " ){
        totalPrice+=q.customPrice2;
       // qDebug() << "Custom Price " << q.customPrice1;
       // qDebug() << totalPrice << endl;
    }

  //  qDebug() << "total is " << totalPrice;
    return totalPrice;
}

*/

void quoteDBPriceManager::processDynamicOverrides(QString overrideValue, int quoteNum){
    QSqlQuery q2;
    QStringList splitted = overrideValue.split("action");
    QString newText = splitted.at(1);
    qDebug() << "newText = " << newText;
    qDebug() << "quoteNum = " << quoteNum;
    qDebug() << "running update script: " << q2.exec("UPDATE `quoteTable` SET value = -1 WHERE quoteNum = "+QString::number(quoteNum)+" AND connectionName = '"+newText+"'");
    qDebug() << "running get script: " << q2.exec("SELECT * FROM `quoteTable` WHERE quoteNum = "+QString::number(quoteNum)+" AND connectionName = '"+newText+"'");
    q2.last();
    qDebug() << q2.value(1).toString() << " " << q2.value(3).toInt();

}












