/*
 * Copyright (c) 2016  Gabriel Alzamora.
 *
 * This code is licensed to you under the terms of the
 * GNU General Public License. See LICENSE file for the
 * text of the license, or the following URL:
 * https://www.gnu.org/licenses/gpl.html
 */

#ifndef MainCore_H
#define MainCore_H

class QTcpServer;
class QTimer;
class Apikinect;
class AttendClient;
class FrameGL;
class ConfigData;
#include "apikinect.h"

namespace Ui {
class MainCore;
}

class MainCore : public QObject
{
    Q_OBJECT

public:
    explicit MainCore(QObject *parent = 0);
    ~MainCore();
    std::vector<uint8_t> videoBuf;//!< container of video info from kinect
    std::vector<uint16_t> depthBuf;//!< container of depth info from kinect
    std::vector<point3rgb> p3rgbBuf;//!< container of points cloud <- video+depth
    //std::vector<point3c> p3cBuf;//!< container of points cloud with transparency component ¿¿¿para ADAPTAR VisorQT ???
    std::vector<point2> p2Buf;//!< container of 2D points = (point cloud) - color - y(coordinate)
    std::vector<uint32_t> barridoBuf;//!< barridoBuf contains distance on angle (360-i)/2 degrees, xOz plane

signals:
    void printVideo();//warn videoBuf ready to be printed
    void printDepth();
    void printBarrido();
    void print3D();
    void print2D();
    void printTimeVector();

    void updateSrvKinect(srvKinect newSrvK);

public slots:
    //freenect kinect
    void startK(int indexK=0);
    void stopK(int indexK=0);
    void updateKinect();//send current ledOption and angle to kinect
    //setters & getters
    int getDeviceStatus();
    void setSrvKinect(srvKinect newSrvK);//set new configuration data
    srvKinect getSrvKinect();
    void setCurrentKIndex(int index);
    int getCurrentKIndex();
    int getKnumber();
    int getTime(eOption opt);//in milliseconds : e_video, e_depth, e_3, e_2, e_barrido, e_accel
    accel getAccel();
    //start timers
    void go();//!< start sending data to mainwindow acord to configdata info
    void stop();//!< stop sending data to mainwindow

private slots:
    void init();
    //server
    void startServer();
    void attendNewClient();
    //
    void nextVideoFrame();//!< convenience function to use qtimers
    void nextDepthFrame();//!< convenience function to use qtimers
    void next3DFrame();//!< convenience function to use qtimers

protected:


private:
    int numKinects;//!< number of detected kinects
    int currentKIndex;//!< index of active kinect
    QTimer *timerVideo;
    QTimer *timerDepth;
    QTimer *timer3D;

    Freenect::Freenect freenect;//!< Freenect class object to start events thread and Apikinect
    freenect_context *context;//!< point to usb context associated to kinect data handling
    Apikinect *device;//!< class object that handle kinect sending led, angle orders, receiving frames, acceleration data
    ConfigData *config;
    QTcpServer *server;
    AttendClient *attendant;
    std::vector<AttendClient*> attendVector;//!< contain active AttendClient (allow to access them)

    accel a;//!< acceleration components x,y,z (y ~ 9,81 if m_iAnguloKinect=0)
    std::vector<int> timeVector;//msecs
    pBuf structBuffers;//!< to tell server where to find data buffers

    int flag;//!< 0 stop loop(), otherwise let loop() run

};
#endif // MainCore_H
