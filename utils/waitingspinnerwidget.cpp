#include "waitingspinnerwidget.h"

#include <cmath>
#include <algorithm>
#include <QPainter>
#include <QTimer>

WaitingSpinnerWidget::WaitingSpinnerWidget(QWidget *parent, bool centerOnParent,bool topRight, bool disableParentWhenSpinning)
    : QWidget(parent),
      _parentRight(topRight),
      _centerOnParent(centerOnParent),
      _disableParentWhenSpinning(disableParentWhenSpinning){
    initialize();
}

WaitingSpinnerWidget::WaitingSpinnerWidget(Qt::WindowModality modality, QWidget *parent, bool centerOnParent, bool disableParentWhenSpinning)
    : QWidget(parent,Qt::Dialog|Qt::FramelessWindowHint),
      _centerOnParent(centerOnParent),
      _disableParentWhenSpinning(disableParentWhenSpinning){
    initialize();

    setWindowModality(modality);
    setAttribute(Qt::WA_TranslucentBackground);


}
void WaitingSpinnerWidget::initialize(){
    _color = QColor::fromRgb(20,140,160);
    _roundness = 70.0;
    _minimumTrailOpacity = 15.0;
    _trailFadePercentage = 70.0;
    _revolutionsPerSecond = 2*1.57079632679489661923;
    _numberOfLines = 13;
    _lineLength = 25;
    _lineWidth = 5 ;
    _innerRadius = 3;
    _currentCounter = 0;
    _isSpinning = false;
    _dataSourceIsEmpty = false;
    _timer = new QTimer(this);
    updateTimer();
    connect(_timer,SIGNAL(timeout()),this,SLOT(rotate()));
    updateSize();
    hide();
}

void WaitingSpinnerWidget::paintEvent(QPaintEvent *){
    updatePosition();
    QPainter painter(this);
    painter.fillRect(this->rect(),Qt::transparent);
    painter.setRenderHint(QPainter::Antialiasing,true);

    if(_dataSourceIsEmpty){
        QImage image(":/images/aucune_donnee_text.png");
        setFixedSize(image.rect().size());
        updatePosition();
        painter.drawImage(rect(),image);
    }else{
        if(_currentCounter >= _numberOfLines){
            _currentCounter = 0;
        }

        painter.setPen(Qt::NoPen);
        for(int i=0 ; i<_numberOfLines ; i++){
            painter.save();
            painter.translate(_innerRadius + _lineLength,_innerRadius + _lineLength);
            qreal rotateAngle = static_cast<qreal>(360 * i) / static_cast<qreal>(_numberOfLines);
            painter.rotate(rotateAngle);
            painter.translate(_innerRadius,0);
            int distance = lineCountDistanceFromPrimary(i,_currentCounter,_numberOfLines);
            QColor color = currentLineColor(distance,_numberOfLines,_trailFadePercentage,_minimumTrailOpacity,_color);
            painter.setBrush(color);
            painter.drawRoundedRect(QRect(0,-_lineWidth/2,_lineLength,_lineWidth),_roundness,_roundness,Qt::RelativeSize);
            painter.restore();
        }
    }
}

void WaitingSpinnerWidget::start(){
    _isSpinning = true;
    rotate();
    show();

    if(parentWidget()->isEnabled() && _disableParentWhenSpinning){
        parentWidget()->setEnabled(false);
    }
    _currentCounter = 0;
    updateTimer();
}

void WaitingSpinnerWidget::stop(){
    _isSpinning = false;
    hide();

    if(!parentWidget()->isEnabled() && _disableParentWhenSpinning){
        parentWidget()->setEnabled(true);
    }

    if(_timer->isActive()){
        _timer->stop();
        _currentCounter = 0;
    }
}

void WaitingSpinnerWidget::setNumberOfLines(int lines){
    _numberOfLines = lines;
    _currentCounter = 0 ;
    updateTimer();
}

void WaitingSpinnerWidget::setLineLength(int length){
    _lineLength = length;
    updateSize();
}

void WaitingSpinnerWidget::setLineWidth(int width){
    _lineWidth = width;
    updateSize();
}

void WaitingSpinnerWidget::setInnerRadius(int radius){
    _innerRadius = radius;
    updateSize();
}

void WaitingSpinnerWidget::setMessage(QString message)
{
    _message = message;
}

void WaitingSpinnerWidget::setDataSourceIsEmpty(bool value)
{
    _dataSourceIsEmpty = value;
}

QColor WaitingSpinnerWidget::color(){
    return _color;
}

qreal WaitingSpinnerWidget::roundness(){
    return _roundness;
}

qreal WaitingSpinnerWidget::minimumTrailOpacity(){
    return _minimumTrailOpacity;
}

qreal WaitingSpinnerWidget::trailFadePercentage(){
    return _trailFadePercentage;
}

qreal WaitingSpinnerWidget::revolutionsPerSecond(){
    return _revolutionsPerSecond;
}

int WaitingSpinnerWidget::numberOfLines(){
    return _numberOfLines;
}

int WaitingSpinnerWidget::lineLength(){
    return _lineLength;
}

int WaitingSpinnerWidget::lineWidth(){
    return _lineWidth;
}

int WaitingSpinnerWidget::innerRadius(){
    return _innerRadius;
}

bool WaitingSpinnerWidget::isSpinning() const{
    return _isSpinning;
}

void WaitingSpinnerWidget::setRoundness(qreal roundness){
    _roundness = std::max(0.0,std::min(100.0,roundness));
}

void WaitingSpinnerWidget::setColor(QColor color){
    _color = color;
}

void WaitingSpinnerWidget::setRevolutionsPerSecond(qreal revolutionsPerSecond){
    _revolutionsPerSecond = revolutionsPerSecond;
    updateTimer();
}

void WaitingSpinnerWidget::setTrailFadePercentage(qreal trail){
    _trailFadePercentage = trail;
}

void WaitingSpinnerWidget::setMinimunTrailOpacity(qreal minimumTrailOpacity){
    _minimumTrailOpacity = minimumTrailOpacity;
}

void WaitingSpinnerWidget::rotate(){
    ++_currentCounter;
    if(_currentCounter >= _numberOfLines){
        _currentCounter = 0;
    }
    update();
}

void WaitingSpinnerWidget::updateSize(){
    int size = (_innerRadius + _lineLength)*2;
    setFixedSize(size,size);
}

void WaitingSpinnerWidget::updateTimer(){
    _timer->start(1000/(_numberOfLines * _revolutionsPerSecond));
}

void WaitingSpinnerWidget::updatePosition(){
    if(_centerOnParent){
        move((parentWidget()->width()/2)-(width()/2),(parentWidget()->height()/2)-(height()/2));
    }

}

int WaitingSpinnerWidget::lineCountDistanceFromPrimary(int current, int primary, int totalNrOfLines){
    int distance = primary - current;
    if(distance < 0){
        distance += totalNrOfLines;
    }

    return distance;
}

QColor WaitingSpinnerWidget::currentLineColor(int countDistance, int totalNrOfLines, qreal trailFadePerc, qreal minOpacity, QColor color){

    if(countDistance == 0){
        return color;
    }

    const qreal minAlphaF = minOpacity/100.0;
    int distanceThreshold = static_cast<int> (ceil((totalNrOfLines-1) * trailFadePerc/100.0));
    if(countDistance > distanceThreshold){
        color.setAlpha(minAlphaF);
    }else{
        qreal alphaDiff = color.alphaF()-minAlphaF;
        qreal gradient = alphaDiff/ static_cast<qreal>(distanceThreshold + 1);
        qreal resultAlpha = color.alphaF()-gradient*countDistance;

        resultAlpha = std::min(1.0,std::max(0.0,resultAlpha));
        color.setAlphaF(resultAlpha);
    }

    return color;
}
