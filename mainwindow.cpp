#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

#include "tiingoconnection.hpp"
#include <QDoubleSpinBox>

static const int limit_pairs = 20;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_connection = new TiingoConnection(this);

    QObject::connect(m_connection, &TiingoConnection::newBid, this, &MainWindow::onNewQuote);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewQuote(QString pair, double bidSz, double bidPr, double askSz, double askPr)
{
    if (m_pairs.count() < limit_pairs && !m_pairs.contains(pair)) {
        m_pairs[pair];
        auto* horizLay = new QHBoxLayout();
        horizLay->addWidget(new QLabel(pair));
        for (int i = 0; i < 4; ++i) {
            auto w = new QDoubleSpinBox(ui->centralwidget);
            w->setMaximum(99999999999);
            w->setDecimals(12);
            w->setReadOnly(true);
            w->setButtonSymbols(QSpinBox::NoButtons);
            m_pairs[pair].append(w);
            horizLay->addWidget(w);
        }
        ui->verticalLayout_3->insertLayout(0, horizLay);
    }
    if (!m_pairs.contains(pair)) {
        return;
    }
    m_pairs[pair][0]->setValue(bidSz);
    m_pairs[pair][1]->setValue(bidPr);
    m_pairs[pair][2]->setValue(askSz);
    m_pairs[pair][3]->setValue(askPr);
}

