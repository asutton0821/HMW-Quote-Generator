#ifndef QUOTESPLASHSCREEN_H
#define QUOTESPLASHSCREEN_H

#include <QDialog>

namespace Ui {
class QuoteSplashScreen;
}

class QuoteSplashScreen : public QDialog
{
    Q_OBJECT

public:
    explicit QuoteSplashScreen(QWidget *parent = 0);
    ~QuoteSplashScreen();

private:
    Ui::QuoteSplashScreen *ui;
};

#endif // QUOTESPLASHSCREEN_H
