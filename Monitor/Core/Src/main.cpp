#include "monitor.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
//    QFile file("./material-blue.qss");/*QSS文件所在的路径*/
//        file.open(QIODevice::ReadOnly);
//        if(file.isOpen())
//        {
//            QString strFile = file.readAll();
//            a.setStyleSheet(strFile);
//            file.close();/*记得关闭QSS文件*/
//        }
    Monitor w;
    w.show();
    return a.exec();
}
