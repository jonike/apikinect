/*
 * Copyright (c) 2016  Gabriel Alzamora.
 *
 * This code is licensed to you under the terms of the
 * GNU General Public License. See LICENSE file for the
 * text of the license, or the following URL:
 * https://www.gnu.org/licenses/gpl.html
 */

#include "configdata.h"
/*!
  \class ConfigData
  \brief A class to handle configuration data

  Used to show parámeters and allow input actions from user
  Used to allow update of server data with client data
 */

/*!
 * \brief ConfigData::ConfigData
 * constructor that show all buttons, sliders... and \
 * connect changes on them to data update functions
 * \param parent
 * pointer to QWidget parent of ConfigData
 */
ConfigData::ConfigData(QWidget *parent) : QWidget(parent)
{
    //------------Start TAB LAYOUT-----------!!!!!!!!!
    QGroupBox *gbDepth = new QGroupBox(tr("depth"));//--------------DEPTH group
        QLabel *DepthLabelrefresco = new QLabel(tr("refresco"));
        DepthSlider = new QSlider(Qt::Horizontal);
        DepthSlider->setTickPosition(QSlider::TicksBelow);
        DepthSlider->setMinimum(33);
        DepthSlider->setMaximum(2000);
        DepthSlider->setSingleStep(200);
        DepthSlider->setValue(33);
        DepthLabelSlider = new QLabel;
        DepthLabelSlider->setFixedWidth(40);
        QString strD;
        DepthLabelSlider->setText(strD.setNum(DepthSlider->sliderPosition()));
        QHBoxLayout *LyDepth1 = new QHBoxLayout;
        LyDepth1->addWidget(DepthLabelrefresco);
        LyDepth1->addWidget(DepthSlider);
        LyDepth1->addWidget(DepthLabelSlider);
        DepthCBenvio = new QCheckBox("envío");
        DepthCBenvio->setChecked(true);
        DepthCBcomprimido = new QCheckBox("comprimido");
        DepthCBcomprimido->setChecked(false);
        QHBoxLayout *LyDepth2 = new QHBoxLayout;
        LyDepth2->addWidget(DepthCBenvio);
        LyDepth2->addWidget(DepthCBcomprimido);
        QVBoxLayout *LyDepth = new QVBoxLayout;//depth group layout
        LyDepth->addLayout(LyDepth1);
        LyDepth->addLayout(LyDepth2);
        LyDepth->addStretch(2);
    gbDepth->setLayout(LyDepth);//setting depth group layout //-----DEPTH group

    QGroupBox *gbVideo = new QGroupBox(tr("video"));//--------------VIDEO group
        QLabel *VideoLabelrefresco = new QLabel(tr("refresco"));
        VideoSlider = new QSlider(Qt::Horizontal);
        VideoSlider->setTickPosition(QSlider::TicksBelow);
        VideoSlider->setMinimum(33);
        VideoSlider->setMaximum(2000);
        VideoSlider->setSingleStep(200);
        VideoSlider->setValue(33);
        VideoLabelSlider = new QLabel;
        VideoLabelSlider->setFixedWidth(40);
        QString strV;
        VideoLabelSlider->setText(strV.setNum(VideoSlider->sliderPosition()));
        QHBoxLayout *LyVideo1 = new QHBoxLayout;
        LyVideo1->addWidget(VideoLabelrefresco);
        LyVideo1->addWidget(VideoSlider);
        LyVideo1->addWidget(VideoLabelSlider);
        VideoCBenvio = new QCheckBox("envío");
        VideoCBenvio->setChecked(true);
        VideoCBcomprimido = new QCheckBox("comprimido");
        VideoCBcomprimido->setChecked(false);
        QHBoxLayout *LyVideo2 = new QHBoxLayout;
        LyVideo2->addWidget(VideoCBenvio);
        LyVideo2->addWidget(VideoCBcomprimido);
        QVBoxLayout *LyVideo = new QVBoxLayout;//video group layout
        LyVideo->addLayout(LyVideo1);
        LyVideo->addLayout(LyVideo2);
        LyVideo->addStretch(2);
    gbVideo->setLayout(LyVideo);//setting video group layout //-----VIDEO group

    QGroupBox *gbLimits = new QGroupBox(tr("limits"));//------------LIMITS group
        QLabel *LimitsLabelAltura = new QLabel(tr("altura"));
        LimitsLineEAltura = new QLineEdit();
        LimitsLineEAltura->setText("0.56");
        QHBoxLayout *LyAltura = new QHBoxLayout;
        LyAltura->addWidget(LimitsLabelAltura);
        LyAltura->addWidget(LimitsLineEAltura);

        QLabel *LimitsLabelAngulo = new QLabel(tr("angulo"));
        LimitsLineEAngulo = new QLineEdit();
        LimitsLineEAngulo->setText("0.0");
        QHBoxLayout *LyAngulo = new QHBoxLayout;
        LyAngulo->addWidget(LimitsLabelAngulo);
        LyAngulo->addWidget(LimitsLineEAngulo);

        QLabel *LimitsLabelAngK = new QLabel(tr("ang Kinect"));
        LimitsLineEAngK = new QLineEdit();
        LimitsLineEAngK->setText("0");
        QHBoxLayout *LyAngK = new QHBoxLayout;
        LyAngK->addWidget(LimitsLabelAngK);
        LyAngK->addWidget(LimitsLineEAngK);

        QVBoxLayout *LyColumn1 = new QVBoxLayout;
        LyColumn1->addLayout(LyAltura);
        LyColumn1->addLayout(LyAngulo);
        LyColumn1->addLayout(LyAngK);

        QLabel *LimitsLabelYmin = new QLabel(tr("Y min"));
        LimitsLineEYmin = new QLineEdit();
        LimitsLineEYmin->setText("-1000");
        QHBoxLayout *LyYmin = new QHBoxLayout;
        LyYmin->addWidget(LimitsLabelYmin);
        LyYmin->addWidget(LimitsLineEYmin);

        QLabel *LimitsLabelYmax = new QLabel(tr("Y max"));
        LimitsLineEYmax = new QLineEdit();
        LimitsLineEYmax->setText("2000");
        QHBoxLayout *LyYmax = new QHBoxLayout;
        LyYmax->addWidget(LimitsLabelYmax);
        LyYmax->addWidget(LimitsLineEYmax);

        QLabel *LimitsLabelZmax = new QLabel(tr("Z max"));
        LimitsLineEZmax = new QLineEdit();
        LimitsLineEZmax->setText("10000");
        QHBoxLayout *LyZmax = new QHBoxLayout;
        LyZmax->addWidget(LimitsLabelZmax);
        LyZmax->addWidget(LimitsLineEZmax);

        QVBoxLayout *LyColumn2 = new QVBoxLayout;
        LyColumn2->addLayout(LyYmin);
        LyColumn2->addLayout(LyYmax);
        LyColumn2->addLayout(LyZmax);

        QHBoxLayout *LyLimits = new QHBoxLayout;//limits group layout
        LyLimits->addLayout(LyColumn1);
        LyLimits->addLayout(LyColumn2);
        LyLimits->addStretch(2);
    gbLimits->setLayout(LyLimits);//setting limits group layout //---LIMITS group

    QGroupBox *gbPoints = new QGroupBox(tr("points 3D"));//---------POINTS group
        QLabel *PointsLabelrefresco = new QLabel(tr("refresco"));
        PointsSlider = new QSlider(Qt::Horizontal);
        PointsSlider->setTickPosition(QSlider::TicksBelow);
        PointsSlider->setMinimum(33);
        PointsSlider->setMaximum(2000);
        PointsSlider->setSingleStep(200);
        PointsSlider->setValue(33);
        PointsLabelSlider = new QLabel;
        PointsLabelSlider->setFixedWidth(40);
        QString strP;
        PointsLabelSlider->setText(strP.setNum(PointsSlider->sliderPosition()));
        QHBoxLayout *LyPoints1 = new QHBoxLayout;
        LyPoints1->addWidget(PointsLabelrefresco);
        LyPoints1->addWidget(PointsSlider);
        LyPoints1->addWidget(PointsLabelSlider);

        QLabel *PointsLabelM = new QLabel(tr("modulo"));
        PointsSliderM = new QSlider(Qt::Horizontal);
        PointsSliderM->setTickPosition(QSlider::TicksBelow);
        PointsSliderM->setMinimum(1);
        PointsSliderM->setMaximum(10);
        PointsSliderM->setSingleStep(1);
        PointsSliderM->setValue(1);
        PointsLabelSliderM = new QLabel;
        PointsLabelSliderM->setFixedWidth(40);
        QString strPM;
        PointsLabelSliderM->setText(strPM.setNum(PointsSliderM->sliderPosition()));
        QHBoxLayout *LyPoints2 = new QHBoxLayout;
        LyPoints2->addWidget(PointsLabelM);
        LyPoints2->addWidget(PointsSliderM);
        LyPoints2->addWidget(PointsLabelSliderM);

        PointsCBenvio3D = new QCheckBox("envío 3D");
        PointsCBenvio3D->setChecked(true);
        PointsCBenvio2 = new QCheckBox("envío 2D");
        PointsCBenvio2->setChecked(false);
        PointsCBenvioB= new QCheckBox("envío Barrido");
        PointsCBenvioB->setChecked(true);
        PointsCBcomprimido = new QCheckBox("comprimido");
        PointsCBcomprimido->setChecked(false);
        QVBoxLayout *LyPoints3 = new QVBoxLayout;
        LyPoints3->addWidget(PointsCBenvio3D);
        LyPoints3->addWidget(PointsCBenvio2);
        LyPoints3->addWidget(PointsCBenvioB);
        LyPoints3->addWidget(PointsCBcomprimido);

        QLabel *PointsLabelYmin = new QLabel(tr("Y min"));
        PointsLineEYmin = new QLineEdit();
        PointsLineEYmin->setText("-1000");
        QHBoxLayout *LyPointsYmin = new QHBoxLayout;
        LyPointsYmin->addWidget(PointsLabelYmin);
        LyPointsYmin->addWidget(PointsLineEYmin);
        QLabel *PointsLabelYmax = new QLabel(tr("Y max"));
        PointsLineEYmax = new QLineEdit();
        PointsLineEYmax->setText("2000");
        QHBoxLayout *LyPointsYmax = new QHBoxLayout;
        LyPointsYmax->addWidget(PointsLabelYmax);
        LyPointsYmax->addWidget(PointsLineEYmax);
        QLabel *PointsLabelEcu = new QLabel(tr("Ecu"));
        PointsLineEEcu = new QLineEdit();
        PointsLineEEcu->setText("10000");
        QHBoxLayout *LyPointsEcu = new QHBoxLayout;
        LyPointsEcu->addWidget(PointsLabelEcu);
        LyPointsEcu->addWidget(PointsLineEEcu);
        QVBoxLayout *LyPoints4 = new QVBoxLayout;
        LyPoints4->addLayout(LyPointsYmin);
        LyPoints4->addLayout(LyPointsYmax);
        LyPoints4->addLayout(LyPointsEcu);

        QHBoxLayout *LyPoints5 = new QHBoxLayout;
        LyPoints5->addLayout(LyPoints3);
        LyPoints5->addLayout(LyPoints4);

        QVBoxLayout *LyPoints = new QVBoxLayout;//points group layout
        LyPoints->addLayout(LyPoints1);
        LyPoints->addLayout(LyPoints2);
        LyPoints->addLayout(LyPoints5);
        LyPoints->addStretch(2);
    gbPoints->setLayout(LyPoints);//setting points group layout //--POINTS group

    QGroupBox *gbLed = new QGroupBox("led");
        QRadioButton *off = new QRadioButton("off");
        QRadioButton *green = new QRadioButton("green");
        QRadioButton *red = new QRadioButton("red");
        QRadioButton *yellow = new QRadioButton("yellow");
        QRadioButton *blinkG = new QRadioButton("blink green");
        QRadioButton *blinkRY = new QRadioButton("blink R/Y");
        QHBoxLayout *LyLed = new QHBoxLayout;
        ledGroup = new QButtonGroup(this);//to handle led state selected
        ledGroup->addButton(off,0);
        ledGroup->addButton(green,1);
        ledGroup->addButton(red,2);
        ledGroup->addButton(yellow,3);
        ledGroup->addButton(blinkG,4);
        ledGroup->addButton(blinkRY,6);
        LyLed->addWidget(off);
        LyLed->addWidget(green);
        LyLed->addWidget(red);
        LyLed->addWidget(yellow);
        LyLed->addWidget(blinkG);
        LyLed->addWidget(blinkRY);
        off->setChecked(true);
        ledOption = 0;//--------ledOption(0)
    gbLed->setLayout(LyLed);

    QHBoxLayout *LyTab1 = new QHBoxLayout;//upper tab layout depth+video
    LyTab1->addStretch();
    LyTab1->addWidget(gbDepth);
    LyTab1->addStretch();
    LyTab1->addWidget(gbVideo);
    LyTab1->addStretch();//-----------------UPPER TAB layout

    QHBoxLayout *LyTab2 = new QHBoxLayout;//mid tab layout limits+points
    LyTab2->addWidget(gbLimits);
    LyTab2->addStretch();
    LyTab2->addWidget(gbPoints);//---------MID TAB layout

    QVBoxLayout *LyTab = new QVBoxLayout;
        LyTab->addStretch();
        LyTab->addLayout(LyTab1);
        LyTab->addStretch();
        LyTab->addLayout(LyTab2);
        LyTab->addStretch();
        LyTab->addWidget(gbLed);
        LyTab->addStretch();

    setLayout(LyTab);

    connect(DepthSlider,SIGNAL(sliderMoved(int)),DepthLabelSlider,SLOT(setNum(int)));
    connect(VideoSlider,SIGNAL(sliderMoved(int)),VideoLabelSlider,SLOT(setNum(int)));
    connect(PointsSlider,SIGNAL(sliderMoved(int)),PointsLabelSlider,SLOT(setNum(int)));
    connect(PointsSliderM,SIGNAL(sliderMoved(int)),PointsLabelSliderM,SLOT(setNum(int)));
    //------------END TAB LAYOUT-----------!!!!!!!!!!
    //------------let's connect-------------
    connect(LimitsLineEAngulo,SIGNAL(editingFinished()),this,SLOT(setConfigData()));//---limits
    connect(LimitsLineEAngK,SIGNAL(editingFinished()),this,SLOT(setConfigData()));
    connect(LimitsLineEAltura,SIGNAL(editingFinished()),this,SLOT(setConfigData()));
    connect(LimitsLineEYmin,SIGNAL(editingFinished()),this,SLOT(setConfigData()));
    connect(LimitsLineEYmax,SIGNAL(editingFinished()),this,SLOT(setConfigData()));
    connect(LimitsLineEZmax,SIGNAL(editingFinished()),this,SLOT(setConfigData()));

    connect(PointsSlider,SIGNAL(sliderReleased()),this,SLOT(setConfigData()));//---------points
    connect(PointsSliderM,SIGNAL(sliderReleased()),this,SLOT(setConfigData()));
    connect(PointsCBenvio3D,SIGNAL(stateChanged(int)),this,SLOT(setConfigData()));
    connect(PointsCBenvio2,SIGNAL(stateChanged(int)),this,SLOT(setConfigData()));
    connect(PointsCBenvioB,SIGNAL(stateChanged(int)),this,SLOT(setConfigData()));
    connect(PointsCBcomprimido,SIGNAL(stateChanged(int)),this,SLOT(setConfigData()));
    connect(PointsLineEEcu,SIGNAL(editingFinished()),this,SLOT(setConfigData()));
    connect(PointsLineEYmin,SIGNAL(editingFinished()),this,SLOT(setConfigData()));
    connect(PointsLineEYmax,SIGNAL(editingFinished()),this,SLOT(setConfigData()));

    connect(DepthSlider,SIGNAL(sliderReleased()),this,SLOT(setConfigData()));//----------depth
    connect(DepthCBenvio,SIGNAL(stateChanged(int)),this,SLOT(setConfigData()));
    connect(DepthCBcomprimido,SIGNAL(stateChanged(int)),this,SLOT(setConfigData()));
    connect(VideoSlider,SIGNAL(sliderReleased()),this,SLOT(setConfigData()));//----------video
    connect(VideoCBenvio,SIGNAL(stateChanged(int)),this,SLOT(setConfigData()));
    connect(VideoCBcomprimido,SIGNAL(stateChanged(int)),this,SLOT(setConfigData()));

    connect(ledGroup,SIGNAL(buttonClicked(int)),this,SLOT(setLedOption(int)));//---led

    setConfigData();
}

/*!
 * \brief ConfigData::setLedOption
 * to set led light on kinect
 * \param integer holding freenect_led_options value to set led light
 */
void ConfigData::setLedOption(int option)
{
    if(option != ledOption){
        ledOption = option;
        emit configDataChanged();
    }
}

/*!
 * \brief ConfigData::getLedOption
 * \return int value of freenect_led_options
 */
int ConfigData::getLedOption()
{
    return ledOption;
}

/*!
 * \brief ConfigData::setConfigData
 * set ConfigData members values as selected in gui
 */
void ConfigData::setConfigData()
{
    srvK.m_fAngulo = LimitsLineEAngulo->text().toFloat();
    srvK.m_iAnguloKinect = LimitsLineEAngK->text().toInt();
    if( srvK.m_iAnguloKinect > 30 ){
        srvK.m_iAnguloKinect = 30;
        LimitsLineEAngK->setText("30");
    }else if( srvK.m_iAnguloKinect < -30 ){
        srvK.m_iAnguloKinect = -30;
        LimitsLineEAngK->setText("-30");
    }
    srvK.m_fAltura = LimitsLineEAltura->text().toFloat();
    srvK.m_fYMin = LimitsLineEYmin->text().toFloat();
    srvK.m_fYMax = LimitsLineEYmax->text().toFloat();
    srvK.m_fZMax = LimitsLineEZmax->text().toFloat();

    srvK.m_ulRefresco3D = PointsSlider->value();
    srvK.m_usModulo3D = PointsSliderM->value();
    if( PointsCBenvio3D->isChecked() ) srvK.m_bEnvio3D = 1;
    else srvK.m_bEnvio3D = 0;
    if( PointsCBenvio2->isChecked() ) srvK.m_bEnvio2D = 1;
    else srvK.m_bEnvio2D = 0;
    if( PointsCBenvioB->isChecked() ) srvK.m_bEnvioBarrido = 1;
    else srvK.m_bEnvioBarrido = 0;
    if( PointsCBcomprimido->isChecked() ) srvK.m_bCompress3D = 1;
    else srvK.m_bCompress3D = 0;
    srvK.m_iBarridoEcu = PointsLineEEcu->text().toInt();
    srvK.m_iBarridoYMin = PointsLineEYmin->text().toInt();
    srvK.m_iBarridoYMax = PointsLineEYmax->text().toInt();

    srvK.m_ulRefrescoDepth = DepthSlider->value();
    if( DepthCBenvio->isChecked() ) srvK.m_bEnvioDepth = 1;
    else srvK.m_bEnvioDepth = 0;
    if( DepthCBcomprimido->isChecked() ) srvK.m_bCompressDepth = 1;
    else srvK.m_bCompressDepth = 0;
    srvK.m_ulRefrescoColor = VideoSlider->value();
    if( VideoCBenvio->isChecked() ) srvK.m_bEnvioColor = 1;
    else srvK.m_bEnvioColor = 0;
    if( VideoCBcomprimido->isChecked() ) srvK.m_bCompressColor = 1;
    else srvK.m_bCompressColor = 0;

    emit configDataChanged();
}

/*!
 * \brief ConfigData::setSrvK
 * sets individual values to all members of srvKinect
 * \param newSrvK   srvKinect to copy in ConfigData.srvK
 */
void ConfigData::setSrvK(srvKinect newSrvK)
{
    srvK.m_fAngulo = newSrvK.m_fAngulo;
    srvK.m_iAnguloKinect = newSrvK.m_iAnguloKinect;
    srvK.m_fAltura = newSrvK.m_fAltura;
    srvK.m_fYMin = newSrvK.m_fYMin;
    srvK.m_fYMax = newSrvK.m_fYMax;
    srvK.m_fZMax = newSrvK.m_fZMax;
    srvK.m_ulRefresco3D = newSrvK.m_ulRefresco3D;
    srvK.m_usModulo3D = newSrvK.m_usModulo3D;
    srvK.m_bEnvio3D = newSrvK.m_bEnvio3D;
    srvK.m_bEnvio2D = newSrvK.m_bEnvio2D;
    srvK.m_bEnvioBarrido = newSrvK.m_bEnvioBarrido;
    srvK.m_bCompress3D = newSrvK.m_bCompress3D;
    srvK.m_iBarridoEcu = newSrvK.m_iBarridoEcu;
    srvK.m_iBarridoYMin = newSrvK.m_iBarridoYMin;
    srvK.m_iBarridoYMax = newSrvK.m_iBarridoYMax;
    srvK.m_ulRefrescoDepth = newSrvK.m_ulRefrescoDepth;
    srvK.m_bEnvioDepth = newSrvK.m_bEnvioDepth;
    srvK.m_bCompressDepth = newSrvK.m_bCompressDepth;
    srvK.m_ulRefrescoColor = newSrvK.m_ulRefrescoColor;
    srvK.m_bEnvioColor = newSrvK.m_bEnvioColor;
    srvK.m_bCompressColor = newSrvK.m_bCompressColor;
}

/*!
 * \brief ConfigData::getSrvK
 * \return ConfigData.srvK
 */
srvKinect ConfigData::getSrvK()
{
    return srvK;
}

/*!
 * \brief ConfigData::setVideoCBcomprimido
 * check box to send video compress, value set
 * show client setting on server ConfigData tab
 * \param value
 * uint8_t = 0 not checked, otherwise checked (send compressed)
 */
void ConfigData::setVideoCBcomprimido(uint8_t value)
{
    if( value ) VideoCBcomprimido->setChecked(true);
    else VideoCBcomprimido->setChecked(false);
}
/**
 * @brief ConfigData::setVideoCBenvio
 * check box to send video, value set
 * show client setting on server ConfigData tab
 * @param value
 * uint8_t = 0 not checked, otherwise checked (send)
 */
void ConfigData::setVideoCBenvio(uint8_t value)
{
    if( value ) VideoCBenvio->setChecked(true);
    else VideoCBenvio->setChecked(false);
}
/**
 * @brief ConfigData::setVideoSlider
 * refresh in msec request next video frame
 * show client setting on server ConfigData tab
 * @param value
 * uint32_t from 1 to 2000 msec
 * below 33 msec is unrealistic
 */
void ConfigData::setVideoSlider(uint32_t value)
{
    VideoSlider->setValue(value);
    QString s;
    s.setNum(value);
    VideoLabelSlider->setText(s);
}
/**
 * @brief ConfigData::setDepthCBcomprimido
 * check box to send depth compress, value set
 * show client setting on server ConfigData tab
 * @param value
 * uint8_t = 0 not checked, otherwise checked (send compressed)
 */
void ConfigData::setDepthCBcomprimido(uint8_t value)
{
    if( value ) DepthCBcomprimido->setChecked(true);
    else DepthCBcomprimido->setChecked(false);
}
/**
 * @brief ConfigData::setDepthCBenvio
 * check box to send depth, value set
 * show client setting on server ConfigData tab
 * @param value
 * uint8_t = 0 not checked, otherwise checked (send)
 */
void ConfigData::setDepthCBenvio(uint8_t value)
{
    if( value ) DepthCBenvio->setChecked(true);
    else DepthCBenvio->setChecked(false);
}
/**
 * @brief ConfigData::setDepthSlider
 * refresh in msec request next depth frame
 * show client setting on server ConfigData tab
 * @param value
 * uint32_t from 1 to 2000 msec
 * below 33 msec is unrealistic
 */
void ConfigData::setDepthSlider(uint32_t value)
{
    DepthSlider->setValue(value);
    QString s;
    s.setNum(value);
    DepthLabelSlider->setText(s);
}
/**
 * @brief ConfigData::setPointsLineEYmax
 * set superior limit in mm to record ConfigData
 * show client setting on server ConfigData tab
 * @param value
 * int32_t distance in mm respect ground level
 */
void ConfigData::setPointsLineEYmax(int32_t value)
{
    QString sY;
    sY.setNum(value);
    PointsLineEYmax->setText(sY);
}
/**
 * @brief ConfigData::setPointsLineEYmin
 * set inferior limit in mm to record ConfigData
 * @param value
 * int32_t distance in mm respect ground level
 */
void ConfigData::setPointsLineEYmin(int32_t value)
{
    QString sY;
    sY.setNum(value);
    PointsLineEYmin->setText(sY);
}
/**
 * @brief ConfigData::setPointsLineEEcu
 * 'barrido' maximum distance in mm to record ConfigData
 * show client setting on server ConfigData tab
 * @param value
 * uint32_t distance in mm
 */
void ConfigData::setPointsLineEEcu(int32_t value)
{
    QString s;
    s.setNum(value);
    PointsLineEEcu->setText(s);
}
/**
 * @brief ConfigData::setPointsCBcomprimido
 * check box to send 'barrido' compress value set
 * show client setting on server ConfigData tab
 * @param value
 * uint8_t = 0 not checked, otherwise checked (send compressed)
 */
void ConfigData::setPointsCBcomprimido(uint8_t value)
{
    if( value ) PointsCBcomprimido->setChecked(true);
    else PointsCBcomprimido->setChecked(false);
}
/**
 * @brief ConfigData::setPointsCBenvioB
 * check box to send 'barrido' value set
 * show client setting on server ConfigData tab
 * @param value
 * uint8_t = 0 not checked, otherwise checked (send)
 */
void ConfigData::setPointsCBenvioB(uint8_t value)
{
    if( value ) PointsCBenvioB->setChecked(true);
    else PointsCBenvioB->setChecked(false);
}
/**
 * @brief ConfigData::setPointsCBenvio2
 * check box to send 2D points value set
 * show client setting on server ConfigData tab
 * @param value
 * uint8_t = 0 not checked, otherwise checked (send)
 */
void ConfigData::setPointsCBenvio2(uint8_t value)
{
    if( value ) PointsCBenvio2->setChecked(true);
    else PointsCBenvio2->setChecked(false);
}
/**
 * @brief ConfigData::setPointsCBenvio3D
 * check box to send 3D points value set
 * show client setting on server ConfigData tab
 * @param value
 * uint8_t = 0 not checked, otherwise checked (send)
 */
void ConfigData::setPointsCBenvio3D(uint8_t value)
{
    if( value ) PointsCBenvio3D->setChecked(true);
    else PointsCBenvio3D->setChecked(false);
}
/**
 * @brief ConfigData::setPointsSliderM
 * from how many points pick one to add to point cloud
 * show client setting on server ConfigData tab
 * @param value
 * uint8_t from 1 (all selected 100%) to 10 (10% selected)
 */
void ConfigData::setPointsSliderM(uint8_t value)
{
    PointsSliderM->setValue(value);
    QString s;
    s.setNum(value);
    PointsLabelSliderM->setText(s);
}
/**
 * @brief ConfigData::setPointsSlider
 * refresh in msec request next point cloud
 * show client setting on server ConfigData tab
 * @param value
 * uint32_t from 1 to 2000 msec
 * below 33 msec is unrealistic
 */
void ConfigData::setPointsSlider(uint32_t value)
{
    PointsSlider->setValue(value);
    QString s;
    s.setNum(value);
    PointsLabelSlider->setText(s);
}
/**
 * @brief ConfigData::setLimitsLineEZmax
 * maximum distance in mm to record ConfigData
 * show client setting on server ConfigData tab
 * @param value
 * double distance in mm from camera to
 * longest distance recorded
 */
void ConfigData::setLimitsLineEZmax(double value)
{
    QString sZ;
    sZ.setNum(value);
    LimitsLineEZmax->setText(sZ);
}
/**
 * @brief ConfigData::setLimitsLineEYmax
 * maximum high in mm to record data
 * show client setting on server ConfigData tab
 * @param value
 * double distance in mm from ground to
 * highest data to be shown
 */
void ConfigData::setLimitsLineEYmax(double value)
{
    QString sY;
    sY.setNum(value);
    LimitsLineEYmax->setText(sY);
}
/**
 * @brief ConfigData::setLimitsLineEYmin
 * minimum hight in mm to start data record
 * show client setting on server ConfigData tab
 * @param value
 * double distance in mm from ground to
 * lowest data to be shown
 */
void ConfigData::setLimitsLineEYmin(double value)
{
    QString sY;
    sY.setNum(value);
    LimitsLineEYmin->setText(sY);
}
/**
 * @brief ConfigData::setLimitsLineEAltura
 * high of camera above ground in meters
 * show client setting on server ConfigData tab
 * @param value
 * double distance in meters to ground from camera
 */
void ConfigData::setLimitsLineEAltura(double value)
{
    QString sA;
    sA.setNum(value);
    LimitsLineEAltura->setText(sA);
}
/**
 * @brief ConfigData::setLimitsLineEAngK
 * angle of kinect camera respect horizontal
 * show client setting on server ConfigData tab
 * @param value
 * integer to set camera angle horizontal = 0º limits(-30 30)
 */
void ConfigData::setLimitsLineEAngK(int8_t value)
{
    if( value < -30 ){
        value = - 30;
        qDebug(" -  máximo angulo -30");
    }
    if( value > 30 ){
        value = 30;
        qDebug(" -  máximo angulo 30");
    }
    QString sAngulo;
    sAngulo.setNum(value);
    LimitsLineEAngK->setText(sAngulo);
}
/**
 * @brief ConfigData::setLimitsLineEAngulo
 * angle of kinect base
 * show client setting on server ConfigData tab
 * @param value
 * double to set angle, horizontal = 0º
 */
void ConfigData::setLimitsLineEAngulo(double value)
{
    /// arregla esto , que esté de -359.99999 a 359.9999----DEBUG
//    if( value > 360.0 ) value = value%360;
    QString sAngulo;
    sAngulo.setNum(value);
    LimitsLineEAngulo->setText(sAngulo);
}

