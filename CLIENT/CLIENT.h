#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CLIENT.h"
#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include "socket.h"
#include <QKeyEvent>
#include <Windows.h>
#include <QTimer>

#define KEY_DOWN 7
#define KEY_UP 8
static int x = 1;

class CLIENT : public QMainWindow
{
    Q_OBJECT

public:
    CLIENT(QWidget *parent = nullptr);
    // void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
   // void keyReleaseEvent(QKeyEvent* event);
    Socket sk;
    ~CLIENT();
private slots:
    void updateMousePosition();
private:
    Ui::CLIENTClass ui;
    QTimer* mouseUpdateTimer;
};
