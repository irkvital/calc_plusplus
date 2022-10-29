#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <cstdio>

#include "../func/func.h"
#include "./qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
 private slots:
  int checkCorrect(char *str);
  void digits_numbers();
  void on_but_eq_clicked();
  void on_inputString_returnPressed();
  void on_but_clear_clicked();
  void on_but_sin_clicked();
  void on_but_asin_clicked();
  void on_but_cos_clicked();
  void on_but_acos_clicked();
  void on_but_tan_clicked();
  void on_but_atan_clicked();
  void on_but_x_clicked();
  void on_but_ln_clicked();
  void on_but_log_clicked();
  void on_but_sqrt_clicked();
  void on_but_mod_clicked();
  void on_but_bracket_left_clicked();
  void on_but_bracket_right_clicked();
  void on_but_exp_clicked();
  void on_but_div_clicked();
  void on_but_mul_clicked();
  void on_but_minus_clicked();
  void on_but_plus_clicked();
  void on_but_del_clicked();
  void on_but_graph_clicked();

  void on_but_credit_clicked();

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
