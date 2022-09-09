#ifndef MODIFIMAGEPROVIDER_H
#define MODIFIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QRegularExpression>
#include <QObject>

class ModifImageProvider : public QQuickImageProvider
{
    Q_OBJECT
private:
    unsigned char *palette;
    double *coeffs;
    int w,h;
public:
    ModifImageProvider()
               : QQuickImageProvider(QQuickImageProvider::Pixmap)
    {
    }



    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
public slots:
    void receivePalette(QList<unsigned char> palette);
    //to avoid doing the decomposition twice, we receive it from the paletteImageProvider when it does the decomposition.
    void receiveDecomposition(double *coeffs, int w, int h);
};

#endif // MODIFIMAGEPROVIDER_H
