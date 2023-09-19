#ifndef MYGRAPHICS_H
#define MYGRAPHICS_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>

#include <gd.h>
#include <gdfontt.h>
#include <gdfonts.h>
#include <gdfontmb.h>
#include <gdfontl.h>
#include <gdfontg.h>

#include "myoptions.h"
#include "myparsing.h"
#include "myregex.h"

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




typedef struct{
    vector<DataElement>* dataElements;
    int colorIndex;
    string legend;
} dataSet;

typedef struct {
    string title;
    string description;
    vector<dataSet> *dataSets;
    int nbMeasures;
    int colorIndex;
    int titleHeight;
    int marginLeft;
    int marginBottom;
    int legendWidth;
    float globalMax;
    float globalMin;

} CurveChartParams;



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
    float getDataVectorMaxValue();
    float getDataVectorMinValue();
    float getDataVectorMaxValue(vector<DataElement> *v);
    float getDataVectorMinValue(vector<DataElement> *v);
    vector<DataElement>* appendDataVector(string label="", float abscisse=0.0, float value=0.0);
    vector<DataElement>* appendDataVector(vector<DataElement> *v,string label="", float abscisse=0.0, float value=0.0);
    void setVector(vector<DataElement>* v, json datas, string dataSet);
    void curveChartInit(CurveChartParams params);
    void curveChartAddCurves(CurveChartParams params);
    void curveChartSetLegend(CurveChartParams params);
    void setAbscisses(CurveChartParams *params, int dataSetIndex=0);



public:
    myGraphics();


    void pieChart();
    void curveChart(json datas, myOptions *options);

};

#endif // MYGRAPHICS_H
