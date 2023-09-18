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

void myGraphics::curveChartInit(CurveChartParams params, string title)
{
    int xOrigin = params.marginLeft;
    int yOrigin = imageSize - params.marginBottom;
    int chartHeight = imageSize - params.marginBottom - params.titleHeight -10;
    int chartWidth = imageSize - params.marginLeft - params.legendWidth -10;
    // Axes
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
    gdImageLine(im, 0, params.titleHeight, imageSize, params.titleHeight, 4);
    gdImageLine(im, imageSize - params.legendWidth, params.titleHeight, imageSize -params.legendWidth, imageSize,4);

    // title
    int xTitle = (imageSize /2) - title.length() *5;
    int yTitle = params.titleHeight *0.5;
    gdImageString(im, fonts[4],xTitle,yTitle,(unsigned char *)title.c_str() ,1);

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
    for (int i=1; i<params.nbMeasures; i++){
        DataElement next = v->data()[i];
        int x1 = xOrigin+(i-1)*xRatio;
        int y1 = yOrigin+current.value*yRatio;
        int x2 = xOrigin+i*xRatio;
        int y2 = yOrigin+next.value*yRatio;
        gdImageLine(im,x1, y1,x2 , y2 , params.colorIndex);
        current = next;
    }
}

void myGraphics::pieChart()
{
    // Titre
    gdImageString(im, fonts[4],(imageSize - titre.length() * 10) /2,50 ,(unsigned char *)titre.c_str(),gdColors[1]);
}


void myGraphics::curveChart(json datas, myOptions *options)
{
    cout << "1" <<endl;
    vector<DataElement>* ozoneVector = new vector<DataElement>();
    setVector(ozoneVector, datas, "OZONE");
    vector<DataElement>* PM10Vector = new vector<DataElement>();
    setVector(PM10Vector, datas, "PM10");
    vector<DataElement>* PM25Vector = new vector<DataElement>();
    setVector(PM25Vector, datas, "PM25");
    cout << "2" <<endl;

    vector<float> vMax={getDataVectorMaxValue(ozoneVector),getDataVectorMaxValue(PM10Vector),getDataVectorMaxValue(PM25Vector)};
    vector<float> vMin={getDataVectorMinValue(ozoneVector),getDataVectorMinValue(PM10Vector),getDataVectorMinValue(PM25Vector)};
    cout << "3" <<endl;
    float globalMax = *max_element(vMax.begin(),vMax.end());
    //float globalMin = *min_element(vMin.begin(),vMin.end());
    float globalMin = 0.0;
    int nbMeasures = datas.size();

    cout <<"Max : "<< globalMax << " Min : " << globalMin << endl;

    CurveChartParams params;

    params.nbMeasures = nbMeasures;
    params.legendWidth = 300;
    params.titleHeight = 80;
    params.marginBottom = 100;
    params.marginLeft = 50;
    params.globalMin = globalMin;
    params.globalMax = globalMax;



    curveChartInit(params,"AIr Quality WAtch");
    params.colorIndex = 7;
    curveChartAddCurve(ozoneVector, params);
    params.colorIndex =6;
    curveChartAddCurve(PM10Vector, params);
    params.colorIndex =3;
    curveChartAddCurve(PM25Vector, params);

    FILE *out = fopen(options->getFullDataCurveChartFileName().c_str(),"wb");
    gdImagePng(im,out);
    fclose(out);

    char commande[300];
    sprintf(commande, "display %s &",options->getFullDataCurveChartFileName().c_str());
    system(commande);

}
