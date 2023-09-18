#ifndef MYGRAPHICS_H
#define MYGRAPHICS_H

#include <iostream>
#include <string>
#include <vector>

#include <gd.h>
#include <gdfontt.h>
#include <gdfonts.h>
#include <gdfontmb.h>
#include <gdfontl.h>
#include <gdfontg.h>

#include "myoptions.h"
#include "myparsing.h"

using namespace std;

typedef struct {
    string nom;
    int indice;
    int red;
    int green;
    int blue;
} Color;

typedef struct {
    string label;
    float abscisse;
    float value;
} DataElement;

class myGraphics
{
    string titre;
    char ficOut[255];
    int imageSize = 1024;
    Color *myPalette[12];
    int gdColors[12];
    gdFontPtr fonts[5];
    gdImagePtr im;
    vector<DataElement> *dataVector;
    void initPalette();
    void initFonts();
    Color *createColor(string nom, int indice, int red, int green, int blue);


public:
    myGraphics();

    vector<DataElement>* appendDataVector(string label="", float abscisse=0.0, float value=0.0);
    void pieChart();
    void curveChart(json datas, myOptions *options);

};

#endif // MYGRAPHICS_H
