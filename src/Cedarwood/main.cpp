#include <QApplication>
#include <QQmlApplicationEngine>

#include <QMessageBox>
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>

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

  QObject *root = 0;
  if (engine.rootObjects().size() > 0) {
    root = engine.rootObjects().at(0);

    QAction *minimizeAction = new QAction(QObject::tr("Mi&nimize"), root);
    root->connect(minimizeAction, SIGNAL(triggered()), root, SLOT(hide()));
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
    trayIcon->showMessage("Cedarwood", "Cedarwood is running");
    root->connect(trayIcon, SIGNAL(messageClicked()), root,  SLOT(showNormal()));

    trayIcon->show();
  }

  return app.exec();
}
