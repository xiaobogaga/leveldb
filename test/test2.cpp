//
// Created by tomzhu on 19-5-26.
//

#include <stdio.h>
#include "leveldb/db.h"
#include <string>
#include <iostream>

using namespace std;

// Using for testing reading leveldb.

int main() {
    string dbPath = "/tmp/testleveldb";
    leveldb::DB *db;
    leveldb::Options options;
    options.error_if_exists = false;
    leveldb::Status status = leveldb::DB::Open(options, dbPath, &db);
    assert(status.ok());
    // first Iterator all keys.
    leveldb::Iterator* ite = db->NewIterator(leveldb::ReadOptions());
    for (ite->SeekToFirst(); ite->Valid(); ite->Next()) {
        string key = ite->key().ToString();
        cout<< "" << key << ",";
    }
    delete ite;
    // getting a snapshot
    leveldb::ReadOptions readOptions;
    readOptions.snapshot = db->GetSnapshot();
    // then we change some values.
    db->Put(leveldb::WriteOptions(), "-1", "-2");
    string value;
    db->Get(readOptions, "-1", &value);
    assert(value == "-1");
    string value2;
    db->Get(leveldb::ReadOptions(), "-1", &value2);
    assert(value2 == "-2");
    delete db;
}