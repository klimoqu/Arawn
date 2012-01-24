#ifndef IMAGEFACTORY_HPP
#define IMAGEFACTORY_HPP

#include <QImage>
#include <QPainter>

class ImageFactory
{
    ImageFactory()
    {
        fieldImages[0] = new QImage("res/field0.png");
        fieldImages[1] = new QImage("res/field1.png");
        fieldImages[2] = new QImage("res/field2.png");
        fieldImages[3] = new QImage("res/field3.png");
        fieldImages[4] = new QImage(40,40, QImage::Format_Mono);
        fieldImages[5] = new QImage("res/field5.png");

        QPainter imgPainter(fieldImages[4]);
        imgPainter.setBrush(Qt::black);
        imgPainter.drawRect(QRect(0,0,40,40));

        QImage bombsF("res/bombs.png");
        for(uchar i = 0; i < 4; i++){ // Játékosok
            for(uchar j = 0; j < 4; j++){ // Bombaállapotok
                bombImages[i][j] = new QImage(bombsF.copy(j*40,i*40,40,40));
            }
        }

        QImage extrasF("res/extras.png");
        bonusImages[0] = new QImage(extrasF.copy(40, 0, 40, 40));
        bonusImages[1] = new QImage(extrasF.copy(360, 0, 40, 40));
        bonusImages[2] = new QImage(extrasF.copy(0, 0, 40, 40));
        bonusImages[3] = new QImage(extrasF.copy(320, 0, 40, 40));
        bonusImages[4] = new QImage(extrasF.copy(80, 0, 40, 40));
        bonusImages[5] = new QImage(extrasF.copy(400, 0, 40, 40));
        bonusImages[6] = new QImage(extrasF.copy(280, 0, 40, 40));
        bonusImages[7] = new QImage(extrasF.copy(240, 0, 40, 40));
        bonusImages[8] = new QImage(extrasF.copy(200, 0, 40, 40));
    }

    ~ImageFactory()
    {
        for(uchar i = 0; i < 6; i++)
            delete fieldImages[i];
        for(uchar i = 0; i < 9; i++)
            delete bonusImages[i];
        for(uchar i = 0; i < 4; i++)
            for(uchar j = 0; j < 4; j++)
                delete bombImages[i][j];
    }

    static ImageFactory *factory;

public:
    static ImageFactory* instance()
    {
        return factory;
    }

    static void clear()
    {
        delete factory;
    }

    static void build()
    {
        factory = new ImageFactory;
    }

    QImage* fieldImages[6];
    QImage* bombImages[4][4];
    QImage* bonusImages[9];

};

#define imgFact ImageFactory::instance()

#endif // IMAGEFACTORY_HPP
