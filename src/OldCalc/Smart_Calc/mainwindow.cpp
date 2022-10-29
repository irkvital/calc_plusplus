#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->Graph_plot->setInteraction(QCP::iRangeZoom, true);
  ui->Graph_plot->setInteraction(QCP::iRangeDrag, true);

  // Цвет фона
  QLinearGradient plotGradient;
  plotGradient.setStart(0, 0);
  plotGradient.setFinalStop(0, 350);
  plotGradient.setColorAt(0, QColor(100, 80, 80));
  plotGradient.setColorAt(1, QColor(30, 50, 130));
  ui->Graph_plot->setBackground(plotGradient);

  connect(ui->but_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->but_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->but_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->but_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->but_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->but_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->but_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->but_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->but_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->but_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->but_dot, SIGNAL(clicked()), this, SLOT(digits_numbers()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString output = ui->inputString->text() + button->text();
  ui->inputString->setText(output);
}

int MainWindow::checkCorrect(char *str) {
  char *tmp_point = str;
  int check_correct = 0, count_dots = 0;
  while (*tmp_point && check_correct == 0) {
    if ((*tmp_point >= '0' && *tmp_point <= '9') || *tmp_point == '.' ||
        *tmp_point == '-') {
      if (*tmp_point == '.') count_dots++;
      if (count_dots > 1) check_correct++;
    } else
      check_correct++;
    tmp_point++;
  }
  return check_correct;
}

void MainWindow::on_but_eq_clicked() {
  char str_x[MAX_LEN_RES] = "";
  strncpy(str_x, ui->inputX->text().toStdString().c_str(), MAX_LEN_RES);
  int check_correct = checkCorrect(str_x);

  if (check_correct == 0) {
    QString input_q = ui->inputString->text();
    char input[MAX_LEN_RES] = "";
    strncpy(input, input_q.toStdString().c_str(), MAX_LEN_RES);
    double x = ui->inputX->text().toDouble();
    char output[MAX_LEN_RES] = "";
    calculator(input, x, output);
    ui->inputString->setText(output);
  } else {
    ui->inputX->setText("INCORRECT!!!");
  }
}

void MainWindow::on_inputString_returnPressed() {
  MainWindow::on_but_eq_clicked();
}

void MainWindow::on_but_clear_clicked() { ui->inputString->setText(""); }

void MainWindow::on_but_sin_clicked() {
  QString output = ui->inputString->text() + "sin(";
  ui->inputString->setText(output);
}

void MainWindow::on_but_asin_clicked() {
  QString output = ui->inputString->text() + "asin(";
  ui->inputString->setText(output);
}

void MainWindow::on_but_cos_clicked() {
  QString output = ui->inputString->text() + "cos(";
  ui->inputString->setText(output);
}

void MainWindow::on_but_acos_clicked() {
  QString output = ui->inputString->text() + "acos(";
  ui->inputString->setText(output);
}

void MainWindow::on_but_tan_clicked() {
  QString output = ui->inputString->text() + "tan(";
  ui->inputString->setText(output);
}

void MainWindow::on_but_atan_clicked() {
  QString output = ui->inputString->text() + "atan(";
  ui->inputString->setText(output);
}

void MainWindow::on_but_x_clicked() {
  QString output = ui->inputString->text() + "x";
  ui->inputString->setText(output);
}

void MainWindow::on_but_ln_clicked() {
  QString output = ui->inputString->text() + "ln(";
  ui->inputString->setText(output);
}

void MainWindow::on_but_log_clicked() {
  QString output = ui->inputString->text() + "log(";
  ui->inputString->setText(output);
}

void MainWindow::on_but_sqrt_clicked() {
  QString output = ui->inputString->text() + "sqrt(";
  ui->inputString->setText(output);
}

void MainWindow::on_but_mod_clicked() {
  QString output = ui->inputString->text() + "mod";
  ui->inputString->setText(output);
}

void MainWindow::on_but_bracket_left_clicked() {
  QString output = ui->inputString->text() + "(";
  ui->inputString->setText(output);
}

void MainWindow::on_but_bracket_right_clicked() {
  QString output = ui->inputString->text() + ")";
  ui->inputString->setText(output);
}

void MainWindow::on_but_exp_clicked() {
  QString output = ui->inputString->text() + "^";
  ui->inputString->setText(output);
}

void MainWindow::on_but_div_clicked() {
  QString output = ui->inputString->text() + "/";
  ui->inputString->setText(output);
}

void MainWindow::on_but_mul_clicked() {
  QString output = ui->inputString->text() + "*";
  ui->inputString->setText(output);
}

void MainWindow::on_but_minus_clicked() {
  QString output = ui->inputString->text() + "-";
  ui->inputString->setText(output);
}

void MainWindow::on_but_plus_clicked() {
  QString output = ui->inputString->text() + "+";
  ui->inputString->setText(output);
}

void MainWindow::on_but_del_clicked() {
  QString output = ui->inputString->text();
  output.chop(1);
  ui->inputString->setText(output);
}

void MainWindow::on_but_graph_clicked() {
  // Считывание x_max, x_min, x_step, обработка ошибок
  QString input_q = ui->inputString->text();
  char input[MAX_LEN_RES] = "";
  char output[MAX_LEN_RES] = "";
  char max_x[MAX_LEN_RES] = "";
  char min_x[MAX_LEN_RES] = "";
  char step_x[MAX_LEN_RES] = "";
  int check_correct_max = 0, check_correct_min = 0, check_correct_step = 0;
  double tmp = 0;

  strncpy(max_x, ui->str_x_max->text().toStdString().c_str(), MAX_LEN_RES);
  check_correct_max = checkCorrect(max_x);

  strncpy(min_x, ui->str_x_min->text().toStdString().c_str(), MAX_LEN_RES);
  check_correct_min = checkCorrect(min_x);

  strncpy(step_x, ui->str_x_step->text().toStdString().c_str(), MAX_LEN_RES);
  check_correct_step = checkCorrect(step_x);

  strncpy(input, input_q.toStdString().c_str(), MAX_LEN_RES);
  double x_min = ui->str_x_min->text().toDouble();
  double x_max = ui->str_x_max->text().toDouble();
  double x_step = ui->str_x_step->text().toDouble();
  if ((x_min >= x_max && x_step <= 0) ||
      ((check_correct_max || check_correct_min) && check_correct_step)) {
    ui->str_err->setText("ERROR STEP & MAX/MIN");
    return;
  } else if (x_min >= x_max || (check_correct_max || check_correct_min)) {
    ui->str_err->setText("ERR MAX/MIN");
    return;
  } else if (x_step <= 0 || check_correct_step) {
    ui->str_err->setText("ERR STEP");
    return;
  } else if (polish(input, output) == 0) {
    int flag = calc(output, x_min, &tmp);
    if (flag == 0 || flag == DIV_ZERO) {
      ui->str_err->setText("y = " + input_q);
    } else {
      ui->str_err->setText("WRONG INPUT FUNCTION");
    }
  } else {
    ui->str_err->setText("WRONG INPUT FUNCTION");
  }

  // Вычисление точек графика
  int n = (x_max - x_min) / x_step + 1;
  double minY = tmp, maxY = tmp;
  QVector<double> x, y;
  int count = 0;
  for (double i = x_min; count < n; i = x_min + count * x_step) {
    calc(output, i, &tmp);
    if (isnan(tmp) == 0) {
      x.push_back(i);
      y.push_back(tmp);
      if (tmp < minY) minY = tmp;
      if (tmp > maxY) maxY = tmp;
    }
    count++;
  }

  if ((minY - maxY) < 10e-6) {
    minY -= 0.5;
    maxY += 0.5;
  }
  // Настройки отображения графика
  ui->Graph_plot->addGraph();
  ui->Graph_plot->graph(0)->setData(x, y);
  ui->Graph_plot->xAxis->setRange(x_min,
                                  x_max);  // Текущий диапазон отображения оси X
  ui->Graph_plot->yAxis->setRange(minY,
                                  maxY);  // Текущий диапазон отображения оси Y
  ui->Graph_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->Graph_plot->graph(0)->setPen(QColor(255, 255, 255, 255));
  ui->Graph_plot->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
  ui->Graph_plot->replot();
}

void MainWindow::on_but_credit_clicked() {
  char input_amount[MAX_LEN_RES] = "";
  char input_term[MAX_LEN_RES] = "";
  char input_rate[MAX_LEN_RES] = "";

  strncpy(input_amount, ui->inp_amount->text().toStdString().c_str(),
          MAX_LEN_RES);
  int check_correct_amount = checkCorrect(input_amount);
  double amount = ui->inp_amount->text().toDouble();
  if (check_correct_amount != 0 || amount < 0)
    ui->inp_amount->setText("WRONG INPUT");

  strncpy(input_term, ui->inp_term->text().toStdString().c_str(), MAX_LEN_RES);
  int check_correct_term = checkCorrect(input_term);
  double term = ui->inp_term->text().toDouble();
  if (check_correct_term != 0 || term < 0) ui->inp_term->setText("WRONG INPUT");

  strncpy(input_rate, ui->inp_persent->text().toStdString().c_str(),
          MAX_LEN_RES);
  int check_correct_rate = checkCorrect(input_rate);
  double rate = ui->inp_persent->text().toDouble() / 100.;
  if (check_correct_rate != 0 || rate < 0)
    ui->inp_persent->setText("WRONG INPUT");

  if (!check_correct_amount && !check_correct_term && !check_correct_rate) {
    if (ui->annuity->isChecked()) {
      // ANNUITY
      double rate_month = rate / 12;
      double month_payment =
          amount * (rate_month / (1 - pow((1 + rate_month), -term)));
      double overpayment = (month_payment * term) - amount;
      ui->out_payment->setText(QString::number(month_payment, 'f', 2));
      ui->out_overpayment->setText(QString::number(overpayment, 'f', 2));
      ui->out_total->setText(QString::number(overpayment + amount, 'f', 2));
    } else if (ui->differentiated->isChecked()) {
      // DIFFERENTIATED
      double rate_month = rate / 12;
      double overpayment = 0;
      double amount_month = amount / term;  // Ежемесячное тело долга
      double amount_curr = amount;     // Остаток тела долга
      double first_month_payment = 0;  // Платеж в первый месяц
      double over_month = 0;  // Проценты за текущий месяц
      for (int i = 0; i < term; i++) {
        over_month = amount_curr * rate_month;
        if (i == 0) first_month_payment = amount_month + over_month;
        overpayment += over_month;
        amount_curr -= amount_month;
      }
      ui->out_payment->setText(
          QString::number(first_month_payment, 'f', 2) + ".." +
          QString::number(over_month + amount_month, 'f', 2));
      ui->out_overpayment->setText(QString::number(overpayment, 'f', 2));
      ui->out_total->setText(QString::number(overpayment + amount, 'f', 2));
    }
  }
}
