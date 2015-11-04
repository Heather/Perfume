#include "stdafx.h"
#include "qmain.h"

#include <QApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QQmlApplicationEngine engine;
  int ret = qmain::main(&engine);
  return (ret == 0) ?
     app.exec() : ret;
}
