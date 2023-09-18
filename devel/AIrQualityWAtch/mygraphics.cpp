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
    myPalette[2] = createColor("orange",2,255,210,0);
    myPalette[3] = createColor("orange2",3,210,110,10);
    myPalette[4] = createColor("bleu",2,120,120,255);
    myPalette[5] = createColor("bleu2",2,60,60,200);
    myPalette[6] = createColor("violet",2,255,80,255);
    myPalette[7] = createColor("violet2",2,180,40,180);
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

float myGraphics::getDataVectorMinValue()
{
    float min = dataVector->begin()->value;
    for ( DataElement de : *dataVector){
        if (de.value < min) min = de.value;
    }
    return min;
}

float myGraphics::getDataVectorMaxValue(vector<DataElement> *v)
{
    float max = v->begin()->value;
    for ( DataElement de : *v){
        if (de.value > max) max = de.value;
    }
    return max;
}

float myGraphics::getDataVectorMinValue(vector<DataElement> *v)
{
    float min = v->begin()->value;
    for ( DataElement de : *v){
        if (de.value < min) min = de.value;
    }
    return min;
}

float myGraphics::getDataVectorMaxValue()
{
    float max = dataVector->begin()->value;
    for ( DataElement de : *dataVector){
        if (de.value > max) max = de.value;
    }
    return max;
}
vector<DataElement>* myGraphics::appendDataVector(string label, float abscisse, float value)
{
    DataElement newElement={label, abscisse, value};
    dataVector->push_back(newElement);
    return dataVector;
}

vector<DataElement> *myGraphics::appendDataVector(vector<DataElement> *v, string label, float abscisse, float value)
{
    DataElement newElement={label, abscisse, value};
    v->push_back(newElement);
    return v;
}

void myGraphics::setVector(vector<DataElement> *v, json datas, string dataSet)
{
    int nbMeasures = datas.size();
    for (int i=0;i < nbMeasures; i++){
        DataElement newDataElement;
        newDataElement.abscisse = static_cast<float>(i);
        newDataElement.value = datas[i]["stations"][0][dataSet];
        newDataElement.label=datas[i]["stations"][0]["updatedAt"];
        v->push_back(newDataElement);
    }

}

void myGraphics::curveChartInit(CurveChartParams params)
{
    int xOrigin = params.marginLeft;
    int yOrigin = imageSize - params.marginBottom;
    int chartHeight = imageSize - params.marginBottom - params.titleHeight -10;
    int chartWidth = imageSize - params.marginLeft - params.legendWidth -10;
    // Axes
    gdImageSetThickness(im,1);
    gdImageLine(im, xOrigin, yOrigin, xOrigin + chartWidth, yOrigin , 1);
    gdImageLine(im, xOrigin, yOrigin, xOrigin , yOrigin - chartHeight, 1);
    gdImageLine(im, xOrigin + chartWidth, yOrigin , xOrigin + chartWidth -5, yOrigin-5 ,1);
    gdImageLine(im, xOrigin + chartWidth, yOrigin , xOrigin + chartWidth -5, yOrigin+5 ,1);
    gdImageLine(im, xOrigin , yOrigin -chartHeight, xOrigin -5 , yOrigin -chartHeight +5,1);
    gdImageLine(im, xOrigin , yOrigin -chartHeight, xOrigin +5 , yOrigin -chartHeight +5,1);

    int yRatio = - static_cast<int>((chartHeight/((params.globalMax-params.globalMin+1))));
    for (int i=10; i<params.globalMax; i+=10){
        gdImageLine(im, xOrigin-3, yOrigin + i * yRatio, xOrigin+3, yOrigin + i * yRatio ,1);
        gdImageDashedLine(im, xOrigin +3, yOrigin + i * yRatio, xOrigin+chartWidth, yOrigin + i * yRatio , 9);
        gdImageString(im, fonts[1], params.marginLeft - 20, yOrigin + i * yRatio - 20, (unsigned char *)to_string(i).c_str(),1);
    }
    int xRatio = static_cast<int>(chartWidth/params.nbMeasures);
    for(int i=1; i<params.nbMeasures; i++){
        gdImageLine(im, xOrigin + i * xRatio, yOrigin-3,xOrigin + i * xRatio, yOrigin+3,1);
    }

    // frame
    gdImageSetThickness(im,2);
    gdImageLine(im, 0, 0, imageSize-1,0, 4);
    gdImageLine(im, imageSize-1, 0, imageSize-1,imageSize-1, 4);
    gdImageLine(im, 0, imageSize-1, imageSize-1,imageSize-1, 4);
    gdImageLine(im, 0, 0, 0,imageSize-1, 4);

    gdImageLine(im, 1, params.titleHeight, imageSize-1, params.titleHeight, 4);
    gdImageLine(im, imageSize - params.legendWidth, params.titleHeight, imageSize -params.legendWidth, imageSize-1,4);
    gdImageSetThickness(im,1);

    // title
    int xTitle = (imageSize /2) - params.title.length() *5;
    int yTitle = params.titleHeight *0.5;
    gdImageString(im, fonts[4],xTitle,yTitle,(unsigned char *)params.title.c_str() ,1);

    // legend title
    int xLegendTitle = (imageSize - params.legendWidth/2) - 60;
    int yLegendTitle = params.titleHeight +20;
    gdImageString(im, fonts[4],xLegendTitle,yLegendTitle,(unsigned char *)string("Legend").c_str() ,1);

}

void myGraphics::curveChartAddCurve(vector<DataElement> *v, CurveChartParams params)
{

    int xOrigin = params.marginLeft;
    int yOrigin = imageSize - params.marginBottom;
    int chartHeight = imageSize - params.marginBottom - params.titleHeight -10;
    int chartWidth = imageSize - params.marginLeft - params.legendWidth -10;
    int xRatio = static_cast<int>(chartWidth/params.nbMeasures);
    int yRatio = - static_cast<int>((chartHeight/((params.globalMax-params.globalMin+1))));
    DataElement current = v->data()[0];
    gdImageSetAntiAliased(im, params.colorIndex);
    gdImageSetThickness(im,2);
    for (int i=1; i<params.nbMeasures; i++){
        DataElement next = v->data()[i];
        int x1 = xOrigin+(i-1)*xRatio;
        int y1 = yOrigin+current.value*yRatio;
        int x2 = xOrigin+i*xRatio;
        int y2 = yOrigin+next.value*yRatio;
        gdImageLine(im,x1, y1,x2 , y2 , params.colorIndex);
        current = next;
    }
    int i=0;
    for (DataElement de : *v){
        gdPoint points[4];
        int x0 = xOrigin+i*xRatio;
        int y0 = yOrigin+de.value*yRatio;
        points[0].x=x0-5;
        points[0].y=y0;
        points[1].x=x0;
        points[1].y=y0-5;
        points[2].x=x0+5;
        points[2].y=y0;
        points[3].x=x0;
        points[3].y=y0+5;
        gdImageFilledPolygon(im,points, 4, params.colorIndex+1);
        i++;
    }
    gdImageSetThickness(im,1);
}

void myGraphics::curveChartSetLegend(CurveChartParams params)
{
    int xOrigin = imageSize - params.legendWidth +10;
    int yOrigin = params.titleHeight + 50;
    int ligne = 1;
    for ( legendParams l : *params.legend){
        gdImageString(im, fonts[2], xOrigin, yOrigin + ligne*20, (unsigned char*)l.title.c_str(),l.colorIndex);
        ligne++;
    }
}

void myGraphics::pieChart()
{
    // Titre
    gdImageString(im, fonts[4],(imageSize - titre.length() * 10) /2,50 ,(unsigned char *)titre.c_str(),gdColors[1]);
}


void myGraphics::curveChart(json datas, myOptions *options)
{
    vector<DataElement>* ozoneVector = new vector<DataElement>();
    setVector(ozoneVector, datas, "OZONE");
    vector<DataElement>* PM10Vector = new vector<DataElement>();
    setVector(PM10Vector, datas, "PM10");
    vector<DataElement>* PM25Vector = new vector<DataElement>();
    setVector(PM25Vector, datas, "PM25");

    vector<float> vMax={getDataVectorMaxValue(ozoneVector),getDataVectorMaxValue(PM10Vector),getDataVectorMaxValue(PM25Vector)};
    vector<float> vMin={getDataVectorMinValue(ozoneVector),getDataVectorMinValue(PM10Vector),getDataVectorMinValue(PM25Vector)};
    float globalMax = *max_element(vMax.begin(),vMax.end());
    //float globalMin = *min_element(vMin.begin(),vMin.end());
    float globalMin = 0.0;
    int nbMeasures = datas.size();


    CurveChartParams params;

    params.nbMeasures = nbMeasures;
    params.legendWidth = 300;
    params.titleHeight = 80;
    params.marginBottom = 100;
    params.marginLeft = 50;
    params.globalMin = globalMin;
    params.globalMax = globalMax;
    params.title = "AIr Quality WAtch";
    params.description = "Ozone, particules fines 10 et 25 um";


    legendParams lp1, lp2, lp3;
    lp1.title = "Ozone (ppb)";
    lp1.colorIndex = 2;
    lp2.title = "Particules fines < 10 um (ug / m3)";
    lp2.colorIndex = 4;
    lp3.title = "Particules fines < 25 um (ug / m3)";
    lp3.colorIndex = 6;
    params.legend = new vector<legendParams>({lp1,lp2,lp3});
    curveChartSetLegend(params);

    curveChartInit(params);
    params.colorIndex = 2;
    curveChartAddCurve(ozoneVector, params);
    params.colorIndex =4;
    curveChartAddCurve(PM10Vector, params);
    params.colorIndex =6;
    curveChartAddCurve(PM25Vector, params);

    FILE *out = fopen(options->getFullDataCurveChartFileName().c_str(),"wb");
    gdImagePng(im,out);
    fclose(out);
    if(options->isDisplay())
    {
        char commande[300];
        sprintf(commande, "display %s &",options->getFullDataCurveChartFileName().c_str());
        system(commande);
    }

}
