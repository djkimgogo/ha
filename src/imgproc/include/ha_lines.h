/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
#pragma once
#ifndef _HA_LINES_H_
#define _HA_LINES_H_

#include "ha_common.h"
#include "ha_config.h"

namespace ha {
  class HaLines : public HaCommon {
    private:
        HaLineTypes m_lineTypes = HaLineTypes::ALL;
        vector<Vec4i> m_lines;
    public:
        HaLines();
        void lineExtractionFrame(cv::Mat &input, const uint8_t scale = 1);
        void setLineTypes(const HaLineTypes lineTypes) {
            this->m_lineTypes = lineTypes;
        }
        HaLineTypes getLineTypes() const {
            return this->m_lineTypes;
        }
        void drawOutput(Mat &dst, const Scalar scalar = Scalar(0,0,255), const uint8_t scale = 1);
  };
}

#endif /* end of include guard:_HA_LINES_H_ */
