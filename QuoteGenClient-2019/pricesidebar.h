#ifndef PRICESIDEBAR_H
#define PRICESIDEBAR_H

#include <QMainWindow>
#include <QDialog>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QString>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QMouseEvent>

namespace Ui {
class PriceSideBar;
}

class PriceSideBar : public QMainWindow
{
    Q_OBJECT

public:
    explicit PriceSideBar(QWidget *parent = nullptr);
    ~PriceSideBar();
    void getNameAndPrices();

private:
    Ui::PriceSideBar *ui;
    QSqlDatabase db;






};

#endif // PRICESIDEBAR_H
