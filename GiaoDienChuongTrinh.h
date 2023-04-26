//GiaoDienChuongTrinh.h
#ifndef GIAODIENCHUONGTRINH_H
#define GIAODIENCHUONGTRINH_H

#include <QApplication>
#include <QTabWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QProgressBar>
#include <QSlider>
#include <QMessageBox>
#include <QList>
#include <QListWidget>
#include <QStringList>

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QElapsedTimer>


#include <QHostAddress>
#include <QTcpSocket>
#include <QtNetwork>


#define MAX 65535

class GiaoDien : public QWidget
{
    Q_OBJECT
public:
    GiaoDien();
    ~GiaoDien();

signals:
    void hoanThanhKiemTraIP();
    void khongHoanThanhKiemTraIP();

    void IP_lineEdit_rong();
    void IP_lineEdit_khongRong();

    void batDauQuet();
    void hoanThanhQuetCong();

    void daDungQuetCong();

    void dungChuongTrinh();

    void daReset();

    void thoatChuongTrinh();

private:
    QTabWidget *cuaSoThe;
    QWidget *tab1;
    QWidget *tab2;
    QListWidget *listKetQua;




    QString IP_Address;
    QString IP_Address_new;
    //QHostAddress IP_HostgaAddress;
    QLineEdit *IP_lineEdit;
    QPushButton *quet;
    QPushButton *dung;
    QPushButton *nutReset;
    QProgressBar *tienTrinh;
    int trangThai = 1;
    int vitriPort = 1;

    QFile *fileKetQua;




    void create_tab1();
    void create_tab2();
    void create_tab3();
    void create_fileKetQua();

private slots:
    void kiemTraIP_lineEdit();
    void kiemTraIPv4();
    void kiemTraTrangThai();

    void quetCong();
    void Dung();
    void resetChuongTrinh();
    void thoatChuongChinh();

    void resetTienTrinh();
    void resetKetQuaQuet();

    void tbQuetIP();
    void tbErro();
    void tbHoanThanhKiemTraIP();
    void tbHoanThanhQuetCong();
    void tbDungChuongTrinh();
    void tbReset();

    void tbLoiTaoThuMuc();
    void tbloiTaoFile();
    void xoaDuLieuFile();


    bool kiemTraThucMucTonTai(QString tenThuMuc);
    QListWidgetItem *portMo(int port);
    //QListWidgetItem *portDong(int port);
    void ghiKetQuaRaFile(int port);
    void ghiIP();
};










#endif // GIAODIENCHUONGTRINH_H
