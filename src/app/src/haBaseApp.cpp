/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <sys/stat.h>

#include "ha_processor.h"
#include "ha_visualizer.h"
#include "ha_optionparser.h"
#include "ha_sqlite_orm.h"
#include "ha_gps.h"

using namespace cv;
using namespace std;
using namespace ha;

//
int main(int argc, char** argv)
{
    HaDatabase haDatabase(string("sample.db"));
    haDatabase.initDb();

    /// init variables
    ha::HaViz haViz;
    ha::HaProcessor haProcessor;
    VideoCapture cap[2], vid[2];
    HaGps haGps;
    HaDbGps gps_db_data(1.0,1.0,std::string(""),std::string(""),1.0,1.0);
    string gps_data;

    // use opencv command line parser
    CommandLineParser parser(argc, argv, keys);
    parser.about("baseApp v1.0.0");

    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }

    int pscale = parser.get<int>("pscale");
    int sscale = parser.get<int>("sscale");
    cv::String path = (parser.has("path") ? parser.get<String>("path") : "");
    cv::String mode = (parser.has("mode") ? parser.get<String>("mode") : "");
    cv::String calib = (parser.has("calib") ? parser.get<String>("calib") : "");
    cv::String process = (parser.has("process") ? parser.get<String>("process") : "");
    int wait = parser.get<int>("wait");
    bool useGps = parser.has("gps");

    if (!parser.check()) {
        parser.printErrors();
        return 0;
    }

    // read GPS data
    // https://havoc.io/post/nmea/; http://www.catb.org/gpsd/client-howto.html#_c_examples_2
    // read ODB data
    // http://www.cplusplus.com/forum/general/128216/; https://github.com/lkrasner/obd-cxx;
    while (useGps) {
        if (haGps.init_gps()) {
            break;
        }
    }

    int count(0);
    while (useGps) {
        if (haGps.read_gps(gps_data)) {
            if (haGps.parse_gps(gps_data, gps_db_data)) {
                spd::get("console")->info("live: ({},{},{}) at {}{}", gps_db_data.latitude(), gps_db_data.longitude(), gps_db_data.angle(), gps_db_data.date(), gps_db_data.time());
                // unsigned long id = haDatabase.insertDbGps(gps_db_data);
                count++;
            }
        }
        if (count>5) {
            break;
        }
    }

    // vector<HaDbGps> gps_data_vector;
    // haDatabase.queryDbGps(gps_data_vector);
    // for (vector<HaDbGps>::iterator i = gps_data_vector.begin(); i!=gps_data_vector.end(); ++i) {
    //     spd::get("console")->info("recorded: ({},{},{}) at {}{}", i->latitude(), i->longitude(), i->angle(), i->date(), i->time());
    // }

    // return 0;

    /// use video Source
    // https://stackoverflow.com/questions/4290834/how-to-get-a-list-of-video-capture-devices-web-cameras-on-linux-ubuntu-c
    spd::get("console")->info("Start grabbing... Press any key to terminate!");

    Mat frame, outFrame;
    double e1, e2, timeL, timeR;
    char frameFileStr[256], cameraWinStr[256];
    unsigned int replay_index(0), timer_index(0), capture_index(0);
    int apiID = cv::CAP_ANY;
    unsigned char timer(0);
    bool capture_left(false), capture_right(false);

    for (;;) {
        for (int32_t i=0; i<2; ++i) {
            if (mode=="replay") {
                string path_str = path.c_str();
                if (path_str.find(".avi")!=string::npos ||
                    path_str.find(".mov")!=string::npos ||
                    path_str.find(".AVI")!=string::npos ||
                    path_str.find(".MOV")!=string::npos) {
                    if (i==1) {
                        continue;
                    }
                    if (!vid[i].isOpened()) {
                        vid[i].open(path);
                        if (vid[i].isOpened()) {
                            vid[i].read(frame);
                        }
                    } else {
                        vid[i].read(frame);
                    }
                } else {
                    snprintf(frameFileStr, 256, "%s/%d/frame%06d.jpg", path.c_str(), i, replay_index);
                    frame = cv::imread(frameFileStr);
                }
            } else if (mode=="capture" || parser.has("preview")) {
                  if (!cap[i].isOpened()) {
                    cap[i].open(i + apiID);
                    if (cap[i].isOpened()) {
                      cap[i].set(CV_CAP_PROP_FRAME_HEIGHT, 720.0);
                      cap[i].set(CV_CAP_PROP_FRAME_WIDTH, 1280.0);
                      cap[i].set(CAP_PROP_AUTOFOCUS, 0);
                      cap[i].set(CAP_PROP_GAIN, 0.0);
                      spd::get("console")->info("gain: {} autofocus: {} brightness: {} exposure: {}\n gamma: {} contrast: {} saturation: {}\n wb_blue_u: {} wb_red_v: {} sharpness: {} focus: {}\n backlight: {}",
                          cap[i].get(CAP_PROP_GAIN),
                          cap[i].get(CAP_PROP_AUTOFOCUS),
                          cap[i].get(CAP_PROP_BRIGHTNESS),
                          cap[i].get(CAP_PROP_EXPOSURE),
                          cap[i].get(CAP_PROP_GAMMA),
                          cap[i].get(CAP_PROP_CONTRAST),
                          cap[i].get(CAP_PROP_SATURATION),
                          cap[i].get(CAP_PROP_WHITE_BALANCE_BLUE_U),
                          cap[i].get(CAP_PROP_WHITE_BALANCE_RED_V),
                          cap[i].get(CAP_PROP_SHARPNESS),
                          cap[i].get(CAP_PROP_FOCUS),
                          cap[i].get(CAP_PROP_BACKLIGHT));
                    //   cap[i].set(CAP_PROP_BRIGHTNESS, 1);
                      cap[i].read(frame);
                    }
                  } else {
                    // cap[i].set(CV_CAP_PROP_FRAME_HEIGHT, 720.0);
                    // cap[i].set(CV_CAP_PROP_FRAME_WIDTH, 1280.0);
                    cap[i].read(frame);
                  }
            }
            if (frame.empty()) {
                if (mode=="replay") {
                    spd::get("console")->error("ERROR! no more available frame(s)");
                    return 1;
                } else {
                    spd::get("console")->error("ERROR! blank frame grabbed");
                    // cap[i].close();
                    break;
                }
            }
            // run process
            snprintf(cameraWinStr, 256, "cam#%d", i);
            if (parser.has("process")) {
                e1 = (double)cv::getTickCount();
                haProcessor.process(frame, outFrame, pscale);
                e2 = (double)cv::getTickCount();
                timeL = (e2 - e1)/ cv::getTickFrequency();
                haViz.imgshow(cameraWinStr, frame, outFrame, timeL, sscale);
                moveWindow(cameraWinStr, i * frame.cols, 0);
            } else if (parser.has("preview")) {
                if (mode=="capture") {
                    if (parser.has("timer")) {
                        if (++timer%10==0) {
                            spd::get("console")->info("{}...\n", timer);
                        }
                        if (timer>=100) {
                            snprintf(frameFileStr, 256, "%s/%d/frame%06d.jpg", path.c_str(), i, timer_index);
                            try {
                                cv::imwrite(frameFileStr, frame);
                            } catch (cv::Exception& e) {
                                spd::get("console")->info(e.what());
                            }
                            if (!capture_left) {
                                if (i == 0) {
                                    capture_left = true;
                                }
                            }
                            if (!capture_right) {
                                if (i == 1) {
                                    capture_right = true;
                                }
                            }
                            if (capture_left && capture_right) {
                                timer = 0;
                                timer_index++;
                                capture_left = capture_right = false;
                            }
                        }
                    } else {
                        snprintf(frameFileStr, 256, "%s/%d/frame%06d.jpg", path.c_str(), i, capture_index);
                        try {
                            cv::imwrite(frameFileStr, frame);
                        } catch (cv::Exception& e) {
                            spd::get("console")->info(e.what());
                        }
                        if (!capture_left) {
                            if (i == 0) {
                                capture_left = true;
                            }
                        }
                        if (!capture_right) {
                            if (i == 1) {
                                capture_right = true;
                            }
                        }
                        if (capture_left && capture_right) {
                            capture_index++;
                            capture_left = capture_right = false;
                        }
                    }
                }
                haViz.imgshow(cameraWinStr, frame, frame, -1, sscale);
                moveWindow(cameraWinStr, i * frame.cols, 0);
                if (useGps) {
                    if (haGps.read_gps(gps_data)) {
                        if (haGps.parse_gps(gps_data, gps_db_data)) {
                            spd::get("console")->info("live: ({},{},{}) at {}{}", gps_db_data.latitude(), gps_db_data.longitude(), gps_db_data.angle(), gps_db_data.date(), gps_db_data.time());
                            unsigned long id_gps = haDatabase.insertDbGps(gps_db_data);
                            // unsigned long id_image = haDatabase.insertDbImage();
                        }
                    }
                }
            }
        }
        replay_index++;
        if (wait <= 0) {
            waitKey(0);
        } else {
            char c = waitKey(wait);
            if (c == 27) {
                break;
            } else if (c == 32) {
                waitKey(0);
            } else if (c == '0') {
                haProcessor.toggleFinalImageTypes();
            } else if (c == '1') {
                haProcessor.toggleLines();
            } else if (c == '2') {
                haProcessor.toggleCircles();
            } else if (c == '3') {
                haProcessor.toggleColors();
            } else if (c == '4') {
                haProcessor.toggleSigns();
            } else if (c == '5') {
                haProcessor.togglePatterns();
            } else if (c == 'v') {
                haProcessor.setLineTypes(HaLineTypes::VERTICAL);
            } else if (c == 'h') {
                haProcessor.setLineTypes(HaLineTypes::HORIZONTAL);
            } else if (c == 'l') {
                haProcessor.setLineTypes(HaLineTypes::LANES);
            } else if (c == 'a') {
                haProcessor.setLineTypes(HaLineTypes::ALL);
            } else if (c == 'g') {
                haProcessor.setEdgeTypes(HaEdgeTypes::L_O_G);
            } else if (c == 'c') {
                haProcessor.setEdgeTypes(HaEdgeTypes::CANNY);
            } else if (c == '(') {
                haProcessor.setPatternTypes(HaPatternTypes::CHESSBOARD);
            } else if (c == ')') {
                haProcessor.setPatternTypes(HaPatternTypes::CIRCLESGRID);
            } else if (c == 'w') {
                printf("not supported yet!\n");
            } else if (c == 's') {
                printf("not supported yet!\n");
            }
        }
    }
    // the camera will be deinitialized automatically in VideoCapture destructor

    return 0;
}
