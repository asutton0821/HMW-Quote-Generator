#include "mainwindow.h"
#include <ui_mainwindow.h>
#include "authentication.h"
#include <QDebug>
#include <QDate>
#include <QString>
#include <QMessageBox>
#include <string>
#include <QFileDialog>
#include <QStandardPaths>
#include <QInputDialog>
#include <QObject>
#include <QCheckBox>
#include <QWidget>
#include <QRadioButton>
#include <QSpinBox>
#include <QDateEdit>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QSqlError>
#include <QSystemTrayIcon>
#include <QtCore>
#include <QtGui>
#include <QRegExpValidator>
#include <QRegExp>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{







    STOPAPP = false;


    authentication au;
    au.exec();
   // qDebug() << "accepted!";
    qApp->installEventFilter(this);
    ui->setupUi(this);
    newQuote = true;
    length = 0;

    this->setFixedSize(QSize(797,403));

    isToggled = 0;

    carriageIndex =0;






    qdbMan.start();
    i = 0;
    this->freeze();
   expandOrShrink = 0; //0= shrink, 1 = expand
    num = 0;
    carriageItems = QList<QString>();

   if(au.buttonPressed == 1){
       ui->tabWidget->hide();





        loginName = au.getUserDescription();
       // qDebug() << loginName;
       this->unfreeze();
        ui->loginLabel->setText("Logged in as: "+loginName);
       // qDebug() << ui->loginLabel->text();
        qS.show();
        qS.begin();

        if(TOGGLECONTACTBAR){
            cs.show();
            cs.addContacts();
        }


       // pS.show();
       // pS.getNameAndPrices();




           //loadConnectionFile();
        loadDefaults();
           iterateChildren(ui->centralWidget);

        checkQuoteStatus();
      //  qDebug() << "Quote Number = " << qdbMan.getNumQuotes();
        if(qdbMan.getNumQuotes() == 1){
           // qDebug() << "We are saying yes to reset";
            reset(true);
           // qDebug() << "isNewQuote? : " << newQuote;
        }
        else{
          //  qDebug() << "SAYING NO TO RESET";
          reset(false); //makes more sense to just call reset since we already have it here
         // qDebug() << "isNewQuote? : " << newQuote;
        }

    }
    else{
       // qDebug() << "false value";
        this->hide();
        qS.hide();
        STOPAPP = true;

    }

    if(STOPAPP == true){
       // qDebug() << "Stopping";
                    this->hide();
        this->close();
    }





//iterateChildren(ui->centralWidget);

    ui->phoneLineEdit->setValidator(new QRegExpValidator(QRegExp("[-()0-9]*")));
    ui->phone2LineEdit->setValidator(new QRegExpValidator(QRegExp("[-()0-9]*")));
    ui->faxLineEdit->setValidator(new QRegExpValidator(QRegExp("[-()0-9]*")));





    makeToolTips(ui->centralWidget);


}




MainWindow::~MainWindow()
{
    delete ui;
}

/*
 *
 * Quit the app when the X button is pressed
 *
 */
void MainWindow::closeEvent(QCloseEvent *bar)
{
    // Do something
    qApp->quit();
}

/*
 * This function will detect whenever the previous button is pressed. It will call the function getQuote, which will then
 * grab the corresponding quote number ( - 1 since the database index starts at 0) and display the information to the user.
 * See getQuote documentation.
 *
*/



void MainWindow::previousButtonPushed(){
    formatText();
    checkQuoteStatus();
    newQuote = false;
    //QuoteDbManager qdb;
    if(ui->actionFilterAll->isChecked()){
        if(ui->quoteNumLineEdit->text().toInt() > 1){
            getQuote(ui->quoteNumLineEdit->text().toInt() - 1);

        }
    }
    else if(ui->actionFilterOpen->isChecked()){
        Quote q;
        for(int i = ui->quoteNumLineEdit->text().toInt()-1; i>0 ;i--){
            //qDebug() << "i " << i << " num " << qdb.getNumQuotes();
            q = qdbMan.getQuote(i);
            QSqlQuery qu;
            qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'status' AND quoteNum = " +QString::number(i));
            qu.last();
            QString status = qu.value(3).toString();
            if(status == "Open"){

                getQuote(q.quoteNum);

                break;

            }
            if(i == 0){
                break;
            }
        }

    }
    else if(ui->actionFilterClosed->isChecked()){
        Quote q;
        for(int i = ui->quoteNumLineEdit->text().toInt()-1; i>0 ;i--){
            //qDebug() << "i " << i << " num " << qdb.getNumQuotes();
            q = qdb.getQuote(i);
            QSqlQuery qu;
            qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'status' AND quoteNum = " +QString::number(i));
            qu.last();
            QString status = qu.value(3).toString();
            if(status == "Closed"){
                getQuote(q.quoteNum);

                break;

            }
            if(i == 0){
                break;
            }
        }

    }

    else if(ui->actionFilterExpired->isChecked()){
        Quote q;
        for(int i = ui->quoteNumLineEdit->text().toInt()-1; i>0 ;i--){
            //qDebug() << "i " << i << " num " << qdb.getNumQuotes();
            q = qdb.getQuote(i);
            QSqlQuery qu;
            qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'status' AND quoteNum = " +QString::number(i));
            qu.last();
            QString status = qu.value(3).toString();
            if(status == "Expired"){
                getQuote(q.quoteNum);

                break;

            }
            if(i == 0){
                break;
            }
        }

    }

}

/*
 *This function will detect when the next button is pushed and will then display the next quote in line.
 * If the next quote doesn't exist, it will call the reset(false) function that will then allow you to create
 * a new quote. You cannot move up past the last number + 1 until you create a new quote.
*/

void MainWindow::nextButtonPushed(){
    formatText();
    checkQuoteStatus();
    newQuote = false;
    //qDebug() << "pressed";
    //QuoteDbManager qdb;
    if(ui->actionFilterAll->isChecked()){
        //qDebug() << "Filtering by all!";
        if(ui->quoteNumLineEdit->text().toInt() < qdbMan.getNumQuotes() - 1){
        //qDebug() << "Pushed" << ui->quoteNumLineEdit->text().toInt();
            getQuote(ui->quoteNumLineEdit->text().toInt() + 1);

           // loadConnectionFile();

        }
        else{
            //reset(false);
        }
    }
    else if(ui->actionFilterOpen->isChecked()){
        Quote q;
        for(int i = ui->quoteNumLineEdit->text().toInt()+1; i<qdb.getNumQuotes() ;i++){
            //qDebug() << "i " << i << " num " << qdb.getNumQuotes();
            q = qdb.getQuote(i);
            QSqlQuery qu;
            qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'status' AND quoteNum = " +QString::number(i));
            qu.last();
            QString status = qu.value(3).toString();
            if(status == "Open"){
                getQuote(q.quoteNum);

                break;

            }
            if(i == qdb.getNumQuotes() - 1){
                break;
            }
        }

    }
    else if(ui->actionFilterClosed->isChecked()){
        Quote q;
        for(int i = ui->quoteNumLineEdit->text().toInt()+1; i<qdb.getNumQuotes() ;i++){
            //qDebug() << "i " << i << " num " << qdb.getNumQuotes();
            q = qdb.getQuote(i);
            QSqlQuery qu;
            qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'status' AND quoteNum = " +QString::number(i));
            qu.last();
            QString status = qu.value(3).toString();
            if(status == "Closed"){
                getQuote(q.quoteNum);

                break;

            }
            if(i == qdb.getNumQuotes() - 1){
                break;
            }
        }

    }
    else if(ui->actionFilterExpired->isChecked()){
        Quote q;
        for(int i = ui->quoteNumLineEdit->text().toInt()+1; i<qdb.getNumQuotes() ;i++){
            //qDebug() << "i " << i << " num " << qdb.getNumQuotes();
            q = qdb.getQuote(i);
            QSqlQuery qu;
            qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'status' AND quoteNum = " +QString::number(i));
            qu.last();
            QString status = qu.value(3).toString();
            if(status == "Expired"){
                getQuote(q.quoteNum);

                break;

            }
            if(i == qdb.getNumQuotes() - 1){
                break;
            }
        }

    }
}

/*
 * This function is to detect when the cancel button is pressed, and thereby exit the program.
 * Other uses for this function could be to reset (incase you do not want the quote you are working on saved.
 *
*/

void MainWindow::reject(){
  //  qDebug() << "You clicked cancel";
    qApp->exit();
}

/*
 * This function updates the date in the date edit text box, so that every new date has the correct
 * current date.
*/
void MainWindow::updateDate(){
    ui->dateEdit->setDate(QDate::currentDate());
}

/*
 * This function updates the quote number each time a new quote is submitted by calling getNumQuotes()
 * in the quotedmanager class.
 *
*/
void MainWindow::updateQuoteNum(){
    ui->quoteNumLineEdit->setText(QString::number(qdbMan.getNumQuotes()));
}

/*
 * This function is fired once you hit the ok button.
 * When this happens, a quote struct is generated and filled
 * with information from the UI, inclduding date, and integer
 * values for the checkboxes and radio buttons and then
 * buildQuote is called inside of quotedbmanager,
 * which then stores the information inside the struct
 * into the database.
 *
 * NOTE: This is where the bulk of code lies. In here, you must scan for checked boxes and checked radio buttons and add them to the corresponding quote value.
 * Make sure that you add the information to the struct in quotebbmanager, so that it can keep up with it. You will be able to add the price and description
 * using a server program.
 *
 * Also, please make sure you put the UI Widget inside of the appropriate functions such as getQuote. This will make
 * sure the boxes clear when changed.
 *
 *
*/
void MainWindow::accept(){

formatText(); // go ahead and format the string.

 //  int numQuotes = qdbMan.getNumQuotes();
  //  int quoteNum = ui->quoteNumLineEdit->text().toInt();
  //  qDebug() << "# of quotes = " << numQuotes << " quote #  = " << quoteNum;


if(cs.checkContactExist(ui->nameLineEdit->text())){
      qDebug() << "it exists";
}
else{
    qDebug() << "does not exist";
    cs.addContact(ui->nameLineEdit->text(), ui->companyNameLineEdit->text(), ui->address1LineEdit->text(), ui->address2LineEdit->text(), ui->cityLineEdit->text(), ui->stateComboBox->currentText(), ui->zipCodeLineEdit->text(), ui->emailLineEdit->text(), ui->faxLineEdit->text(), ui->phoneLineEdit->text(), ui->phone2LineEdit->text() );
    cs.clear();
    cs.addContacts();
}


Quote q; //Check quote and store in database.
q.date = ui->dateEdit->date().toString("MM/dd/yyyy");
q.name = ui->nameLineEdit->text();


//q.quoteNum = ui->quoteNumLineEdit->text().toInt();






if(ui->nameLineEdit->text() == "" && ui->nameLineEdit->text() == " ") {
    QMessageBox::information(this, tr("Invalid!"), tr("Quote requires name field to not be blank!"));
        return;
}

if(ui->phoneLineEdit->text().count() < 10){ //warn if less than 10.
    QMessageBox::information(this, tr("Invalid Phone Number"), tr("Phone number requires 10 digits"));
    return;
}






if((ui->emailLineEdit->text() != "" && ui->emailLineEdit->text() != " ") || (ui->phoneLineEdit->text() != " " && ui->phoneLineEdit->text() != "") || (ui->phone2LineEdit->text() != "" && ui->phone2LineEdit->text() != " ") ){
    //pass
}
else{
    QMessageBox::information(this, tr("Invalid!"), tr("Quote requires a  phone number/email address!"));
    return;
}

if(ui->statusBox->currentText().compare("Open") == 0){
    q.status = 0;
    q.handled = 0;

}
if(ui->statusBox->currentText().compare("Closed") == 0){
    q.status = 1;
    q.handled = 0;
}
q.custom1 = ui->custom1LineEdit->text();
q.custom2 = ui->custom2LineEdit->text();




//custom
q.customPrice1 = ui->customPrice1SpinBox->text().toInt();
q.customPrice2 = ui->customPrice2SpinBox->text().toInt();


//saw specs
q.sawSpecs = ui->sawSpeedSpinBox->text().toInt();



if(newQuote == true){ // a new quote is being created
 //   qDebug() << "We are creating a new quote!!";
    updateQuoteNum(); //update this to reflect what the ACTUAL quote number is
    q.quoteNum = ui->quoteNumLineEdit->text().toInt();
}
else{
   // qDebug() << "We are just updating";
    q.quoteNum = ui->quoteNumLineEdit->text().toInt(); //otherwise, just set the current number since we are currently updating a quote.
}


setConnections(connectionsFrom,connectionsTo,i);
//qDebug() << "Built Struct";


qdbMan.buildQuote(q);



QList<QString> list = applyCheckedItems();


qP.priceQuote(q,list,list.count(),ui->quoteNumLineEdit->text().toInt());





//reset(false); //uncomment to reset everytime you make a quote. comment to disable this feature



checkQuoteStatus();
getQuote(q.quoteNum);
qS.update();
qS.begin();
newQuote = false;
}

/*
 *
 * Grabs the checked items and then puts them into the list and returns them to be matched up with the connections file.
 *
 */

QList<QString> MainWindow::applyCheckedItems(){
    QList<QLineEdit*> lineEditList = MainWindow::findChildren<QLineEdit*>(); //find all the line edits.
    QList<QRadioButton*> radioButtonList = MainWindow::findChildren<QRadioButton*>(); //find all the line edits.
    QList<QCheckBox*> checkBoxList = MainWindow::findChildren<QCheckBox*>(); //find all the line edits.
    QList<QSpinBox*> spinBoxList = MainWindow::findChildren<QSpinBox*>();
    QList<QComboBox*> comboBoxList = MainWindow::findChildren<QComboBox*>();
    QList<QString> namesChecked;
    QList<QString> connectionNamesChecked;


    for(int j = 0; j<radioButtonList.count();j++){
        if(radioButtonList.at(j)->isChecked()){

            qDebug() << radioButtonList.at(j)->objectName();

            if(radioButtonList.at(j)->objectName() == "carriageLPFortyEightInchKneeOpeningsRadioButton"){
                connectionNamesChecked.append("carriageLPFortyEightInchKneeOpenings");
            }
            if(radioButtonList.at(j)->objectName() == "carriageLPFortyTwoInchKneeOpeningsRadioButton"){
                connectionNamesChecked.append("carriageLPFortyTwoInchKneeOpenings");
            }

            namesChecked.append(radioButtonList.at(j)->objectName());

        }
    }


    for(int j = 0; j<checkBoxList.count();j++){
        if(checkBoxList.at(j)->isChecked()){

            qDebug() << checkBoxList.at(j)->objectName();
            namesChecked.append(checkBoxList.at(j)->objectName());

        }
    }


    int p = 0; //variable for namesChecked
    int j = 0; //variable for connectionsFrom
    int newIndex = 0;
  //  qDebug() << "i is " << i;



    while(p <= i){
       // qDebug() << "looking at namesChecked(" << j << ") = " << namesChecked.at(j);
        //qDebug() << "comparing to connectionsFrom(" << p << ") = " << connectionsFrom[p];
       // qDebug() << "items counted: " << namesChecked.count();
       // qDebug() << namesChecked;
        if(namesChecked.isEmpty()){
            return namesChecked;
        } //THIS MIGHT BREAK SOMETHING, NOT SURE

        if(namesChecked.at(j) != connectionsFrom[p]){

           // qDebug() << "j is " << j << "p is " << p << " in the does not equal statement! ";
          //  j++;
        }
        else if(namesChecked.at(j) == connectionsFrom[p]){
            if(namesChecked.at(j).contains("carriage")){

                if(ui->magnumLTCheckBox->isChecked()){
                       QString nameIndex = namesChecked.at(j);
                      //  qDebug() << "names " << nameIndex;
                       QString name = "";
                       if(nameIndex.contains("CheckBox")){
                          name =  nameIndex.replace("CheckBox","");
                       }
                       if(nameIndex.contains("RadioButton")){
                          name =  nameIndex.replace("RadioButton","");
                       }


                       QString newName = name.replace("carriage","carriageLT");
                      // qDebug() << "newName of LT " << newName;
                       for(int i = 0; i<carriageItems.length(); i++){
                           //qDebug() << carriageItems.at(i);
                           if(carriageItems.at(i) == newName){
                              // qDebug() << carriageItems.at(i) << " " << newName;
                             //  qDebug() << "found match in LT" << newName;
                               QSqlQuery query;
                               query.exec("SELECT * FROM `quoteTable` WHERE name = '"+namesChecked.at(j)+"'");
                               query.last();
                              // qDebug() << "data: " << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();


                               QSqlQuery query2;
                              query2.exec("UPDATE `quoteTable` SET `quoteNum`='"+query.value(0).toString()+"',`name`='"+query.value(1).toString()+"',`connectionName`='"+newName+"',`value`='"+query.value(3).toString()+"' WHERE name = '"+query.value(1).toString() +"'");


                              if(!connectionNamesChecked.contains(newName)){

                               connectionNamesChecked.append(newName);
                                newIndex++;
                              }

                               //qDebug() << connectionNamesChecked;

                               break;
                               //qDebug() << "found a match! BOOYA " << newName;

                           }
                       }


                }


                else if(ui->magnumLPCheckBox->isChecked()){
                   // qDebug() << "namesChecked in LP : " << namesChecked;
                    QString nameIndex = namesChecked.at(j);

                   // qDebug() << "nameIndex: " << namesChecked.at(j);

                    QString name = "";

                    if(nameIndex.contains("CheckBox")){
                       name =  nameIndex.replace("CheckBox","");
                    }
                    if(nameIndex.contains("RadioButton")){
                       name =  nameIndex.replace("RadioButton","");
                    }
                    QString newName = name.replace("carriage","carriageLP");

                  //  qDebug()<< newName;

                   // qDebug() << "newName of LP " << newName;
                    for(int i = 0; i<carriageItems.length(); i++){
                        //qDebug() << carriageItems.at(i);
                       // qDebug() << "carriage items " << carriageItems;
                        if(carriageItems.at(i) == newName){

                            //qDebug() << carriageItems.at(i) << " : " << newName;

                          //  qDebug() << "found match in LP" << newName << " is " << carriageItems.at(i);
                           // qDebug() << newName << " " << carriageItems.at(i);
                            QSqlQuery query;
                            query.exec("SELECT * FROM `quoteTable` WHERE name = '"+namesChecked.at(j)+"'");
                            query.last();
                           // qDebug() << "data: " << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();

                            QSqlQuery query2;
                           query2.exec("UPDATE `quoteTable` SET `quoteNum`='"+query.value(0).toString()+"',`name`='"+query.value(1).toString()+"',`connectionName`='"+newName+"',`value`='"+query.value(3).toString()+"' WHERE name = '"+query.value(1).toString() +"'");

                           if(!connectionNamesChecked.contains(newName)){
                            connectionNamesChecked.append(newName);
                            newIndex++;
                            }

                           //qDebug() << "found a match! BOOYA LP " << newName;
                            break;
                        }
                    }

                }



                }







           // if(namesChecked.at(j) == "carriageLPFortyTwoInchKneeOpeningsRadioButton"){
            //    qDebug() << "fortyTwoChecked";
               // connectionNamesChecked.append("carriageLPFortyTwoInchKneesOpenings");
          //  }

            else{

                if(!connectionNamesChecked.contains(connectionsTo[p])){
                    connectionNamesChecked.append(connectionsTo[p]);
                     newIndex++;
                }
               //  qDebug() << "adding " << connectionsTo[p];
         //   qDebug() << "J: " << j << "p: " << p << "Array: " << connectionNamesChecked.at(newIndex);

            }
        }
        if(j == namesChecked.count() -1 ){
            j = 0;
            p++;
           // qDebug() << "j was reset to 0";
        }
        else{
            j++;

        }


    }

      // qDebug() << connectionNamesChecked;
qDebug() << "connectionsNamesChecked = " << connectionNamesChecked;
    return connectionNamesChecked;




}

/*
 *
 * This function "clears the board" and allows a new quote to be generated, while updating the date and quote number for you.
 * It connects the OK button (so that the quote gets stored), the Cancel button (so that the program can exit), the next button,
 * the previous button, the numLineEdit field (so that you can jump between quotes), the radio buttons (for default value
 * prediction), the checkboxes (for default value prediction), the newQuote action found in the file menu,
 * and the about action found in the about menu.
 *
 * Connects the change file location button to change the location in which PDFs are stored.
 *
 * Connects status box to close the quote if needed.
 *
 *
 */

void MainWindow::reset(bool startOver){
    ui->setupUi(this);







    connect(ui->okCancelButtonBox, SIGNAL(rejected()), this, SLOT(reject())); //Connect Cancel Button
    connect(ui->okCancelButtonBox, SIGNAL(accepted()), this, SLOT(accept()));

    connect(ui->okCancelButtonBox_2, SIGNAL(rejected()), this, SLOT(reject())); //Connect Cancel Button
    connect(ui->okCancelButtonBox_2, SIGNAL(accepted()), this, SLOT(accept()));


    //Connect OK button
    connect(ui->okCancelButtonBox2, SIGNAL(rejected()), this, SLOT(reject())); //Connect Cancel Button
    connect(ui->okCancelButtonBox2, SIGNAL(accepted()), this, SLOT(accept())); //Connect OK button

    connect(ui->previousPushButton, SIGNAL(clicked()), this, SLOT(previousButtonPushed())); //Connect Previous Button
    connect(ui->nextPushButton, SIGNAL(clicked()), this, SLOT(nextButtonPushed())); //Connect Next Button

    connect(ui->adjustPricePushButton, SIGNAL(clicked()), this, SLOT(adjustPricePushButtonPushed()));
    connect(ui->newQuotePushButton, SIGNAL(clicked()), this, SLOT(resetButton())); //connects new quote button

    connect(ui->quoteNumLineEdit, SIGNAL(textEdited(QString)), this, SLOT(onTextChanged())); //Connect TextEdit on numLineEdit
    connect(ui->phoneLineEdit,SIGNAL(textEdited(QString)),this, SLOT(formatText()));
    connect(ui->phone2LineEdit,SIGNAL(textEdited(QString)),this, SLOT(formatText()));
    connect(ui->faxLineEdit,SIGNAL(textEdited(QString)),this, SLOT(formatText()));
    connect(ui->platform40RadioButton, SIGNAL(toggled(bool)), this, SLOT(connectRadioButtons())); //Connect radio button
    connect(ui->platform48RadioButton, SIGNAL(toggled(bool)), this, SLOT(connectRadioButtons())); //Connect radio button
    connect(ui->platform60RadioButton, SIGNAL(toggled(bool)), this, SLOT(connectRadioButtons())); //Connect radio button
    connect(ui->platform52RadioButton, SIGNAL(toggled(bool)), this, SLOT(connectRadioButtons())); //Connect radio button


    connect(ui->magnumLTSetshaftradioButton, SIGNAL(toggled(bool)), this, SLOT(connectRadioButtons()));//connect radio button

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabSelected()));




    connect(ui->cantPushOffCheckBox, SIGNAL(toggled(bool)), this, SLOT(connectCheckBoxes())); //Connect radio button
    connect(ui->cantTurnersCheckBox, SIGNAL(toggled(bool)), this, SLOT(connectCheckBoxes())); //Connect checkbox
    connect(ui->brownsvilleCheckBox,SIGNAL(toggled(bool)),this,SLOT(connectCheckBoxes()));
    connect(ui->horizontalEdgerCheckBox, SIGNAL(toggled(bool)), this, SLOT(connectCheckBoxes())); //Connect checkbox
    connect(ui->linearCompSetworksCheckBox, SIGNAL(toggled(bool)), this, SLOT(connectCheckBoxes()));

    connect(ui->magnumLTCheckBox,SIGNAL(toggled(bool)), this, SLOT(connectCheckBoxes()));
    connect(ui->magnumLPCheckBox,SIGNAL(toggled(bool)), this, SLOT(connectCheckBoxes()));


    connect(ui->linearCheckBox,SIGNAL(toggled(bool)),this,SLOT(connectCheckBoxes()));
    connect(ui->deluxeSeatCheckBox, SIGNAL(toggled(bool)), this, SLOT(connectCheckBoxes()));
    connect(ui->actionNew_Quote, SIGNAL(triggered(bool)),this,SLOT(resetButton())); //connect newQuote action


    connect(ui->actionAbout_Quote_Generator, SIGNAL(triggered(bool)),this,SLOT(displayVersion())); //connect About Action
    connect(ui->pdfPushButton, SIGNAL(clicked()),this,SLOT(printPDF())); //connect PDF Button
    connect(ui->pdfPushButton_2, SIGNAL(clicked()),this,SLOT(printPDF())); //connect PDF Button
    connect(ui->actionChange_Save_Location, SIGNAL(triggered(bool)),this,SLOT(changeSaveLocation()));
    connect(ui->statusBox,SIGNAL(currentTextChanged(QString)),this,SLOT(changeQuoteStatus()));
   //connect menu bar items
   connect(ui->actionFilterAll, SIGNAL(triggered(bool)),this,SLOT(quoteFilterMenuSelection()));

   connect(ui->actionFilterOpen, SIGNAL(triggered(bool)),this,SLOT(quoteFilterMenuSelection()));
   connect(ui->actionFilterClosed, SIGNAL(triggered(bool)),this,SLOT(quoteFilterMenuSelection()));
   connect(ui->actionFilterExpired, SIGNAL(triggered(bool)),this,SLOT(quoteFilterMenuSelection()));
   connect(ui->actionCompletionDate,SIGNAL(triggered(bool)),this,SLOT(showCompDateBox()));
    connect(ui->actionClose_Sidebar,SIGNAL(triggered(bool)),this,SLOT(sidebar()));
    connect(ui->actionClose_Price_Sidebar,SIGNAL(triggered(bool)), this, SLOT(priceSideBar()));
    connect(ui->actionClose_Customer_Info, SIGNAL(triggered(bool)), this, SLOT(customerinfo()));
   //

   connect(ui->actionSetOpen, SIGNAL(triggered(bool)),this,SLOT(quoteMenuSelection()));
   connect(ui->actionSetClosed, SIGNAL(triggered(bool)),this,SLOT(quoteMenuSelection()));
   //Connect price change items
   connect(ui->actionhoriz, SIGNAL(triggered()),this,SLOT(connectOverrideFunctions()));
   connect(ui->actionvertEdg, SIGNAL(triggered()),this,SLOT(connectOverrideFunctions()));
   connect(ui->actiontopSaw, SIGNAL(triggered()),this,SLOT(connectOverrideFunctions()));
   connect(ui->actionfeedJoyStick, SIGNAL(triggered()),this,SLOT(connectOverrideFunctions()));
   connect(ui->actionhdOutFeed, SIGNAL(triggered()),this,SLOT(connectOverrideFunctions()));
   connect(ui->actionsawDustChain, SIGNAL(triggered()),this,SLOT(connectOverrideFunctions()));
   connect(ui->actionpulley36, SIGNAL(triggered()),this,SLOT(connectOverrideFunctions()));
   //connect(ui->action52_Trailer, SIGNAL(triggered(bool)),this,SLOT(connectOverrideFunctions()));
   connect(ui->actionextraTrailer, SIGNAL(triggered()),this,SLOT(connectOverrideFunctions()));
   connect(ui->actioncantTurner, SIGNAL(triggered()),this,SLOT(connectOverrideFunctions()));
   connect(ui->actionhamDog, SIGNAL(triggered()),this,SLOT(connectOverrideFunctions()));
   connect(ui->actionextraAxle, SIGNAL(triggered()),this,SLOT(connectOverrideFunctions()));


   connect(ui->actionlinearCarriage, SIGNAL(triggered()),this,SLOT(connectOverrideFunctions()));

   connect(ui->tabButton,SIGNAL(clicked()),this,SLOT(doTheThing()));


   //CONNECT TOTAL PRICE HERE
   connect(ui->cantPushOffCheckBox,SIGNAL(toggled(bool)), this, SLOT(push(bool)));
   connect(ui->verticalEdgerCheckBox,SIGNAL(toggled(bool)), this, SLOT(push(bool)));
   connect(ui->horizontalEdgerCheckBox,SIGNAL(toggled(bool)), this, SLOT(push(bool)));
   connect(ui->topSawCheckBox,SIGNAL(toggled(bool)), this, SLOT(push(bool)));
   connect(ui->cantTurnersCheckBox,SIGNAL(toggled(bool)), this, SLOT(push(bool)));
   connect(ui->brownsvilleCheckBox,SIGNAL(toggled(bool)), this, SLOT(push(bool)));
   connect(ui->feedJoystickCheckBox, SIGNAL(toggled(bool)), this, SLOT(push(bool)));
   connect(ui->offbearerBeltCheckBox,SIGNAL(toggled(bool)), this, SLOT(push(bool)));
   connect(ui->linearCompSetworksCheckBox, SIGNAL(toggled(bool)), this, SLOT(push(bool)));
   connect(ui->linearCheckBox,SIGNAL(toggled(bool)),this,SLOT(push(bool)));
   connect(ui->deluxeSeatCheckBox, SIGNAL(toggled(bool)), this, SLOT(push(bool)));
   connect(ui->fourStrandDeckRadioButton, SIGNAL(toggled(bool)), this, SLOT(push(bool)));
   //connect(ui->hdOutfeedCheckBox, SIGNAL(toggled(bool)), this, SLOT(push(bool)));
   connect(ui->sawdustChainCheckBox, SIGNAL(toggled(bool)), this, SLOT(push(bool)));
   connect(ui->drivePulleyCheckBox, SIGNAL(toggled(bool)), this, SLOT(push(bool)));
   connect(ui->extraLegCheckBox, SIGNAL(toggled(bool)), this, SLOT(push(bool)));
   connect(ui->hamDogCheckBox, SIGNAL(toggled(bool)), this, SLOT(push(bool)));
   connect(ui->extraAxleCheckBox, SIGNAL(toggled(bool)), this, SLOT(push(bool)));


   connect(ui->platform40RadioButton, SIGNAL(toggled(bool)), this, SLOT(push(bool)));
   connect(ui->magnumRadioButton,SIGNAL(toggled(bool)), this, SLOT(push(bool)));

   connect(ui->platform48RadioButton,SIGNAL(toggled(bool)), this, SLOT(push(bool)));
   connect(ui->threeStrandDeckRadioButton,SIGNAL(toggled(bool)), this, SLOT(push(bool)));

   tabSelected();





  /*
   *
   * Find a spinbox connection to trigger "push";
   */




   //





   ui->salesPersonComboBox->addItems(getDatabaseElements("authentication"));
   ui->salesPersonComboBox->setCurrentText(loginName);
    updateDate();
    updateQuoteNum();
    checkQuoteStatus();
    ui->twoStrandDeckRadioButton->setEnabled(true);
    ui->threeStrandDeckRadioButton->setEnabled(true);
    ui->fourStrandDeckRadioButton->setEnabled(true);


     ui->loginLabel->setText("Logged in as: \n"+loginName);
    ui->createdByLabel->setText("");



    if(startOver == true){ //this prevents this from being called on the first quote... this will make it so we can determine if one quote is already available or not.
        newQuote = true; //this will tell the program that we ARE creating a new quote. This should SOVLE the real-time dilemna
    }

    QSqlQuery query;
    query.exec("TRUNCATE TABLE quoteTableTemp");






   makeToolTips(ui->centralWidget); //to keep up with price updates
  // makeCarriageToolTips(ui->centralWidget);




}

/*
 * This function will detect text changing in the quoteNumLineEdit box that will allow you to jump to
 * quotes that are stored. Going over the amount of quotes + 1 (taking into account a new quote action),
 * will cause the program to jump back to the amount of quotes + 1. Thereby, eliminating the fact
 * that the database may be populated with out of order quote numbers.
 *
 *
 */
void MainWindow::onTextChanged(){
if(ui->quoteNumLineEdit->text().compare("") != 0 && ui->quoteNumLineEdit->text().compare("0") != 0){
   int a = qdbMan.getNumQuotes();
   QString string(ui->quoteNumLineEdit->text());
   int textNumber = string.toInt();
   if(textNumber > a){
       ui->quoteNumLineEdit->setText(QString::number(a));
       reset(false);
   }
   else if(textNumber < a){
       getQuote(textNumber);
   }
   else{
       reset(false);
   }
}
else{
    ui->quoteNumLineEdit->setText("1");
    getQuote(1);
}

}


void MainWindow::tabSelected(){

    if(ui->tabWidget->currentIndex() == 0){
        ui->carriageLPFortyTwoInchKneeOpeningsRadioButton->setAutoExclusive(false);
        ui->carriageLPFortyEightInchKneeOpeningsRadioButton->setAutoExclusive(false);
        ui->magnumLTSetshaftradioButton->setAutoExclusive(false);
        ui->magnumLTSetshaftradioButton->setAutoExclusive(false);

        ui->carriageLPFortyTwoInchKneeOpeningsRadioButton->setChecked(false);
        ui->carriageLPFortyEightInchKneeOpeningsRadioButton->setChecked(false);
        ui->magnumLTSetshaftradioButton->setChecked(false);
        ui->magnumLTSetshaftradioButton->setChecked(false);

        ui->carriageLPFortyTwoInchKneeOpeningsRadioButton->setAutoExclusive(true);
        ui->carriageLPFortyEightInchKneeOpeningsRadioButton->setAutoExclusive(true);
        ui->magnumLTSetshaftradioButton->setAutoExclusive(true);
        ui->magnumLTSetshaftradioButton->setAutoExclusive(true);

    }

    if(ui->tabWidget->currentIndex() == 1){


        ui->platform40RadioButton->setAutoExclusive(false);
        ui->platform48RadioButton->setAutoExclusive(false);
        ui->platform52RadioButton->setAutoExclusive(false);
        ui->platform60RadioButton->setAutoExclusive(false);
        ui->magnumRadioButton->setAutoExclusive(false);
        ui->twoStrandDeckRadioButton->setAutoExclusive(false);
        ui->threeStrandDeckRadioButton->setAutoExclusive(false);
        ui->fourStrandDeckRadioButton->setAutoExclusive(false);
        ui->noDeckRadioButton->setAutoExclusive(false);
        ui->stdChainRadioButton->setAutoExclusive(false);
        ui->hdChainRadioButton->setAutoExclusive(false);
        ui->barRadioButton->setAutoExclusive(false);
        ui->camboxRadioButton->setAutoExclusive(false);
        ui->nanosetRadioButton->setAutoExclusive(false);
        ui->compsetRadioButton->setAutoExclusive(false);


        ui->platform40RadioButton->setChecked(false);
        ui->platform48RadioButton->setChecked(false);
        ui->platform52RadioButton->setChecked(false);
        ui->platform60RadioButton->setChecked(false);
        ui->magnumRadioButton->setChecked(false);
        ui->twoStrandDeckRadioButton->setChecked(false);
        ui->threeStrandDeckRadioButton->setChecked(false);
        ui->fourStrandDeckRadioButton->setChecked(false);
        ui->noDeckRadioButton->setChecked(false);
        ui->stdChainRadioButton->setChecked(false);
        ui->hdChainRadioButton->setChecked(false);
        ui->barRadioButton->setChecked(false);
        ui->camboxRadioButton->setChecked(false);
        ui->nanosetRadioButton->setChecked(false);
        ui->compsetRadioButton->setChecked(false);


        ui->platform40RadioButton->setAutoExclusive(true);
        ui->platform48RadioButton->setAutoExclusive(true);
        ui->platform52RadioButton->setAutoExclusive(true);
        ui->platform60RadioButton->setAutoExclusive(true);
        ui->magnumRadioButton->setAutoExclusive(true);
        ui->twoStrandDeckRadioButton->setAutoExclusive(true);
        ui->threeStrandDeckRadioButton->setAutoExclusive(true);
        ui->fourStrandDeckRadioButton->setAutoExclusive(true);
        ui->noDeckRadioButton->setAutoExclusive(true);
        ui->stdChainRadioButton->setAutoExclusive(true);
        ui->hdChainRadioButton->setAutoExclusive(true);
        ui->barRadioButton->setAutoExclusive(true);
        ui->camboxRadioButton->setAutoExclusive(true);
        ui->nanosetRadioButton->setAutoExclusive(true);
        ui->compsetRadioButton->setAutoExclusive(true);







    }

}


/*
 *
 *This will get a specified quotenumber from the Database using qdbMan
 *
 *
 */


void MainWindow::getQuote(int quoteNumber){
    uncheckOverrides();
    checkQuoteStatus();

    QSqlQuery qu;
    qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'status' AND quoteNum = "+QString::number(quoteNumber));
    qu.last();
    QString status = qu.value(3).toString();
    if(status == "Open"){
        ui->statusBox->setCurrentText("Open");
        ui->actionSetClosed->setChecked(false);
        ui->actionSetOpen->setChecked(true);

    }
    else if(status == "Closed"){
        ui->statusBox->setCurrentText("Closed");
        ui->actionSetClosed->setChecked(true);
        ui->actionSetOpen->setChecked(false);

    }
    else if(status == "Expired"){
        ui->statusBox->setCurrentText("Expired");
        ui->actionSetClosed->setChecked(false);
        ui->actionSetOpen->setChecked(false);

    }

    getConnections(quoteNumber,connectionsTo,connectionsFrom,i);
    Quote q = qdbMan.getQuote(quoteNumber);
    ui->dateEdit->setDate(QDate::fromString(q.date,"MM/dd/yyyy"));
    getOverrides();
    //qDebug() << "Set date of " << q.date << " on quote num " << q.quoteNum;

}

/*
 *
 * This function connects the radio buttons
 * and allows them to fill in "Default" values
 * when you check one.
 *
 *
 *
 */


void MainWindow::connectRadioButtons(void){//if radio button <- goes here for modifications

    ui->twoStrandDeckRadioButton->setEnabled(true);
    ui->threeStrandDeckRadioButton->setEnabled(true);
    ui->fourStrandDeckRadioButton->setEnabled(true);

    ui->magnumLTSetshaftradioButton->setEnabled(false);
    ui->magnumLTSetshaftradioButton->setChecked(false);

    if(ui->platform40RadioButton->isChecked() == true && ui->carriageKneesSpinBox->value() >= 2 && ui->carriageKneesSpinBox->value() >= 2){
        ui->carriageKneesSpinBox->setValue(2);
        ui->cantTurnersSpinBox->setValue(2);
        ui->cantTurnersSpinBox->setMaximum (2);




        ui->magnumLTSetshaftradioButton->setEnabled(true);




        ui->stdChainRadioButton->setChecked(true);
        ui->camboxRadioButton->setChecked(true);
        ui->magnumRadioButton->setChecked(true);
        //ui->wheelSizeCheckBox->setChecked(true);

        ui->fourStrandDeckRadioButton->setEnabled(false);


        if(ui->fourStrandDeckRadioButton->isChecked()){
            ui->twoStrandDeckRadioButton->setChecked(true);
        }




        if(!ui->twoStrandDeckRadioButton->isChecked() && !ui->threeStrandDeckRadioButton->isChecked() && !ui->fourStrandDeckRadioButton->isChecked() && !ui->noDeckRadioButton->isChecked()){
                    ui->twoStrandDeckRadioButton->setChecked(true);

               }



    }
    if(ui->platform48RadioButton->isChecked() == true && ui->carriageKneesSpinBox->value() >= 2){
        ui->carriageKneesSpinBox->setValue(3);
        ui->cantTurnersSpinBox->setValue(3);
        ui->cantTurnersSpinBox->setMaximum (3);

        ui->stdChainRadioButton->setChecked(true);
        ui->camboxRadioButton->setChecked(true);
        ui->magnumRadioButton->setChecked(true);
        ui->twoStrandDeckRadioButton->setEnabled(false);


        if(ui->twoStrandDeckRadioButton->isChecked()){
            ui->threeStrandDeckRadioButton->setChecked(true);
        }



        if(!ui->twoStrandDeckRadioButton->isChecked() && !ui->threeStrandDeckRadioButton->isChecked() && !ui->fourStrandDeckRadioButton->isChecked() && !ui->noDeckRadioButton->isChecked()){
                    ui->threeStrandDeckRadioButton->setChecked(true);

               }
    }
    if(ui->platform60RadioButton->isChecked() == true && ui->carriageKneesSpinBox->value() >= 2){
        ui->carriageKneesSpinBox->setValue(4);
        ui->cantTurnersSpinBox->setValue(4);
        ui->cantTurnersSpinBox->setMaximum (4);

        ui->stdChainRadioButton->setChecked(true);
        ui->camboxRadioButton->setChecked(true);
        ui->magnumRadioButton->setChecked(true);

        ui->twoStrandDeckRadioButton->setEnabled(false);
        ui->threeStrandDeckRadioButton->setEnabled(false);

        if(ui->twoStrandDeckRadioButton->isChecked() || ui->threeStrandDeckRadioButton->isChecked()){
            ui->fourStrandDeckRadioButton->setChecked(true);
        }


        if(!ui->twoStrandDeckRadioButton->isChecked() && !ui->threeStrandDeckRadioButton->isChecked() && !ui->fourStrandDeckRadioButton->isChecked() && !ui->noDeckRadioButton->isChecked()){
                    ui->fourStrandDeckRadioButton->setChecked(true);

               }

    }
    if(ui->platform52RadioButton->isChecked() == true && ui->carriageKneesSpinBox->value() >= 2){
        ui->carriageKneesSpinBox->setValue(3);
        ui->cantTurnersSpinBox->setValue(3);

        ui->stdChainRadioButton->setChecked(true);
        ui->camboxRadioButton->setChecked(true);
        ui->magnumRadioButton->setChecked(true);

        ui->twoStrandDeckRadioButton->setEnabled(false);

        if(ui->twoStrandDeckRadioButton->isChecked()){
            ui->fourStrandDeckRadioButton->setChecked(true);
        }


        if(!ui->twoStrandDeckRadioButton->isChecked() && !ui->threeStrandDeckRadioButton->isChecked() && !ui->fourStrandDeckRadioButton->isChecked() && !ui->noDeckRadioButton->isChecked()){
                    ui->threeStrandDeckRadioButton->setChecked(true);

               }

    }

    ui->brownsvilleSpinBox->setValue(ui->carriageKneesSpinBox->value());
    //both of these depends on knees and change as the knees change//
    ui->cantPushOffSpinBox->setValue(ui->carriageKneesSpinBox->value());

}

/*
 *
 * This allows the cant turner check box to properly update
 * the value when needed.
 *
 *
 */

void MainWindow::connectCheckBoxes(){


    if(ui->cantTurnersCheckBox->isChecked()){
        if(ui->platform40RadioButton->isChecked()){
            ui->cantTurnersSpinBox->setValue(2);
        }
        if(ui->platform48RadioButton->isChecked()){
            ui->cantTurnersSpinBox->setValue(3);
        }
        if(ui->platform52RadioButton->isChecked()){
            ui->cantTurnersSpinBox->setValue(3);
        }
        if(ui->platform60RadioButton->isChecked()){
            ui->cantTurnersSpinBox->setValue(4);
        }

    }


    /*
     * DEPENDENCIES UNDER THIS LINE.
     */

    if(ui->linearCheckBox->isChecked()){
        ui->linearCompSetworksCheckBox->setEnabled(true);
    }
    else{
        ui->linearCompSetworksCheckBox->setEnabled(false);
        ui->linearCompSetworksCheckBox->setChecked(false); //if it is checked when disabled, set it to an unchecked state so the system does not count it.
    }

    if(ui->tabWidget->currentIndex() == 1){






        if(sender()->objectName() == "magnumLTCheckBox" && isToggled == 0){

            isToggled = 1;


          //  qDebug() << "LT Checkbox";
            ui->magnumLTCheckBox->setCheckable(true);
            ui->magnumLPCheckBox->setChecked(false);
            ui->carriageLPFortyTwoInchKneeOpeningsRadioButton->setAutoExclusive(false);
            ui->carriageLPFortyEightInchKneeOpeningsRadioButton->setAutoExclusive(false);
            ui->carriageLPFortyEightInchKneeOpeningsRadioButton->setChecked(false);
            ui->carriageLPFortyTwoInchKneeOpeningsRadioButton->setChecked(false);
            ui->carriageLPFortyEightInchKneeOpeningsRadioButton->setEnabled(false);
            ui->carriageLPFortyTwoInchKneeOpeningsRadioButton->setEnabled(false);
            ui->carriageLPFortyTwoInchKneeOpeningsRadioButton->setAutoExclusive(true);
            ui->carriageLPFortyEightInchKneeOpeningsRadioButton->setAutoExclusive(true);
            ui->carriageLPSixtyRailCheckBox->setEnabled(false);
            ui->carriageLTFortyRailCheckBox->setEnabled(true);


            ui->carriageSetShaftRadioButton->setEnabled(true);
            ui->carriageLinearRadioButton->setEnabled(true);


        isToggled = 0;





        }



         if(sender()->objectName() == "magnumLPCheckBox" && isToggled == 0){
             isToggled = 1;









         //   qDebug() << "LP Checkbox";
            ui->magnumLPCheckBox->setCheckable(true);
            ui->magnumLTCheckBox->setChecked(false);
            ui->carriageSetShaftRadioButton->setAutoExclusive(false);
            ui->carriageLinearRadioButton->setAutoExclusive(false);
            ui->carriageSetShaftRadioButton->setChecked(false);
            ui->carriageLinearRadioButton->setChecked(false);

            ui->carriageSetShaftRadioButton->setEnabled(false);
            ui->carriageLinearRadioButton->setEnabled(false);

            ui->carriageSetShaftRadioButton->setAutoExclusive(true);
            ui->carriageLinearRadioButton->setAutoExclusive(true);
            ui->carriageLTFortyRailCheckBox->setEnabled(false);
            ui->carriageLPSixtyRailCheckBox->setEnabled(true);

            ui->carriageLPFortyTwoInchKneeOpeningsRadioButton->setEnabled(true);
            ui->carriageLPFortyEightInchKneeOpeningsRadioButton->setEnabled(true);

            isToggled = 0;


         //   qDebug() << ui->magnumLPCheckBox->isChecked();




        }


    }







        }




/*
 *
 * Displays the version string found in the header file.
 *
 */

void MainWindow::displayVersion(){

    QMessageBox::information(this, tr("Quote Generator"), tr("Hurdle Machine Works\nQuote Generator Client\nVersion 2 \n Project Overseer: Jeff Hurdle \n Created By: Colson Sutton \n Completed By:BJ Dunson") );

}


/*
 *
 * This functionc calls the qdbManager, grabs the quote that is found
 * on the screen, and then prints it using quotePDFMager. Passes the priceArray and pIndex variable
 * to the PDF manager for dynamic pricing.
 *
 */
void MainWindow::printPDF(){

    accept();
  //  QString arr[100];

  //  for(int g = 0; g < list.count();g++){
   //     arr[g] = list.at(g);

  //  }



    if(ui->nameLineEdit->text() == " " || ui->nameLineEdit->text() == ""){
            return;
    }

    if((ui->emailLineEdit->text() != "" && ui->emailLineEdit->text() != " ") || (ui->phoneLineEdit->text() != " " && ui->phoneLineEdit->text() != "") || (ui->phone2LineEdit->text() != "" && ui->phone2LineEdit->text() != " ") ){

    }
    else{
        return;
    }

    QList<QString> list = applyCheckedItems();

    Quote q;
    q = qdbMan.getQuote(ui->quoteNumLineEdit->text().toInt());

    qPDF.updateLength(length);
    qPDF.updateArray(qP.getArray());
    int tPrice = qP.getTotalPrice();
    qPDF.updateTotalPrice(tPrice);


   // setConnections(connectionsFrom, connectionsTo,i);
  //  qPDF.print(ui->quoteNumLineEdit->text().toInt(),q,priceArray,pIndex);


   // QString fileName = QFileDialog::getSaveFileName(this,
          //  tr("Save PDF"), "",
         //   tr("PDF (*.pdf)"));

    QString fileName = "";
   // qDebug() << "Name is " << ui->nameLineEdit->text();

    if(ui->nameLineEdit->text() != ""){
        fileName = fileName + ui->nameLineEdit->text() + " Quote " + ui->quoteNumLineEdit->text();
    }

    if(ui->companyNameLineEdit->text() != ""){
        fileName = fileName+"-"+ ui->companyNameLineEdit->text();
    }

    fileName = fileName+"-"+ui->dateEdit->date().toString("MM-dd-yy");



        //qDebug() << fileName;

    qPDF.print(ui->quoteNumLineEdit->text().toInt(),q,list,list.count(),fileName);

    //qDebug() << "Generated!";


}

/*
 *
 * Allows the user to specify a save location for their quotes. Remembers this on exit too,
 * by storing the path in a file in the build directory.
 *
 *
 */
void MainWindow::changeSaveLocation(){
    QString saveName = QFileDialog::getExistingDirectory(this, tr("Change Save Location"),
                               QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));

    qPDF.updateLocation(saveName);
  //  qDebug() << "file location updated to " << saveName;

}

/*
 * This will allow the user to
 * choose whether to print the entire
 * HMW packet or not.
 *
 *NOT USED - FEATURE NOT YET AVAILABLE
 */
void MainWindow::promptPacketPrint(){

      QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Print Entire Packet?", "Quote",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
      //  qDebug() << "Yes was clicked";
        QApplication::quit();
      } else {
      //  qDebug() << "Yes was *not* clicked";
      }

}

/*
 * Formats string based on the parameter passed
 *
 */

void MainWindow::formatText(){

        int numberOfCharacters = ui->phoneLineEdit->text().count(); //long variable names, what is this? Apple?
      //   qDebug() << "Number of Characters: " << numberOfCharacters;
        if(numberOfCharacters == 10 && ui->phoneLineEdit->text().contains(QRegExp("^[0-9]"))){ //9012860096...

            QString phone = ui->phoneLineEdit->text();
            QString firstThree = phone.mid(0,3);
            QString middleThree = phone.mid(3,3);
            QString lastFour = phone.mid(6,4);
           // qDebug() << firstThree << middleThree << lastFour;
            QString newString = firstThree.left(0).append("(") + firstThree.right(3).append(")") + middleThree.right(7).append("-")+phone.mid(6,4);
          //  qDebug() << newString;
            ui->phoneLineEdit->setText(newString);


    }
        int numberOfCharacters2 = ui->phone2LineEdit->text().count(); //long variable names, what is this? Apple?
       //  qDebug() << "Number of Characters: " << numberOfCharacters2;
        if(numberOfCharacters2 == 10 && ui->phone2LineEdit->text().contains(QRegExp("^[0-9]"))){ //9012860096...

            QString phone = ui->phone2LineEdit->text();
            QString firstThree = phone.mid(0,3);
            QString middleThree = phone.mid(3,3);
            QString lastFour = phone.mid(6,4);
            //qDebug() << firstThree << middleThree << lastFour;
            QString newString = firstThree.left(0).append("(") + firstThree.right(3).append(")") + middleThree.right(7).append("-")+phone.mid(6,4);
            //qDebug() << newString;
            ui->phone2LineEdit->setText(newString);


    }
        int numberOfCharacters3 = ui->faxLineEdit->text().count(); //long variable names, what is this? Apple?
         //qDebug() << "Number of Characters: " << numberOfCharacters;
        if(numberOfCharacters3 == 10 && ui->faxLineEdit->text().contains(QRegExp("^[0-9]"))){ //9012860096...

            QString phone = ui->faxLineEdit->text();
            QString firstThree = phone.mid(0,3);
            QString middleThree = phone.mid(3,3);
            QString lastFour = phone.mid(6,4);
           // qDebug() << firstThree << middleThree << lastFour;
            QString newString = firstThree.left(0).append("(") + firstThree.right(3).append(")") + middleThree.right(7).append("-")+phone.mid(6,4);
           // qDebug() << newString;
            ui->faxLineEdit->setText(newString);


    }

}

/*
 *
 * Detects when a quote is closed or open.
 * If it is closed, it will disable all fields
 * until reopened.
 *
 * Note: Expired has the same behavior as closed.
 *
 *
 */

void MainWindow::changeQuoteStatus(){

    if(ui->statusBox->currentText() == "Closed" || ui->statusBox->currentText() == "Expired"){

        QList<QLineEdit*> lineEditList = MainWindow::findChildren<QLineEdit*>(); //find all the line edits.
        QList<QRadioButton*> radioButtonList = MainWindow::findChildren<QRadioButton*>(); //find all the line edits.
        QList<QCheckBox*> checkBoxList = MainWindow::findChildren<QCheckBox*>(); //find all the line edits.
        QList<QSpinBox*> spinBoxList = MainWindow::findChildren<QSpinBox*>();
        QList<QComboBox*> comboBoxList = MainWindow::findChildren<QComboBox*>();



        for(int i = 0;i<lineEditList.count();i++){
            if(lineEditList.at(i)->objectName() != "quoteNumLineEdit"){ //never disable the quote number form
                lineEditList.at(i)->setReadOnly(true);
            }
        }
        for(int i = 0;i<radioButtonList.count();i++){
            radioButtonList.at(i)->setEnabled(false);
        }
        for(int i = 0;i<checkBoxList.count();i++){
            checkBoxList.at(i)->setEnabled(false);
        }
        for(int i = 0;i<spinBoxList.count();i++){
            spinBoxList.at(i)->setReadOnly(true);
        }
        for(int i = 0;i<comboBoxList.count();i++){

            comboBoxList.at(i)->setEnabled(false);
        }




    }
    if(ui->statusBox->currentText() == "Open"){




        ui->dateEdit->setDate(QDate::currentDate());
        QList<QLineEdit*> lineEditList = MainWindow::findChildren<QLineEdit*>(); //find all the line edits.
        QList<QRadioButton*> radioButtonList = MainWindow::findChildren<QRadioButton*>(); //find all the line edits.
        QList<QCheckBox*> checkBoxList = MainWindow::findChildren<QCheckBox*>(); //find all the line edits.
        QList<QSpinBox*> spinBoxList = MainWindow::findChildren<QSpinBox*>();
        QList<QComboBox*> comboBoxList = MainWindow::findChildren<QComboBox*>();



        for(int i = 0;i<lineEditList.count();i++){
            lineEditList.at(i)->setReadOnly(false);
        }
        for(int i = 0;i<radioButtonList.count();i++){
            radioButtonList.at(i)->setEnabled(true);
        }
        for(int i = 0;i<checkBoxList.count();i++){
            checkBoxList.at(i)->setEnabled(true);
        }
        for(int i = 0;i<spinBoxList.count();i++){
            spinBoxList.at(i)->setReadOnly(false);
        }
        for(int i = 0;i<comboBoxList.count();i++){
            if(comboBoxList.at(i)->objectName() != "statusBox"){
                comboBoxList.at(i)->setEnabled(true);
            }
        }


    }


}

/*
 * Checks the status of each quote. If the quote is expired
 * by 30 days, then it will notify the user.
 * Once the user hits okay, they will not be notified of
 * the "past" expired quotes. However, once a new quote
 * becomes expired, they will be reminded of that one again.

 *
 *
 */
void MainWindow::checkQuoteStatus(){
    //qDebug() << "Running date check";
    int quotesExpired[qdbMan.getNumQuotes()];
    int numOfQuotesExpired = 0;
    for(int i = 1; i<qdbMan.getNumQuotes(); i++){
        Quote q = qdbMan.getQuote(i);
        QDate quoteDate = QDate::fromString(q.date, "MM/dd/yyyy");
        int status = 0;
        QSqlQuery qu;
         qu.exec("SELECT * FROM quoteTable WHERE quoteNum = "+QString::number(i)+" AND connectionName = 'status'");
        qu.last();
        //qDebug() << "value: " << qu.value(3).toString();
        if(qu.value(3).toString() == "Open"){
            status = 0;
        }
        else{
            status = 1;
        }
        QDate currentDate = QDate::currentDate();
       // qDebug() << "status; " << status;
      //qDebug() << "Comparing " << quoteDate << " to " << currentDate;
        if(quoteDate != currentDate){
            //qDebug() << "Checking for date of: " << currentDate.addDays(-30).toString();

            if(quoteDate < currentDate.addDays(-30)  && status == 0){ //only if quote is OPEN
               // qDebug() << "Quote: "<<q.quoteNum << " is expired! ";
                QSqlQuery query;

                //q.status = 2;
                query.prepare("UPDATE quoteTable SET value=:statusQuote WHERE quoteNum=:quoteNum AND connectionName = 'status';");
                query.bindValue(":statusQuote","Expired");
                query.bindValue(":quoteNum",q.quoteNum);
               // qDebug() << "status: " << query.exec();
                quotesExpired[q.quoteNum] = 1;
                numOfQuotesExpired++;
            }
        }
    }

    QString expiredString = "";
    if(numOfQuotesExpired > 1){
        //qDebug() << "You have " << numOfQuotesExpired << " quotes expired! ";
        expiredString+="You have " +QString::number(numOfQuotesExpired)+ " quotes expired!";

    }
    else if(numOfQuotesExpired == 1){
       //qDebug() << "You have " << numOfQuotesExpired << " quote expired ";
        expiredString+="You have " +QString::number(numOfQuotesExpired)+ " quote expired!";

    }
    else{
      // qDebug() << "You have no  quotes expired ";
    }
    bool showString = false;


    if(numOfQuotesExpired > 0){
     expiredString+= "\nQuotes {";
    }
    else{
        expiredString = "";
    }

    int quoteExpired = 0;
    for(int i = 1; i<qdbMan.getNumQuotes();i++){
        //qDebug() << quotesExpired[i] << "num expired: " << numOfQuotesExpired << "Handled? : " << qdbMan.getQuote(i).handled;

        if(quotesExpired[i] == 1){
            quoteExpired++;
            //qDebug() << "Entered first if";
            //qDebug() << "i is " << i << " numQuotesExpired = " << numOfQuotesExpired;
            if(quoteExpired < numOfQuotesExpired && qdbMan.getQuote(i).handled == 0){
                //qDebug() << "Enter if";
            expiredString+=""+QString::number(qdbMan.getQuote(i).quoteNum)+ ",";

            showString = true;
            }

            else if(quoteExpired  == numOfQuotesExpired && qdbMan.getQuote(i).handled == 0){
               // qDebug() << "Enter else if";
                showString = true;
                expiredString+=""+QString::number(qdbMan.getQuote(i).quoteNum)+ "}";
            }

        }
    }


        expiredString+=" are expired! ";

   //qDebug() << expiredString;
    if(numOfQuotesExpired > 0 && showString == true){
    QMessageBox::StandardButton reply;

      reply = QMessageBox::question(this, tr("Expired Quotes!"), expiredString,
                                    QMessageBox::Ok|QMessageBox::Cancel);
      if (reply == QMessageBox::Yes) {
        //qDebug() << "Ok was clicked";
        getQuote(ui->quoteNumLineEdit->text().toInt());
        QApplication::quit();
      } else {
        //qDebug() << "Cancelled was clicked";
      }


      for(int i = 1; i<qdbMan.getNumQuotes();i++){
          if(quotesExpired[i] == 1){
               Quote q = qdbMan.getQuote(i);
              q.handled = 1;
              qdbMan.buildQuote(q);

          }
      }
    }

}

/*
 *
 *
 * Filters the quotes by the specified option.
 * Therefore, "Open" shows all Open Quotes, Closed, Expired
 * do the same thing respectively.
 *
 * Note: When selecting a new filter, the Quote Generator finds the first quote matching
 * that filter type. Therfore, if Quote 1 = Open and Quote 2 = Closed, and you are on Quote 7
 * and filter by Closed, the quote generator will jump to Quote 2.
 *
 *
 */


void MainWindow::quoteFilterMenuSelection(){
    //qDebug() << "Triggered" << sender();
    int numQuotes = qdbMan.getNumQuotes();
    if(numQuotes > 1){
        if(sender()->objectName() == "actionFilterOpen"){
            ui->actionFilterAll->setChecked(false);
            ui->actionFilterClosed->setChecked(false);
            ui->actionFilterExpired->setChecked(false);
            //find the first open quote and be able to iterate through them
            Quote q;
            for(int i = 1; i<qdbMan.getNumQuotes() ;i++){
                q = qdbMan.getQuote(i);
                QSqlQuery qu;
                qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'status' AND quoteNum = " +QString::number(i));
                qu.last();
                QString status = qu.value(3).toString();
               // qDebug() << "OPEN STATUS : " << status << "numQuotes " << qdbMan.getNumQuotes() << " quote num : " << i;
                if(status == "Open"){
                    getQuote(q.quoteNum);
                    break;

                }
                if(i == qdbMan.getNumQuotes() - 1){
                    QMessageBox::information(this, tr("Cannot Find Filter Type!"), tr("No Open Quotes!"));
                    ui->actionFilterAll->setChecked(true);
                    break;
                }
            }

        }
        if(sender()->objectName() == "actionFilterClosed"){
            ui->actionFilterAll->setChecked(false);
            ui->actionFilterOpen->setChecked(false);
            ui->actionFilterExpired->setChecked(false);
            //find the first open quote and be able to iterate through them
            Quote q;
            for(int i = 1; i<qdbMan.getNumQuotes() ;i++){
                q = qdbMan.getQuote(i);
                QSqlQuery qu;
                qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'status' AND quoteNum = " +QString::number(i));
                qu.last();
                QString status = qu.value(3).toString();
                if(status == "Closed"){
                    getQuote(q.quoteNum);
                    break;

                }
                if(i == qdbMan.getNumQuotes() - 1){
                    QMessageBox::information(this, tr("Cannot Find Filter Type!"), tr("No Closed Quotes!"));
                    ui->actionFilterAll->setChecked(true);
                    break;
                }
            }


        }
        if(sender()->objectName() == "actionFilterExpired"){
            ui->actionFilterAll->setChecked(false);
            ui->actionFilterClosed->setChecked(false);
            ui->actionFilterOpen->setChecked(false);
            //find the first open quote and be able to iterate through them
            Quote q;
            for(int i = 1; i<qdbMan.getNumQuotes() ;i++){
                QSqlQuery qu;
                qu.exec("SELECT * FROM quoteTable WHERE connectionName = 'status' AND quoteNum = " +QString::number(i));
                qu.last();
                QString status = qu.value(3).toString();
                q = qdbMan.getQuote(i);
                if(status == "Expired"){
                    getQuote(q.quoteNum);
                    break;

                }
                if(i == qdbMan.getNumQuotes() - 1){
                    QMessageBox::information(this, tr("Cannot Find Filter Type!"), tr("No Expired Quotes!"));
                    ui->actionFilterAll->setChecked(true);
                    break;
                }
            }



        }
        if(sender()->objectName() == "actionFilterAll"){

            ui->actionFilterOpen->setChecked(false);
            ui->actionFilterClosed->setChecked(false);
            ui->actionFilterExpired->setChecked(false);
            //find the first open quote and be able to iterate through them
            getQuote(1);
        }

    }
    else{
        QMessageBox::information(this, tr("Invalid!"), tr("No Quotes Available to Search!"));
    }


}

/*
 *
 * Displays the completion date box to allow the user to change the completion date.
 * The date displayes is the current date + 32 days on startup.
 * However, this value is saved in a file, and the user can change the specified date if they want.
 * Once the specified date is 10 days greater than or equal to the current date,
 * the specified date s to 33 days after the current date. Therfore, keeping
 * a nice completion date.
 *
 *
 */

void MainWindow::showCompDateBox(){
    bool ok;
    quotePDFManager qPDF;
    qDebug() << qPDF.getCompletionDate().toString("MM/dd/yyyy");
    QString prompt = "Enter New Date (mm/dd/yyyy)";
    QString text = QInputDialog::getText(0, "Completion Date","Current Completion Date: "+qPDF.getCompletionDate().toString("MM/dd/yyyy"),QLineEdit::Normal,prompt,&ok);
    if(ok == true && (text != prompt && prompt != "" && prompt != " ")){
       // qDebug() << text << QDate::fromString(text,"MM/dd/yyyy");
        if(QDate::fromString(text,"MM/dd/yyyy").toString() == ""){
            QMessageBox::information(this, tr("Invalid Date!"), tr("Please enter a valid date in the following format: mm/dd/yyyy"));
        }
        else{

            qPDF.updateCompletionDate(QDate::fromString(text,"MM/dd/yyyy"));
           // qDebug() << "Date updated! " << QDate::fromString(text,"MM/dd/yyyy");
           // qDebug() << qPDF.getCompletionDate().toString("MM/dd/yyyy");
        }
    }


}

/*
 *
 *
 * Changes the status of the quote
 * by allowing selection from the menu.
 *
 *
 */

void MainWindow::quoteMenuSelection(){
   // qDebug() << "Triggered" << sender();
    if(sender()->objectName() == "actionSetClosed"){
        //qDebug() << "Closing";
        ui->statusBox->setCurrentText("Closed");
        //ui->actionSetOpen->setChecked(false);

        MainWindow::findChild<QAction*>("actionSetOpen")->setChecked(false);

    }
    else{
        if(sender()->objectName() == "actionSetOpen"){
           // qDebug() << "Opened";
            ui->statusBox->setCurrentText("Open");
            //ui->actionSetClosed->setChecked(false);
            MainWindow::findChild<QAction*>("actionSetClosed")->setChecked(false);
        }
    }
    accept();
}


/*
 *
 * Connects the override function.
 *
 */

void MainWindow::connectOverrideFunctions(){
    //qDebug() << "OBJECT : " << sender()->objectName();
    //qDebug() << MainWindow::findChild<QAction*>(sender()->objectName())->objectName();
    if(((QAction*) sender())->isChecked()){
        //qDebug() << "is checked...";
        QStringList splitted = sender()->objectName().split("action");
        QString newText = splitted.at(1); //grab the part for the connectionName.

        QSqlQuery q2;
        QSqlQuery q3;

        q2.exec("SELECT * FROM quoteTable WHERE quoteNum = " + QString::number(ui->quoteNumLineEdit->text().toInt()) + " AND connectionName='"+newText+"'");
        q2.last();
        int quoteNum = q2.value(0).toInt();
        QString name = q2.value(1).toString();
        QString connectionName = q2.value(2).toString();

        //qDebug() << "q3 running " << q3.exec("SELECT * FROM quoteTable WHERE quoteNum = " + QString::number(ui->quoteNumLineEdit->text().toInt()) + " AND connectionName='"+newText+"'");


        QSqlQuery q6;
        q6.exec("SELECT * FROM quoteOverrides WHERE quoteNum = "+QString::number(ui->quoteNumLineEdit->text().toInt())+ " AND connectionName = '"+newText+"'");
        q6.last();
        if(q6.value(2).toString() != newText){
           // qDebug() << "No match between " << q6.value(2).toString() << " and " << newText;
            q3.prepare("INSERT INTO quoteOverrides VALUES (:quoteNum, :name, :connectionName) ");
            q3.bindValue(":quoteNum",quoteNum);
            q3.bindValue(":name",name);
            q3.bindValue(":connectionName",connectionName); //grab the connectionName for pricing.
            //qDebug() << "Running q3 " << q3.exec();
            q3.exec();
        }
        else{
            qDebug() << "a database entry already exists with this value.";
        }
    }
    else{ //if unchecked...
       // qDebug() << "unchecked.. ";
        QStringList splitted = sender()->objectName().split("action");
        QString newText = splitted.at(1); //grab the part for the connectionName.
        QSqlQuery q6;
        q6.exec("DELETE FROM quoteOverrides WHERE quoteNum = "+QString::number(ui->quoteNumLineEdit->text().toInt())+ " AND connectionName = '"+newText+"'");
    }







}

/*
 *
 * Clears all checks when new quote is generated.
 *
 *
 */
void MainWindow::uncheckOverrides(){



    QList<QAction*> actionList = MainWindow::findChildren<QAction*>();

    for(int j = 0; j< i; j++){
        for(int y = 0; y<actionList.length(); y++){
            if("action"+connectionsTo[j] == actionList.at(y)->objectName()){
                //qDebug() << "CHECKING " << actionList.at(y)->objectName();
                actionList.at(y)->setChecked(false);
            }
        }
    }




}


void MainWindow::checkOverrides(){

    QList<QAction*> actionList = MainWindow::findChildren<QAction*>();

    for(int j = 0; j< i; j++){
        for(int y = 0; y<actionList.length(); y++){
            if("action"+connectionsTo[j] == actionList.at(y)->objectName()){
                //qDebug() << "CHECKING " << actionList.at(y)->objectName();
                actionList.at(y)->setChecked(true);
            }
        }
    }





}

void MainWindow::getOverrides(){

    QList<QAction*> actionList = MainWindow::findChildren<QAction*>();
    for(int h = 0; h < i ; h++){
        for(int k = 0; k < actionList.length(); k++){
            QString name = "action"+connectionsTo[h];
            if(name == actionList.at(k)->objectName() ){
                //qDebug() << "FOUND A MATCH";
                QStringList splitted = actionList.at(k)->objectName().split("action");
                QString newText = splitted.at(1);
                QSqlQuery q2;
                q2.exec("SELECT * FROM quoteOverrides WHERE quoteNum = " + QString::number(ui->quoteNumLineEdit->text().toInt()) + " AND connectionName='"+newText+"'");
                if(q2.last()){
                    actionList.at(k)->setChecked(true);
                   // qDebug() << " is checked? : " << actionList.at(k)->isChecked();
                }

          }
       }
    }

}




/*
 *
 * Loads the connections file that is placed on the desktop. Once loaded,
 * this builds the standard connections between the object names and the
 * names in the databases. If you add a new object,
 * just add the name : databaseName in the connections file
 * and the program will take care of the rest.
 *
 *
 */


void MainWindow::loadConnectionFile(){

    //int i = 0;
    QFile file(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+"/connections");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Connections File Doesn't Exist";
    }
    if(QFileInfo(file).exists()){
      //  qDebug()<< "Save file exists";
        QTextStream in(&file);

        while(!in.atEnd()){
            QString line = in.readLine();
            //qDebug() << line;
             QStringList splitted = line.split(":");
           // qDebug() << splitted;
            //qDebug() << splitted.at(0) << splitted.at(1);
             connectionsFrom[i] = splitted.at(0);
             connectionsTo[i] = splitted.at(1);
             i++;
        }
        file.close();

    }
/*
    for(int j = 0; j<i;j++){
        qDebug() << "Connections to [" << j << "] : " << connectionsTo[j];
        qDebug() << "Connections from [" << j << "] : " << connectionsFrom[j];

    } */

}


/*

void MainWindow::loadConnectionFile(){

    //Let's search through the MainUI and find all the elements, adding them to the file.

    QObjectList list = ui->centralWidget->children();
    qDebug() << "found " << list.count();
    int interator = 0;

    connectionsFrom[iterator] = list.at(iterator)->objectName();

    //No more connections file needed.
    qu.exec("SELECT * FROM quoteItems"); //grab all of the items in quote items.
    while(qu.next()){ //while there is a next object to grab.
        qDebug() << "Grabbing: " << qu.value(0);
        connectionsFrom[i] = splitted.at(0);
        connectionsTo[i] = splitted.at(1);

    }




}
*/















/*
 *
 * Sets the connections in the arrays.
 *
 *
 */


void MainWindow::setConnections(QString array[], QString connectionArray[], int index){
    //qDebug() << "Set running";
    updateCurrentQuote(ui->quoteNumLineEdit->text().toInt());
    for(int i = 0; i < index ; i++){
        //qDebug() << "Index is : " << index << " i is : " << i << "i @ index is " << array[i];
       // QList<QLineEdit*> lineEditList = MainWindow::findChildren<QLineEdit*>();
        if(MainWindow::findChild<QCheckBox *>(array[i])){
            //qDebug() << "Found Child with name: " << MainWindow::findChild<QCheckBox*>(array[i])->objectName() << " and type of CheckBox";
            QString lineToSplit = MainWindow::findChild<QCheckBox *>(array[i])->objectName();
            QStringList list = lineToSplit.split("CheckBox");
            //qDebug() << "Split name is " << list.at(0);
            //qDebug() << "Appending spinbox..... " << list.at(0)+"SpinBox";
            if(MainWindow::findChild<QSpinBox *>(list.at(0)+"SpinBox")){
                if(MainWindow::findChild<QCheckBox *>(array[i])->isChecked()){
                  // qDebug() << "Child is checked with SpinBox value!";
                    QSqlQuery qu;

                    qu.prepare("INSERT INTO quoteTable VALUES (:quoteNum, :name, :connectionName, :value) ");
                    qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
                    qu.bindValue(":name",array[i]);
                    qu.bindValue(":connectionName",connectionArray[i]); //grab the connectionName for pricing.
                    qu.bindValue(":value",MainWindow::findChild<QSpinBox *>(list.at(0)+"SpinBox")->value());
                   qu.exec();
                }
            }
            //Here we insert into the new SQL database, if checked, and then go from there. This makes life easier...
            else if(MainWindow::findChild<QCheckBox *>(array[i])->isChecked()){
               // qDebug() << "Child is checked!";
                QSqlQuery qu;
                qu.prepare("INSERT INTO quoteTable VALUES (:quoteNum, :name, :connectionName, :value) ");
                qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
                qu.bindValue(":name",array[i]);
                qu.bindValue(":connectionName",connectionArray[i]); //grab the connectionName for pricing.
                qu.bindValue(":value",1);
                 qu.exec();







            }

        }
        else if(MainWindow::findChild<QRadioButton*>(array[i])){
            //qDebug() << "Found Child with name: " << MainWindow::findChild<QRadioButton*>(array[i])->objectName() << " and type of RadioButton";
            //Here we insert into the new SQL database, if checked, and then go from there. This makes life easier...
            if(MainWindow::findChild<QRadioButton *>(array[i])->isChecked()){
              //  qDebug() << "CHILD IS CHECKED!";
                QSqlQuery qu;
                qu.prepare("INSERT INTO quoteTable VALUES (:quoteNum, :name, :connectionName, :value) ");
                qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
                qu.bindValue(":name",array[i]);
                qu.bindValue(":connectionName",connectionArray[i]); //grab the connectionName for pricing.
                qu.bindValue(":value",1);
                qu.exec();
            }

        }
        else if(MainWindow::findChild<QLineEdit*>(array[i])){
          //qDebug() << "Found Child with name: " << MainWindow::findChild<QLineEdit*>(array[i])->objectName() << " and type of Line Edit";
            //Here we insert into the new SQL database, if checked, and then go from there. This makes life easier...
            if(MainWindow::findChild<QLineEdit *>(array[i])->text().compare("") != 0  && MainWindow::findChild<QLineEdit *>(array[i])->text().compare(" ") != 0){
                //qDebug() << "Line Edit is not blank!";
                QSqlQuery qu;
                qu.prepare("INSERT INTO quoteTable VALUES (:quoteNum, :name, :connectionName, :value) ");
                qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
                qu.bindValue(":name",array[i]);
                qu.bindValue(":connectionName",connectionArray[i]); //grab the connectionName for pricing.
                qu.bindValue(":value",MainWindow::findChild<QLineEdit*>(array[i])->text());
               // qDebug() << "adding to database: " << array[i] << " with connectionName: " << connectionArray[i];

               qu.exec();

            }

        }
        else if(MainWindow::findChild<QDateEdit*>(array[i])){
        //   qDebug() << "Found Child with name: " << MainWindow::findChild<QDateEdit*>(array[i])->objectName() << " and type of Date Edit";
            //Here we insert into the new SQL database, if checked, and then go from there. This makes life easier...
            if(MainWindow::findChild<QDateEdit *>(array[i])->date().toString("MM/dd/yyyy").compare("") != 0){
                //qDebug() << "Date Edit is not blank!";
                QSqlQuery qu;
                qu.prepare("INSERT INTO quoteTable VALUES (:quoteNum, :name, :connectionName, :value) ");
                qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
                qu.bindValue(":name",array[i]);
                qu.bindValue(":connectionName",connectionArray[i]); //grab the connectionName for pricing.
                qu.bindValue(":value",MainWindow::findChild<QDateEdit*>(array[i])->date().toString("MM/dd/yyyy"));
               qu.exec();
            }

        }
        else if(MainWindow::findChild<QPlainTextEdit*>(array[i])){
          //qDebug() << "Found Child with name: " << MainWindow::findChild<QPlainTextEdit*>(array[i])->objectName() << " and type of Plain Text Edit";
           // Here we insert into the new SQL database, if checked, and then go from there. This makes life easier...
            if(MainWindow::findChild<QPlainTextEdit *>(array[i])->toPlainText() != ""){
               // qDebug() << "QPlainTextEdit is not blank!";
                QSqlQuery qu;

                qu.prepare("INSERT INTO quoteTable VALUES (:quoteNum, :name, :connectionName, :value) ");
                qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
                qu.bindValue(":name",array[i]);
                qu.bindValue(":connectionName",connectionArray[i]); //grab the connectionName for pricing.
                qu.bindValue(":value",MainWindow::findChild<QPlainTextEdit*>(array[i])->toPlainText());
                qu.exec();
            }

        }
        else if(MainWindow::findChild<QComboBox*>(array[i])){
          //qDebug() << "Found Child with name: " << MainWindow::findChild<QComboBox*>(array[i])->objectName() << " and type of Combo Box";
            //Here we insert into the new SQL database, if checked, and then go from there. This makes life easier...
            if(MainWindow::findChild<QComboBox *>(array[i])->currentText().compare("") != 0){
               // qDebug() << "ComboBox!";
                QSqlQuery qu;
                qu.prepare("INSERT INTO quoteTable VALUES (:quoteNum, :name, :connectionName, :value) ");
                qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
                qu.bindValue(":name",array[i]);
                qu.bindValue(":connectionName",connectionArray[i]); //grab the connectionName for pricing.
                qu.bindValue(":value",MainWindow::findChild<QComboBox*>(array[i])->currentText());
                qu.exec();
            }

        }
        else if(MainWindow::findChild<QSpinBox*>(array[i])){
          // qDebug() << "Found Child with name: " << MainWindow::findChild<QComboBox*>(array[i])->objectName() << " and type of Combo Box";
            //Here we insert into the new SQL database, if checked, and then go from there. This makes life easier...
            if(MainWindow::findChild<QSpinBox *>(array[i])->value() != 0){
               // qDebug() << "ComboBox!";
                QSqlQuery qu;
                qu.prepare("INSERT INTO quoteTable VALUES (:quoteNum, :name, :connectionName, :value) ");
                qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
                qu.bindValue(":name",array[i]);
                qu.bindValue(":connectionName",connectionArray[i]); //grab the connectionName for pricing.
                qu.bindValue(":value",MainWindow::findChild<QSpinBox*>(array[i])->value());
                qu.exec();
            }
        }
    }


    if(ui->createdByLabel->text() != ""){
        QString createdBy = ui->createdByLabel->text();
        QString lineToSplit = createdBy;
        QStringList list = lineToSplit.split("Created By: ");
        QSqlQuery qu;
        qu.prepare("INSERT INTO quoteTable VALUES (:quoteNum, :name, :connectionName, :value) ");
        qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
        qu.bindValue(":name","createdByConnection");
        qu.bindValue(":connectionName","createdBy"); //grab the connectionName for pricing.
        qu.bindValue(":value",list.at(1));
        qu.exec();
    }

    else{
        QSqlQuery qu;
        qu.prepare("INSERT INTO quoteTable VALUES (:quoteNum, :name, :connectionName, :value) ");
        qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
        qu.bindValue(":name","createdByConnection");
        qu.bindValue(":connectionName","createdBy"); //grab the connectionName for pricing.
        qu.bindValue(":value",loginName);
        qu.exec();
    }















}


void MainWindow::setTemporaryConnections(QString array[], QString connectionArray[], int index){  //real time display for pricing
    //qDebug() << "Set running";
    //updateCurrentQuote(ui->quoteNumLineEdit->text().toInt());
    for(int i = 0; i < index ; i++){
        //qDebug() << "Index is : " << index << " i is : " << i << "i @ index is " << array[i];
       // QList<QLineEdit*> lineEditList = MainWindow::findChildren<QLineEdit*>();
        if(MainWindow::findChild<QCheckBox *>(array[i])){
            //qDebug() << "Found Child with name: " << MainWindow::findChild<QCheckBox*>(array[i])->objectName() << " and type of CheckBox";
            QString lineToSplit = MainWindow::findChild<QCheckBox *>(array[i])->objectName();
            QStringList list = lineToSplit.split("CheckBox");
            //qDebug() << "Split name is " << list.at(0);
            //qDebug() << "Appending spinbox..... " << list.at(0)+"SpinBox";
            if(MainWindow::findChild<QSpinBox *>(list.at(0)+"SpinBox")){
                if(MainWindow::findChild<QCheckBox *>(array[i])->isChecked()){
                  // qDebug() << "Child is checked with SpinBox value!";
                    QSqlQuery qu;

                    qu.prepare("INSERT INTO quoteTableTemp VALUES (:quoteNum, :name, :connectionName, :value) ");
                    qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
                    qu.bindValue(":name",array[i]);
                    qu.bindValue(":connectionName",connectionArray[i]); //grab the connectionName for pricing.
                    qu.bindValue(":value",MainWindow::findChild<QSpinBox *>(list.at(0)+"SpinBox")->value());
                   qu.exec();
                }
            }
            //Here we insert into the new SQL database, if checked, and then go from there. This makes life easier...
            else if(MainWindow::findChild<QCheckBox *>(array[i])->isChecked()){
               // qDebug() << "Child is checked!";
                QSqlQuery qu;
                qu.prepare("INSERT INTO quoteTableTemp VALUES (:quoteNum, :name, :connectionName, :value) ");
                qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
                qu.bindValue(":name",array[i]);
                qu.bindValue(":connectionName",connectionArray[i]); //grab the connectionName for pricing.
                qu.bindValue(":value",1);
                 qu.exec();
            }

        }
        else if(MainWindow::findChild<QRadioButton*>(array[i])){
            //qDebug() << "Found Child with name: " << MainWindow::findChild<QRadioButton*>(array[i])->objectName() << " and type of RadioButton";
            //Here we insert into the new SQL database, if checked, and then go from there. This makes life easier...
            if(MainWindow::findChild<QRadioButton *>(array[i])->isChecked()){
              //  qDebug() << "CHILD IS CHECKED!";
                QSqlQuery qu;
                qu.prepare("INSERT INTO quoteTableTemp VALUES (:quoteNum, :name, :connectionName, :value) ");
                qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
                qu.bindValue(":name",array[i]);
                qu.bindValue(":connectionName",connectionArray[i]); //grab the connectionName for pricing.
                qu.bindValue(":value",1);
                qu.exec();
            }

        }
        else if(MainWindow::findChild<QLineEdit*>(array[i])){
          //qDebug() << "Found Child with name: " << MainWindow::findChild<QLineEdit*>(array[i])->objectName() << " and type of Line Edit";
            //Here we insert into the new SQL database, if checked, and then go from there. This makes life easier...
            if(MainWindow::findChild<QLineEdit *>(array[i])->text().compare("") != 0  && MainWindow::findChild<QLineEdit *>(array[i])->text().compare(" ") != 0){
                //qDebug() << "Line Edit is not blank!";
                QSqlQuery qu;
                qu.prepare("INSERT INTO quoteTableTemp VALUES (:quoteNum, :name, :connectionName, :value) ");
                qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
                qu.bindValue(":name",array[i]);
                qu.bindValue(":connectionName",connectionArray[i]); //grab the connectionName for pricing.
                qu.bindValue(":value",MainWindow::findChild<QLineEdit*>(array[i])->text());
               // qDebug() << "adding to database: " << array[i] << " with connectionName: " << connectionArray[i];

               qu.exec();

            }

        }
        else if(MainWindow::findChild<QDateEdit*>(array[i])){
        //   qDebug() << "Found Child with name: " << MainWindow::findChild<QDateEdit*>(array[i])->objectName() << " and type of Date Edit";
            //Here we insert into the new SQL database, if checked, and then go from there. This makes life easier...
            if(MainWindow::findChild<QDateEdit *>(array[i])->date().toString("MM/dd/yyyy").compare("") != 0){
                //qDebug() << "Date Edit is not blank!";
                QSqlQuery qu;
                qu.prepare("INSERT INTO quoteTableTemp VALUES (:quoteNum, :name, :connectionName, :value) ");
                qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
                qu.bindValue(":name",array[i]);
                qu.bindValue(":connectionName",connectionArray[i]); //grab the connectionName for pricing.
                qu.bindValue(":value",MainWindow::findChild<QDateEdit*>(array[i])->date().toString("MM/dd/yyyy"));
               qu.exec();
            }

        }
        else if(MainWindow::findChild<QPlainTextEdit*>(array[i])){
          //qDebug() << "Found Child with name: " << MainWindow::findChild<QPlainTextEdit*>(array[i])->objectName() << " and type of Plain Text Edit";
           // Here we insert into the new SQL database, if checked, and then go from there. This makes life easier...
            if(MainWindow::findChild<QPlainTextEdit *>(array[i])->toPlainText() != ""){
               // qDebug() << "QPlainTextEdit is not blank!";
                QSqlQuery qu;

                qu.prepare("INSERT INTO quoteTableTemp VALUES (:quoteNum, :name, :connectionName, :value) ");
                qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
                qu.bindValue(":name",array[i]);
                qu.bindValue(":connectionName",connectionArray[i]); //grab the connectionName for pricing.
                qu.bindValue(":value",MainWindow::findChild<QPlainTextEdit*>(array[i])->toPlainText());
                qu.exec();
            }

        }
        else if(MainWindow::findChild<QComboBox*>(array[i])){
          //qDebug() << "Found Child with name: " << MainWindow::findChild<QComboBox*>(array[i])->objectName() << " and type of Combo Box";
            //Here we insert into the new SQL database, if checked, and then go from there. This makes life easier...
            if(MainWindow::findChild<QComboBox *>(array[i])->currentText().compare("") != 0){
               // qDebug() << "ComboBox!";
                QSqlQuery qu;
                qu.prepare("INSERT INTO quoteTableTemp VALUES (:quoteNum, :name, :connectionName, :value) ");
                qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
                qu.bindValue(":name",array[i]);
                qu.bindValue(":connectionName",connectionArray[i]); //grab the connectionName for pricing.
                qu.bindValue(":value",MainWindow::findChild<QComboBox*>(array[i])->currentText());
                qu.exec();
            }

        }
        else if(MainWindow::findChild<QSpinBox*>(array[i])){
          // qDebug() << "Found Child with name: " << MainWindow::findChild<QComboBox*>(array[i])->objectName() << " and type of Combo Box";
            //Here we insert into the new SQL database, if checked, and then go from there. This makes life easier...
            if(MainWindow::findChild<QSpinBox *>(array[i])->value() != 0){
               // qDebug() << "ComboBox!";
                QSqlQuery qu;
                qu.prepare("INSERT INTO quoteTableTemp VALUES (:quoteNum, :name, :connectionName, :value) ");
                qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
                qu.bindValue(":name",array[i]);
                qu.bindValue(":connectionName",connectionArray[i]); //grab the connectionName for pricing.
                qu.bindValue(":value",MainWindow::findChild<QSpinBox*>(array[i])->value());
                qu.exec();
            }
        }
    }


    if(ui->createdByLabel->text() != ""){
        QString createdBy = ui->createdByLabel->text();
        QString lineToSplit = createdBy;
        QStringList list = lineToSplit.split("Created By: ");
        QSqlQuery qu;
        qu.prepare("INSERT INTO quoteTableTemp VALUES (:quoteNum, :name, :connectionName, :value) ");
        qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
        qu.bindValue(":name","createdByConnection");
        qu.bindValue(":connectionName","createdBy"); //grab the connectionName for pricing.
        qu.bindValue(":value",list.at(1));
        qu.exec();
    }

    else{
        QSqlQuery qu;
        qu.prepare("INSERT INTO quoteTableTemp VALUES (:quoteNum, :name, :connectionName, :value) ");
        qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
        qu.bindValue(":name","createdByConnection");
        qu.bindValue(":connectionName","createdBy"); //grab the connectionName for pricing.
        qu.bindValue(":value",loginName);
        qu.exec();
    }

}


/*
 *
 *
 * Looks for the objects on the MainWindow form and then sets their texts, values, and names
 * to the corresponding connection as given in the connections file.
 *
 */

void MainWindow::getConnections(int quoteNum, QString to[], QString from[], int index){
    clearQuoteForm();
    QSqlQuery qu;
    //qDebug() << qu.exec("SELECT * FROM quoteTable WHERE quoteNum =" + QString::number(quoteNum));
    qu.exec("SELECT * FROM quoteTable WHERE quoteNum =" + QString::number(quoteNum));
    //qDebug() << "VALUE FROM SELECT: " << qu.value(1).toString();
    QString name = "";
    for(int i = 0; i < index; i++){
        while(qu.next()){
           // qDebug() << "Getting connections";
            if(MainWindow::findChild<QCheckBox*>(qu.value(1).toString())){
               // qDebug() << "Found: " << MainWindow::findChild<QCheckBox*>(qu.value(1).toString())->objectName();
                MainWindow::findChild<QCheckBox*>(qu.value(1).toString())->setChecked(true);
                name = qu.value(1).toString();
                QString lineToSplit = MainWindow::findChild<QCheckBox *>(qu.value(1).toString())->objectName();
                QStringList list = lineToSplit.split("CheckBox");
               // qDebug() << "Split name is " << list.at(0);
                //qDebug() << "Appending spinbox..... " << list.at(0)+"SpinBox";
                if(MainWindow::findChild<QSpinBox *>(list.at(0)+"SpinBox")){
                   // qDebug() << "found spinbox!" << " connection name is " << qu.value(1).toString();
                        QString name = qu.value(1).toString();
                        QSqlQuery qu2;

                       // qDebug() << "name = " << name;
                        qu2.exec("SELECT value FROM `quoteTable` WHERE name = '"+name+"'");
                        qu2.last();
                       // qDebug() << "spinbox value is " << qu.value(3).toInt();
                        MainWindow::findChild<QSpinBox *>(list.at(0)+"SpinBox")->setValue(qu2.value(0).toInt());
                }




            }
            else if(MainWindow::findChild<QRadioButton*>(qu.value(1).toString())){
                //qDebug() << "Found: " << MainWindow::findChild<QRadioButton*>(qu.value(1).toString())->objectName();
               // qDebug() << "Checking the four strand button now: ";
                MainWindow::findChild<QRadioButton*>(qu.value(1).toString())->setChecked(true);


                //qDebug() << "Should be checked ";
            }
            else if(MainWindow::findChild<QLineEdit*>(qu.value(1).toString())){
               // qDebug() << "Found: " << MainWindow::findChild<QLineEdit*>(qu.value(1).toString())->objectName();
                MainWindow::findChild<QLineEdit*>(qu.value(1).toString())->setText(qu.value(3).toString());
            }
            else if(MainWindow::findChild<QPlainTextEdit*>(qu.value(1).toString())){
               // qDebug() << "Found: " << MainWindow::findChild<QLineEdit*>(qu.value(1).toString())->objectName();
                MainWindow::findChild<QPlainTextEdit*>(qu.value(1).toString())->setPlainText(qu.value(3).toString());
            }
            else if(MainWindow::findChild<QDateEdit*>(qu.value(1).toString())){
               // qDebug() << "Found: " << MainWindow::findChild<QDateEdit*>(qu.value(1).toString())->objectName();
                QString str(qu.value(3).toString());
                QDate date = QDate::fromString(str, "MM/dd/yyyy");
               // qDebug() << date;
                MainWindow::findChild<QDateEdit*>(qu.value(1).toString())->setDate(date);
                MainWindow::findChild<QDateEdit*>(qu.value(1).toString())->show();

            }
            else if(MainWindow::findChild<QComboBox*>(qu.value(1).toString())){
              // qDebug() << "Found: " << MainWindow::findChild<QComboBox*>(qu.value(1).toString())->objectName();
                MainWindow::findChild<QComboBox*>(qu.value(1).toString())->setCurrentText(qu.value(3).toString());
            }
            else if(MainWindow::findChild<QSpinBox*>(qu.value(1).toString())){
                //qDebug() << "Found: " << QSpinBox::findChild<QComboBox*>(qu.value(1).toString())->objectName();

                MainWindow::findChild<QSpinBox*>(qu.value(1).toString())->setValue(qu.value(3).toInt());
            }





        }
    }
    qu.exec("SELECT `value` FROM quoteTable WHERE connectionName = 'createdBy' AND quoteNum = " + QString::number(quoteNum));
    //qDebug() << qu.lastError().text();
    if(qu.last()){
            //ui->createdByLabel->show();
            ui->createdByLabel->setText("Created By: "+qu.value(0).toString());

    }

}

/*
 *
 * Allows us to delete a quote.
 * This function is essential to the performance. It allows the
 * database to delete ALL current info on the quote after it has been called down
 * from the database. In doing so, it is then erased and re-added
 *
 */

void MainWindow::updateCurrentQuote(int quoteNumber){
    QSqlQuery qu;
    //qDebug() << "Deleting " << quoteNumber << " from database... ";

    qu.exec("DELETE FROM quoteTable WHERE quoteNum = "+ui->quoteNumLineEdit->text()+ " and not name  = 'adjustPrice'");
   // qDebug() << qu.exec("DELETE FROM quoteTable WHERE quoteNum = " + quoteNumber);
}

/*
 * Clears the form, resets all checks, texts, etc.
 *
 */
void MainWindow::clearQuoteForm(){
    QList<QLineEdit*> lineEditList = MainWindow::findChildren<QLineEdit*>(); //find all the line edits.
    QList<QRadioButton*> radioButtonList = MainWindow::findChildren<QRadioButton*>(); //find all the line edits.
    QList<QCheckBox*> checkBoxList = MainWindow::findChildren<QCheckBox*>(); //find all the line edits.
    QList<QSpinBox*> spinBoxList = MainWindow::findChildren<QSpinBox*>();
    QList<QComboBox*> comboBoxList = MainWindow::findChildren<QComboBox*>();
    QList<QPlainTextEdit *> plainTextList = MainWindow::findChildren<QPlainTextEdit*>();
    for(int i = 0;i<lineEditList.count();i++){
        if(lineEditList.at(i)->objectName().compare("quoteNumLineEdit") != 0){
            lineEditList.at(i)->setText("");
        }
    }
    for(int i = 0;i<radioButtonList.count();i++){
        radioButtonList.at(i)->setChecked(false);
    }
    for(int i = 0;i<checkBoxList.count();i++){
        checkBoxList.at(i)->setChecked(false);
    }
    for(int i = 0;i<spinBoxList.count();i++){
        spinBoxList.at(i)->setValue(0);
    }
    for(int i = 0;i<comboBoxList.count();i++){
        comboBoxList.at(i)->setCurrentIndex(0);
    }
    for(int i=0;i<plainTextList.count();i++){
        plainTextList.at(i)->setPlainText("");
    }

    ui->salesPersonComboBox->setCurrentText(loginName);
   // uncheckOverrides();

}

/*
 *
 * Makes the form non-editable
 *
 */

void MainWindow::freeze(){
    QList<QLineEdit*> lineEditList = MainWindow::findChildren<QLineEdit*>(); //find all the line edits.
    QList<QRadioButton*> radioButtonList = MainWindow::findChildren<QRadioButton*>(); //find all the line edits.
    QList<QCheckBox*> checkBoxList = MainWindow::findChildren<QCheckBox*>(); //find all the line edits.
    QList<QSpinBox*> spinBoxList = MainWindow::findChildren<QSpinBox*>();
    QList<QComboBox*> comboBoxList = MainWindow::findChildren<QComboBox*>();
    QList<QPlainTextEdit *> plainTextList = MainWindow::findChildren<QPlainTextEdit*>();
    for(int i = 0;i<lineEditList.count();i++){
        if(lineEditList.at(i)->objectName().compare("quoteNumLineEdit") != 0){
            lineEditList.at(i)->setText("");
        }
    }
    for(int i = 0;i<radioButtonList.count();i++){
        radioButtonList.at(i)->setEnabled(false);
    }
    for(int i = 0;i<checkBoxList.count();i++){
        checkBoxList.at(i)->setEnabled(false);
    }
    for(int i = 0;i<spinBoxList.count();i++){
        spinBoxList.at(i)->setEnabled(false);
    }
    for(int i = 0;i<comboBoxList.count();i++){
        comboBoxList.at(i)->setEnabled(false);
    }
    for(int i=0;i<plainTextList.count();i++){
        plainTextList.at(i)->setEnabled(false);
    }
}


/*
 *
 * Restores ability to edit on the form.
 *
 */
void MainWindow::unfreeze(){

   //qDebug() << "password entered correctly.";
    QList<QLineEdit*> lineEditList = MainWindow::findChildren<QLineEdit*>(); //find all the line edits.
    QList<QRadioButton*> radioButtonList = MainWindow::findChildren<QRadioButton*>(); //find all the line edits.
    QList<QCheckBox*> checkBoxList = MainWindow::findChildren<QCheckBox*>(); //find all the line edits.
    QList<QSpinBox*> spinBoxList = MainWindow::findChildren<QSpinBox*>();
    QList<QComboBox*> comboBoxList = MainWindow::findChildren<QComboBox*>();
    QList<QPlainTextEdit *> plainTextList = MainWindow::findChildren<QPlainTextEdit*>();

    for(int i = 0;i<lineEditList.count();i++){
        if(lineEditList.at(i)->objectName().compare("quoteNumLineEdit") != 0){
            lineEditList.at(i)->setText("");
        }
    }
    for(int i = 0;i<radioButtonList.count();i++){
        radioButtonList.at(i)->setEnabled(true);
    }
    for(int i = 0;i<checkBoxList.count();i++){
        checkBoxList.at(i)->setEnabled(true);
    }
    for(int i = 0;i<spinBoxList.count();i++){
        spinBoxList.at(i)->setEnabled(true);
    }
    for(int i = 0;i<comboBoxList.count();i++){
        comboBoxList.at(i)->setEnabled(true);
    }
    for(int i=0;i<plainTextList.count();i++){
        plainTextList.at(i)->setEnabled(true);
    }




}

/*
 *
 * Gets the database elements from the given database.
 *
 */
QStringList MainWindow::getDatabaseElements(QString databaseName){

    QSqlQuery query;
    QStringList list;
    query.exec("SELECT * FROM "+databaseName+";");
    //query.next(); //grab the first index

        while(query.next()){
            if(query.value(4).toInt() == 1){
                list.append(query.value(3).toString());
            }
        }




    return list;


}
/*
 * Mouse move event. Will detect when the mouse has been moved.
 * This increases performance when selecting quotes to jump to.
 * Instead of having to code specific listeners for change requests/values,
 * we can use this.
 *
 */


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type() == QEvent::MouseMove)
  {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    //statusBar()->showMessage(QString("Mouse move (%1,%2)").arg(mouseEvent->pos().x()).arg(mouseEvent->pos().y()));
    if(qS.quoteNumberToGo > -1){
        getQuote(qS.quoteNumberToGo);
        qS.quoteNumberToGo = -1;
        qS.update();
        qS.begin();

    }

    if(qS.isHidden()){
        ui->actionClose_Sidebar->setText("Open Sidebar");
    }
    if(pS.isHidden()){
        ui->actionClose_Price_Sidebar->setText("Open Price Sidebar");
    }
    if(cS.isHidden()){
        ui->actionClose_Customer_Info->setText("Open Customer Sidebar");
    }


    if(!cs.stringList.isEmpty()){
        ui->nameLineEdit->setText(cs.stringList.at(0));
        ui->companyNameLineEdit->setText(cs.stringList.at(1));
        ui->address1LineEdit->setText(cs.stringList.at(2));
        ui->address2LineEdit->setText(cs.stringList.at(3));
        ui->cityLineEdit->setText(cs.stringList.at(4));
        ui->stateComboBox->setCurrentText(cs.stringList.at(5));
        ui->zipCodeLineEdit->setText(cs.stringList.at(6));
        ui->emailLineEdit->setText(cs.stringList.at(7));
        ui->faxLineEdit->setText(cs.stringList.at(8));
        ui->phoneLineEdit->setText(cs.stringList.at(9));
        ui->phone2LineEdit->setText(cs.stringList.at(10));
        cs.stringList.clear();

    }


    //qS.update();
   // qS.begin();



    //updateQuoteNum();

  }
  return false;
}
/*
 * For the reset function button to work
 */
void MainWindow::resetButton(){
    reset(true);
}

/*
 * Manages the sidebar. Closes/Opens.
 *
 */

void MainWindow::sidebar(){

    if(ui->actionClose_Sidebar->text() == "Close Sidebar"){
        ui->actionClose_Sidebar->setText("Open Sidebar");
        qS.hide();
    }
    else{
        ui->actionClose_Sidebar->setText("Close Sidebar");
        qS.show();
        qS.update();
        qS.begin();
    }

}

void MainWindow::priceSideBar(){
    if(ui->actionClose_Price_Sidebar->text() == "Close Price Sidebar"){
        ui->actionClose_Price_Sidebar->setText("Open Price Sidebar");
        pS.hide();
    }
    else{
        ui->actionClose_Price_Sidebar->setText("Close Price Sidebar");
        pS.show();
        pS.getNameAndPrices();
        pS.update();

    }
}

void MainWindow::customerinfo(){

    if(ui->actionClose_Customer_Info->text() == "Close Customer Info"){

        ui->actionClose_Customer_Info->setText("Open Customer Info");
         cS.hide();

    }
    else{
        ui->actionClose_Customer_Info->setText("Close Customer Info");
        cS.show();
        cS.addContacts();

    }
}


/*
 * This will cause the window to expand or shrink based on the "Tabs" button pushed.
 */
void MainWindow::doTheThing(){
    //qDebug() << "Expand or shrink is equal to " << expandOrShrink;
    //this->setFixedSize(QSize(740,1030));

    if(expandOrShrink == 0){ //if shrunk, expand
        ui->tabWidget->show();
        ui->okCancelButtonBox2->hide();
       // ui->saveCheckBox->setChecked(false);

       // ui->saveCheckBox->hide();
        ui->tab_2->setDisabled(false); //Change to 0 to launch Resaw tab for live use
        ui->tab_3->setDisabled(true); //Change to 0 to launch Custom Tab for live use


        this->setFixedSize(QSize(797,1010));

        ui->tabButton->setText("▲");

        expandOrShrink = 1;

    }
    else if(expandOrShrink == 1){ //if expanded, shrink
        ui->okCancelButtonBox2->show();
       /* ui->saveCheckBox->setChecked(true);
        ui->saveCheckBox->setDisabled(true);
        ui->saveCheckBox->show();*/
        ui->tabWidget->hide();

        this->setFixedSize(797,403);
        ui->tabButton->setText("▼");
        expandOrShrink = 0;
    }

}
/*
 * Loads any hardcoded defaults into the recursion array needed.
 *
 *
 */


void MainWindow::loadDefaults(){


    connectionsTo[i] = "wheelSize";
    connectionsFrom[i] = "wheelSizeSpinBox";
    i++;
    connectionsTo[i] = "mill40";
    connectionsFrom[i] = "platform40RadioButton";
    i++;
    connectionsTo[i] = "mill48";
    connectionsFrom[i] = "platform48RadioButton";
    i++;
    connectionsTo[i] = "mill60";
    connectionsFrom[i] = "platform60RadioButton";
    i++;
    connectionsTo[i] = "mill52";
    connectionsFrom[i] = "platform52RadioButton";
    i++;
    connectionsTo[i] = "mill52";
    connectionsFrom[i] = "platform52RadioButton";
    i++;
    connectionsTo[i] = "threeStrand";
    connectionsFrom[i] = "threeStrandDeckRadioButton";
    i++;
    connectionsTo[i] = "fourStrand";
    connectionsFrom[i] = "fourStrandDeckRadioButton";
    i++;
    connectionsTo[i] = "twoStrand";
    connectionsFrom[i] = "twoStrandDeckRadioButton";
    i++;
    connectionsTo[i] = "noStrand";
    connectionsFrom[i] = "noDeckRadioButton";
    i++;
    connectionsTo[i] = "magnumCarriage";
    connectionsFrom[i] = "magnumRadioButton";
    i++;
    connectionsTo[i] = "challengerCarriage";
    connectionsFrom[i] = "challengerRadioButton";
    i++;
    connectionsTo[i] = "phone";
    connectionsFrom [i] = "phoneLineEdit";
    i++;
    connectionsTo[i] = "phone2";
    connectionsFrom [i] = "phone2LineEdit";
    i++;
    connectionsTo[i] = "compName";
    connectionsFrom[i] = "companyNameLineEdit";
    i++;


    connectionsTo[i] = "barLog";
    connectionsFrom[i] = "barRadioButton";
    i++;
    connectionsTo[i] = "cantPushOff";
    connectionsFrom[i] = "cantPushOffSpinBox";
    i++;
    connectionsTo[i] = "brownsville";
    connectionsFrom[i] = "brownsvilleSpinBox";
    i++;
    connectionsTo[i] = "customPrice1";
    connectionsFrom[i] = "customPrice1SpinBox";
    i++;
    connectionsTo[i] = "customPrice2";
    connectionsFrom[i] = "customPrice2SpinBox";
    i++;
    connectionsTo[i] = "custom1";
    connectionsFrom[i] = "custom1LineEdit";
    i++;
    connectionsTo[i] = "custom2";
    connectionsFrom[i] = "custom2LineEdit";
    i++;
    connectionsTo[i] = "linearCarriage";
    connectionsFrom[i] = "linearCheckBox";
    i++;

    connectionsTo[i] = "magnumCarriageKnees";
    connectionsFrom[i] = "carriageKneesSpinBox_2";

    i++;













    }




    /*
     * nanosetRadioButton:nanoSet
compsetRadioButton:compSet
hdChainRadioButton:hdChain
barRadioButton:barLog
stdChainRadioButton:standardChain
twoStrandDeckRadioButton:twoStrand
threeStrandDeckRadioButton:threeStrand
fourStrandDeckRadioButton:fourStrand
noDeckRadioButton:noStrand
challengerRadioButton:challengerCarriage
magnumRadioButton:magnumCarriage
     */


void MainWindow::push(bool checked){


    setTemporaryConnections(connectionsFrom,connectionsTo,i);
    //qDebug() << "Built Struct";

    Quote q;

    q.date = ui->dateEdit->date().toString("MM/dd/yyyy");
    q.name = ui->nameLineEdit->text();
    QList<QString> list = applyCheckedItems();



    int totalPrice = qP.tempPriceQuote(q,list,list.count(),ui->quoteNumLineEdit->text().toInt());



    ui->totalLabel->setText( "<font color='green'>Est.Total Price: "+QString::number(totalPrice));


}

void MainWindow::iterateChildren(QWidget * parent){
    //we do not want to iterate literal children.

    QObjectList children = parent->children(); //recursion
    QStringList connectionTo;
    QStringList connectionFrom;
    QObjectList::const_iterator it = children.begin(); //iterator begin
    QObjectList::const_iterator eIt = children.end(); //iterator end
    while( it != eIt ){ //while beginning does not equal end
       QSqlQuery qu;
       QWidget * parentChild = (QWidget *) (*it++);
          if(QString::compare(parentChild->objectName(),"label") && !parentChild->objectName().contains("tab") && !parentChild->objectName().contains("groupBox") && !parentChild->objectName().toLower().contains("layout") && !parentChild->objectName().contains("qt_spinbox") &&  !parentChild->objectName().contains("label_") && !parentChild->objectName().contains("line") && !parentChild->objectName().contains("qt_scroll") && QString::compare("",parentChild->objectName())){
            //qDebug() << parentChild->objectName();


              QString replacedString;






              if(parentChild->objectName().contains("CheckBox")){
                 replacedString = parentChild->objectName().replace("CheckBox","");
              }
              else if(parentChild->objectName().contains("SpinBox")){
                 replacedString = parentChild->objectName().replace("SpinBox","");
             }
              else if(parentChild->objectName().contains("RadioButton")){
                  //qDebug() << "found a radio button " << parentChild->objectName();
                  replacedString = parentChild->objectName().replace("RadioButton","");
                //  replacedString = parentChild->objectName().replace("CheckBox","");

              }
              else if(parentChild->objectName().contains("LineEdit")){

                      replacedString = parentChild->objectName().replace("LineEdit","");


              }
              else if(parentChild->objectName().contains("PlainTextEdit")){
                  replacedString = parentChild->objectName().replace("PlainTextEdit","");
              }
              else if(parentChild->objectName().contains("ComboBox")){
                  replacedString = parentChild->objectName().replace("ComboBox","");
              }


                for(int j = 0; j<i;j++){
                    if(connectionsTo[j].contains(replacedString)){
                        break;
                    }

                }


                connectionsTo[i] = replacedString;
                connectionsFrom[i] = parentChild->objectName();

                i++;



          }


         iterateChildren( parentChild );


       }









}


void MainWindow::makeToolTips(QWidget * parent){
    QObjectList children = parent->children(); //recursion
    QObjectList::const_iterator it = children.begin(); //iterator begin
    QObjectList::const_iterator eIt = children.end(); //iterator end
    while( it != eIt ){ //while beginning does not equal end
       QSqlQuery qu;
       QWidget * parentChild = (QWidget *) (*it++);

    int endOfJ = i;


       for(int j = 0; j<i; j++){
           if(parentChild->objectName() == connectionsFrom[j] && !connectionsTo[j].contains("carriageLT") && !connectionsTo[j].contains("carriageLP") && !connectionsTo[j].contains("carriage")){
       qDebug() <<"found a match: " << parentChild->objectName() << " with " << connectionsFrom[j] << "connectionsTO = " + connectionsTo[j];
               qu.exec("SELECT * FROM quoteItems where name = '"+connectionsTo[j]+"'");
               qu.last();
               if(!qu.isNull(0)){
                 qDebug() << " this is a valid query: "  << connectionsTo[j] << " and " << parentChild->objectName();


                   parentChild->setToolTip("$"+qu.value(2).toString());
                   parentChild->setToolTipDuration(1000);


               }
           }


               // if the connection contains the word carriage, then try and make a valid connection by appending LT and LP in front of carriage. If this does not work, move on.



           if(parentChild->objectName() == connectionsFrom[j] && connectionsTo[j].contains("carriage") && !connectionsTo[j].contains("carriageLT") && !connectionsTo[j].contains("carriageLP") ){
                   qu.exec("SELECT * FROM quoteItems where name = '"+connectionsTo[j]+"'");
                   qu.last();
                   if(!qu.isNull(0)){
                     qDebug() << " this is a valid query: "  << connectionsTo[j] << " and " << parentChild->objectName();


                       parentChild->setToolTip("$"+qu.value(2).toString());
                       parentChild->setToolTipDuration(1000);


                   }

                   else{
                        qDebug() << "found an invalid query with objectname of " << parentChild->objectName();
                        QString newString1 = connectionsTo[j].replace("carriage","carriageLP");
                        qDebug() << newString1;
                        QString newString2 = connectionsTo[j].replace("carriageLP","carriageLT");
                         qDebug() << newString2;

                        qu.exec("SELECT * FROM quoteItems where name = '"+newString1+"'");
                        qu.last();

                        QString price1 = qu.value(2).toString();

                        qu.exec("SELECT * FROM quoteItems where name = '"+newString2+"'");
                        qu.last();

                        QString price2 = qu.value(2).toString();



                   //     connectionsFrom[endOfJ] = parentChild->objectName();
                      //  connectionsTo[endOfJ] = newString1;
                      //  endOfJ++;

                        carriageItems.append(newString1);
                        carriageItems.append(newString2);





                        qDebug() << newString1 << " with " << newString2 << " = " << price1 << " and " << price2;


                        parentChild->setToolTip("LP: $"+price1+", LT: $"+price2);
                        parentChild->setToolTipDuration(1000);







                     }
                  // qDebug() << "sorting: " << connectionsTo[j] << endl;


           }

          // qDebug() << "You are on " << parentChild->objectName() << "connectionTo = " << connectionsTo[j] << " connectionsFrom = " << connectionsFrom[j] << " j = " << j;




               if(parentChild==ui->cantTurnersCheckBox){
                   ui->cantTurnersCheckBox->setToolTip("$"+qu.value(2).toString()+" ea");
               }
               if(parentChild==ui->brownsvilleCheckBox){
                   ui->brownsvilleCheckBox->setToolTip("$"+qu.value(2).toString()+" ea");
               }

               if(parentChild==ui->cantPushOffCheckBox){
                   ui->cantPushOffCheckBox->setToolTip("$"+qu.value(2).toString()+" ea");
           }
               if(parentChild->objectName()== "platform40RadioButton"){
                   qu.exec("SELECT * FROM quoteItems where name = 'mill40LT'");
                   qu.last();
                   ui->platform40RadioButton->setToolTip("$" +qu.value(2).toString());

               }
               if(parentChild->objectName()== "platform48RadioButton"){
                   qu.exec("SELECT * FROM quoteItems where name = 'mill48LT'");
                   qu.last();
                   ui->platform48RadioButton->setToolTip("$" +qu.value(2).toString());

               }
               if(parentChild->objectName()== "platform52RadioButton"){
                   qu.exec("SELECT * FROM quoteItems where name = 'mill52LT'");
                   qu.last();
                   ui->platform52RadioButton->setToolTip("$" +qu.value(2).toString());

               }
               if(parentChild->objectName()== "platform60RadioButton"){
                   qu.exec("SELECT * FROM quoteItems where name = 'mill60LT'");
                   qu.last();
                   ui->platform60RadioButton->setToolTip("$" +qu.value(2).toString());

               }
       }



       makeToolTips(parentChild);

    }

//qDebug() << "QList of carriage: " << carriageItems;



}
void MainWindow::makeCarriageToolTips(QWidget * parent){
    QObjectList children = parent->children(); //recursion
    QObjectList::const_iterator it = children.begin(); //iterator begin
    QObjectList::const_iterator eIt = children.end(); //iterator end
    while( it != eIt ){ //while beginning does not equal end
       QSqlQuery qu;
       QWidget * parentChild = (QWidget *) (*it++);

for(int j = 0; j<i; j++){
    if(parentChild->objectName() == connectionsFrom[j]){

      // qDebug() <<"found a match: " << parentChild->objectName() << " with " << connectionsFrom[j] << "connectionsTO = " + connectionsTo[j];
        qu.exec("SELECT * FROM carriageQuoteItems where name = '"+connectionsTo[j]+"'");
        qu.last();


        if(qu.isValid()){
           qDebug() << " this is a valid query: "  << connectionsFrom[j] << " and " << parentChild->objectName();


            parentChild->setToolTip("$"+qu.value(2).toString());
            parentChild->setToolTipDuration(1000);

    }








}







makeCarriageToolTips(parentChild);
}
    }



}

void MainWindow::adjustPricePushButtonPushed(){
    QString adjustPriceField = QInputDialog::getText(this, tr("Adjust Price?"), tr(""),QLineEdit::Normal, "");

    qDebug() << adjustPriceField;

    QSqlQuery qu;
    qu.prepare("INSERT INTO quoteTable VALUES (:quoteNum, :name, :connectionName, :value) ");
    qu.bindValue(":quoteNum",ui->quoteNumLineEdit->text().toInt());
    qu.bindValue(":name","adjustPriceConnection");
    qu.bindValue(":connectionName","adjustPrice"); //grab the connectionName for pricing.
    qu.bindValue(":value",adjustPriceField);
    qDebug() << qu.exec() << qu.lastError().text();


}




