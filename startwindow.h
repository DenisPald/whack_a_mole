#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <QAbstractButton>
#include <QTimer>
#include <QStackedWidget>
#include <QList>
#include <QPushButton>
#include <QTextBrowser>

QT_BEGIN_NAMESPACE
namespace Ui {
class StartWindow;
}
QT_END_NAMESPACE

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private slots:
    void on_startButton_clicked();
    void on_endGameButton_clicked();
    void updateScore();
    void on_button_n_clicked();
    void newMole();

private:
    const int MAX_INTERVAL = 1500;
    const int MIN_INTERVAL = 50;
    QStackedWidget *stackedWidget;
    QTextBrowser *scoreText;
    QList<QPushButton*> buttons;
    QTimer *timer;
    int score;

};
#endif // STARTWINDOW_H
