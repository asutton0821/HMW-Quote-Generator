#include "encryptionhandler.h"

encryptionHandler::encryptionHandler()
{


}

/*
 * Encrypts a string that is thrown at it with the saltvalue of %^3
 *
 */
QString encryptionHandler::encryptString(QString str){
    QString newString = str;
   int i;

         for(i = 0; i< newString.length(); i++){
            //str.at(i) = str.at(i) + 2; //the key for encryption is 3 that is added to ASCII value
           // QChar n = str.at(i);
           // n = n - 2;

            QChar n = newString.at(i);
            int toAscii = n.toLatin1();
            //qDebug() << toAscii;
            int saltValue = 5 * 5 * 5;
            toAscii = toAscii + saltValue;
            //qDebug() << toAscii;
            newString[i] = n.fromLatin1(toAscii);





         }

        // qDebug() << "\nEncrypted string: " << str << " is " << newString;

         return newString;




}

/*
 *
 * Decrypts a string that is thrown to it with a salt value of 5^3
 *
 */

QString encryptionHandler::decryptString(QString str){

    QString newString = str;

    int i;

    //second case for decrypting a string

       for(i = 0; i < newString.length(); i++){
       //str.at(i) = str.at(i) - 2; //the key for encryption is 3 that is subtracted to ASCII value
           QChar n = newString.at(i);
           int toAscii = n.toLatin1();
           int saltValue = 5 * 5 * 5;
           //qDebug() << toAscii;
           toAscii = toAscii - saltValue;
           //qDebug() << toAscii;
           newString[i] = n.fromLatin1(toAscii);

        }

   // qDebug() << "\nDecrypted string: " << str << " is " << newString;



 return newString;
}
