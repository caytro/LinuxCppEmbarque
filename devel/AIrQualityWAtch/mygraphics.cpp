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


void myGraphics::curveChart(json datas, myOptions *options)
{
    dataVector = new vector<DataElement>();
    int nbMeasures = datas.size();
    for (int i=0;i < nbMeasures; i++){
        DataElement newDataElement;
        newDataElement.abscisse = static_cast<float>(i);
        newDataElement.value = datas[i]["stations"][0]["OZONE"];
        newDataElement.label=datas[i]["stations"][0]["updatedAt"];
        dataVector->push_back(newDataElement);
    }
    float max = dataVector->begin()->value;
    for ( DataElement de : *dataVector){
        if (de.value > max) max = de.value;
    }


    gdImageLine(im, 10,imageSize -10, imageSize-10, imageSize-10, 1);
    gdImageLine(im, 10,imageSize -10, 10, 10, 1);
    FILE *out = fopen("/home/sylvain/datas/chart.png","wb");
    DataElement current = dataVector->data()[0];
    for (int i=1; i<nbMeasures; i++){
        DataElement next = dataVector->data()[i];

        gdImageLine(im,static_cast<int>(10 + (i-1)*((imageSize-20)/nbMeasures)),current.value, static_cast<int>(10+i*((imageSize-20)/nbMeasures)),next.value, 7);
        current = next;
    }
    gdImagePng(im,out);
    fclose(out);

    char commande[300];
    sprintf(commande, "display %s &","/home/sylvain/datas/chart.png");
    system(commande);

}
