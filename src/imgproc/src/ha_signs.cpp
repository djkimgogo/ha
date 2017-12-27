/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
 #include "ha_signs.h"

 #include <opencv2/imgproc.hpp>

 void ha::HaSigns::signExtractionFrame(cv::Mat &input, const uint8_t scale) {
     scaleTo(input, input, scale);
    //  input.copyTo(output);
     // TBD
 }

 void ha::HaSigns::drawOutput(Mat &dst, const Scalar scalar, const uint8_t scale) {
     if (this->m_finalImageType == HaFinalImageTypes::INTERIM && !this->m_interimImg.empty()) {
         this->m_interimImg.copyTo(dst);
     }
     // TBD
 }
