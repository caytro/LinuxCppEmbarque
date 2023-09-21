#include "mygraphics.h"


myGraphics::myGraphics()
{
    im = gdImageCreate(imageSize,imageSize);
    initPalette();
    initFonts();

}


void myGraphics::initPalette()
{
    myPalette[0] = createColor("bgColor",0,0,0,0);
    myPalette[1] = createColor("fgColor",1,255,255,255);
    myPalette[2] = createColor("orange",2,255,160,120);
    myPalette[3] = createColor("orange2",3,210,100,60);
    myPalette[4] = createColor("bleu",2,120,120,255);
    myPalette[5] = createColor("bleu2",2,60,60,200);
    myPalette[6] = createColor("violet",2,255,80,255);
    myPalette[7] = createColor("violet2",2,140,60,140);
    myPalette[8] = createColor("vert",2,100,255,100);
    myPalette[9] = createColor("vert2",2,80,140,80);
    myPalette[10] = createColor("lightGray",2,100,100,100);
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

    // graduations ordonnées
    int yRatio = - static_cast<int>((chartHeight/((params.globalMax-params.globalMin+1))));
    for (int i=10; i<params.globalMax; i+=10){
        gdImageLine(im, xOrigin-3, yOrigin + i * yRatio, xOrigin+3, yOrigin + i * yRatio ,1);
        gdImageDashedLine(im, xOrigin +3, yOrigin + i * yRatio, xOrigin+chartWidth, yOrigin + i * yRatio , 10);
        gdImageString(im, fonts[1], params.marginLeft - 20, yOrigin + i * yRatio - 20, (unsigned char *)to_string(i).c_str(),1);
    }

    // graduations abscisses
    int xRatio = static_cast<int>(chartWidth/params.nbMeasures);
    for(int i=1; i<params.nbMeasures; i++){
        gdImageLine(im, xOrigin + i * xRatio, yOrigin-3,xOrigin + i * xRatio, yOrigin+3,1);
        updatedAt date = myRegex::ambeeDataGetDateTime( params.dataSets->data()[0].dataElements->data()[i].label);
        if (date.hour ==0){

            string s= myRegex::toFormatDDMMYY(params.dataSets->data()[0].dataElements->data()[i].label);
            gdImageStringUp(im,fonts[1],xOrigin + i * xRatio-5, yOrigin + 60, (unsigned char*)s.c_str(),1);
        }

    }
    int i=params.nbMeasures-1;
    string s= myRegex::toFormatHHMM(params.dataSets->data()[0].dataElements->data()[i].label);
    gdImageStringUp(im,fonts[1],xOrigin + i * xRatio-5, yOrigin + 40, (unsigned char*)s.c_str(),1);

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
    int yTitle = 20;
    gdImageString(im, fonts[4],xTitle,yTitle,(unsigned char *)params.title.c_str() ,1);

    //description
    int xDescription = (imageSize /2) - params.description.length() *5;
    int yDescription = 50;
    gdImageString(im, fonts[3],xDescription,yDescription,(unsigned char *)params.description.c_str() ,1);


    // legend title
    int xLegendTitle = (imageSize - params.legendWidth/2) - 60;
    int yLegendTitle = params.titleHeight +20;
    gdImageString(im, fonts[4],xLegendTitle,yLegendTitle,(unsigned char *)string("Legend").c_str() ,1);

}

void myGraphics::pieChartInit(CurveChartParams params)
{
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
    int yTitle = 20;
    gdImageString(im, fonts[4],xTitle,yTitle,(unsigned char *)params.title.c_str() ,1);

    //description
    int xDescription = (imageSize /2) - params.description.length() *5;
    int yDescription = 50;
    gdImageString(im, fonts[3],xDescription,yDescription,(unsigned char *)params.description.c_str() ,1);


    // legend title
    int xLegendTitle = (imageSize - params.legendWidth/2) - 60;
    int yLegendTitle = params.titleHeight +20;
    gdImageString(im, fonts[4],xLegendTitle,yLegendTitle,(unsigned char *)string("Legend").c_str() ,1);

}

void myGraphics::pieChartDraw(CurveChartParams params)
{
    int chartHeight = imageSize - params.marginBottom - params.titleHeight -10;
    int chartWidth = imageSize - params.marginLeft - params.legendWidth -10;

    int xc = params.marginLeft + chartWidth/2;
    int yc = params.titleHeight + chartHeight /2;
    double ratio = 0.8;
    double zRatio = 0.6;
    int w = chartWidth * ratio;
    int h = chartHeight * ratio * zRatio;
    int textRadius = w /2 * 1.1;
    int percentRadius = w * 0.4;
    double ratioAngle = calcRatioPourcent(params);  // Normalise les données de pieChart pour que la somme des valeurs soit égale à 100 (affichage en pourcentage)
    float curAngle = 0.0;
    char label[256];
    gdImageSetThickness(im,1);
    DataElement curPieData;
    int colorIndex;
    for(int offset =0; offset <100; offset ++)  // empile des couches façon imprimante 3D pour obtenir le rendu 3D
    {
         // les indices 0 et 1 sont réservées pour backgroundColor et foregroundColor resp.
        curAngle = 0.0;

        for (unsigned long i = 0; i<params.dataSets->size(); i++)
        {
            curPieData = params.dataSets->data()[i].dataElements->data()[0];
            colorIndex=params.dataSets->data()[i].colorIndex;
            float curAngle2 = curAngle  + curPieData.value * ratioAngle * 360.0 /100.0;
            gdImageFilledArc(im,xc ,yc + 40 - 0.4*offset,w,h,static_cast<int>(curAngle+1.2),static_cast<int>(curAngle2-1.2),colorIndex,0);
            int x = static_cast<int>(xc + (w/2) * cos((curAngle2 -1) * M_PI /180.0));
            int y = static_cast<int>(yc + 40 - (0.4 * offset) +(h/2) * sin ((curAngle2 -1) * M_PI /180.0));
            gdImageLine(im,x,y,x,y,colorIndex+1);
            x = static_cast<int>(xc + (w/2) * cos((curAngle +1) * M_PI /180.0));
            y = static_cast<int>(yc + 40 - (0.4 * offset) +(h/2) * sin ((curAngle +1) * M_PI /180.0));
            gdImageLine(im,x,y,x,y+1,colorIndex+1);
            if(offset ==0)
            {
                gdImageArc(im,xc ,yc +40,w+2,h+2,static_cast<int>(curAngle + 1),static_cast<int>(curAngle2 - 1),colorIndex+1);
                gdImageLine(im,xc,yc +40,xc +static_cast<int>((w/2) * cos ((curAngle+1)*M_PI /180)),yc + 40 +static_cast<int>((h/2) * sin ((curAngle+1)*M_PI /180)),colorIndex+1);
                gdImageLine(im,xc,yc +40,xc + static_cast<int>((w/2) * cos ((curAngle2-1)*M_PI /180)),yc + 40 + static_cast<int>((h/2) * sin ((curAngle2-1)*M_PI /180)),colorIndex+1);

            }
            curAngle = curAngle2;
        }
    }

        curAngle = 0.0;
        for (unsigned long i = 0; i<params.dataSets->size(); i++)
        {
            curPieData = params.dataSets->data()[i].dataElements->data()[0];
            colorIndex=params.dataSets->data()[i].colorIndex;
            double curAngle2 =curAngle  + curPieData.value * ratioAngle * 360.0 /100.0;

            gdImageArc(im,xc ,yc,w,h,round(curAngle+1.1),static_cast<int>(curAngle2-1.1),colorIndex+1);
            gdImageLine(im,xc,yc,xc +round((w/2) * cos ((curAngle+1)*M_PI /180)),yc +round((h/2) * sin ((curAngle+1)*M_PI /180)),colorIndex+1);
            gdImageLine(im,xc,yc,xc +round((w/2) * cos ((curAngle2-1)*M_PI /180)),yc + round((h/2) * sin ((curAngle2-1)*M_PI /180)),colorIndex+1);

            // label
            int xText = (int) (xc + textRadius * cos ( (curAngle + curAngle2)/2 * M_PI/180 ));
            int yText = (int) (yc + textRadius  * sin ( (curAngle + curAngle2)/2 * M_PI/180 ));
            if((((curAngle + curAngle2)/2)>90) && (((curAngle + curAngle2)/2)<270)){  // partie gauche du camembert
                xText -= (int)(curPieData.label.length())*8;
            }
            gdImageString(im, fonts[2],(int)xText,(int)yText,(unsigned char *)curPieData.label.c_str(),colorIndex);

            //Pourcentages
            xText = (int) (xc + percentRadius * cos ( (curAngle + curAngle2)/2 * M_PI/180 ));
            if((((curAngle + curAngle2)/2)>270) || (((curAngle + curAngle2)/2)<90)){  // partie droite du camembert
                xText -= 30; // Décalage du texte vers la gauche pour avoir un affichage plus homogène
            }
            yText = (int) (yc + percentRadius * zRatio * sin ( (curAngle + curAngle2)/2 * M_PI/180 ));
            sprintf(label,"%.2f",curPieData.value );
            gdImageString(im, fonts[2],(int)xText,(int)yText,(unsigned char *)label ,0);
            curAngle = curAngle2;

        }

}

double myGraphics::calcRatioPourcent(CurveChartParams params)
{
    vector<dataSet> *v = params.dataSets;
    float total = 0.0;
    for (dataSet ds : *v){
        DataElement de = ds.dataElements->data()[0];
        total+=de.value;
    }
    if (total == 0) total = 1.0;
    return 100.0 / total;
}



void myGraphics::curveChartAddCurves(CurveChartParams params)
{

    int xOrigin = params.marginLeft;
    int yOrigin = imageSize - params.marginBottom;
    int chartHeight = imageSize - params.marginBottom - params.titleHeight -10;
    int chartWidth = imageSize - params.marginLeft - params.legendWidth -10;
    int xRatio = static_cast<int>(chartWidth/params.nbMeasures);
    int yRatio = - static_cast<int>((chartHeight/((params.globalMax-params.globalMin+1))));
    int count = 0;
    for (dataSet ds : *params.dataSets){
        vector<DataElement>* v=ds.dataElements;
        DataElement current = v->data()[0];

        //diamonds
        int i=0;
        for (DataElement de : *v){
//            gdPoint points[4];
            int x0 = xOrigin+i*xRatio;
            int y0 = yOrigin+de.value*yRatio;
            gdImageFilledRectangle(im, x0-3, y0-3, x0+3, y0+3, ds.colorIndex+1);
            i++;
        }

        // curves
        gdImageSetAntiAliased(im, ds.colorIndex);
        gdImageSetThickness(im,2);
        for (int i=1; i<params.nbMeasures; i++){
            DataElement next = v->data()[i];
            int x1 = xOrigin+(i-1)*xRatio;
            int y1 = yOrigin+current.value*yRatio;
            int x2 = xOrigin+i*xRatio;
            int y2 = yOrigin+next.value*yRatio;
            gdImageLine(im,x1, y1,x2 , y2 , ds.colorIndex);
            current = next;
        }

        count++;
    }

    gdImageSetThickness(im,1);
}

void myGraphics::curveChartSetLegend(CurveChartParams params)
{
    int xOrigin = imageSize - params.legendWidth +10;
    int yOrigin = params.titleHeight + 50;
    int ligne = 1;
    for ( dataSet ds : *params.dataSets){

        gdImageString(im, fonts[2], xOrigin, yOrigin + ligne*20, (unsigned char*)ds.legend.c_str(),ds.colorIndex);
        ligne++;
    }
}




void myGraphics::pieChart(json datas, myOptions *options)
{
    int s = datas.size();
    json data = datas[s-1];
    DataElement* deOzone = new DataElement();
    deOzone->value = data["stations"][0]["OZONE"];
    deOzone->label = "OZONE";
    dataSet*  ozoneDataSet = new dataSet();
    ozoneDataSet->dataElements = new vector<DataElement>();
    ozoneDataSet->dataElements->push_back(*deOzone);
    ozoneDataSet->colorIndex = 2;
    ozoneDataSet->legend = string("Ozone (ppb)");

    DataElement* deNO2 = new DataElement();
    deNO2->value = data["stations"][0]["NO2"];
    deNO2->label = "NO2";
    dataSet*  NO2DataSet = new dataSet();
    NO2DataSet->dataElements = new vector<DataElement>();
    NO2DataSet->dataElements->push_back(*deNO2);
    NO2DataSet->colorIndex = 8;
    NO2DataSet->legend = string("NO2 (ppb)");

    DataElement* dePM10 = new DataElement();
    dePM10->value = data["stations"][0]["PM10"];
    dePM10->label = "PM10";
    dataSet*  PM10DataSet = new dataSet();
    PM10DataSet->dataElements = new vector<DataElement>();
    PM10DataSet->dataElements->push_back(*dePM10);
    PM10DataSet->colorIndex = 4;
    PM10DataSet->legend = string("Particules fines < 10 um (ug / m3)");

    DataElement* dePM25 = new DataElement();
    dePM25->value = data["stations"][0]["PM25"];
    dePM25->label = "PM25";
    dataSet*  PM25DataSet = new dataSet();
    PM25DataSet->dataElements = new vector<DataElement>();
    PM25DataSet->dataElements->push_back(*dePM25);
    PM25DataSet->colorIndex = 6;
    PM25DataSet->legend = string("Particules fines < 25 um (ug / m3)");

    CurveChartParams params;
    params.dataSets = new vector<dataSet>();
    params.dataSets->push_back(*ozoneDataSet);
    params.dataSets->push_back(*NO2DataSet);
    params.dataSets->push_back(*PM10DataSet);
    params.dataSets->push_back(*PM25DataSet);
    params.nbMeasures = 1;
    params.legendWidth = 300;
    params.titleHeight = 80;
    params.marginBottom = 100;
    params.marginLeft = 50;
    params.globalMin = 0;
    params.globalMax = 1;
    params.title = "AIr Quality WAtch";
    params.description = string("Location : ").append(datas[0]["stations"][0]["city"]);
    params.description.append(" ").append(datas[0]["stations"][0]["postalCode"]);
    params.description.append(" ").append(datas[0]["stations"][0]["placeName"]);
    params.description.append(" (").append(datas[0]["stations"][0]["countryCode"]).append(")");
    params.description.append(" - Updated ").append(myRegex::toFormatDDMMYYHHMM( datas[datas.size()-1]["stations"][0]["updatedAt"]));

    pieChartInit(params);
    curveChartSetLegend(params);
    pieChartDraw(params);


    FILE *out = fopen(options->getFullPieChartFileName().c_str(),"wb");
    gdImagePng(im,out);
    fclose(out);
    if(options->isDisplay())
    {
        char commande[300];
        sprintf(commande, "display %s &",options->getFullPieChartFileName().c_str());
        system(commande);
    }



}


void myGraphics::curveChart(json datas, myOptions *options)
{
    vector<DataElement>* ozoneVector = new vector<DataElement>();
    setVector(ozoneVector, datas, "OZONE");
    vector<DataElement>* PM10Vector = new vector<DataElement>();
    setVector(PM10Vector, datas, "PM10");
    vector<DataElement>* PM25Vector = new vector<DataElement>();
    setVector(PM25Vector, datas, "PM25");
    vector<DataElement>* NO2Vector = new vector<DataElement>();
    setVector(NO2Vector, datas, "NO2");

    CurveChartParams params;
    params.dataSets = new vector<dataSet>();

    dataSet* ozoneDataSet = new dataSet();
    ozoneDataSet->colorIndex = 2;
    ozoneDataSet->legend = string("Ozone (ppb)");
    ozoneDataSet->dataElements = ozoneVector;
    params.dataSets->push_back(*ozoneDataSet);

    dataSet* PM10DataSet = new dataSet();
    PM10DataSet->colorIndex = 4;
    PM10DataSet->legend = string("Particules fines < 10 um (ug / m3)");
    PM10DataSet->dataElements = PM10Vector;
    params.dataSets->push_back(*PM10DataSet);

    dataSet* PM25DataSet = new dataSet();
    PM25DataSet->colorIndex = 6;
    PM25DataSet->legend = string("Particules fines < 25 um (ug / m3)");
    PM25DataSet->dataElements = PM25Vector;
    params.dataSets->push_back(*PM25DataSet);

    dataSet* NO2DataSet = new dataSet();
    NO2DataSet->colorIndex = 8;
    NO2DataSet->legend = string("NO2 (ppb)");
    NO2DataSet->dataElements = NO2Vector;
    params.dataSets->push_back(*NO2DataSet);

    float globalMax = 0.0; // Dans ce cas, toutes les valeurs sont >0, sinon, prendre le max du premier dataset
    for (dataSet ds : *params.dataSets){
            float max = getDataVectorMaxValue(ds.dataElements);
            if(max > globalMax) globalMax = max;
    }

    float globalMin = 0.0;  // Dans ce cas, toutes les valeurs sont >0, sinon, faire une recherche de globalMin
    int nbMeasures = datas.size();

    params.nbMeasures = nbMeasures;
    params.legendWidth = 300;
    params.titleHeight = 80;
    params.marginBottom = 100;
    params.marginLeft = 50;
    params.globalMin = globalMin;
    params.globalMax = globalMax;
    params.title = "AIr Quality WAtch Evolution";
    params.description = string("Location : ").append(datas[0]["stations"][0]["city"]);
    params.description.append(" ").append(datas[0]["stations"][0]["postalCode"]);
    params.description.append(" ").append(datas[0]["stations"][0]["placeName"]);
    params.description.append(" (").append(datas[0]["stations"][0]["countryCode"]).append(")");
    params.description.append(" - Updated ").append(myRegex::toFormatDDMMYYHHMM( datas[datas.size()-1]["stations"][0]["updatedAt"]));

    curveChartInit(params);

    curveChartSetLegend(params);

    curveChartAddCurves(params);

    FILE *out = fopen(options->getFullCurveChartFileName().c_str(),"wb");
    gdImagePng(im,out);
    fclose(out);
    if(options->isDisplay())
    {
        char commande[300];
        sprintf(commande, "display %s &",options->getFullCurveChartFileName().c_str());
        system(commande);
    }

}
