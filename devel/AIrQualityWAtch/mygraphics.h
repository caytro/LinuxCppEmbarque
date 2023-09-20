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

    ///
    /// \brief initPalette
    ///
    void initPalette();

    ///
    /// \brief initFonts
    ///
    void initFonts();

    ///
    /// \brief createColor
    /// \param nom
    /// \param indice
    /// \param red
    /// \param green
    /// \param blue
    /// \return
    ///
    Color *createColor(string nom, int indice, int red, int green, int blue);

    ///
    /// \brief getDataVectorMaxValue
    /// \return
    ///
    float getDataVectorMaxValue();

    ///
    /// \brief getDataVectorMinValue
    /// \return
    ///
    float getDataVectorMinValue();

    ///
    /// \brief getDataVectorMaxValue
    /// \param v
    /// \return
    ///
    float getDataVectorMaxValue(vector<DataElement> *v);

    ///
    /// \brief getDataVectorMinValue
    /// \param v
    /// \return
    ///
    float getDataVectorMinValue(vector<DataElement> *v);

    ///
    /// \brief appendDataVector
    /// \param label
    /// \param abscisse
    /// \param value
    /// \return
    ///
    vector<DataElement>* appendDataVector(string label="", float abscisse=0.0, float value=0.0);

    ///
    /// \brief appendDataVector
    /// \param v
    /// \param label
    /// \param abscisse
    /// \param value
    /// \return
    ///
    vector<DataElement>* appendDataVector(vector<DataElement> *v,string label="", float abscisse=0.0, float value=0.0);

    ///
    /// \brief setVector
    /// \param v
    /// \param datas
    /// \param dataSet
    ///
    void setVector(vector<DataElement>* v, json datas, string dataSet);

    ///
    /// \brief curveChartInit
    /// \param params
    ///
    void curveChartInit(CurveChartParams params);

    ///
    /// \brief pieChartInit
    /// \param params
    ///
    void pieChartInit(CurveChartParams params);

    ///
    /// \brief pieChartDraw
    /// \param params
    ///
    void pieChartDraw(CurveChartParams params);

    ///
    /// \brief calcRatioPourcent
    /// \param params
    /// \return
    ///
    double calcRatioPourcent(CurveChartParams params);

    ///
    /// \brief curveChartAddCurves
    /// \param params
    ///
    void curveChartAddCurves(CurveChartParams params);

    ///
    /// \brief curveChartSetLegend
    /// \param params
    ///
    void curveChartSetLegend(CurveChartParams params);

    ///
    /// \brief setAbscisses
    /// \param params
    /// \param dataSetIndex
    ///
    void setAbscisses(CurveChartParams *params, int dataSetIndex=0);


public:

    ///
    /// \brief myGraphics
    ///
    myGraphics();

    ///
    /// \brief pieChart
    /// \param datas
    /// \param options
    ///
    void pieChart(json datas, myOptions *options);

    ///
    /// \brief curveChart
    /// \param datas
    /// \param options
    ///
    void curveChart(json datas, myOptions *options);

};

#endif // MYGRAPHICS_H
