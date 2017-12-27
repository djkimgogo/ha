/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
 #include "ha_processor.h"

 using namespace ha;

 void ha::HaProcessor::process(Mat &src, Mat &dst, const uint8_t scale) {
     try {
         scaleTo(src, src, scale);
         src.copyTo(dst);

         if (this->m_patterns.enabled()) {
             vector<Point2f> corners;
             if (this->m_patterns.findPatternFrame(src, corners, scale)) {
                 this->m_patterns.drawPatternCorners(dst, Mat(corners));
             } else {
                 this->m_patterns.drawPatternCorners(dst, Mat(corners), false);
             }
         }
         if (this->m_circles.enabled()) {
             this->m_circles.circleExtractionFrame(src);
             this->m_circles.drawOutput(dst, Scalar(255,0,0));
         }
         if (this->m_lines.enabled()) {
             this->m_lines.lineExtractionFrame(src);
             this->m_lines.drawOutput(dst, Scalar(0,0,255));
         }
         if (this->m_colors.enabled()) {
             this->m_colors.colorExtractionFrame(src);
             this->m_colors.drawOutput(dst);
         }
         if (this->m_signs.enabled()) {
             this->m_signs.signExtractionFrame(src);
             this->m_signs.drawOutput(dst);
         }
     } catch (Exception &e) {
         spd::get("console")->error("{0}", e.what());
     }
 }

 void ha::HaProcessor::drawOutput(Mat &dst, const Scalar scalar, const uint8_t scale) {
     if (this->m_finalImageType == HaFinalImageTypes::INTERIM && !this->m_interimImg.empty()) {
         this->m_interimImg.copyTo(dst);
     }
     // TBD
 }
