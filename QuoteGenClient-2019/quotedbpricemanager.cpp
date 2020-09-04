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
  // qDebug() << array[length];

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

    bool carriageLP = false;
    bool carriage = false;
    totalPrice = 0;
    totalPrice = 0;

    QList<QString> excludeArray;
    QString carriageString;

    if((findInArray(array,"magnumLP",index)&&findInArray(array, "carriageLPFortyTwoInchKneeOpenings",index))){
        carriageLP = true;
        qDebug() << "found forty two in price";
        query.exec("SELECT * FROM quoteTable WHERE connectionName = 'magnumCarriageKnees' and quoteNum = " + QString::number(quoteNum));
        query.last();

        if(query.value(3) == 2){
           // qDebug() << "found forty two in price in knees";
            query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPLinearTwoKnee'");
            query.last();
            carriageLP = true;
            int price = query.value(2).toInt();
            totalPrice+=price;
            excludeArray.append("carriageLPLinearTwoKnee");
        }

        if(query.value(3) == 3){
         //   qDebug() << "found forty two in price in knees";
            query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPLinearThreeKnee'");
            query.last();
            carriageLP = true;
            int price = query.value(2).toInt();
            totalPrice+=price;
            excludeArray.append("carriageLPLinearThreeKnee");
        }

        if(query.value(3) == 4){
            //qDebug() << "found forty two in price in knees";
            query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPLinearFourKnee'");
            query.last();
            carriageLP = true;
            int price = query.value(2).toInt();
            totalPrice+=price;
            excludeArray.append("carriageLPLinearFourKnee");
        }
      }

    if(findInArray(array,"magnumLP",index)&&findInArray(array, "carriageLPTiltFrame",index)){
        query.exec("SELECT * FROM quoteTable WHERE connectionName = 'magnumCarriageKnees' and quoteNum = " + QString::number(quoteNum));
        query.last();

        int kneePrice = query.value(3).toInt();
         carriageLP = true;

         //qDebug() << "Magnum Knees: " << query.value(2).toString();


         query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPTiltFrame'");
         query.last();


         int basePrice = query.value(2).toInt();
         int newPriceWithKnees = basePrice * kneePrice; //multiply the base price times the amount of knees...

         qDebug() << "base price : " << basePrice << " * " << kneePrice  << " = " << newPriceWithKnees;

         totalPrice+=newPriceWithKnees;
         excludeArray.append("carriageLPTiltFrame");


}
    if((findInArray(array,"magnumLP",index)&&findInArray(array, "carriageLPFortyEightInchKneeOpenings",index))){
        carriageLP = true;
        //qDebug() << "found forty 8 in price";
        query.exec("SELECT * FROM quoteTable WHERE connectionName = 'magnumCarriageKnees' and quoteNum = " + QString::number(quoteNum));
        query.last();


                if(findInArray(array,"magnumLP",index)&&findInArray(array, "carriageLPFortyEightInchKneeOpenings",index)){
                    query.exec("SELECT * FROM quoteTable WHERE connectionName = 'magnumCarriageKnees' and quoteNum = " + QString::number(quoteNum));
                    query.last();
                    carriageLP = true;



                    if(query.value(3).toInt() == 2){

                        //qDebug() << "adding 2 knees  in price manager";
                        query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPFortyEightInchKneeOpenings'");
                        query.last();

                        qDebug() << "got price here" << query.value(2).toString();

                         totalPrice+=query.value(2).toInt() * 2;


                         query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPLinearTwoKnee'");
                         query.last();
                         totalPrice+=query.value(2).toInt();

                         qDebug()  << " new total price = "<<  totalPrice;
                       // totalPrice+=query.value(2).toInt();
                       // qDebug() << "got price2  here" << query.value(2).toString() << "totalPrice = " << totalPrice;
                        //qDebug() << "CarriageLP is True";
                        excludeArray.append("carriageLPFortyEightInchKneeOpenings");

                    }
                    if(query.value(3).toInt() == 3){
                        //qDebug() << "adding 3 knees  in price manager";
                        query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPFortyEightInchKneeOpenings'");
                        query.last();

                        qDebug() << "got price here" << query.value(2).toString();

                         totalPrice+=query.value(2).toInt() * 3;


                         query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPLinearThreeKnee'");
                         query.last();
                         totalPrice+=query.value(2).toInt();

                         qDebug()  << " new total price = "<<  totalPrice;
                       // totalPrice+=query.value(2).toInt();
                       // qDebug() << "got price2  here" << query.value(2).toString() << "totalPrice = " << totalPrice;
                        //qDebug() << "CarriageLP is True";
                        excludeArray.append("carriageLPFortyEightInchKneeOpenings");
                        excludeArray.append("magnumCarriageKnees");
                    }
                    if(query.value(3).toInt() == 4){
                        //qDebug() << "adding 4 knees in price manager";
                        query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPFortyEightInchKneeOpenings'");
                        query.last();

                        qDebug() << "got price here" << query.value(2).toString();

                         totalPrice+=query.value(2).toInt() * 4;


                         query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPLinearFourKnee'");
                         query.last();
                         totalPrice+=query.value(2).toInt();

                         qDebug()  << " new total price = "<<  totalPrice;
                       // totalPrice+=query.value(2).toInt();
                       // qDebug() << "got price2  here" << query.value(2).toString() << "totalPrice = " << totalPrice;
                        //qDebug() << "CarriageLP is True";
                        excludeArray.append("carriageLPFortyEightInchKneeOpenings");
                    }
}
    }


    if(findInArray(array, "magnumLT",index) && findInArray(array, "carriageLTLinear",index)){
       carriage = true;
       query.exec("SELECT * FROM quoteTable WHERE connectionName = 'magnumCarriageKnees' and quoteNum = " + QString::number(quoteNum));
       query.last();
       //qDebug() << "knees value = " << query.value(3).toString();

       if(query.value(3).toInt() == 2){
           //qDebug() << "adding 2 knees";
           query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLinearTwoKnee'");
           query.last();
           totalPrice+=query.value(2).toInt();
           //qDebug() << "total : " << totalPrice;
           excludeArray.append("carriageLTLinear");

       }
       if(query.value(3).toInt() == 3){
           //qDebug() << "adding 3 knees";
           query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLinearThreeKnee'");
           query.last();
           totalPrice+=query.value(2).toInt();
           //qDebug() << "total : " << totalPrice;
           excludeArray.append("carriageLTLinear");
       }
       if(query.value(3).toInt() == 4){
           //qDebug() << "adding 4 knees";
           query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLinearFourKnee'");
           query.last();
           totalPrice+=query.value(2).toInt();
           //qDebug() << "total : " << totalPrice;
           excludeArray.append("carriageLTLinear");
       }


    if(findInArray(array,"magnumLT",index)&&findInArray(array, "carriageLTTiltFrame",index)){
         query.exec("SELECT * FROM quoteTable WHERE connectionName = 'magnumCarriageKnees' and quoteNum = " + QString::number(quoteNum));
         query.last();
         carriageLP = true;

         query.exec("SELECT * FROM quoteTable WHERE connectionName = 'magnumCarriageKnees' and quoteNum = " + QString::number(quoteNum));
         query.last();
         carriageLP = true;

         ///qDebug() << "Magnum Knees: " << query.value(3).toString();

         int numberOfKnees = query.value(3).toInt();

         query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLTTiltFrame'");
         query.last();
         int basePrice = query.value(2).toInt();
         int newPriceWithKnees = basePrice * numberOfKnees; //multiply the base price times the amount of knees...

         //qDebug() << "base price : " << basePrice << " * " << numberOfKnees << " = " << newPriceWithKnees;

         totalPrice+=newPriceWithKnees;
         excludeArray.append("carriageLTTiltFrame");


 }


    if(findInArray(array,"magnumLT",index)&&findInArray(array, "carriageLTFortyRail",index)){

        //qDebug() << "DID PICKUP RAIL";
         query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageFortyRail'");
         query.last();

         int basePrice = query.value(2).toInt();

         query.exec("SELECT * FROM quoteTable WHERE connectionName = 'carriageLTFortyRail' and quoteNum = " + QString::number(quoteNum));
         query.last();

         int feet = query.value(3).toInt();

         int multipliedPrice = basePrice * feet;

         totalPrice+=multipliedPrice;

         excludeArray.append("carriageLTFortyRail");



 }

    if(findInArray(array,"magnumLP",index)&&findInArray(array, "carriageLPSixtyRail",index)){

        //qDebug() << "DID PICKUP RAIL";
         query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageSixtyRail'");
         query.last();

         int basePrice = query.value(2).toInt();

         query.exec("SELECT * FROM quoteTable WHERE connectionName = 'carriageLPSixtyRail' and quoteNum = " + QString::number(quoteNum));
         query.last();

         int feet = query.value(3).toInt();

         int multipliedPrice = basePrice * feet;

         totalPrice+=multipliedPrice;

         excludeArray.append("carriageLPSixtyRail");



 }




    }

    if(findInArray(array, "magnumLT",index) && findInArray(array, "carriageLTSetShaft",index)){
        carriage = true;

       query.exec("SELECT * FROM `quoteTable` WHERE connectionName = 'magnumCarriageKnees' and quoteNum = " + QString::number(quoteNum));
       query.last();
       //qDebug() << "knees value = " << query.value(3).toString();

       if(query.value(3).toInt() == 2){
           //qDebug() << "adding 2 knees";
          query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageSetshaftTwoKnee'");
           query.last();
           totalPrice+=query.value(2).toInt();
           excludeArray.append("carriageLTSetShaft");


       }
       if(query.value(3).toInt() == 3){
           //qDebug() << "adding 3 knees";
           query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageSetshaftThreeKnee'");
           query.last();
           totalPrice+=query.value(2).toInt();
           excludeArray.append("carriageLTSetShaft");

       }
       if(query.value(3).toInt() == 4){
           //qDebug() << "adding 4 knees";
           query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageSetshaftFourKnee'");
           query.last();
           totalPrice+=query.value(2).toInt();
           excludeArray.append("carriageLTSetShaft");

       }



       if(findInArray(array,"magnumLT",index) &&findInArray(array, "carriageLTTiltFrame",index)){
           query.exec("SELECT * FROM quoteTable WHERE connectionName = 'magnumCarriageKnees' and quoteNum = " + QString::number(quoteNum));
           query.last();
           carriageLP = true;

           query.exec("SELECT * FROM quoteTable WHERE connectionName = 'magnumCarriageKnees' and quoteNum = " + QString::number(quoteNum));
           query.last();
           carriageLP = true;

           //qDebug() << "Magnum Knees: " << query.value(3).toString();

           int numberOfKnees = query.value(3).toInt();

           query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLTTiltFrame'");
           query.last();
           int basePrice = query.value(2).toInt();
           int newPriceWithKnees = basePrice * numberOfKnees; //multiply the base price times the amount of knees...

           //qDebug() << "base price : " << basePrice << " * " << numberOfKnees << " = " << newPriceWithKnees;

           totalPrice+=newPriceWithKnees;
           excludeArray.append("carriageLTTiltFrame");



    }
}



    if(findInArray(array,"mill48",index) && findInArray(array,"challengerCarriage",index)&& carriage == false){
        carriageString+="mill48Chal";
    }
    if(findInArray(array,"mill40",index) && findInArray(array,"challengerCarriage",index) && carriage == false){
        carriageString+="mill40Chal";
    }
    if(findInArray(array,"mill60",index) && findInArray(array,"challengerCarriage",index)&& carriage == false){
        carriageString+="mill60Chal";
    }
    if(findInArray(array,"mill48",index) && findInArray(array,"magnumCarriage",index)&& carriage == false){
        carriageString+="mill48LT";
    }
    if(findInArray(array,"mill40",index) && findInArray(array,"magnumCarriage",index)&& carriage == false){
        carriageString+="mill40LT";
    }
    if(findInArray(array,"mill60",index) && findInArray(array,"magnumCarriage",index)&& carriage == false){
        carriageString+="mill60LT";
    }
    if(findInArray(array,"mill52",index) && findInArray(array,"challengerCarriage",index)&& carriage == false){
        carriageString+="mill52Chal";
    }
    if(findInArray(array,"mill52",index) && findInArray(array,"magnumCarriage",index)&& carriage == false){
        carriageString+="mill52LT";
    }

   // qDebug() << "Selecting " << carriageString;
    query.exec("SELECT * FROM quoteItems WHERE name = '"+carriageString+"';");
    query.last();
    //qDebug() << query.value(0).toString();
    //qDebug() << query.value(1).toString() << ":" << query.value(2).toString();
    totalPrice+=query.value(2).toInt();
    //qDebug() << totalPrice << endl;


    if(findInArray(array,"mill40",index) && findInArray(array,"threeStrand",index)&& carriage == false){
        query.exec("SELECT * FROM quoteItems WHERE name = 'LD3Over2';");
        //query.exec("SELECT LD3Over2 FROM quoteItems");
        query.last();
       //qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice+=query.value(2).toInt();
        //qDebug() << totalPrice << endl;

    }
    if(findInArray(array,"mill48",index) && findInArray(array,"fourStrand",index)&& carriage == false){
        query.exec("SELECT * FROM quoteItems WHERE name = 'LD4Over3';");
        //query.exec("SELECT LD4Over3 FROM quoteItems");
        query.last();
       // qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice+=query.value(2).toInt();
        //qDebug() << totalPrice << endl;

    }

    if(findInArray(array,"mill52",index) && findInArray(array,"fourStrand",index)&& carriage == false){
        query.exec("SELECT * FROM quoteItems WHERE name = 'LD4Over3';");
        //query.exec("SELECT LD4Over3 FROM quoteItems");
        query.last();
       // qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice+=query.value(2).toInt();
        //qDebug() << totalPrice << endl;
    }



    //No log deck options:

    if(findInArray(array,"mill40",index) && findInArray(array,"noStrand",index)&& carriage == false){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD2';");
        //query.exec("SELECT noLD2 FROM quoteItems");
        query.last();
       // qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice-=query.value(2).toInt();
        //qDebug() << totalPrice << endl;
    }
    if(findInArray(array,"mill48",index) && findInArray(array,"noStrand",index)&& carriage == false){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD3';");
        //query.exec("SELECT noLD3 FROM quoteItems");
        query.last();
       // qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice-=query.value(2).toInt();
        //qDebug() << totalPrice << endl;

    }
    if(findInArray(array,"mill60",index) && findInArray(array,"noStrand",index)&& carriage == false){
        query.exec("SELECT * FROM quoteItems WHERE name = 'noLD4';");
        //query.exec("SELECT noLD4 FROM quoteItems");
        query.last();
        //qDebug() << query.value(1).toString() << query.value(2).toInt();
        totalPrice-=query.value(2).toInt();
        //qDebug() << totalPrice << endl;

    }
    if(findInArray(array,"mill52",index) && findInArray(array,"noStrand",index) && carriage == false){
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
                   //qDebug() << "ITEM: " << array.at(i) << " PRICE : " << query.value(2).toInt() << " * " << value << "=" << query.value(2).toInt() * value;
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


//CULPRIT!!!
        else{
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array.at(i)+"';"); //find all the things that are marked... grab their prices
          if(query.last() && array.at(i) != "carriageLPFortyTwoInchKneeOpenings" && !excludeArray.contains(array.at(i))){

               // qDebug() << "ITEM: " << array.at(i) << " PRICE: " << query.value(2).toInt();
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

    query.exec("SELECT * FROM quoteTable WHERE quoteNum = "+QString::number(q.quoteNum)+" and connectionName = 'adjustPrice'");
    query.last();
    int adjustedPriceToAdd = query.value(3).toInt();
    //qDebug() << "Cant Turner : " << value << " * knees = " << totalValue;
    totalPrice+=adjustedPriceToAdd;


    qDebug() << "total Price is equal to : " << totalPrice;
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
    QList<QString> excludeArray;

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


    if(findInArray(array, "magnumLT",index) && findInArray(array, "carriageLTSetShaft",index)){

       // carriage = true;

       query.exec("SELECT * FROM `quoteTableTemp` WHERE connectionName = 'magnumCarriageKnees' and quoteNum = " + QString::number(quoteNum));
       query.last();
       //qDebug() << "knees value = " << query.value(3).toString();

       if(query.value(3).toInt() == 2){


          query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageSetshaftTwoKnee'");
           query.last();
           totalPrice+=query.value(2).toInt() ;
           excludeArray.append("carriageLTSetShaft");


       }
       if(query.value(3).toInt() == 3){
           //qDebug() << "adding 3 knees";
           query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageSetshaftThreeKnee'");
           query.last();
           totalPrice+=query.value(2).toInt();
           excludeArray.append("carriageLTSetShaft");

       }
       if(query.value(3).toInt() == 4){
           //qDebug() << "adding 4 knees";
           query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageSetshaftFourKnee'");
           query.last();
           totalPrice+=query.value(2).toInt();
           excludeArray.append("carriageLTSetShaft");

       }
}

    if((findInArray(array,"magnumLP",index)&&findInArray(array, "carriageLPFortyEightInchKneeOpenings",index))){
        //carriageLP = true;
        //qDebug() << "found forty 8 in price";
        query.exec("SELECT * FROM quoteTableTemp WHERE connectionName = 'magnumCarriageKnees' and quoteNum = " + QString::number(quoteNum));
        query.last();


                if(findInArray(array,"magnumLP",index)&&findInArray(array, "carriageLPFortyEightInchKneeOpenings",index)){
                    query.exec("SELECT * FROM quoteTableTemp WHERE connectionName = 'magnumCarriageKnees' and quoteNum = " + QString::number(quoteNum));
                    query.last();
                   // carriageLP = true;



                    if(query.value(3).toInt() == 2){

                        //qDebug() << "adding 2 knees  in price manager";
                        query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPFortyEightInchKneeOpenings'");
                        query.last();

                        qDebug() << "got price here" << query.value(2).toString();

                         totalPrice+=query.value(2).toInt() * 2;


                         query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPLinearTwoKnee'");
                         query.last();
                         totalPrice+=query.value(2).toInt() -2500;

                         qDebug()  << " new total price = "<<  totalPrice;
                       // totalPrice+=query.value(2).toInt();
                       // qDebug() << "got price2  here" << query.value(2).toString() << "totalPrice = " << totalPrice;
                        //qDebug() << "CarriageLP is True";
                        excludeArray.append("carriageLPFortyEightInchKneeOpenings");

                    }
                    if(query.value(3).toInt() == 3){
                        //qDebug() << "adding 3 knees  in price manager";
                        query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPFortyEightInchKneeOpenings'");
                        query.last();

                        qDebug() << "got price here" << query.value(2).toString();

                         totalPrice+=query.value(2).toInt() * 3;


                         query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPLinearThreeKnee'");
                         query.last();
                         totalPrice+=query.value(2).toInt()-2500;

                         qDebug()  << " new total price = "<<  totalPrice;
                       // totalPrice+=query.value(2).toInt();
                       // qDebug() << "got price2  here" << query.value(2).toString() << "totalPrice = " << totalPrice;
                        //qDebug() << "CarriageLP is True";
                        excludeArray.append("carriageLPFortyEightInchKneeOpenings");
                        excludeArray.append("magnumCarriageKnees");
                    }
                    if(query.value(3).toInt() == 4){
                        //qDebug() << "adding 4 knees in price manager";
                        query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPFortyEightInchKneeOpenings'");
                        query.last();

                        qDebug() << "got price here" << query.value(2).toString();

                         totalPrice+=query.value(2).toInt() * 4;


                         query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPLinearFourKnee'");
                         query.last();
                         totalPrice+=query.value(2).toInt()-2500;

                         qDebug()  << " new total price = "<<  totalPrice;
                       // totalPrice+=query.value(2).toInt();
                       // qDebug() << "got price2  here" << query.value(2).toString() << "totalPrice = " << totalPrice;
                        //qDebug() << "CarriageLP is True";
                        excludeArray.append("carriageLPFortyEightInchKneeOpenings");
                    }
}
    }

    if((findInArray(array,"magnumLP",index)&&findInArray(array, "carriageLPFortyTwoInchKneeOpenings",index))){
        //carriageLP = true;
        query.exec("SELECT * FROM `quoteTableTemp` WHERE connectionName = 'magnumCarriageKnees' and quoteNum = " + QString::number(quoteNum));
        query.last();
        if(query.value(3) == 2){
           // qDebug() << "found forty two in price in knees";
            query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPLinearTwoKnee'");
            query.last();
            //carriageLP = true;
            int price = query.value(2).toInt();
            totalPrice+=price;
            excludeArray.append("carriageLPLinearTwoKnee");
        }
        if(query.value(3) == 3){
         //   qDebug() << "found forty two in price in knees";
            query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPLinearThreeKnee'");
            query.last();
            //carriageLP = true;
            int price = query.value(2).toInt();
            totalPrice+=price;
            excludeArray.append("carriageLPLinearThreeKnee");
        }
        if(query.value(3) == 4){
            //qDebug() << "found forty two in price in knees";
            query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPLinearFourKnee'");
            query.last();
           // carriageLP = true;
            int price = query.value(2).toInt();
            totalPrice+=price;
            excludeArray.append("carriageLPLinearFourKnee");
        }
      }
    if(findInArray(array, "magnumLT",index) && findInArray(array, "carriageLTLinear",index)){
       //carriage = true;
       query.exec("SELECT * FROM quoteTableTemp WHERE connectionName = 'magnumCarriageKnees' and quoteNum = " + QString::number(quoteNum));
       query.last();
       //qDebug() << "knees value = " << query.value(3).toString();

       if(query.value(3).toInt() == 2){
           //qDebug() << "adding 2 knees";
           query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLinearTwoKnee'");
           query.last();
           totalPrice+=query.value(2).toInt();
           //qDebug() << "total : " << totalPrice;
           excludeArray.append("carriageLTLinear");

       }
       if(query.value(3).toInt() == 3){
           //qDebug() << "adding 3 knees";
           query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLinearThreeKnee'");
           query.last();
           totalPrice+=query.value(2).toInt();
           //qDebug() << "total : " << totalPrice;
           excludeArray.append("carriageLTLinear");
       }
       if(query.value(3).toInt() == 4){
           //qDebug() << "adding 4 knees";
           query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLinearFourKnee'");
           query.last();
           totalPrice+=query.value(2).toInt();
           //qDebug() << "total : " << totalPrice;
           excludeArray.append("carriageLTLinear");
       }


    if(findInArray(array,"magnumLT",index) &&findInArray(array, "carriageLTTiltFrame",index)){
        query.exec("SELECT * FROM quoteTableTemp WHERE connectionName = 'magnumCarriageKnees' and quoteNum = " + QString::number(quoteNum));
        query.last();
       // carriageLP = true;

        //qDebug() << "Magnum Knees: " << query.value(3).toString();

        int numberOfKnees = query.value(3).toInt();

        query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLTTiltFrame'");
        query.last();
        int basePrice = query.value(2).toInt();
        int newPriceWithKnees = basePrice * numberOfKnees; //multiply the base price times the amount of knees...

        //qDebug() << "base price : " << basePrice << " * " << numberOfKnees << " = " << newPriceWithKnees;

        totalPrice+=newPriceWithKnees;
        excludeArray.append("carriageLTTiltFrame");


}


    if(findInArray(array,"magnumLP",index)&&findInArray(array, "carriageLPTiltFrame",index)){
        query.exec("SELECT * FROM quoteTableTemp WHERE connectionName = 'magnumCarriageKnees' and quoteNum = " + QString::number(quoteNum));
        query.last();

        int kneePrice = query.value(3).toInt();
        // carriageLP = true;

         //qDebug() << "Magnum Knees: " << query.value(2).toString();


         query.exec("SELECT * FROM `quoteItems` WHERE  name = 'carriageLPTiltFrame'");
         query.last();


         int basePrice = query.value(2).toInt();
         int newPriceWithKnees = basePrice * kneePrice; //multiply the base price times the amount of knees...

         qDebug() << "base price : " << basePrice << " * " << kneePrice  << " = " << newPriceWithKnees;

         totalPrice+=newPriceWithKnees;
         excludeArray.append("carriageLPTiltFrame");


}


 }




  //  qDebug() << "index is " << index;
    for(int i = 0; i<index;i++){
        QRegExp re("\\d*");

        query.exec("SELECT * FROM quoteTableTemp WHERE quoteNum = " + QString::number(quoteNum) + " AND connectionName = '"+array.at(i)+"'");
        if(query.last() && query.value(3).toInt() > 1 && re.exactMatch(query.value(3).toString())){
          //  qDebug() << array;
            if(findOverride(array[i],quoteNum)){
                      //  qDebug() << "FOUND AN OVERRIDE @ " << quoteNum << " OF " << array[i];
                        totalPrice+=0;
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
          //  qDebug() << "FOUND AN OVERRIDE @ " << quoteNum << " OF " << array[i];
            totalPrice+=0;
                }

            else{
            query.exec("SELECT * FROM quoteItems WHERE name = '"+array.at(i)+"';"); //find all the things that are marked... grab their prices
            if(query.last()){
                    totalPrice+=query.value(2).toInt();
                }
              }
            }


    query.exec("SELECT * FROM quoteTable WHERE quoteNum = " + QString::number(quoteNum) + " and name = 'customPrice1SpinBox'");
    query.last();
   // qDebug() << "Quote Num = " << quoteNum << " value = " << query.value(3).toString();
   // qDebug() <<"total+value = " << totalPrice+query.value(3).toInt();
    if(query.isValid()){
        totalPrice = totalPrice + query.value(3).toInt();
    }


    query.exec("SELECT * FROM quoteTable WHERE quoteNum = " + QString::number(quoteNum ) + " and name = 'customPrice2SpinBox'");
    query.last();
   // qDebug() << "Quote Num = " << quoteNum << " value = " << query.value(3).toString();
       // qDebug() <<"total+value = " << totalPrice+query.value(3).toInt();
    if(query.isValid()){
       totalPrice = totalPrice + query.value(3).toInt();
    }


    return totalPrice;
}




void quoteDBPriceManager::processDynamicOverrides(QString overrideValue, int quoteNum){
    QSqlQuery q2;
    QStringList splitted = overrideValue.split("action");
    QString newText = splitted.at(1);
    //qDebug() << "newText = " << newText;
    //qDebug() << "quoteNum = " << quoteNum;
    qDebug() << "running update script: " << q2.exec("UPDATE `quoteTable` SET value = -1 WHERE quoteNum = "+QString::number(quoteNum)+" AND connectionName = '"+newText+"'");
    qDebug() << "running get script: " << q2.exec("SELECT * FROM `quoteTable` WHERE quoteNum = "+QString::number(quoteNum)+" AND connectionName = '"+newText+"'");
    q2.last();
    qDebug() << q2.value(1).toString() << " " << q2.value(3).toInt();

}












