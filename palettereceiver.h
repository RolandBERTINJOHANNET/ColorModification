#ifndef PALETTERECEIVER_H
#define PALETTERECEIVER_H

#include <QQuickItem>
#include <QList>

class PaletteReceiver : public QQuickItem
{
private:
    Q_OBJECT

    Q_PROPERTY (QList<unsigned char> xx READ xx WRITE setXX NOTIFY xxChanged)
    QList<unsigned char> m_xx;
public:
    PaletteReceiver(QQuickItem *parent = 0);

    QList<unsigned char> xx() const
    {
        qDebug()<<"called that function ";
        return m_xx;
    }
public slots:
    void setXX (QList<unsigned char> arg)
    {
        qDebug()<<"set xx";
        emit xxChanged(this->m_xx);
        if (m_xx != arg) {
            m_xx = arg;
        }
    }
signals:
    void xxChanged (QList<unsigned char> arg);
};

#endif // PALETTERECEIVER_H
