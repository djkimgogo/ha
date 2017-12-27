/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
#pragma once
#ifndef _HA_CALIB_COMMON_H_
#define _HA_CALIB_COMMON_H_

#include "ha_config.h"
#include "ha_common.h"

#include <opencv2/opencv.hpp>

using namespace cv;

namespace ha {
    class HaCalibCommon : HaCommon {
    private:
        Mat m_cameraMatrix[2];
        Mat m_distCoeffs[2];
        Mat m_R, m_T, m_E, m_F;
        Mat m_R1, m_R2, m_P1, m_P2, m_Q;
    public:
        HaCommon();
        ~HaCommon();

        void saveIntrinsic(std::string &intrinsic_file);
        void loadIntrinsic(std::string &intrinsic_file);
        void saveExtrinsic(std::string &extrinsic_file);
        void loadExtrinsic(std::string &extrinsic_file);
        void stereoRectify(Mat &left, Mat &right, Mat &rect_left, Mat &rect_right);
        void generateUndistortMap();
        void undistortImage(Mat &src, Mat &dst);
    };
}

#endif // _HA_CALIB_COMMON_H_;