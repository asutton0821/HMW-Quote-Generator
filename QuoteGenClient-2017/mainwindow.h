#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "quotepdfmanager.h"
#include "quotedbmanager.h"
#include "quotedbpricemanager.h"
#include "quotestatus.h"
#include <QStringList>




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void freeze(void);
    void unfreeze(void);
    bool STOPAPP;

private:
    Ui::MainWindow *ui;
    QuoteDbManager qdbMan;
    QuoteDbManager qdb;
    int quoteNum;
    quotePDFManager qPDF;
    quoteDBPriceManager qP;
    int length;
    QString priceArray[100];
    int pIndex;
    QString connectionsTo[100];
    QString connectionsFrom[100];
    int i;
    QString loginName;
    QuoteStatus qS;
    bool newQuote;
    int expandOrShrink;




private slots:
    void accept(void);
    void reject(void);
    void previousButtonPushed(void);
    void updateQuoteNum(void);
    void updateDate(void);
    void reset(bool);
    void getQuote(int );
    void nextButtonPushed(void);
    void onTextChanged( void );
    void connectRadioButtons(void );
    void connectCheckBoxes(void);
    void displayVersion(void);
    void printPDF(void);
    void changeSaveLocation(void);
    void promptPacketPrint(void);
    void changeQuoteStatus(void);
    void checkQuoteStatus(void);
    void quoteMenuSelection(void);
    void quoteFilterMenuSelection(void);
    void showCompDateBox(void);
    void connectOverrideFunctions(void);
    void uncheckOverrides(void);
    void loadConnectionFile(void);
    void setConnections(QString array[], QString connectionArray[], int index);
    void getConnections(int quoteNum, QString to[], QString from[], int index);
    void updateCurrentQuote(int quoteNumber);
    void clearQuoteForm(void);
    void sidebar(void);
    void resetButton();
    bool eventFilter(QObject *obj, QEvent *event);
    void closeEvent(QCloseEvent *bar);
    void doTheThing(void);
    QStringList getDatabaseElements(QString databaseName);

    void getOverrides(void);
    void checkOverrides(void);
    void iterateChildren(QWidget * parent);



    QList<QString> applyCheckedItems(void);

};



#endif // MAINWINDOW_H
