/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
#pragma once
#ifndef _HA_COMMON_H_
#define _HA_COMMON_H_

#include <spdlog/spdlog.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
namespace spd = spdlog;

namespace ha {

    enum class HaLineTypes {
        ALL,
        VERTICAL,
        HORIZONTAL,
        LANES
    };

    enum class HaEdgeTypes {
      CANNY,
      L_O_G
    };

    enum class HaPatternTypes {
            CHESSBOARD,
            CIRCLESGRID
    };

    enum class HaColorTypes {
            R,
            G,
            B,
            W
    };

    enum class HaSignTypes {
            TRAFFIC,
            ROAD,
            ETC
    };

    enum class HaCircleTypes {
        ELLIPSE,
        CIRCLE
    };

    enum class HaFinalImageTypes {
        RAW,
        INTERIM
    };

    class HaCommon {
    private:
        bool m_enabled = false;
    protected:
        HaEdgeTypes m_edgeType = HaEdgeTypes::CANNY;
        HaFinalImageTypes m_finalImageType = HaFinalImageTypes::RAW;
        cv::Mat m_kernelGauss, m_kernelLaplace;
        Mat m_interimImg;
    public:
        HaCommon();
        ~HaCommon();

        // properties
        void setEdgeTypes(const HaEdgeTypes edgeType) {
            this->m_edgeType = edgeType;
        }
        HaEdgeTypes getEdgeTypes() const {
            return this->m_edgeType;
        }
        void toggleFinalImageTypes() {
            if (this->m_finalImageType == HaFinalImageTypes::RAW) {
                this->m_finalImageType = HaFinalImageTypes::INTERIM;
            } else {
                this->m_finalImageType = HaFinalImageTypes::RAW;
            }
        }

        void toggle() {
            this->m_enabled = !this->m_enabled;
        }
        bool enabled() {
            return this->m_enabled;
        }
        void cvtToColor(Mat &src, Mat &dst);
        void cvtToGray(Mat &src, Mat &dst);
        void scaleTo(Mat &src, Mat &dst, const uint8_t scale = 1);

        virtual void drawOutput(Mat &dst, const Scalar scalar = Scalar(0,0,255), const uint8_t scale = 1) = 0;

        void preFlight();
    };
}

#endif // _HA_COMMON_H_
