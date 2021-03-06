/*
 * Copyright (c) 2017  Gabriel Alzamora.
 * Copyright (c) 2010 individual OpenKinect contributors.
 *
 * This code is licensed to you under the terms of the
 * GNU General Public License. See LICENSE file for the
 * text of the license, or the following URL:
 * https://www.gnu.org/licenses/gpl.html
 */

#include <math.h>       // sqrt(), atan()...
#include "apikinect2.h"

/*!
 * \class Apikinect2 adapted Apikinect for Calibration
 * \brief holds all kinect device properties to read & handel it.
 */

/*!
 * \brief constructor: reserve memory and set initial flags.
 * \param [out] _ctx return usb context to communicate with kinect.
 * \param [in] _index selected kinect index.
 */
Apikinect2::Apikinect2(freenect_context *_ctx, int _index)
    : Freenect::FreenectDevice(_ctx, _index),
      m_buffer_video(freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_VIDEO_RGB).bytes),
      m_buffer_depth(freenect_find_depth_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_DEPTH_11BIT).bytes / 2),
      m_new_rgb_frame(false),
      m_new_depth_frame(false)
{
    myself = const_cast<freenect_device*>(this->getDevice());//las vueltas que da la vida :o)
    setDepthFormat(FREENECT_DEPTH_11BIT);
}

/*!
 * \brief called if usb video event in Freenect::m_thread.
 * \param [out] _rgb poitns buffer where to save usb incoming video frame.
 * \param timestamp internal use to synchronize video & depth frames.
 * \see libfreenect.hpp Freenect::Freenect
 */
void Apikinect2::VideoCallback(void *_rgb, uint32_t timestamp)
{
    std::lock_guard<std::mutex> lock(m_rgb_mutex);//lock will be destroyed when exit VideoCallback
    uint8_t* rgb = static_cast<uint8_t*>(_rgb);
    copy(rgb, rgb+getVideoBufferSize(), m_buffer_video.begin());
    m_new_rgb_frame = true;
}

/*!
 * \brief called if usb depth event in Freenect::m_thread.
 * \param [out] _depth points buffer where to save usb incoming depth frame.
 * \param timestamp internal use to synchronize video & depth frames.
 * \see libfreenect.hpp Freenect::Freenect
 */
void Apikinect2::DepthCallback(void *_depth, uint32_t timestamp)
{
    std::lock_guard<std::mutex> lock(m_depth_mutex);//lock will be destroyed when exit DepthCallback
    uint16_t* depth = static_cast<uint16_t*>(_depth);
    copy(depth, depth+getDepthBufferSize()/2, m_buffer_depth.begin());
    m_new_depth_frame = true;
}

/*!
 * \brief retrieve video frame.
 * \param [out] buffer points to buffer where new video frame is stored.
 * \return true if we have new video frame, false if not new.
 */
bool Apikinect2::getRGB(std::vector<uint8_t> &buffer)
{
    std::lock_guard<std::mutex> lock(m_rgb_mutex);
    if (!m_new_rgb_frame)
        return false;
    buffer.swap(m_buffer_video);
    m_new_rgb_frame = false;
    return true;
}

/*!
 * \brief retrieve depth frame.
 * \param [out] buffer points to buffer where new depth frame is stored.
 * \return true if we have new depth frame, false if not new.
 */
bool Apikinect2::getDepth(std::vector<uint16_t> &buffer)
{
    std::lock_guard<std::mutex> lock(m_depth_mutex);
    if (!m_new_depth_frame)
        return false;
    buffer.swap(m_buffer_depth);
    m_new_depth_frame = false;
    return true;
}

/*!
 * \brief funtion to retrieve point cloud & barrido (swept) from video & depth data.
 *
 * Return 3D point cloud (2D may be retrieved from it) and barrido (swept)
 * in camera coordinates (Oz to where camera is looking, Ox right hand and
 * Oy downward to Oz)
 * \param [out] buffer3 buffer to receive point cloud.
 * \param [out] bufferB buffer to receive Barrido (swept).
 */
void Apikinect2::getAll(std::vector<point3rgb> &buffer3, std::vector<uint32_t> &bufferB)
{
    point3rgb p3;
    rgb color;
    buffer3.resize(0);
    for(int i=0;i<360;i++) bufferB[i]=0;
    float f = 595.f;//intrinsec kinect camera parameter fx=fy=f

    for (int i = 0; i < 480*640; ++i)
    {
        // Convert from image plane coordinates to world coordinates
        if( (p3.z = m_buffer_depth[i]) != 0  ){                  // Z = d
            p3.x = (i%640-(640-1)/2.f)*m_buffer_depth[i]/f;      // X = (x - cx) * d / fx
            p3.y = (i/640 - (480-1)/2.f) * m_buffer_depth[i] / f;// Y = (y - cy) * d / fy
            color.rgbRed = m_buffer_video[3*i+0];    // R
            color.rgbGreen = m_buffer_video[3*i+1];  // G
            color.rgbBlue = m_buffer_video[3*i+2];   // B
            p3.color = color;
            buffer3.push_back(p3);//MainWindow::p3Buf

            int index = 180-int(2*atan(double(p3.x)/double(p3.z))*180/M_PI);
            uint32_t length = uint32_t(sqrt( p3.x*p3.x + p3.z*p3.z ));//distance en mm
            if( bufferB[index]==0 || bufferB[index]>length)
                bufferB[index]=length;
        }
    }
}
/*!
 * \brief funtion to retrieve 3D, 2D & Barrido from video & depth data.
 *
 * From video, depth frames and srvKinect store 3D, 2D & Barrido in
 * structBuffers buffers in world coordinates (Oz horizontal ahead,
 * Ox horizontal right hand and Oy downwards).
 * \param [out] structBuffers points to struct holding buffers.
 * \param [in] aSrvKinect configuration data.
 */
void Apikinect2::getAll(pBuf *structBuffers, srvKinect *aSrvKinect)
{
    point2 p2;//2 dimensions points cloud
    point3rgb p3;//3D + color points cloud
    rgb color;
    structBuffers->ptrP3Buf->resize(0);//reset 3D points cloud
    structBuffers->ptrP2Buf->resize(0);//reset 2D points cloud
    for(int i=0;i<360;i++) (*structBuffers->ptrBarridoBuf)[i]=0;//reset Barrido vector
    float f = 595.f;//intrinsec kinect camera parameter fx=fy=f
    float angle(aSrvKinect->m_iAnguloKinect*M_PI/180.0);

    for (int i = 0; i < 480*640; i+=aSrvKinect->m_usModulo3D)
    {

        // Convert from image plane coordinates to world coordinates
        // Z into screen, Y downwards, X to the right as OpenGL
        // Z = depth*cos(angleKinect)+y*sin(angleKinect)  if angleKinect around x axis positive when Kinect upwards
        p3.z = m_buffer_depth[i]*cos(angle) + ((i/640-(480-1)/2.f)*m_buffer_depth[i]/f)*sin(angle);
        //within z limits
        if( (p3.z != 0) && (p3.z <= aSrvKinect->m_fZMax) ){
            // Y = (y - cy) * d / fy but remember angleKinect plus camera high
            // Y = y*cos((-1)*angleKinect)-depth*sin(angleKinect)-CameraHigh if angleKinect around Ox axis
            p3.y = ((i/640-(480-1)/2.f)*m_buffer_depth[i]/f)*cos(angle) - m_buffer_depth[i]*sin(angle) - aSrvKinect->m_fAltura*1000;
            //within y limits
            if( (p3.y >= (-1)*aSrvKinect->m_fYMax) && (p3.y <= (-1)*aSrvKinect->m_fYMin) ){//within y limits (remember Y downwards)
                p2.z = p3.z;
                p3.x = (i%640-(640-1)/2.f)*m_buffer_depth[i]/f;// X = (x - cx) * d / fx
                p2.x = p3.x;
                color.rgbRed = m_buffer_video[3*i+0];    // R
                color.rgbGreen = m_buffer_video[3*i+1];  // G
                color.rgbBlue = m_buffer_video[3*i+2];   // B
                p3.color = color;
                structBuffers->ptrP3Buf->push_back(p3);//stored in MainWindow::p3Buf
                structBuffers->ptrP2Buf->push_back(p2);//stored in MainWindow::p2Buf

                int index = 180-int(2*atan(double(p3.x)/double(p3.z))*180/M_PI);
                uint32_t distance = uint32_t(sqrt( p3.x*p3.x + p3.z*p3.z ));//distance en mm

                //within Barrido limits
                if( (p3.y >= (-1)*aSrvKinect->m_iBarridoYMax) && (p3.y <= (-1)*aSrvKinect->m_iBarridoYMin) ){
                    if( (*structBuffers->ptrBarridoBuf)[index]==0 || (*structBuffers->ptrBarridoBuf)[index]>distance )
                        (*structBuffers->ptrBarridoBuf)[index]=distance;
                }
            }
        }
    }
}

/*!
 * \brief store acceleration  components in a, accel strut
 * \param [out] a where acceleration components is saved as accel struct
 */
void Apikinect2::getAccel(accel &a)
{
    freenect_update_tilt_state(myself);
    freenect_get_mks_accel(freenect_get_tilt_state(myself), &a.accel_x, &a.accel_y, &a.accel_z);
}

/*!
 * \brief store angle in a
 * \param [out] a where angle is saved as int
 */
void Apikinect2::getAngle(int &a)
{
    freenect_raw_tilt_state *state;
    state = freenect_get_tilt_state(myself);
    a = state->tilt_angle;
}

/*!
 * \brief set kinect at int a angle
 * \param [in] a angle to be set
 *
 * kinect set angle over horizon, a=-10 head down 10º if its horizontal
 * but if it is looking down at -5º a=-10 will only tilt down 5º to
 * reach -10º. Limited to +-27º tilt
 */
void Apikinect2::setAngle(int a)
{
    if(a>27) a=27;
    if(a<-27) a=-27;
    this->setTiltDegrees(double(a));
}
