#include "mainwindow.h"

#include <QApplication>
#include <QScreen>
#include <QSharedMemory>
#include<QWidget>
#include<QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
      QSharedMemory shared_memory;
    shared_memory.setKey(QString("PipeClimber"));
    if(shared_memory.attach())
        return -1;
    if(shared_memory.create(1))
    {
        MainWindow mainWindow;
        QIcon icon = QIcon(":/prefix1/app.ico");
        mainWindow.setWindowIcon(icon);
        QScreen *screen = QGuiApplication::primaryScreen();
        if (screen) {
            // 获取主屏幕的分辨率
            QRect screenGeometry = screen->geometry();
            // 计算窗口居中的位置
            int width = mainWindow.width();
            int height = mainWindow.height();
            QPoint center(screenGeometry.x() + screenGeometry.width() / 2 - width / 2,
                          screenGeometry.y() + screenGeometry.height() / 2 - height / 2);

            // 设置窗口的位置
            mainWindow.setGeometry(QRect(center, QSize(width, height)));
        }
        mainWindow.show();
        return a.exec();
    }
	QApplication a(argc, argv);
      QSharedMemory shared_memory;
    shared_memory.setKey(QString("PipeClimber"));
    if(shared_memory.attach())
        return -1;
    if(shared_memory.create(1))
    {
        MainWindow mainWindow;
        QIcon icon = QIcon(":/prefix1/app.ico");
        mainWindow.setWindowIcon(icon);
        QScreen *screen = QGuiApplication::primaryScreen();
        if (screen) {
            // 获取主屏幕的分辨率
            QRect screenGeometry = screen->geometry();
            // 计算窗口居中的位置
            int width = mainWindow.width();
            int height = mainWindow.height();
            QPoint center(screenGeometry.x() + screenGeometry.width() / 2 - width / 2,
                          screenGeometry.y() + screenGeometry.height() / 2 - height / 2);

            // 设置窗口的位置
            mainWindow.setGeometry(QRect(center, QSize(width, height)));
        }
        mainWindow.show();
        return a.exec();
    }

}
