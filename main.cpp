#include "mainwindow.h"
#include <QApplication>
#include "QTranslator"
#include "QString"
#include"QDir"
int main(int argc, char *argv[])
{
 // if (QT_VERSION >= QT_VERSION_CHECK(5, 9, 0))
     //       QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);//适应不同分辨率屏幕

     QApplication a(argc, argv);
//启动画面
      QPixmap pixmap(QCoreApplication::applicationDirPath()+"\\Image\\start_screen.jpg");
      QSplashScreen splash(pixmap);
      splash.show();
      a.processEvents();
 // qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
  //QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
//  QCoreApplication::setAttribute(Qt::AA_Use96Dpi);

 // QCoreApplication::setAttribute(Qt::AA_);
    //QApplication a(argc, argv);
    MainWindow w;
 //   if (QT_VERSION >= QT_VERSION_CHECK(5, 9, 0))
 //             QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);//适应不同分辨率屏幕
    w.show();
//QString file= QDir::currentPath();
//    QTranslator trans;
//       trans.load("qt_zh_CN.qm",file);
//       a.installTranslator(&trans);
    splash.finish(&w);
   //    return a.exec();
    return a.exec();
}
