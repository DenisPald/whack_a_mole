#include "startwindow.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QString>
#include <QList>

#include <QApplication>
#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QTextBrowser>
#include <QGridLayout>
#include <QFrame>
#include <QSizePolicy>
#include <QVBoxLayout>
#include <QHBoxLayout>

StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent), scoreText(nullptr), score(0)
{
    this->setWindowTitle("Whack A Mole");
    this->resize(900, 900);

    stackedWidget = new QStackedWidget(this);

    QWidget *startPage = new QWidget();
    QVBoxLayout *startLayout = new QVBoxLayout(startPage);
    QPushButton *startButton = new QPushButton("Начать", startPage);
    startButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    startLayout->addWidget(startButton, 0, Qt::AlignCenter);
    connect(startButton, &QPushButton::clicked, this, &StartWindow::on_startButton_clicked);
    startPage->setLayout(startLayout);

    QWidget *gamePage = new QWidget();
    QVBoxLayout *gameLayout = new QVBoxLayout(gamePage);
    gamePage->setLayout(gameLayout);

    QFrame *frame = new QFrame(gamePage);
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    QHBoxLayout *frameLayout = new QHBoxLayout(frame);
    frame->setMaximumHeight(50);
    scoreText = new QTextBrowser(frame);
    scoreText->setMaximumHeight(50);
    frameLayout->addWidget(scoreText);
    QPushButton *endGameButton = new QPushButton("Завершить игру", frame);
    frameLayout->addWidget(endGameButton);
    connect(endGameButton, &QPushButton::clicked, this, &StartWindow::on_endGameButton_clicked);
    gameLayout->addWidget(frame);

    QFrame *mainGame = new QFrame(gamePage);
    mainGame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QGridLayout *gridLayoutGame = new QGridLayout(mainGame);
    gridLayoutGame->setSpacing(10);

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            QPushButton *button = new QPushButton("...", mainGame);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            gridLayoutGame->addWidget(button, row, col);
            buttons.append(button);
            connect(button, &QPushButton::clicked, this, &StartWindow::on_button_n_clicked);
        }
    }
    mainGame->setLayout(gridLayoutGame);
    gameLayout->addWidget(mainGame);

    stackedWidget->addWidget(startPage);
    stackedWidget->addWidget(gamePage);

    this->setCentralWidget(stackedWidget);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &StartWindow::newMole);
}

StartWindow::~StartWindow(){}

void StartWindow::on_startButton_clicked()
{
    score = 0;
    updateScore();
    stackedWidget->setCurrentIndex(1);
    newMole();
}

void StartWindow::on_button_n_clicked()
{
    QAbstractButton *button = qobject_cast<QAbstractButton*>(sender());
    if (button && button->property("mole").toBool())
    {
        score++;
        updateScore();
        button->setProperty("mole", 0);
        button->setStyleSheet("");
        button->setText("...");
    }
}

void StartWindow::on_endGameButton_clicked()
{
    for (QPushButton* button: buttons){
        button->setProperty("mole", 0);
        button->setStyleSheet("");
        button->setText("...");
    }
    timer->stop();
    stackedWidget->setCurrentIndex(0);
}

void StartWindow::newMole()
{
    int button_index = QRandomGenerator::global()->bounded(buttons.size());
    QAbstractButton *button = buttons[button_index];

    button->setProperty("mole", 1);
    button->setStyleSheet("background-color: red");
    button->setText("КРОТ");

    int random_time_interval_ms = QRandomGenerator::global()->bounded(MAX_INTERVAL-MIN_INTERVAL) + MIN_INTERVAL;
    timer->start(random_time_interval_ms);
}

void StartWindow::updateScore()
{
    QString score_string = QString::number(score);
    scoreText->setText(score_string);
}
