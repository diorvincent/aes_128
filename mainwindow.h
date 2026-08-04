#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string.h>
#include <QStandardPaths>
#include <QDir>
#include "aes_128_decrypt.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  aes_128_decrypt m_aes128encrypt;
  QString m_strBinFileName;
  QString m_strEncryptFile;

private slots:
  void BrowseFile();
  void Encrypt();
  void Decrypt();

  void dllDecrypt();
  void Exist();
};
#endif // MAINWINDOW_H
