#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    const auto seriaPortInfos=QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &seriaPortInfo:seriaPortInfos){
        ui->comboBox->addItem(seriaPortInfo.portName());
        ui->comboBox->setMinimumSize(85, 20);
        ui->comboBox_2->setMinimumSize(85, 20);
        ui->comboBox_3->setMinimumSize(85, 20);
        ui->comboBox_4->setMinimumSize(85, 20);
        ui->comboBox_5->setMinimumSize(85, 20);
    }
    serialport=new QSerialPort(this);
    connect(serialport,SIGNAL(readyRead()),this,SLOT(ready_read()));
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::open_serial);//打开
    connect(ui->pushButton_2,&QPushButton::clicked,this,&MainWindow::close_seial);//关闭
    connect(ui->pushButton_3,&QPushButton::clicked,this,&MainWindow::ready_write);//发送
    connect(ui->pushButton_4,&QPushButton::clicked,this,&MainWindow::txt_clear);//清除
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::ready_read()
{

    QString buf;
    buf = QString(serialport->readAll());
    ui->recvEdit->appendPlainText(buf);
}
void MainWindow::ready_write(){
    serialport->write(ui->sendEdit->toPlainText().toLocal8Bit().data());
}
void MainWindow::open_serial(){
    QSerialPort::BaudRate baudRate; //波特率
    QSerialPort::DataBits dataBits; //数据位
    QSerialPort::StopBits stopBits; //停止位
    QSerialPort::Parity checkBits; //校验位
    if(ui->comboBox_2->currentText()=="1200")
            baudRate=QSerialPort::Baud1200;
        else if(ui->comboBox_2->currentText()=="2400")
            baudRate=QSerialPort::Baud2400;
        else if(ui->comboBox_2->currentText()=="4800")
            baudRate=QSerialPort::Baud4800;
        else if(ui->comboBox_2->currentText()=="9600")
            baudRate=QSerialPort::Baud9600;
        else if(ui->comboBox_2->currentText()=="19200")
            baudRate=QSerialPort::Baud19200;
        else if(ui->comboBox_2->currentText()=="38400")
            baudRate=QSerialPort::Baud38400;
        else if(ui->comboBox_2->currentText()=="57600")
            baudRate=QSerialPort::Baud57600;
        else if(ui->comboBox_2->currentText()=="115200")
            baudRate=QSerialPort::Baud115200;


    if(ui->comboBox_3->currentText()=="5")
        dataBits=QSerialPort::Data5;
    else if(ui->comboBox_3->currentText()=="6")
        dataBits=QSerialPort::Data6;
    else if(ui->comboBox_3->currentText()=="7")
        dataBits=QSerialPort::Data7;
    else if(ui->comboBox_3->currentText()=="8")
        dataBits=QSerialPort::Data8;

    if (ui->comboBox_5->currentText() == "1" ) stopBits = QSerialPort::OneStop;
    else if(ui->comboBox_5->currentText() == "1.5" )  stopBits = QSerialPort::OneAndHalfStop;
    else if(ui->comboBox_5->currentText() == "2" ) stopBits = QSerialPort::TwoStop;

    if(ui->comboBox_4->currentText()=="无校验") checkBits=QSerialPort::NoParity;
    else if(ui->comboBox_4->currentText()=="奇校验") checkBits=QSerialPort::OddParity;
    else if(ui->comboBox_4->currentText()=="偶校验") checkBits=QSerialPort::EvenParity;

    serialport->setPortName(ui->comboBox->currentText());
    serialport->setBaudRate(baudRate);
    serialport->setDataBits(dataBits);
    serialport->setStopBits(stopBits);
    serialport->setParity(checkBits);
    if(serialport->open(QIODevice::ReadWrite) == true){
    QMessageBox::information(this,"提示","成功");
    }else{
    QMessageBox::critical(this,"提示","失败");
    }
}
void MainWindow::close_seial(){
    serialport->close();
}
void MainWindow::txt_clear(){
    ui->sendEdit->clear();
}
