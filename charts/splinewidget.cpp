#include "splinewidget.h"

#include <QChart>
#include <QSplineSeries>
#include <QValueAxis>

SplineWidget::SplineWidget(std::unordered_map<unsigned int, int>* redFrequency ,
                           std::unordered_map<unsigned int, int>* blueFrequency ,
                           std::unordered_map<unsigned int, int>* greenFrequency ,
                           QWidget *parent)
    : ContentWidget(parent)
{
    //![1]
    auto chart = new QChart;
    chart->setTitle("<b>Histogram of the Image</b>");
    //![1]
    //![2]
    int maxPixelCount = 0;
    if(redFrequency && blueFrequency && greenFrequency)
    {
        auto redSeries = new QSplineSeries;
        redSeries->setName("Red");
        redSeries->setColor(QColor(Qt::GlobalColor::red));
        auto greenSeries = new QSplineSeries;
        greenSeries->setName("Green");
        greenSeries->setColor(Qt::GlobalColor::green);
        auto blueSeries = new QSplineSeries;
        blueSeries->setName("Blue");
        blueSeries->setColor(Qt::GlobalColor::blue);
        for(auto pixelValue : *redFrequency)
        {
            if(pixelValue.second > maxPixelCount)
            {
                maxPixelCount = pixelValue.second;
            }
        }
        for(auto pixelValue : *greenFrequency)
        {
            if(pixelValue.second > maxPixelCount)
            {
                maxPixelCount = pixelValue.second;
            }
        }
        for(auto pixelValue : *blueFrequency)
        {
            if(pixelValue.second > maxPixelCount)
            {
                maxPixelCount = pixelValue.second;
            }
        }
        for(int i=0; i<256; ++i)
        {
            redSeries->append(i,(*redFrequency)[i]);
        }
        for(int i=0; i<256; ++i)
        {
            greenSeries->append(i,(*greenFrequency)[i]);
        }
        for(int i=0; i<256; ++i)
        {
            blueSeries->append(i,(*blueFrequency)[i]);
        }
        chart->addSeries(redSeries);
        chart->addSeries(greenSeries);
        chart->addSeries(blueSeries);
    }
    else if(redFrequency && !blueFrequency  && !greenFrequency) // Only Red Channel Wanted
    {
        auto redSeries = new QSplineSeries;
        redSeries->setName("Red");
        redSeries->setColor(QColor(Qt::GlobalColor::red));
        for(auto pixelValue : *redFrequency)
        {
            if(pixelValue.second > maxPixelCount)
            {
                maxPixelCount = pixelValue.second;
            }
        }
        for(int i=0; i<256; ++i)
        {
            redSeries->append(i,(*redFrequency)[i]);
        }
        chart->addSeries(redSeries);

    }
    else if(greenFrequency && !redFrequency && !blueFrequency) // Only Green Channel Wanted
    {
        auto greenSeries = new QSplineSeries;
        greenSeries->setName("Green");
        greenSeries->setColor(QColor(Qt::GlobalColor::green));
        for(auto pixelValue : *greenFrequency)
        {
            if(pixelValue.second > maxPixelCount)
            {
                maxPixelCount = pixelValue.second;
            }
        }
        for(int i=0; i<256; ++i)
        {
            greenSeries->append(i,(*greenFrequency)[i]);
        }
        chart->addSeries(greenSeries);
    }
    else if (blueFrequency && !redFrequency && !greenFrequency) // Only Blue Channel Wanted
    {
        auto blueSeries = new QSplineSeries;
        blueSeries->setName("Blue");
        blueSeries->setColor(QColor(Qt::GlobalColor::blue));
        for(auto pixelValue : *blueFrequency)
        {
            if(pixelValue.second > maxPixelCount)
            {
                maxPixelCount = pixelValue.second;
            }
        }
        for(int i=0; i<256; ++i)
        {
            blueSeries->append(i,(*blueFrequency)[i]);
        }
        chart->addSeries(blueSeries);

    }
    else // Something wrong with parameters
    {
        return;
    }

    //![2]

    //![3]
    auto axisX = new QValueAxis;
    auto axisY = new QValueAxis;
    axisX->setRange(0,255);
    axisY->setRange(0,maxPixelCount);
    axisX->setTitleText("Intensity");
    axisY->setTitleText("Frequency");
    chart->addAxis(axisX,Qt::AlignBottom);
    chart->addAxis(axisY,Qt::AlignLeft);

    //![3]

    //![4]
    createDefaultChartView(chart);
    //![4]
}
