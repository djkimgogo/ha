/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
 #pragma once
 #ifndef _HA_SQLITE_ORM_H_
 #define _HA_SQLITE_ORM_H_

#include <odb/database.hxx>
#include <odb/transaction.hxx>

#include "ha_config.h"
#include "ha_common.h"
#include "ha_db_database.h" // create_database

#include "ha_db_gps.hxx"
#include "ha_db_gps-odb.hxx"
#include "ha_db_image.hxx"
#include "ha_db_image-odb.hxx"

using namespace std;
using namespace odb::core;

namespace ha {
    class HaDatabase {
    private:
        std::string m_db_filename;
    public:
        HaDatabase(const std::string& db_filename);
        bool initDb();
        unsigned long insertDbGps(HaDbGps& gps_data);
        bool updateDbGps(const unsigned long id, HaDbGps& gps_data);
        bool deleteDpGps(const unsigned long id);
        void queryDbGps(vector<HaDbGps>& gps_data_vector);
    };
}

#endif // _HA_SQLITE_ORM_H_
