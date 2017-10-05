#include "coefficientmanager.h"
#include "ui_coefficientmanager.h"
#include <vector>
#include <fstream>
#include "Player.h"
#include <QMessageBox>

using namespace std;

void CoefficientManager::refreshCoefficients(const vector<double> & vect_of_coef)
{
  ui->coef_1_LineEdit->setText(QString::number(vect_of_coef[0]));
  ui->coef_2_LineEdit->setText(QString::number(vect_of_coef[1]));
  ui->coef_3_LineEdit->setText(QString::number(vect_of_coef[2]));
  ui->coef_4_LineEdit->setText(QString::number(vect_of_coef[3]));
  ui->coef_5_LineEdit->setText(QString::number(vect_of_coef[4]));
  ui->coef_6_LineEdit->setText(QString::number(vect_of_coef[5]));
  ui->coef_7_LineEdit->setText(QString::number(vect_of_coef[6]));
  ui->coef_8_LineEdit->setText(QString::number(vect_of_coef[7]));
  ui->coef_9_LineEdit->setText(QString::number(vect_of_coef[8]));
  ui->coef_10_LineEdit->setText(QString::number(vect_of_coef[9]));
  ui->coef_11_LineEdit->setText(QString::number(vect_of_coef[10]));
  ui->coef_12_LineEdit->setText(QString::number(vect_of_coef[11]));
  ui->coef_13_LineEdit->setText(QString::number(vect_of_coef[12]));
  ui->coef_14_LineEdit->setText(QString::number(vect_of_coef[13]));
  ui->coef_15_LineEdit->setText(QString::number(vect_of_coef[14]));
  ui->coef_16_LineEdit->setText(QString::number(vect_of_coef[15]));
}

CoefficientManager::CoefficientManager(vector<double> & vect_of_coef, QWidget *parent, Qt::WindowFlags f) :
  QDialog(parent, f),
  ui(new Ui::CoefficientManager),
  coefficients(vect_of_coef)
{
  ui->setupUi(this);

  ui->coef_1_LineEdit->setValidator(new QDoubleValidator(-1.0, 1.0, 15, this));
  ui->coef_2_LineEdit->setValidator(new QDoubleValidator(-1.0, 1.0, 15, this));
  ui->coef_3_LineEdit->setValidator(new QDoubleValidator(-1.0, 1.0, 15, this));
  ui->coef_4_LineEdit->setValidator(new QDoubleValidator(-1.0, 1.0, 15, this));
  ui->coef_5_LineEdit->setValidator(new QDoubleValidator(-1.0, 1.0, 15, this));
  ui->coef_6_LineEdit->setValidator(new QDoubleValidator(-1.0, 1.0, 15, this));
  ui->coef_7_LineEdit->setValidator(new QDoubleValidator(-1.0, 1.0, 15, this));
  ui->coef_8_LineEdit->setValidator(new QDoubleValidator(-1.0, 1.0, 15, this));
  ui->coef_9_LineEdit->setValidator(new QDoubleValidator(-1.0, 1.0, 15, this));
  ui->coef_10_LineEdit->setValidator(new QDoubleValidator(-1.0, 1.0, 15, this));
  ui->coef_11_LineEdit->setValidator(new QDoubleValidator(-1.0, 1.0, 15, this));
  ui->coef_12_LineEdit->setValidator(new QDoubleValidator(-1.0, 1.0, 15, this));
  ui->coef_13_LineEdit->setValidator(new QDoubleValidator(-1.0, 1.0, 15, this));
  ui->coef_14_LineEdit->setValidator(new QDoubleValidator(-1.0, 1.0, 15, this));
  ui->coef_15_LineEdit->setValidator(new QDoubleValidator(-1.0, 1.0, 15, this));
  ui->coef_16_LineEdit->setValidator(new QDoubleValidator(-1.0, 1.0, 15, this));

  this->refreshCoefficients(coefficients);

}

CoefficientManager::~CoefficientManager()
{
  delete ui;
}

void CoefficientManager::on_readCoeffiecientsFromFileButton_clicked()
{
  string fileName = "Optimization_Results//";
  fileName += ui->fileNameLineEdit->text().toStdString();
  fileName += ".txt";

  ifstream fin(fileName.c_str());
  if (!fin.is_open())
  {
    QString message = "Fails ar nosaukumu ";
    message += ui->fileNameLineEdit->text();
    message += " nebija atrasts!\n";
    QMessageBox::critical(this, QString("Kļūda!"), message);
    return;
  }

  vector<double> loadedEvaluationFunction;
  double currentCoefficient;
  int currentCoefficientNumber = 0;
  while (currentCoefficientNumber < EvaluationFunctionPlayer::NUMBER_OF_COEF_IN_EVAL_FUN && !fin.eof())
  {
    fin >> currentCoefficient;

    if (fin.fail())
    {
      QString message = "Fails ar nosaukumu ";
      message += ui->fileNameLineEdit->text();
      message += " satur nederīgus datus!\n";
      QMessageBox::critical(this, QString("Kļūda!"), message);
      fin.close();
      return;
    }
    else
    {
      loadedEvaluationFunction.push_back(currentCoefficient);
      currentCoefficientNumber++;
    }
  }

  fin.close();

  if (currentCoefficientNumber < EvaluationFunctionPlayer::NUMBER_OF_COEF_IN_EVAL_FUN)
  {
    QString message = "Fails ar nosaukumu ";
    message += ui->fileNameLineEdit->text();
    message += " satur mazāk koeficientu, nekā ir vajadzīgs!\n";
    QMessageBox::critical(this, QString("Kļūda!"), message);
    return;
  }
  else
    this->refreshCoefficients(loadedEvaluationFunction);
}

void CoefficientManager::on_saveCoefficientsButton_clicked()
{
  vector<double> newCoefficients(EvaluationFunctionPlayer::NUMBER_OF_COEF_IN_EVAL_FUN);
  double currentCoefficient;

  currentCoefficient = ui->coef_1_LineEdit->text().toDouble();
  newCoefficients[0] = currentCoefficient;
  currentCoefficient = ui->coef_2_LineEdit->text().toDouble();
  newCoefficients[1] = currentCoefficient;
  currentCoefficient = ui->coef_3_LineEdit->text().toDouble();
  newCoefficients[2] = currentCoefficient;
  currentCoefficient = ui->coef_4_LineEdit->text().toDouble();
  newCoefficients[3] = currentCoefficient;
  currentCoefficient = ui->coef_5_LineEdit->text().toDouble();
  newCoefficients[4] = currentCoefficient;
  currentCoefficient = ui->coef_6_LineEdit->text().toDouble();
  newCoefficients[5] = currentCoefficient;
  currentCoefficient = ui->coef_7_LineEdit->text().toDouble();
  newCoefficients[6] = currentCoefficient;
  currentCoefficient = ui->coef_8_LineEdit->text().toDouble();
  newCoefficients[7] = currentCoefficient;
  currentCoefficient = ui->coef_9_LineEdit->text().toDouble();
  newCoefficients[8] = currentCoefficient;
  currentCoefficient = ui->coef_10_LineEdit->text().toDouble();
  newCoefficients[9] = currentCoefficient;
  currentCoefficient = ui->coef_11_LineEdit->text().toDouble();
  newCoefficients[10] = currentCoefficient;
  currentCoefficient = ui->coef_12_LineEdit->text().toDouble();
  newCoefficients[11] = currentCoefficient;
  currentCoefficient = ui->coef_13_LineEdit->text().toDouble();
  newCoefficients[12] = currentCoefficient;
  currentCoefficient = ui->coef_14_LineEdit->text().toDouble();
  newCoefficients[13] = currentCoefficient;
  currentCoefficient = ui->coef_15_LineEdit->text().toDouble();
  newCoefficients[14] = currentCoefficient;
  currentCoefficient = ui->coef_16_LineEdit->text().toDouble();
  newCoefficients[15] = currentCoefficient;

  int i = 0;
  while (i < 16 && newCoefficients[i] >= -1.0 && newCoefficients[i] <= 1.0)
    i++;
  if (i < 16)
  {
    QString message = QString::number(i + 1);
    message += ". coeficients nav robežos [-1.0; 1.0].\nLūdzu, ierakstiet derīgo koeficienta vērtību.";
    QMessageBox::warning(this, QString("Kļūda!"), message);
    return;
  }
  else
  {
    coefficients = newCoefficients;
    this->close();
  }
}



void CoefficientManager::on_backButton_clicked()
{
  this->close();
}
