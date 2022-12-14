#ifndef WIDGET_H
#define WIDGET_H

#include <QRandomGenerator>
#include <QTcpSocket>
#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

/**
 * @brief The Widget class
 */
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QTcpSocket* mSock;
private slots:
    void envoisColis();
    void Connected();
    void Disconnected();
};
#endif // WIDGET_H
