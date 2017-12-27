#pragma once
#ifndef _HA_CONFIG_H_
#define _HA_CONFIG_H_

#define CHESSBOARD_W (9)
#define CHESSBOARD_H (7)
#define CIRCLE_GRID_ROW (11)
#define CIRCLE_GRID_COL (4)

// cv::HoughLineP
#define CV_HOUGHLINESP_RHO   (1.0)
#define CV_HOUGHLINESP_THETA   (CV_PI/180.0)
#define CV_HOUGHLINESP_TH   (30)
#define CV_HOUGHLINESP_MIN_LINE_LENGTH   (100.0)
#define CV_HOUGHLINESP_MAX_LINE_GAP   (10.0)

// cv::Canny
#define CV_CANNY_TH_1 (10)
#define CV_CANNY_TH_2 (250)
#define CV_CANNY_APERTURE_SIZE (5)

// cv::Laplacian
#define CV_LAPLACIAN_DDEPTH (CV_16S)
#define CV_LAPLACIAN_KSIZE (7)
#define CV_LAPLACIAN_SCALE (1.0)
#define CV_LAPLACIAN_DELTA (0.0)

#define CV_CVTSCALEABS_SIGMA (3)

// cv::HoughCircles
#define CV_HOUGH_CIRCLES_A (100)
#define CV_HOUGH_CIRCLES_B (30)
#define CV_HOUGH_CIRCLES_MIN_RADIUS (1)
#define CV_HOUGH_CIRCLES_MAX_RADIUS (30)

// ha::lines
#define HA_HOUGH_LINES_TOL  (5.0)

#endif // _HA_CONFIG_H_
