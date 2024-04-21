#include "barwidget.h"

#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QLegend>
#include <QValueAxis>
#include <QString>

BarWidget::BarWidget( std::unordered_map<unsigned int, int>* redFrequency ,
                      std::unordered_map<unsigned int, int>* blueFrequency ,
                      std::unordered_map<unsigned int, int>* greenFrequency ,
                     QWidget *parent)
    : ContentWidget(parent)
{
    int maxPixelCount = 0;
    QBarSeries* series = new QBarSeries;
    if(redFrequency && blueFrequency && greenFrequency)
    {

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

        auto redSet = new QBarSet("Red");
        for(int i=0; i<256; ++i)
        {
            *redSet << *std::to_string((*redFrequency)[i]).c_str();
        }
        auto greenSet = new QBarSet("Green");
        for(int i=0; i<256; ++i)
        {
            *greenSet << *std::to_string((*greenFrequency)[i]).c_str();
        }
        auto blueSet = new QBarSet("Blue");
        for(int i=0; i<256; ++i)
        {
            *blueSet << *std::to_string((*blueFrequency)[i]).c_str();
        }
        series->append(redSet);
        series->append(greenSet);
        series->append(blueSet);
    }
    else if(redFrequency && !blueFrequency  && !greenFrequency) // Only Red Channel Wanted
    {
        for(auto pixelValue : *redFrequency)
        {
            if(pixelValue.second > maxPixelCount)
            {
                maxPixelCount = pixelValue.second;
            }
        }
        auto redSet = new QBarSet("Red");
        for(int i=0; i<256; ++i)
        {
            *redSet << *std::to_string((*redFrequency)[i]).c_str();
        }
        series->append(redSet);
    }
    else if(greenFrequency && !redFrequency && !blueFrequency) // Only Green Channel Wanted
    {
        for(auto pixelValue : *greenFrequency)
        {
            if(pixelValue.second > maxPixelCount)
            {
                maxPixelCount = pixelValue.second;
            }
        }
        auto greenSet = new QBarSet("Green");
        for(int i=0; i<256; ++i)
        {
            *greenSet << *std::to_string((*greenFrequency)[i]).c_str();
        }
        series->append(greenSet);
    }
    else if (blueFrequency && !redFrequency && !greenFrequency) // Only Blue Channel Wanted
    {
        for(auto pixelValue : *blueFrequency)
        {
            if(pixelValue.second > maxPixelCount)
            {
                maxPixelCount = pixelValue.second;
            }
        }
        auto blueSet = new QBarSet("Blue");
        for(int i=0; i<256; ++i)
        {
            *blueSet << *std::to_string((*blueFrequency)[i]).c_str();
        }
        series->append(blueSet);

    }
    else // Something wrong with parameters
    {
        return;
    }

    //![3]
    auto chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("Histogram");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    //![3]

    //![4]
    QStringList categories;
    for(int pixelValue=0; pixelValue<256; ++pixelValue)
    {
        if(((*redFrequency)[pixelValue] != 0) || ((*greenFrequency)[pixelValue] != 0) || ((*blueFrequency)[pixelValue] != 0))
        categories.push_back(QString(std::to_string(pixelValue).c_str()));
    }
    auto axisX = new QBarCategoryAxis;
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto axisY = new QValueAxis;

    axisY->setRange(0,100);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    //![4]

    //![5]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    //![5]

    //![6]
    createDefaultChartView(chart);
    //![6]
}
