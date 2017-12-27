/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
#include "ha_lines.h"

#include <opencv2/imgproc.hpp>

ha::HaLines::HaLines() {
}

void ha::HaLines::lineExtractionFrame(cv::Mat &src, const uint8_t scale) {
  Mat dst;
  Mat gimg1, gimg2;
  scaleTo(src, src, scale);
  switch (this->m_edgeType) {
    case HaEdgeTypes::CANNY:
        Canny( src, dst, CV_CANNY_TH_1, CV_CANNY_TH_2, CV_CANNY_APERTURE_SIZE, true );
        break;
    case HaEdgeTypes::L_O_G:
        // under experiment...
        cvtToGray(src, gimg1);
        cv::filter2D(gimg1, gimg2, gimg1.depth(), this->m_kernelGauss);
        cv::filter2D(gimg2, dst, gimg2.depth(), this->m_kernelLaplace);
        Canny( dst, dst, 100, 200, CV_CANNY_APERTURE_SIZE );
        break;
    default:
        break;
    }

    dst.copyTo(this->m_interimImg);

#if 0
  vector<Vec2f> lines;
  HoughLines( dst, lines, 1, CV_PI/180, 100 );
  for( size_t i = 0; i < lines.size(); i++ )
  {
      float rho = lines[i][0];
      float theta = lines[i][1];
      double a = cos(theta), b = sin(theta);
      double x0 = a*rho, y0 = b*rho;
      Point pt1(cvRound(x0 + 1000*(-b)),
                cvRound(y0 + 1000*(a)));
      Point pt2(cvRound(x0 - 1000*(-b)),
                cvRound(y0 - 1000*(a)));
      line( color_dst, pt1, pt2, Scalar(0,0,255), 3, 8 );
  }
#else

    int offset(0);
    if (this->m_lineTypes == HaLineTypes::HORIZONTAL || this->m_lineTypes == HaLineTypes::LANES) {
        offset = dst.rows/2;
    }
    HoughLinesP( dst(Rect(0,offset,dst.cols,dst.rows - offset)), this->m_lines, CV_HOUGHLINESP_RHO, CV_HOUGHLINESP_THETA, CV_HOUGHLINESP_TH, CV_HOUGHLINESP_MIN_LINE_LENGTH, CV_HOUGHLINESP_MAX_LINE_GAP );
    for ( size_t i=0; i<this->m_lines.size() && offset!=0; ++i ) {
        this->m_lines[i][1] += offset;
        this->m_lines[i][3] += offset;
    }
#endif
}

void ha::HaLines::drawOutput(Mat &dst, const Scalar scalar, const uint8_t scale) {
    if (this->m_finalImageType == HaFinalImageTypes::INTERIM && !this->m_interimImg.empty()) {
        this->m_interimImg.copyTo(dst);
    }
    scaleTo(dst, dst, scale);
    cvtToColor(dst, dst);

    int minX(0),maxX(0);
    for( size_t i = 0; i < this->m_lines.size(); i++ ) {
        bool drawLine(false);
        Point pt1(this->m_lines[i][0], this->m_lines[i][1]), pt2(this->m_lines[i][2], this->m_lines[i][3]);
        double slope = std::atan2(pt2.y - pt1.y, pt2.x - pt1.x) * 180.0/CV_PI;
        // spd::get("console")->info("slope = {}", slope);
        switch (this->m_lineTypes) {
            case HaLineTypes::ALL:
                drawLine = true;
                break;
            case HaLineTypes::VERTICAL:
                if (std::abs(std::abs(slope) - 90.0) <= HA_HOUGH_LINES_TOL) {
                    drawLine = true;
                }
                break;
            case HaLineTypes::HORIZONTAL:
                if ((std::abs(std::abs(slope) - 180.0) <= HA_HOUGH_LINES_TOL) || (std::abs(slope) <= HA_HOUGH_LINES_TOL)) {
                    drawLine = true;
                }
                break;
            case HaLineTypes::LANES:
                minX = std::min(pt1.x,pt2.x);
                maxX = std::max(pt1.x,pt2.x);
                if ((minX > dst.cols/2 && (std::abs(std::abs(slope) - 135.0) <= HA_HOUGH_LINES_TOL)) ||
                    (maxX < dst.cols/2 && (std::abs(std::abs(slope) - 45.0) <= HA_HOUGH_LINES_TOL))) {
                    drawLine = true;
                }
                break;
            default:
                break;
        }
        if (!drawLine) {
            continue;
        }
        line( dst, pt1, pt2, scalar, 1, 8 );
    }
}
