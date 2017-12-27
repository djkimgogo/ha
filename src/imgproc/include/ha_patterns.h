/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
#pragma once
#ifndef _HA_PATTERNS_H_
#define _HA_PATTERNS_H_

#include "ha_common.h"
#include "ha_config.h"

namespace ha {
  class HaPatterns : public HaCommon {
    private:
        HaPatternTypes m_patternTypes;
        Size m_patternSize;
        bool m_found;
    public:
        void setPatternTypes(const HaPatternTypes &patternType) {
            this->m_patternTypes = patternType;
        }
        HaPatternTypes getPatternTypes() { return this->m_patternTypes; }
      bool findPatternFrame(cv::Mat &input, vector<Point2f> corners, const uint8_t scale = 1);
      void drawPatternCorners(cv::Mat &input, vector<Point2f> corners, const bool found = true);
      void drawOutput(Mat &dst, const Scalar scalar = Scalar(0,0,255), const uint8_t scale = 1);
  };
}

#endif // end of include guard:_HA_PATTERNS_H_
