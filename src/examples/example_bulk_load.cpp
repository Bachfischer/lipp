#include <lipp.h>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int main()
{
    LIPP<uint64_t, uint64_t> lipp;

    // prepare data
    vector<pair<uint64_t, uint64_t>> data;
    for (int i = 0; i < 100000000; i ++) {
        data.push_back({i, i % 127});
    }
    cout << "Keys loaded succesfully" << endl;


    // bulk load
    lipp.bulk_load(data.data(), data.size());
    cout << "Finished bulk load" << endl;

    // normal insert
    lipp.insert(-100, 5);
    lipp.insert(187688, 4);

    // verify LIPP data structure
    lipp.verify();

    // test correctness
    assert(lipp.at(-100) == 5);
    assert(lipp.at(187688) == 4);
    for (int i = 0; i < 100000; i ++) {
        assert(lipp.exists(i));
        assert(lipp.at(i) == (i % 127));
    }

    cout << "bolk load success" << endl;

    return 0;
}
