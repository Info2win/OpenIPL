#ifndef BARWIDGET_H
#define BARWIDGET_H

#include "../contentwidget.h"

class BarWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit BarWidget( std::unordered_map<unsigned int, int>* redFrequency=nullptr ,
                        std::unordered_map<unsigned int, int>* blueFrequency=nullptr ,
                        std::unordered_map<unsigned int, int>* greenFrequency=nullptr ,
                       QWidget *parent = nullptr);
};

#endif // BARWIDGET_H
