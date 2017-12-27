/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
#pragma once
#ifndef _HA_CIRCLES_H_
#define _HA_CIRCLES_H_

#include "ha_common.h"
#include "ha_config.h"

namespace ha {
  class HaCircles : public HaCommon {
    private:
        HaCircleTypes m_circleTypes = HaCircleTypes::CIRCLE;
        std::vector<Vec3f> m_circles;
    public:
      void circleExtractionFrame(cv::Mat &input, const uint8_t scale = 1);
      void setCircleTypes(const HaCircleTypes circleType) { this->m_circleTypes = circleType; }
      void drawOutput(Mat &dst, const Scalar scalar = Scalar(0,0,255), const uint8_t scale = 1);
  };
}

#endif /* end of include guard:_HA_CIRCLES_H_ */
