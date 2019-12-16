#ifndef QUOTESTATUS_H
#define QUOTESTATUS_H

#include <QDialog>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QString>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QMouseEvent>
#include <QSystemTrayIcon>

namespace Ui {
class QuoteStatus;
}

class QuoteStatus : public QDialog
{
    Q_OBJECT

public:
    explicit QuoteStatus(QWidget *parent = 0);
    ~QuoteStatus();
    int quoteNumberToGo;

    void addAllOpen(void);
    void addAllClosed(void);
    void addAllExpired(void);
    void sortBy(QString sortType);
    void update(void);
    void count(void);



private:
    Ui::QuoteStatus *ui;
    QSystemTrayIcon* trayIcon;


private slots:
    void accept(void);
    void reject(void);


public slots:
    void begin(void);

};

#endif // QUOTESTATUS_H
