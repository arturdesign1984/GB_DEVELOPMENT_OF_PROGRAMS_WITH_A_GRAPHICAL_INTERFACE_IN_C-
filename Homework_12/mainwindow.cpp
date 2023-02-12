#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    parser = new ParseText();
    ui->setupUi(this);
    downloader = new Downloader(this);
    ui->progressBar->setValue(0);
    connect(downloader, SIGNAL(downloadProgress(qint64,qint64)), SLOT(slotDownloadProgress(qint64,qint64)));
    connect(downloader, SIGNAL(done(const QUrl&, const QByteArray&)), SLOT(slotDone(const QUrl&, const QByteArray&)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete parser;
    delete downloader;
}

void MainWindow::on_pushButton_clicked()
{
    QNetworkAccessManager *manager; // Менеджер по запросам к сети
    QNetworkRequest request; // Запрос
    QSslConfiguration sSlConfig; // SSL настройки

    // Задаем параметры для SSL
    sSlConfig.setDefaultConfiguration(QSslConfiguration::defaultConfiguration());
    sSlConfig.setProtocol(QSsl::TlsV1_2);
    request.setSslConfiguration(sSlConfig);

    // Если нужно, то разрешаем переходить по редиректам
    //request.setAttribute(QNetworkRequest::RedirectionTargetAttribute, true); //QNetworkRequest::FollowRedirectsAttribute, true);

    // Создаем экземпляр менеджера и связываем сигнал прихода ответа к какому-нибудь слоту
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
          this, SLOT(replyFinished(QNetworkReply*)));

    // Задаем адрес нужной страницы
    request.setUrl(QUrl("https://yandex.ru/images/search?text=" + ui->lineEdit_search->text()));

    // Отправляем запрос
    manager->get(request);
}

void MainWindow::slotError()
{
    QMessageBox::critical(this, "Error", "Error!");
}

void MainWindow::slotDownloadProgress(qint64 reseived, qint64 total)
{
    if(total <= 0)
    {
        slotError();
        return;
    }
    ui->progressBar->setValue(100 * reseived / total);
}

void MainWindow::slotDone(const QUrl & url, const QByteArray & ba)
{
    QFile file(url.path().section('/',-1));
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(ba);
        file.close();
    }
    showPic(file.fileName());
}

void MainWindow::showPic(const QString &path)
{
    mtx.lock();
    QPixmap pix(path);
    pix = pix.scaled(QSize(ui->label_1->width(), (ui->label_1->width() * pix.size().height()/pix.size().width())));
    switch (selectLable) {
    case 0:
        ui->label_1->hide();
        ui->label_1->setPixmap(pix);
        ui->label_1->setFixedSize(pix.size());
        ui->label_1->show();
        ++selectLable;
        on_pushButton_Go_clicked();
        break;
    case 1:
        ui->label_2->hide();
        ui->label_2->setPixmap(pix);
        ui->label_2->setFixedSize(pix.size());
        ui->label_2->show();
        ++selectLable;
        on_pushButton_Go_clicked();
        break;
    case 2:
        ui->label_3->hide();
        ui->label_3->setPixmap(pix);
        ui->label_3->setFixedSize(pix.size());
        ui->label_3->show();
        selectLable = 0;
        break;
    }
    mtx.unlock();
}

void MainWindow::replyFinished(QNetworkReply* reply) {
  if (reply->error() == QNetworkReply::NoError) {
    //Ответ от сервера приводим к строке
    QByteArray bytes = reply->readAll();
    QString html = QString::fromUtf8(bytes.data(), bytes.size());

    // Отправляем в парсер
    if(parser->parse(html))
    {
        ui->lineEdit_Url->setText("Done.");
    } else
    {
        ui->lineEdit_Url->setText("Error!");
    }

    // Код ответа от сервера: 200, 404 и др.
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    // С какого url нам пришел ответ
    QString url = reply->url().toString();

    // Используем полученные данные по своему усмотрению
    ui->textEdit->setText("");
    ui->textEdit->insertPlainText("statusCode = " + QString::number(statusCode) + "\n");
    ui->textEdit->insertPlainText("url = " + url + "\n");
    ui->textEdit->insertPlainText("html = " + html + "\n");
  } else {
    // Если что-то пошло не так, то обрабатываем ошибку как нам это нужно
    qDebug() << reply->errorString();
  }

  // Удаляем ответ от сервера
  reply->deleteLater();
}

void MainWindow::on_pushButton_Go_clicked()
{
//    qDebug() << parser->getUrlList()[i] << '\n';
    downloader->download(QUrl(parser->getUrlList()[selectLable]));
}

