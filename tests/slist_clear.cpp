#include "test_utils.hpp"
#include "test_fixtures.hpp"

TEST_P(ClearFull, ClearTest) {
    slist_t *lst = GetParam();
    slist_clear(lst);
    tuti::testEmpty(lst);
    tuti::tearDown(lst);
}

INSTANTIATE_TEST_SUITE_P(ClearSuite, ClearFull, ::testing::Values(
    tuti::toSlist(std::vector<int>{1, 2 ,3, 4, 5}),
    tuti::toSlist(std::vector<int>{1, 4, 5}),
    tuti::toSlist(std::vector<int>{}),
    tuti::toSlist(std::vector<int>{1})
));