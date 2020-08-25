#ifndef CUSTOMERINFO_H
#define CUSTOMERINFO_H

#include <QMainWindow>
#include <QDialog>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QString>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QMouseEvent>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QItemSelectionModel>
#include <QCloseEvent>
#include <QSqlError>

#define SEARCHALLFIELDS false // make this true to search by all fields, otherwise make it false to only search names.


namespace Ui {
class customerInfo;
}

class customerInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit customerInfo(QWidget *parent = nullptr);
    ~customerInfo();
    void addContacts();
    QSqlDatabase db;
    QStringList stringList;
    bool checkContactExist(QString);
    void addContact(QString, QString, QString, QString, QString, QString, QString, QString, QString, QString, QString);
    void clear();
    void update();

private:
    Ui::customerInfo *ui;
    void closeEvent(QCloseEvent *);



private slots:
    void copyButtonPushed();
    void deleteButtonPushed();
    void edited(QTableWidgetItem *);
    void search(QString);



};

#endif // CUSTOMERINFO_H
