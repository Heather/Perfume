#include "stdafx.h"

#include <QApplication>
#include <QQmlApplicationEngine>

#include <QQuickWindow>
#include <QMessageBox>
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>

using namespace boost::interprocess;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  if (!QSystemTrayIcon::isSystemTrayAvailable()) {
    QMessageBox::critical(0, QObject::tr("Systray"),
      QObject::tr("I couldn't detect any system tray "
      "on this system."));
    return 1;
  }
  QApplication::setQuitOnLastWindowClosed(false);

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  if (engine.rootObjects().size() > 0) {
    QObject* root = engine.rootObjects().at(0);

    QAction *minimizeAction = new QAction(QObject::tr("Mi&nimize"), root);
    root ->connect(minimizeAction, SIGNAL(triggered()), root, SLOT(hide()));
    QAction *maximizeAction = new QAction(QObject::tr("Ma&ximize"), root);
    root->connect(maximizeAction, SIGNAL(triggered()), root, SLOT(showMaximized()));
    QAction *restoreAction = new QAction(QObject::tr("&Restore"), root);
    root->connect(restoreAction, SIGNAL(triggered()), root, SLOT(showNormal()));
    QAction *quitAction = new QAction(QObject::tr("&Quit"), root);
    root->connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu *trayIconMenu = new QMenu();
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(root);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/resources/logo.png"));
    trayIcon->show();

    root->connect(trayIcon, &QSystemTrayIcon::activated,
      [root] (QSystemTrayIcon::ActivationReason reason) {
        switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
          ((QQuickWindow *)root)->showNormal();
          break;
        case QSystemTrayIcon::MiddleClick:
          ((QQuickWindow *)root)->hide();
          break;
        default:
          ;
        }
    });

    //Open managed segment
    managed_shared_memory segment(open_only, "Patchouli");

    std::pair<sharedString * , size_t > p= segment.find<sharedString>("sharedString");
    ((QQuickWindow *)root)->setTitle( p.first->c_str() );
  }

  return app.exec();
}
