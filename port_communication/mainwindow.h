#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void open_serial();
    void close_seial();
    void txt_clear();
    void ready_write();
private slots:
    void ready_read();
private:
    Ui::MainWindow *ui;
    QSerialPort *serialport;
};
#endif // MAINWINDOW_H
