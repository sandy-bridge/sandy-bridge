#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::DisconnectSocket()
{
    QString stop = "Stop";
    QByteArray dataToWrite;
    QDataStream dataStream(&dataToWrite, QIODevice::WriteOnly);
    QByteArray size;
    QDataStream sizeDataStream(&size, QIODevice::WriteOnly);
    sizeDataStream.setByteOrder(QDataStream::LittleEndian);
    dataStream.setByteOrder(QDataStream::LittleEndian);
    dataStream << stop << '\0';
    sizeDataStream << dataToWrite.size();
    dataToWrite.replace(0, 4, size);
    localSocket.write(dataToWrite);
    if(!localSocket.waitForDisconnected(50) && localSocket.state() != QLocalSocket::UnconnectedState){
        localSocket.disconnectFromServer();
    }
    if(localSocket.waitForDisconnected(100) || localSocket.state() == QLocalSocket::UnconnectedState){
        return true;
    }
    return false;
}

void MainWindow::on_connectButton_clicked()
{
    localSocket.connectToServer("\\\\.\\pipe\\ics0025");
    if(localSocket.waitForConnected(1000)){
        ui->statusText->setPlainText("Konnekted!");
        ui->connectButton->setEnabled(false);
        ui->computeButton->setEnabled(true);
        ui->breakButton->setEnabled(true);
    }
    else {
        ui->statusText->setPlainText(localSocket.errorString());
    }
}


void MainWindow::on_exitButton_clicked()
{
    if(localSocket.state() == QLocalSocket::ConnectedState){
        MainWindow::DisconnectSocket();
    }
    QApplication::exit();
}


void MainWindow::on_computeButton_clicked()
{
    ui->X0->setValidator(new QDoubleValidator);
    ui->Xn->setValidator(new QDoubleValidator);
    ui->nPoints->setValidator(new QIntValidator);
    ui->order->setValidator(new QIntValidator);
    double x_0 = ui->X0->text().toDouble();
    double x_n = ui->Xn->text().toDouble();
    int nPoints = ui->nPoints->text().toInt();
    int order = ui->order->text().toInt();
    QString type = ui->functionSelector->currentText();
    type.append(QChar(0));
    QByteArray dataToWrite;
    QDataStream dataStream(&dataToWrite, QIODevice::WriteOnly);
    QByteArray size;
    QDataStream sizeDataStream(&size, QIODevice::WriteOnly);
    sizeDataStream.setByteOrder(QDataStream::LittleEndian);
    dataStream.setByteOrder(QDataStream::LittleEndian);
    dataStream << type << x_0 << x_n << nPoints << order;
    sizeDataStream << dataToWrite.size();
    dataToWrite.replace(0, 4, size);
    localSocket.write(dataToWrite);
    if (!localSocket.waitForReadyRead(1000) ) {
        ui->statusText->setPlainText(localSocket.errorString());
        return;
    }
    QByteArray receivedData = localSocket.readAll();
    QDataStream receivedDataStream(&receivedData, QIODevice::ReadOnly);
    receivedDataStream.setByteOrder(QDataStream::LittleEndian);
    int receivedLength;
    receivedDataStream >> receivedLength;
    ui->statusText->setPlainText(QString::number(receivedLength));
    QString messageType;
    while(true){
        QChar test = '\0';
        receivedDataStream >> test;
        if (test == '\0'){
            break;
        }
        messageType += test;
    }
    if(messageType != "Curve"){
        ui->statusText->setPlainText(messageType);
        return;
    }
    ui->statusText->setPlainText("Curve received.");
    QVector<double> x, y;
    double minX = 0, minY = 0, maxX = 0, maxY = 0;
    while(!receivedDataStream.atEnd()){
        double xt, yt;
        receivedDataStream >> xt >> yt;
        x.push_back(xt);
        y.push_back(yt);
        if(xt > maxX){
            maxX = xt;
        }
        if(yt > maxY){
            maxY = yt;
        }
        if(xt < minX){
            minX = xt;
        }
        if(yt < minY){
            minY = yt;
        }
    }
    ui->plot->addGraph();
    ui->plot->graph(0)->setData(x, y);
    ui->plot->xAxis->setRange(minX, maxX);
    ui->plot->yAxis->setRange(minY, maxY);
    ui->plot->replot();
;}


void MainWindow::on_breakButton_clicked()
{
    if(MainWindow::DisconnectSocket()){
        ui->statusText->setPlainText("Not connected");
        ui->connectButton->setEnabled(true);
        ui->computeButton->setEnabled(false);
        ui->breakButton->setEnabled(false);
    }
    else {
        ui->statusText->setPlainText(localSocket.errorString());
    }
}

