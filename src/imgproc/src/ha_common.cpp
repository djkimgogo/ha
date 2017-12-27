/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
 #include "ha_common.h"

 #include <opencv2/imgproc.hpp>

 void ha::HaCommon::cvtToColor(Mat &src, Mat &dst) {
     if (src.channels()==1) {
         cvtColor(src, dst, COLOR_GRAY2BGR);
     } else {
         src.copyTo(dst);
     }
 }

 void ha::HaCommon::cvtToGray(Mat &src, Mat &dst) {
     if (src.channels()==3) {
         cvtColor(src, dst, COLOR_BGR2GRAY);
     } else {
         src.copyTo(dst);
     }
 }

 void ha::HaCommon::scaleTo(Mat &src, Mat &dst, const uint8_t scale) {
     if (scale != 1) {
       resize(src, dst, cv::Size(src.cols/scale, dst.rows/scale));
   } else {
       src.copyTo(dst);
   }
 }

 ha::HaCommon::HaCommon() {
     static auto console = spd::stdout_color_mt("console");

     preFlight();
 }

 void ha::HaCommon::preFlight() {
     // 1/16 = 0.0625
     this->m_kernelGauss = cv::Mat(3, 3, CV_32F, cv::Scalar(0.0625));

     // Define matriz do filtro de Gauss
     this->m_kernelGauss.at<float>(0, 1) = 0.125;
     this->m_kernelGauss.at<float>(1, 0) = 0.125;
     this->m_kernelGauss.at<float>(1, 1) = 0.25;
     this->m_kernelGauss.at<float>(1, 2) = 0.125;
     this->m_kernelGauss.at<float>(2, 1) = 0.125;

     this->m_kernelLaplace = cv::Mat(3, 3, CV_32F, cv::Scalar(0.0));

     // Define matriz do filtro de Laplace
     this->m_kernelLaplace.at<float>(0, 1) = -1.0;
     this->m_kernelLaplace.at<float>(1, 0) = -1.0;
     this->m_kernelLaplace.at<float>(1, 1) = +4.0;
     this->m_kernelLaplace.at<float>(1, 2) = -1.0;
     this->m_kernelLaplace.at<float>(2, 1) = -1.0;

     /*
      float matrixLaplace [] = {
      0f,  1f,  0f,
      1f, -4f,  1f,
      0f,  1f,  0f
      };
      */
 }

 ha::HaCommon::~HaCommon() {

 }
