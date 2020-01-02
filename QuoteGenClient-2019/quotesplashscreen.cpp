#include "quotesplashscreen.h"
#include "ui_quotesplashscreen.h"

QuoteSplashScreen::QuoteSplashScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuoteSplashScreen)
{
    ui->setupUi(this);
}

QuoteSplashScreen::~QuoteSplashScreen()
{
    delete ui;
}
