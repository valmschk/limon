#include "styl.h"
#include<QPixmap>
#include<QPalette>



QString Styl::getStartButtonsStyle()
{
    return "QPushButton{"
           "color:#fff;"
           "border-radius:19px;"
           "background-color:skyblue }";

}
QString Styl::getStartWindowStyle(){
    return "QWidget#centralwidget{"
           "background-image:url(:/resources/resources/3d784859eb76163d624346071c4ab33b.jpg);"
           "background-repeat: no-repeat;"
           "background-position: left;"
           "background-size: 60% 100%;"
           "background-color:bisque;"
           "}";
}

