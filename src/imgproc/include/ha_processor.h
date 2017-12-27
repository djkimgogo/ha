/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
 #pragma once
 #ifndef _HA_PROCESSOR_H_
 #define _HA_PROCESSOR_H_

#include "ha_common.h"
#include "ha_config.h"

#include "ha_patterns.h"
#include "ha_circles.h"
#include "ha_colors.h"
#include "ha_lines.h"
#include "ha_signs.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

namespace ha {
    class HaProcessor : public HaCommon {
    private:
        HaPatterns m_patterns;
        HaCircles m_circles;
        HaColors m_colors;
        HaLines m_lines;
        HaSigns m_signs;
    public:
        void togglePatterns() { this->m_patterns.toggle(); }
        void toggleCircles() { this->m_circles.toggle(); }
        void toggleColors() { this->m_colors.toggle(); }
        void toggleLines() { this->m_lines.toggle(); }
        void toggleSigns() { this->m_signs.toggle(); }

        void toggleFinalImageTypes() {
            this->m_lines.toggleFinalImageTypes();
            this->m_circles.toggleFinalImageTypes();
            this->m_colors.toggleFinalImageTypes();
            this->m_signs.toggleFinalImageTypes();
            this->m_patterns.toggleFinalImageTypes();
        }
        void setEdgeTypes(const HaEdgeTypes edgeType) {
            this->m_lines.setEdgeTypes(edgeType);
            this->m_circles.setEdgeTypes(edgeType);
            this->m_colors.setEdgeTypes(edgeType);
            this->m_signs.setEdgeTypes(edgeType);
            this->m_patterns.setEdgeTypes(edgeType);
        }

        void setLineTypes(const HaLineTypes lineType) { this->m_lines.setLineTypes(lineType); }
        void setPatternTypes(const HaPatternTypes patternType) { this->m_patterns.setPatternTypes(patternType); }
        void setColorTypes(const HaColorTypes colorType) { this->m_colors.setColorTypes(colorType); }
        void setSignTypes(const HaSignTypes signType) { this->m_signs.setSignTypes(signType); }
        void setCircleTypes(const HaCircleTypes circleType) { this->m_circles.setCircleTypes(circleType); }
        void process(Mat &src, Mat &dst, const uint8_t scale = 1);
        void drawOutput(Mat &dst, const Scalar scalar = Scalar(0,0,255), const uint8_t scale = 1);
    };
}

#endif // _HA_PROCESSOR_H_
