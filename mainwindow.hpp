#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMap>

class TiingoConnection;
class QDoubleSpinBox;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void onNewQuote(QString pair, double bidSz, double bidPr, double askSz, double askPr);

private:
    Ui::MainWindow *ui;
    TiingoConnection* m_connection = nullptr;
    QMap<QString, QVector<QDoubleSpinBox*>> m_pairs;
};
#endif // MAINWINDOW_HPP
