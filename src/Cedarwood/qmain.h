#pragma once
#include "stdafx.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QMessageBox>
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>

class qmain {
public:
  static int main(QQmlApplicationEngine* engine);
};
