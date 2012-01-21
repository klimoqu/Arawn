#ifndef IMAGEFACTORY_HPP
#define IMAGEFACTORY_HPP

#include <QImage>

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

    }

    static ImageFactory* factory;

public:
    static ImageFactory* instance()
    {
        if(factory) return factory;
        factory = new ImageFactory;
    }

    QImage* fieldImages[10];
    QImage* bombImages[16];
    QImage* bonusImages[];

};

#endif // IMAGEFACTORY_HPP
