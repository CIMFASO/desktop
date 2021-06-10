#ifndef WAITINGSPINNERWIDGET_H
#define WAITINGSPINNERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QColor>

class WaitingSpinnerWidget : public QWidget{
    Q_OBJECT
public:
    WaitingSpinnerWidget(QWidget *parent=0,bool centerOnParent = true ,bool parentRight = false , bool disableParentWhenSpinning = true);
    WaitingSpinnerWidget(Qt::WindowModality modality,QWidget *parent = 0,bool centerOnParent = true, bool disableParentWhenSpinning = true);

public slots:
    void start();
    void stop();
public:
    void setColor(QColor color);
    void setRoundness(qreal roundness);
    void setMinimunTrailOpacity(qreal minimumTrailOpacity);
    void setRevolutionsPerSecond(qreal revolutionsPerSecond);
    void setTrailFadePercentage(qreal trail);
    void setNumberOfLines(int lines);
    void setLineLength(int length);
    void setLineWidth(int width);
    void setInnerRadius(int radius);
    void setMessage(QString message);
    void setDataSourceIsEmpty(bool value);

    QColor color();
    qreal roundness();
    qreal minimumTrailOpacity();
    qreal trailFadePercentage();
    qreal revolutionsPerSecond();
    int numberOfLines();
    int lineLength();
    int lineWidth();
    int innerRadius();

    bool isSpinning() const;

private slots:
    void rotate();

protected:
    void paintEvent(QPaintEvent *event);
private:
    static int lineCountDistanceFromPrimary(int current, int primary,int totalNrOfLines);
    static QColor currentLineColor(int distance,int totalNrOfLines,qreal trailFadePerc,qreal minOpacity,QColor color);
    void initialize();
    void updateSize();
    void updateTimer();
    void updatePosition();

private:
    QColor _color;
    qreal _roundness;
    qreal _minimumTrailOpacity;
    qreal _revolutionsPerSecond;
    qreal _trailFadePercentage;
    int _numberOfLines;
    int _lineLength;
    int _lineWidth;
    int _innerRadius;

private:
    WaitingSpinnerWidget(const WaitingSpinnerWidget&);
    WaitingSpinnerWidget& operator =(const WaitingSpinnerWidget&);
    QTimer *_timer;
    QString _message;
    bool _parentRight;
    bool _centerOnParent;
    bool _disableParentWhenSpinning;
    int _currentCounter;
    bool _isSpinning;
    bool _dataSourceIsEmpty;
};

#endif // WAITINGSPINNERWIDGET_H
