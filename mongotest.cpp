//============================================================================
// Name        : mongotest.cpp
// Author      : Yin Li
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <boost/smart_ptr.hpp>
#include "mongo/client/dbclient.h"
#include "mongo/client/connpool.h"
#include "mongo/bson/bsonobjbuilder.h"
#include "mongo/bson/bson.h"
#include "mongo/bson/bson_db.h"
using namespace std;
using namespace boost;

void printIfAge(mongo::DBClientConnection& c, int age) {
  auto_ptr<mongo::DBClientCursor> cursor =
    c.query("tutorial.persons", QUERY("age" << age).sort("name"));
  while (cursor->more()) {
    mongo::BSONObj p = cursor->next();
    cout << p.getStringField("name") << endl;   // p["name"]
  }
}

void run() {
  mongo::DBClientConnection c;
  c.connect("localhost");

  // BSONObj p = BSON(GENOID << "name" << "Joe" << "age" << 33);
  mongo::BSONObjBuilder b;
  b.append("name", "Joe");
  b.append("age", 33);
  mongo::BSONObj p = b.obj();

  c.insert("tutorial.persons", p);
  cout << "count:" << c.count("tutorial.persons") << endl;

  auto_ptr<mongo::DBClientCursor> cursor =
    c.query("tutorial.persons", mongo::BSONObj());
  while (cursor->more())
      cout << cursor->next().toString() << endl;

  c.ensureIndex("tutorial.persons", mongo::fromjson("{age:1}"));
//  c.ensureIndex("tutorial.persons", BSON( "age" << 1 ));

  c.update("tutorial.persons",
             BSON("name" << "Joe" << "age" << 33),
             BSON("$inc" << BSON( "visits" << 1)));
}

int main() {
  try {
    run();
    std::cout << "connected ok" << std::endl;
  } catch( const mongo::DBException &e ) {
    std::cout << "caught " << e.what() << std::endl;
  }
  return EXIT_SUCCESS;
}
