#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QLibrary>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow),
    m_strBinFileName("")
{
  ui->setupUi(this);

  connect(ui->pbEncrypt, &QPushButton::clicked, this, &MainWindow::Encrypt);
  connect(ui->pbDecrypt, &QPushButton::clicked, this, &MainWindow::Decrypt);
  connect(ui->pbExist, &QPushButton::clicked, this, &MainWindow::Exist);
  connect(ui->pbBrowse, &QPushButton::clicked, this, &MainWindow::BrowseFile);
  connect(ui->pbDllDecrypt,&QPushButton::clicked, this, &MainWindow::dllDecrypt);

  m_aes128encrypt.my_aes_init();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::BrowseFile()
{
  m_strBinFileName = QFileDialog::getOpenFileName(this, tr("选择固件文件"),
                                                "", tr("Bin Files (*.bin)"));
  ui->teFilePath->setText(m_strBinFileName);
}

void MainWindow::dllDecrypt()
{
  QLibrary aec_128("/aes_128_encrypt.dll");
  if(aec_128.isLoaded())
     QMessageBox::information(this,QStringLiteral("信息"), QStringLiteral("aec_128_encrypt.dll已经被载入"));
  else
    {
      QMessageBox::critical(this, QStringLiteral("错误"),QStringLiteral("解密库文件aec_128_encrypt.dll加载失败"));
      return;
    }

   typedef void (*AES_128_CMAC)(const char *buffer, uint16_t size, const uint8_t *key, uint8_t *token); //需要声明函数原型的类型
   AES_128_CMAC  AEC_128_Decrypt=(AES_128_CMAC)aec_128.resolve("AES_128_CMAC"); //解析DLL中的AES_128_CMAC函数

   //aes-128 encrypt bin data
   QByteArray binArr;
   QFile* firmwareFile = new QFile(m_strBinFileName);
   if (!firmwareFile->open(QIODevice::ReadOnly)) {
       QMessageBox::critical(this, tr("文件错误"),
                            tr("无法打开固件文件：%1").arg(firmwareFile->errorString()));
       delete firmwareFile;
       firmwareFile = nullptr;
       return;
   }
   firmwareFile->close();
   delete firmwareFile;
   firmwareFile = nullptr;

   quint64 uBinSize = firmwareFile->size();
   binArr.append(firmwareFile->readAll());

   unsigned char aes_key[16] = {0x43,0x44,0x45,0x46,0x31,0x32,0x33,0x34,0x39,0x30,0x41,0x42,0x35,0x36,0x37,0x38};
   int encryptDataSize = uBinSize*4 + 1;
   unsigned char encrypt_data[encryptDataSize];
   //invoke dlls' func
   AEC_128_Decrypt(binArr.data(), uBinSize, aes_key, encrypt_data);


   //保存加密后的文件
   QString strFile;
   int nPos = m_strBinFileName.lastIndexOf("/");
   strFile = m_strBinFileName.left(nPos) + "/encrypt.bin";

   QFile* binFile = new QFile(strFile);
   if (!binFile->open(QIODevice::WriteOnly)) {
       QMessageBox::critical(this, tr("文件错误"),
                            tr("无法打开固件文件：%1").arg(binFile->errorString()));
       delete binFile;
       binFile = nullptr;
       return;
   }
   else{
       QByteArray baEncrypt;
       for(int i = 0; i< (int)uBinSize; i++)
         baEncrypt.append(encrypt_data[i]);
       binFile->write(baEncrypt , uBinSize);

       binFile->close();
       delete binFile;
       binFile = nullptr;

       ui->teFileContent->setHtml(baEncrypt);

       QMessageBox::information(this, tr("提示"), tr("Bin已完成加密,加密后的文件名为encrypt.bin"));
   }
}

void MainWindow::Encrypt()
{
  //aes-128 encrypt bin data
  QByteArray binArr;
  QFile* firmwareFile = new QFile(m_strBinFileName);
  if (!firmwareFile->open(QIODevice::ReadOnly)) {
      QMessageBox::critical(this, tr("文件错误"),
                           tr("无法打开固件文件：%1").arg(firmwareFile->errorString()));
      delete firmwareFile;
      firmwareFile = nullptr;
      return;
  }

  //each encrypt block size 160 byte
  int nBlockSize = 160;
  quint64 uBinSize = firmwareFile->size();
  int nReadTimes = uBinSize/nBlockSize + 1;
  char pBuff[nBlockSize];

  for(int i = 0; i<nReadTimes; i++)
  {
    memset(pBuff, 0, sizeof(pBuff));
    firmwareFile->seek(i * nBlockSize);
    firmwareFile->read(pBuff, nBlockSize);

    //要加密的内容
    unsigned char sourceMsg[nBlockSize];
    unsigned char encrypt_data[nBlockSize*4+1];

    memset(encrypt_data, 0, nBlockSize*4+1);
    memcpy(sourceMsg, pBuff, nBlockSize);

    m_aes128encrypt.PrintData("sourceMsg", sourceMsg, nBlockSize);
    m_aes128encrypt.my_aes_encrypt(sourceMsg,encrypt_data, nBlockSize);

    //保存加密后的文件
    QString strFile;
    int nPos = m_strBinFileName.lastIndexOf("/");
    strFile = m_strBinFileName.left(nPos) + "/encrypt.bin";

    QFile* binFile = new QFile(strFile);
    if (!binFile->open(QIODevice::WriteOnly | QIODevice::Append)) {
        QMessageBox::critical(this, tr("文件错误"),
                             tr("无法打开固件文件：%1").arg(binFile->errorString()));
        delete binFile;
        binFile = nullptr;
        return;
    }
    else{
        QByteArray baEncrypt;
        for(int i = 0; i< nBlockSize; i++)
          baEncrypt.append(encrypt_data[i]);
        binFile->write(baEncrypt , nBlockSize);

        binFile->close();
        delete binFile;
        binFile = nullptr;

        ui->teFileContent->append(baEncrypt);
    }
  }

  firmwareFile->close();
  delete firmwareFile;
  firmwareFile = nullptr;

  QMessageBox::information(this, tr("提示"), tr("Bin已完成加密,加密后的文件名为encrypt.bin"));
}

void MainWindow::Exist()
{
  close();
}

void MainWindow::Decrypt()
{
  //aes-128 decrypt bin data
  QByteArray binArr;
  QFile* firmwareFile = new QFile(m_strBinFileName);

  if (!firmwareFile->open(QIODevice::ReadOnly)) {
      QMessageBox::critical(this, tr("文件错误"),
                           tr("无法打开固件文件：%1").arg(firmwareFile->errorString()));
      delete firmwareFile;
      firmwareFile = nullptr;
      return;
  }

  //each encrypt block size 160 byte
  int nBlockSize = 160;
  quint64 uBinSize = firmwareFile->size();
  int nReadTimes = uBinSize/nBlockSize + 1;
  char pBuff[nBlockSize];

  for(int i = 0; i< nReadTimes; i++)
  {
      memset(pBuff, 0, sizeof(pBuff));
      firmwareFile->seek(i * nBlockSize);
      if(i==nReadTimes - 1)
      {
        nBlockSize = uBinSize % nBlockSize;
        firmwareFile->read(pBuff, nBlockSize);
      }
      else
      {  firmwareFile->read(pBuff, nBlockSize);}

      //要解密的内容
      unsigned char sourceMsg[nBlockSize];
      unsigned char decrypt_data[nBlockSize];

      memset(decrypt_data, 0, nBlockSize);
      memcpy(sourceMsg, pBuff, nBlockSize);

      m_aes128encrypt.PrintData("sourceMsg", sourceMsg, nBlockSize);
      m_aes128encrypt.my_aes_decrypt(sourceMsg,decrypt_data, nBlockSize);

      //保存加密后的文件
      QString strNewPath;
      // 获取系统临时目录的路径
      QString tempDirPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation);

      int nPos = m_strBinFileName.lastIndexOf("/");
      strNewPath =m_strBinFileName.left(nPos) + "/decrypt.bin";

      //strNewPath =tempDirPath + "/decrypt.bin";

      QFile* binFile = new QFile(strNewPath);
      //if(binFile->exists())
      //  binFile->remove(strNewPath);

      if (!binFile->open(QIODevice::WriteOnly | QIODevice::Append)) {
          QMessageBox::critical(this, tr("文件错误"),
                               tr("无法打开固件文件：%1").arg(binFile->errorString()));
          delete binFile;
          binFile = nullptr;
          return;
      }
      else{
          QByteArray baDecrypt;
          for(int i = 0; i< nBlockSize; i++)
            baDecrypt.append(decrypt_data[i]);

          binFile->write(baDecrypt , nBlockSize);
          //binFile->remove(strNewPath);

          binFile->close();
          delete binFile;
          binFile = nullptr;

          ui->teFileContent->append(baDecrypt);
      }
  }


  firmwareFile->close();
  delete firmwareFile;
  firmwareFile = nullptr;
  QMessageBox::information(this, tr("提示"), tr("Bin已完成解密,解密后的文件名为decrypt.bin"));

}
