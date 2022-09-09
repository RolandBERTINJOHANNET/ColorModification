#ifndef PALETTEIMAGEPROVIDER_H
#define PALETTEIMAGEPROVIDER_H

#include <QQuickImageProvider>

class PaletteImageProvider :  public QQuickImageProvider
{
    Q_OBJECT
private:
    double *coeffs;
    unsigned char *palette;
public:
    PaletteImageProvider()
               : QQuickImageProvider(QQuickImageProvider::Pixmap)
    {
    }

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
public slots:
    void receivePalette(QList<unsigned char>);
signals:
    void sendData(double *coeffs,int w,int h);
};

#endif // PALETTEIMAGEPROVIDER_H
