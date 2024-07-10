#include <QApplication>

#include "View/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::Controller controller(&model);
  MainWindow w(&controller);
  w.setWindowTitle("Smart Calculator v2.0");
  w.show();
  return a.exec();
}
