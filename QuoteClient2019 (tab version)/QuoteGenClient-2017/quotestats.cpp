#include "quotestats.h"
#include "ui_quotestats.h"

quoteStats::quoteStats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::quoteStats)
{
    ui->setupUi(this);
}

quoteStats::~quoteStats()
{
    delete ui;
}





void quoteStats::begin(){

}
