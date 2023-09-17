#include "mygraphics.h"

myGraphics::myGraphics()
{
    im = gdImageCreate(imageSize,imageSize);
    initPalette();
    initFonts();
    dataVector = new vector<DataElement>();
}


void myGraphics::initPalette()
{
    myPalette[0] = createColor("bgColor",0,0,0,0);
    myPalette[1] = createColor("fgColor",1,255,255,255);
    myPalette[2] = createColor("rouge",2,255,0,0);
    myPalette[3] = createColor("vert",2,0,255,0);
    myPalette[4] = createColor("bleu",2,0,0,255);
    myPalette[5] = createColor("bleuClair",2,180,180,255);
    myPalette[6] = createColor("jaune",2,200,200,0);
    myPalette[7] = createColor("orange",2,255,128,0);
    myPalette[8] = createColor("violet",2,255,0,255);
    myPalette[9] = createColor("lightGray",2,200,200,200);
    myPalette[10] = createColor("darkGray",2,30,30,30);
    myPalette[11] = createColor("black",2,0,0,0);

    for (int colorIndex = 0; colorIndex<12; colorIndex++)
    {
        gdColors[colorIndex] = gdImageColorAllocate(im,myPalette[colorIndex]->red,myPalette[colorIndex]->green,myPalette[colorIndex]->blue);
    }
}

void myGraphics::initFonts()
{
    fonts[0] = gdFontGetTiny ();
    fonts[1] = gdFontGetSmall ();
    fonts[2] = gdFontGetMediumBold ();
    fonts[3] = gdFontGetLarge ();
    fonts[4] = gdFontGetGiant ();
}



Color *myGraphics::createColor(string nom, int indice, int red, int green, int blue)
{
    Color *newColor = new Color();
    newColor->nom =nom;
    newColor->indice = indice;
    newColor->red = red;
    newColor->green = green;
    newColor->blue = blue;
    return newColor;
}

vector<DataElement>* myGraphics::appendDataVector(string label, float abscisse, float value)
{
    DataElement newElement={label, abscisse, value};
    dataVector->push_back(newElement);
    return dataVector;
}

void myGraphics::pieChart()
{
    // Titre
        gdImageString(im, fonts[4],(imageSize - titre.length() * 10) /2,50 ,(unsigned char *)titre.c_str(),gdColors[1]);
}
