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


///
/// \brief The myGraphics class
/// \details #include "myoptions.h"
/// \details #include "myparsing.h"
/// \details #include "myregex.h"
/// \details #include "gd.h"
/// \details requires -lgd flag
/// \details Provides methods for generating, displaying and saving pie charts and curve charts
///
class myGraphics
{
    string titre;
    char ficOut[255];
    int imageSize = 1024;
    Color *myPalette[12];
    int gdColors[12];
    gdFontPtr fonts[5];
    gdImagePtr im;

    ///
    /// \brief initPalette
    /// \details creates 12 colors palette
    /// \details Each color works in pair
    /// \details eg: 2 -> green and 3 -> darkgreen
    /// \details 0 -> black
    /// \details 1 -> white
    ///
    void initPalette();

    ///
    /// \brief initFonts
    /// \details Initialize fonts
    /// \details based on _<gdfontt.h> <gdfonts.h> <gdfontmb.h> <gdfontl.h> <gdfontg.h>
    ///
    void initFonts();

    ///
    /// \brief createColor
    /// \param nom
    /// \param indice
    /// \param red
    /// \param green
    /// \param blue
    /// \return struct Color object. See gdImageColorAllocate documentation.
    ///
    Color *createColor(string nom, int indice, int red, int green, int blue);

    ///
    /// \brief getDataVectorMaxValue
    /// \param vector<DataElement> *v
    /// \return float
    /// \details required to set curve chart ordinate scale
    ///
    float getDataVectorMaxValue(vector<DataElement> *v);

    ///
    /// \brief getDataVectorMinValue
    /// \param vector<DataElement> *v
    /// \return float
    /// \details required to set curve chart ordinate scale
    ///
    float getDataVectorMinValue(vector<DataElement> *v);


    ///
    /// \brief appendDataVector
    /// \param vector<DataElement> *v
    /// \param string label=""
    /// \param float abscisse=0.0
    /// \param float value=0.0
    /// \return vector<DataElement>*
    /// \details Create new DataElement and appends it to v
    ///
    vector<DataElement>* appendDataVector(vector<DataElement> *v,string label="", float abscisse=0.0, float value=0.0);

    ///
    /// \brief setVector
    /// \param vector<DataElement>* v
    /// \param json datas
    /// \param string dataSet
    /// \details Creates a DataElement for each measure stored in json datas
    /// \details parsing datas using dataset : datas[i]["stations"][0][dataSet];
    ///
    void setVector(vector<DataElement>* v, json datas, string dataSet);

    ///
    /// \brief curveChartInit
    /// \param CurveChartParams params
    /// \details Draws Frame, axes, title and description
    ///
    void curveChartInit(CurveChartParams params);

    ///
    /// \brief pieChartInit
    /// \param CurveChartParams params
    /// \details Draws Frame, axes, title and description
    ///
    void pieChartInit(CurveChartParams params);

    ///
    /// \brief pieChartDraw
    /// \param CurveChartParams params
    /// \details Draws pie chart
    ///
    void pieChartDraw(CurveChartParams params);

    ///
    /// \brief calcRatioPourcent
    /// \param CurveChartParams params
    /// \return double
    /// \details Compute S sum of the values
    /// \detail returns 100/S
    /// \details Required to calculate the angles of the pie chart
    ///
    double calcRatioPourcent(CurveChartParams params);

    ///
    /// \brief curveChartAddCurves
    /// \param CurveChartParams params
    /// \details Draw lines
    ///
    void curveChartAddCurves(CurveChartParams params);

    ///
    /// \brief curveChartSetLegend
    /// \param CurveChartParams params
    /// \details Displays colored labels in legend area
    ///
    void curveChartSetLegend(CurveChartParams params);


public:

    ///
    /// \brief myGraphics
    /// \details Constructor
    /// \details Initialize image, palette and fonts
    ///
    myGraphics();

    ///
    /// \brief pieChart
    /// \param json datas
    /// \param myOptions *options
    /// \details generate, displays and save pie chart
    ///
    void pieChart(json datas, myOptions *options);

    ///
    /// \brief curveChart
    /// \\param json datas
    /// \param myOptions *options
    /// \details generate, displays and save curve chart
    ///
    void curveChart(json datas, myOptions *options);

};

#endif // MYGRAPHICS_H
