/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
 #include "ha_sqlite_orm.h"

ha::HaDatabase::HaDatabase(const std::string& db_filename)
: m_db_filename(db_filename)
{

}

bool ha::HaDatabase::initDb() {
  bool success(false);
  try {
    create_database (this->m_db_filename);
    success = true;
  } catch (const odb::exception& e) {
    spd::get("console")->error(e.what ());
  }
  return success;
}

unsigned long ha::HaDatabase::insertDbGps(HaDbGps& gps_data) {
  unsigned long id(-1);
  try {
    unique_ptr<database> db (open_database (this->m_db_filename));
    transaction t (db->begin ());
    id = db->persist (gps_data);
    t.commit ();

  } catch (const odb::exception& e) {
    spd::get("console")->error(e.what ());
  }
  return id;
}

bool ha::HaDatabase::updateDbGps(const unsigned long id, HaDbGps& gps_data) {
  bool success(false);
  try {
    unique_ptr<database> db (open_database (this->m_db_filename));
    transaction t (db->begin ());
    unique_ptr<HaDbGps> gps_old (db->load<HaDbGps> (id));
    gps_old->latitude (gps_data.latitude ());
    gps_old->longitude (gps_data.longitude ());
    gps_old->date (gps_data.date ());
    gps_old->time (gps_data.time ());
    gps_old->speed (gps_data.speed ());
    gps_old->angle (gps_data.angle ());
    db->update (*gps_old);
    t.commit ();
    success = true;
  } catch (const odb::exception& e) {
    spd::get("console")->error(e.what ());
  }
  return success;
}

bool ha::HaDatabase::deleteDpGps(const unsigned long id) {
  bool success(false);
  try {
    unique_ptr<database> db (open_database (this->m_db_filename));
    transaction t (db->begin ());
    db->erase<HaDbGps>(id);
    t.commit();
    success = true;
  } catch (const odb::exception& e) {
    spd::get("console")->error(e.what ());
  }
  return success;
}

void ha::HaDatabase::queryDbGps(vector<HaDbGps>& gps_data_vector) {
  try {
    typedef odb::query<HaDbGps> query;
    typedef odb::result<HaDbGps> result;
    unique_ptr<database> db (open_database (this->m_db_filename));
    transaction t (db->begin ());
    result r (db->query<HaDbGps> ());
    for (result::iterator i (r.begin ()); i != r.end (); ++i)
    {
      // spd::get("console")->info("({},{},{}) at {}{}", i->latitude (), i->longitude (), i->angle(), i->date(), i->time());
      HaDbGps gps_data(i->latitude (), i->longitude (), i->date(), i->time(), i->speed(), i->angle());
      gps_data_vector.push_back(gps_data);
    }
    t.commit();
  } catch (const odb::exception& e) {
    spd::get("console")->error(e.what ());
  }
}

//  void ha::HaDatabase::test(std::string db_filename) {
//     try
//     {
//       unique_ptr<database> db (create_database (db_filename));

//       unsigned long john_id, joe_id;

//       // Create a few persistent person objects.
//       //
//       {
//         HaDbGps john (1,1,"1","a",1,1);
//         HaDbGps jane (2,2,"2","b",2,2);
//         HaDbGps joe (3,3,"3","c",3,3);

//         transaction t (db->begin ());

//         // Make objects persistent and save their ids for later use.
//         //
//         john_id = db->persist (john);
//         db->persist (jane);
//         joe_id = db->persist (joe);

//         t.commit ();
//       }

//       typedef odb::query<HaDbGps> query;
//       typedef odb::result<HaDbGps> result;

//       // Say hello to those over 30.
//       //
//       {
//         transaction t (db->begin ());

//         result r (db->query<HaDbGps> (query::latitude > 2));

//         for (result::iterator i (r.begin ()); i != r.end (); ++i)
//         {
//           cout << "Hello, " << i->latitude () << " " << i->longitude () << "!" << endl;
//         }

//         t.commit ();
//       }

//       // Joe Dirt just had a birthday, so update his age.
//       //
//       {
//         transaction t (db->begin ());

//         unique_ptr<HaDbGps> joe (db->load<HaDbGps> (joe_id));
//         joe->latitude (joe->latitude () + 1);
//         db->update (*joe);

//         t.commit ();
//       }

//       // Alternative implementation without using the id.
//       //
//       /*
//       {
//         transaction t (db->begin ());

//         // Here we know that there can be only one Joe Dirt in our
//         // database so we use the query_one() shortcut instead of
//         // manually iterating over the result returned by query().
//         //
//         unique_ptr<person> joe (
//           db->query_one<person> (query::first == "Joe" &&
//                                  query::last == "Dirt"));

//         if (joe.get () != 0)
//         {
//           joe->age (joe->age () + 1);
//           db->update (*joe);
//         }

//         t.commit ();
//       }
//       */

//       // Print some statistics about all the people in our database.
//       //
//       {
//         transaction t (db->begin ());

//         // The result of this (aggregate) query always has exactly one element
//         // so use the query_value() shortcut.
//         //
//         // person_stat ps (db->query_value<person_stat> ());

//         // cout << endl
//         //      << "count  : " << ps.count << endl
//         //      << "min age: " << ps.min_age << endl
//         //      << "max age: " << ps.max_age << endl;

//         // t.commit ();
//       }

//       // John Doe is no longer in our database.
//       //
//       {
//         transaction t (db->begin ());
//         db->erase<HaDbGps> (john_id);
//         t.commit ();
//       }
//     }
//     catch (const odb::exception& e)
//     {
//       cerr << e.what () << endl;
//       return;
//     }
//  }

//  void ha::HaDatabase::init() {
//     this->m_storage = make_storage(this->m_db_filename,
//         make_table("gps",
//             make_column("id",
//                 &HaDbGps::id,
//                 primary_key()),
//             make_column("angle",
//                 &HaDbGps::angle),
//             make_column("date",
//                 &HaDbGps::date),
//             make_column("time",
//                 &HaDbGps::time),
//             make_column("latitude",
//                 &HaDbGps::latitude),
//             make_column("longitude",
//                 &HaDbGps::longitude),
//             make_column("speed",
//                 &HaDbGps::speed)
//             ),
//         make_table("image",
//             make_column("id",
//                 &HaDbImage::id,
//                 primary_key()),
//             make_column("frame",
//                 &HaDbImage::frame),
//             make_column("imageGps",
//                 &HaDbImage::imageGps)
//             )
//         );
//  }

//  void ha::HaDatabase::save() {

//  }

//  void ha::HaDatabase::load() {

//  }
