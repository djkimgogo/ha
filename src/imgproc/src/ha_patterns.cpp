/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
#include "ha_patterns.h"

#include <opencv2/imgproc.hpp>

bool ha::HaPatterns::findPatternFrame(cv::Mat &input, vector<Point2f> corners, const uint8_t scale) {
    bool found(false);

    scaleTo(input, input, scale);
    Mat inputGray;
    cvtToGray(input, inputGray);

    if (this->m_patternTypes == HaPatternTypes::CHESSBOARD) {
      this->m_patternSize = Size(CHESSBOARD_H, CHESSBOARD_W);
      found = findChessboardCorners(inputGray, this->m_patternSize, corners, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK);
      if (found) {
        cornerSubPix(inputGray, corners, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
      }
    } else if (this->m_patternTypes == HaPatternTypes::CIRCLESGRID) {
      found = findCirclesGrid(inputGray, this->m_patternSize, corners, CALIB_CB_ASYMMETRIC_GRID);
    }
    // input.copyTo(output);


    return found;
}

void ha::HaPatterns::drawPatternCorners(cv::Mat &input, vector<Point2f> corners, const bool found) {
    drawChessboardCorners(input, this->m_patternSize, corners, found);
}

void ha::HaPatterns::drawOutput(Mat &dst, const Scalar scalar, const uint8_t scale) {
    if (this->m_finalImageType == HaFinalImageTypes::INTERIM && !this->m_interimImg.empty()) {
        this->m_interimImg.copyTo(dst);
    }
    // TBD
}
