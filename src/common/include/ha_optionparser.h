/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
 #pragma once
#ifndef _HA_OPTION_PARSER_H_
#define  _HA_OPTION_PARSER_H_

#include <assert.h>
#include <stdio.h>
// #include "optionparser/optionparser.h"

const String keys =
    "{help h usage ?  |       | print this message   }"
    "{mode            |<none>       | mode of operations [capture,replay] }"
    "{path            |.      | path to file}"
    "{calib            |<none>       | calibrate camera(s) [chessboard,lines] }"
    "{process            |<none>       | process frame(s) [lines,circles] }"
    "{preview            |       | preview frame(s) }"
    "{sscale            |1       | scale factor for display }"
    "{pscale            |1       | scale factor for process }"
    "{timer             |       | timer for calibration process}"
    "{wait           |0       | wait for xx msec (0 = forever)}"
    "{gps            |        | gps tagging enabled}"
    "{rectify        |        | rectify images if calibrated (found *.yml)}"
    ;

// using option::Option;
// using option::Descriptor;
// using option::Parser;
// using option::Stats;
// using option::ArgStatus;
//
// struct Arg: public option::Arg {
//    static ArgStatus Required(const Option& option, bool) {
//      return option.arg == 0 ? option::ARG_ILLEGAL : option::ARG_OK;
//    }
//   static ArgStatus Empty(const Option& option, bool) {
//      return (option.arg == 0 || option.arg[0] == 0) ? option::ARG_OK : option::ARG_IGNORE;
//    }
//  };
//
// enum  optionIndex { MODE, CALIBRATION, PROCESS, PREVIEW, SCALE };
// const option::Descriptor usage[] =
// {
//   {MODE, 0, "" , "mode"    , Arg::Required, "  --mode \tCapture Frame(s) Mode" },
//   {CALIBRATION,    0, "", "calib", Arg::Required, "  --calib  \tCalibrate Camera(s)" },
//   {PROCESS, 0, "" ,  "process"   ,  Arg::Required, "  --process \tProcess Frame(s) with given command" },
//   {PREVIEW, 0, "" ,  "preview"   , option::Arg::None, "  --preview \tPreview Frame(s)" },
//   {SCALE, 0, "" ,  "scale"   , Arg::Required, "  --scale \tScale factor for everything" } //,
//   // {CIRCLES, 0, "" ,  "circles"   , option::Arg::None, "  --circles \tDetect & Show Circles" }
// };

#endif
