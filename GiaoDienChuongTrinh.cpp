//GiaoDienChuongTrinh.cpp
#include "GiaoDienChuongTrinh.h"

GiaoDien::GiaoDien() : QWidget()
{
    //khoi tao
    cuaSoThe = new QTabWidget(this);
    tab1 = new QWidget;
    tab2 = new QWidget;

    cuaSoThe->addTab(tab1, "Thong Tin");
    cuaSoThe->addTab(tab2, "Ket Qua");

    //tab1
    create_tab1();
    //tab2
    create_tab2();

    create_fileKetQua();


    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->addWidget(cuaSoThe);
    setLayout(vbox);
};

GiaoDien::~GiaoDien()
{
    delete cuaSoThe;
    delete tab1;
    delete tab2;
    delete tienTrinh;
}


void GiaoDien::create_tab1()
{
    QGridLayout *cuaSo1 = new QGridLayout(tab1);

    QLabel *label = new QLabel("IP Address: ");
    QLabel *label2 = new QLabel("Tien Trinh:");
    QPushButton *thoat = new QPushButton("Thoat");
    nutReset = new QPushButton("Reset");
    IP_lineEdit = new QLineEdit();
    IP_Address = IP_lineEdit->text();

    quet = new QPushButton("Quet");
    dung = new QPushButton("Dung");
    tienTrinh = new QProgressBar();
    tienTrinh->setRange(1,MAX);
    tienTrinh->setValue(1);

    //nhan tin hieu khi nhan nut quet kiem tra IP_lineEdit
    connect(quet,SIGNAL(clicked(bool)),this,SLOT(kiemTraIP_lineEdit()));
    connect(this,SIGNAL(IP_lineEdit_rong()),this,SLOT(tbErro()));
    connect(this,SIGNAL(IP_lineEdit_khongRong()),this,SLOT(kiemTraIPv4()));
    connect(this,SIGNAL(khongHoanThanhKiemTraIP()),this,SLOT(tbErro()));
    connect(this,SIGNAL(hoanThanhKiemTraIP()),this,SLOT(kiemTraTrangThai()));
    connect(this,SIGNAL(batDauQuet()),this,SLOT(quetCong()));

    connect(this,SIGNAL(hoanThanhQuetCong()),this,SLOT(tbHoanThanhQuetCong()));


    //tin hieu nhan nut dung
    connect(dung,SIGNAL(clicked(bool)),this,SLOT(Dung()));
    connect(this,SIGNAL(daDungQuetCong()),this,SLOT(tbDungChuongTrinh()));

    //tin hieu reset
    connect(nutReset,SIGNAL(clicked(bool)),this,SLOT(resetChuongTrinh()));
    connect(this,SIGNAL(daReset()),this,SLOT(tbReset()));

    //tin hieu nut thoat
    connect(thoat,SIGNAL(clicked(bool)),this,SLOT(thoatChuongChinh()));
    connect(this,SIGNAL(dungChuongTrinh()),this,SLOT(Dung()));

    cuaSo1->addWidget(label,0,0);
    cuaSo1->addWidget(IP_lineEdit,0,2,1,3);
    cuaSo1->addWidget(label2,1,0);
    cuaSo1->addWidget(tienTrinh,1,2,1,3);
    cuaSo1->addWidget(quet,2,0,1,2);
    cuaSo1->addWidget(nutReset,3,0,1,2);
    cuaSo1->addWidget(dung,2,2,1,3);
    cuaSo1->addWidget(thoat,3,2,1,3);
    tab1->setLayout(cuaSo1);
};

void GiaoDien::create_tab2()
{
    listKetQua = new  QListWidget();
    QVBoxLayout *cuaSo2 = new QVBoxLayout(tab2);
    cuaSo2->addWidget(listKetQua);
    tab2->setLayout(cuaSo2);
};

void GiaoDien::create_fileKetQua()
{
    QString tenThuMuc = "ketQua";

    if(!kiemTraThucMucTonTai(tenThuMuc))
    {
        QDir dir;
        if (!dir.mkdir("ketQua"))
        {
            tbLoiTaoThuMuc();// không thể tạo thư mục mới
        }

        fileKetQua = new QFile(tenThuMuc+"/portOpen.txt");
        if (!fileKetQua->open(QIODevice::WriteOnly | QIODevice::Text))
        {
            tbloiTaoFile();// không thể tạo file mới
        }
    }
    else
    {
        fileKetQua = new QFile(tenThuMuc+"/portOpen.txt");
        if (!fileKetQua->open(QIODevice::WriteOnly | QIODevice::Text))
        {
            tbloiTaoFile();// không thể tạo file mới
        }
    }
    fileKetQua->close();
    QString message = "Tao file thang cong";
    QMessageBox::information(this, "Thong Bao", message);
}

void GiaoDien::thoatChuongChinh()
{
    //tao tin hien thoat

    int luaCHon = QMessageBox::question(this,"thong bao","Ban co muon thoat chuong trinh?");
    if(luaCHon == QMessageBox::Yes)
    {
        trangThai = 0;
        qApp->exit(1);
    }
    else if(luaCHon == QMessageBox::No)
    {
        emit dungChuongTrinh();
    }
};

void GiaoDien::Dung()
{
    //set trang thai
    trangThai = 0;
    emit daDungQuetCong();
};

void GiaoDien::kiemTraIP_lineEdit()
{
    if(IP_lineEdit->text().isEmpty())
    {
        //rong
        emit IP_lineEdit_rong();
    }
    else
    {
        //khong rong
        emit IP_lineEdit_khongRong();
    }
}

void GiaoDien::kiemTraTrangThai()
{
    if(trangThai == 1)
    {
        QMessageBox::information(this, "Thong Bao", "Quet IP: " + IP_Address);
        xoaDuLieuFile();
        ghiIP();
        listKetQua->clear();
        vitriPort = 1;
        emit batDauQuet();
    }
    if(trangThai == 2)
    {
        //hoi nguoi dung co tiep tui quet khong
        int luaCHon = QMessageBox::question(this,"thong bao","Ban co muon tiep tuc quet?");
        if(luaCHon == QMessageBox::Yes)
        {
            trangThai = 1;
            QMessageBox::information(this, "Thong Bao", "Quet IP: " + IP_Address);
            emit batDauQuet();
        }
        else if(luaCHon == QMessageBox::No)
        {

            trangThai = 1;
            vitriPort = 1;
            listKetQua->clear();
            QMessageBox::information(this, "Thong Bao", "Quet IP: " + IP_Address);
            xoaDuLieuFile();
            ghiIP();
            emit batDauQuet();
        }
    }
    else if(trangThai == 3)
    {
        trangThai = 1;
        vitriPort = 1;
        xoaDuLieuFile();
        ghiIP();
        listKetQua->clear();
        QMessageBox::information(this, "Thong Bao", "Quet IP: " + IP_Address);
        emit batDauQuet();
    }

}

void GiaoDien::kiemTraIPv4()
{
    IP_Address_new = IP_lineEdit->text();
    QStringList octets = IP_Address_new.split(".");
    if(octets.size() != 4)
    {
        emit khongHoanThanhKiemTraIP();
    }
    else
    {
        for(int i = 0; i < octets.size(); i++)
        {
            bool ok;
            int octetValue = octets[i].toInt(&ok);
            if(!ok || octetValue < 0 || octetValue > 255)
            {
                emit khongHoanThanhKiemTraIP();
            }
        }
    }
    if(IP_Address.isEmpty())//IP_address hien tai rong thi
    {
        IP_Address = IP_Address_new;
        trangThai = 1;
    }
    else if(IP_Address == IP_Address_new && trangThai == 4)//vao trang thai tiep tuc quet
    {
        trangThai = 1;
    }
    else if(IP_Address == IP_Address_new && trangThai != 4)
    {
        trangThai = 2;//quet chuong trinh lai
    }
    else if(IP_Address != IP_Address_new)
    {
        trangThai = 3;
        IP_Address = IP_Address_new;
    }
    emit hoanThanhKiemTraIP();
}


void GiaoDien::quetCong()
{
    int port;
    port = vitriPort; //set port bang vitriport
    tienTrinh->setValue(port);//set thanh tien trinh

    for (; port < MAX; port++) //vong lap quet tu vitriport den max
    {
        if(trangThai == -1)//da nhan vao nut reset
        {
            port = 1;
            QCoreApplication::processEvents();
            break;
        }

        //thuc hien ket noi va quet port cua ip dich
        QTcpSocket socket;
        socket.connectToHost(IP_Address, port);
        if (socket.waitForConnected(1000))
        {
            // Nếu kết nối thành công
            listKetQua->addItem(portMo(port));//them vao danh sach ket qua
            ghiKetQuaRaFile(port);//goi ham ghi len file
            QCoreApplication::processEvents();//cap nhat giao dien
        }

        tienTrinh->setValue(port);//set thanh tien trinh
        vitriPort = port;//cap nhat vitri port
        QCoreApplication::processEvents();

        if(trangThai == 0)//da nhan dung
        {
            QCoreApplication::processEvents();
            break;
        }
    }
    tienTrinh->setValue(port);//set thanh tien trinh
    vitriPort = port;//cap nhat vitri port
    //thuc hien quet xong
    if(vitriPort == MAX)
    {
        trangThai = 4;
        emit hoanThanhQuetCong();
    }

    tienTrinh->setValue(port);
    QCoreApplication::processEvents();//cap nhap giao dien
};



QListWidgetItem* GiaoDien::portMo(int port)
{
    QString itemText = "prot: " + QString::number(port) + " ---" + "Dang Mo";
    QListWidgetItem* newItem = new QListWidgetItem(itemText);
    return newItem;
}

//QListWidgetItem* GiaoDien::portDong(int port)
//{
//    QString itemText = "prot: " + QString::number(port) + "---" + "Ddp mo";
//    QListWidgetItem* newItem = new QListWidgetItem(itemText);
//    return newItem;
//}


void GiaoDien::tbQuetIP()
{
    QMessageBox::information(this, "Thong Bao", "Quet IP: " + IP_Address);
}

void GiaoDien::tbErro()
{
    QString message = "Dia chi IP khong hop le";
    QMessageBox::critical(this, "Erro", message);
    resetChuongTrinh();
}

void GiaoDien::tbHoanThanhKiemTraIP()
{
    QString message = "Dia chi IP hop le";
    QMessageBox::information(this, "Thong Bao", "Quet IP: " + IP_Address);
}

void GiaoDien::tbHoanThanhQuetCong()
{
    QString message = "Hoan Thanh quet cong";
    QMessageBox::information(this, "Thong Bao", message);
}

void GiaoDien::tbDungChuongTrinh()
{
    QString message = "Dung Quet";
    QMessageBox::information(this, "Thong Bao", message);
}

void GiaoDien::tbReset()
{
    QString message = "Da Reset";
    QMessageBox::information(this, "Thong Bao", message);
}

void GiaoDien::tbLoiTaoThuMuc()
{
    QString message = "Khong tao duoc thu muc";
    QMessageBox::critical(this, "Erro", message);
}

void GiaoDien::tbloiTaoFile()
{
    QString message = "Khong tao duoc file";
    QMessageBox::critical(this, "Erro", message);
}

bool GiaoDien::kiemTraThucMucTonTai(QString Path)
{
    QDir directory(Path);
    return directory.exists();
}

void GiaoDien::xoaDuLieuFile()
{
    if (fileKetQua->open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        fileKetQua->close();
    }
}

void GiaoDien::ghiKetQuaRaFile(int port)
{
    QString ketQua = "port: " + QString::number(port) + " ---" + "Dang Mo";
    fileKetQua->open(QIODevice::Append | QIODevice::Text);
    QTextStream out(fileKetQua);
    out << ketQua << endl;
    fileKetQua->close();
}

void GiaoDien::ghiIP()
{
    QTime currentTime = QTime::currentTime();
    fileKetQua->open(QIODevice::Append | QIODevice::Text);
    QTextStream out(fileKetQua);
    out << "Quet IP: " << IP_Address << "---" << currentTime.toString()  << endl;
    fileKetQua->close();
}

void GiaoDien::resetKetQuaQuet()
{
    listKetQua->clear();
    xoaDuLieuFile();
}

void GiaoDien::resetTienTrinh()
{
    tienTrinh->setValue(1);
}

void GiaoDien::resetChuongTrinh()
{
    IP_lineEdit->clear();
    trangThai = -1;
    IP_Address.clear();
    IP_Address_new.clear();
    listKetQua->clear();
    resetTienTrinh();
    xoaDuLieuFile();
    QCoreApplication::processEvents();
    emit daReset();
}
