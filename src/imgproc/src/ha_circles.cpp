/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
#include "ha_circles.h"

#include <opencv2/imgproc.hpp>

void ha::HaCircles::circleExtractionFrame(cv::Mat &input, const uint8_t scale) {
    scaleTo(input, input, scale);

    Mat gray, gimg1, gimg2;
    cvtToGray(input, gray);
    medianBlur(gray, gray, 5);

    switch (this->m_edgeType) {
      case HaEdgeTypes::CANNY:
          Canny( gray, gray, CV_CANNY_TH_1, CV_CANNY_TH_2, CV_CANNY_APERTURE_SIZE, true );
          break;
      case HaEdgeTypes::L_O_G:
          // under experiment...
          cvtToGray(gray, gimg1);
          cv::filter2D(gimg1, gimg2, gimg1.depth(), this->m_kernelGauss);
          cv::filter2D(gimg2, gray, gimg2.depth(), this->m_kernelLaplace);
          Canny( gray, gray, 100, 200, CV_CANNY_APERTURE_SIZE );
          break;
      default:
          break;
      }

      gray.copyTo(this->m_interimImg);

      int offset(0);
      if (1) {
          offset = gray.rows/2;
      }
      HoughCircles(gray(Rect(0,offset,gray.cols,gray.rows - offset)), this->m_circles, HOUGH_GRADIENT, 1,
                 gray.rows/16, // change this value to detect circles with different distances to each other
                 CV_HOUGH_CIRCLES_A, CV_HOUGH_CIRCLES_B, CV_HOUGH_CIRCLES_MIN_RADIUS, CV_HOUGH_CIRCLES_MAX_RADIUS // change the last two parameters
                                // (min_radius & max_radius) to detect larger circles
                 );
    for ( size_t i=0; i<this->m_circles.size() && offset!=0; ++i ) {
     this->m_circles[i][1] += offset;
    //  this->m_lines[i][3] += offset;
    }
}

void ha::HaCircles::drawOutput(Mat &dst, const Scalar scalar, const uint8_t scale) {
    if (this->m_finalImageType == HaFinalImageTypes::INTERIM && !this->m_interimImg.empty()) {
        this->m_interimImg.copyTo(dst);
    }
    scaleTo(dst, dst, scale);

    for( size_t i = 0; i < this->m_circles.size(); i++ ) {
        Vec3i c = this->m_circles[i];
        circle( dst, Point(c[0], c[1]), c[2], scalar, 3, LINE_AA);
        // circle( dst, Point(c[0], c[1]), 2, scalar, 3, LINE_AA);
    }
}
