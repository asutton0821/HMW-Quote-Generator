#ifndef QUOTESTATS_H
#define QUOTESTATS_H

#include <QDialog>




namespace Ui {
class quoteStats;
}

class quoteStats : public QDialog
{
    Q_OBJECT

public:
    explicit quoteStats(QWidget *parent = 0);
    ~quoteStats();

private:
    Ui::quoteStats *ui;
};

#endif // QUOTESTATS_H
