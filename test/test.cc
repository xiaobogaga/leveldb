#include <stdio.h>
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"
#include <stdlib.h>
#include <string>
#include <iostream>
#include "leveldb/write_batch.h"

using namespace std;

// Writing some data to leveldb.

int main() {
    // Open a level db on a specific directory and create it if it doesn't exists.
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    char name[20] = "/tmp/testleveldb";
    leveldb::Status status = leveldb::DB::Open(options, name, &db);
    assert(status.ok());

    // Try to put some values.
    // First using put to write <-1, -1>
    leveldb::Slice key1 = "-1";
    db->Put(leveldb::WriteOptions(), key1, key1);

    // Then Write keys from 1 --> 1000
    int startKey = 0;
    int endKey = 1000;
    int i = startKey;
    leveldb::WriteBatch batch;
    for (; i <= endKey; i++) {
        string str = std::to_string(i);
        batch.Put(str, str);
    }
    db->Write(leveldb::WriteOptions(), &batch);
    string value;
    db->Get(leveldb::ReadOptions(), "-1", &value);
    cout<< "-1 : " << value << std::endl;
    // Closing
    delete db;
}