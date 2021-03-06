/*
 * Copyright (c) 2017  Gabriel Alzamora.
 *
 * This code is licensed to you under the terms of the
 * GNU General Public License. See LICENSE file for the
 * text of the license, or the following URL:
 * https://www.gnu.org/licenses/gpl.html
 */

#ifndef APIKINECT2_H
#define APIKINECT2_H

#include <mutex>
#include <vector>
#include "apikinect/include/libfreenect.hpp"
#include "apikinect/configdata.h"

class Apikinect2 : public Freenect::FreenectDevice
{

public:
    explicit Apikinect2(freenect_context *_ctx, int _index);

public:
    void VideoCallback(void *_rgb, uint32_t timestamp);// Do not call directly, even in child
    void DepthCallback(void *_depth, uint32_t timestamp);// Do not call directly, even in child
    bool getRGB(std::vector<uint8_t> &buffer);
    bool getDepth(std::vector<uint16_t> &buffer);

    void getAll(std::vector<point3rgb> &buffer3,std::vector<uint32_t> &bufferB);//
    void getAll(pBuf *structBuffers, srvKinect *aSrvKinect);

    void getAccel(accel &a);
    void getAngle(int &a);
    void setAngle(int a);

private:
    freenect_device * myself;
    std::mutex m_rgb_mutex;//!< mutex to ensure video frame data save access
    std::mutex m_depth_mutex;//!< mutex to ensure depth frame data save access

    std::vector<uint8_t> m_buffer_video;//!< buffer to store usb incoming video frame (see VideoCallback)
    std::vector<uint16_t> m_buffer_depth;//!< buffer to store usb incoming depth frame (see DepthCallback)
    bool m_new_rgb_frame;//!< flag true if we have new frame data in m_buffer_video, otherwise false
    bool m_new_depth_frame;//!< flag true if we have new frame data in m_buffer_depth, otherwise false
};

#endif // APIKINECT2_H
