#ifndef SPLINEWIDGET_H
#define SPLINEWIDGET_H

#include "contentwidget.h"

class SplineWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit SplineWidget(std::unordered_map<unsigned int, int>* redFrequency=nullptr ,
                          std::unordered_map<unsigned int, int>* blueFrequency=nullptr ,
                          std::unordered_map<unsigned int, int>* greenFrequency=nullptr ,
                          QWidget *parent = nullptr);
};

#endif
