#include "test_utils.hpp"
#include "test_fixtures.hpp"

TEST_P(FrontItemNull, FrontItemTest) {
    auto lst = GetParam();
    EXPECT_EQ(slist_front_item(lst), nullptr);
    tuti::tearDown(lst);
}

INSTANTIATE_TEST_SUITE_P(FrontItemNullSuite, FrontItemNull, ::testing::Values (
    static_cast<slist_t*>(nullptr), slist_create(sizeof(int))
));

TEST_P(FrontItemFull, FrontItemTest) {
    auto [v, val] = GetParam();
    slist_t* lst = tuti::toSlist(v);
    EXPECT_EQ(*(int*)slist_front_item(lst), val);
    tuti::compareWith(lst, v);
    tuti::tearDown(lst);
}

INSTANTIATE_TEST_SUITE_P(FrontItemFullSuite, FrontItemFull, ::testing::Values (
    std::make_tuple((std::vector<int>{1, 2, 3, 4, 5}), 1),
    std::make_tuple((std::vector<int>{2, 1, 3, 4, 5}), 2),
    std::make_tuple((std::vector<int>{3, 2, 1, 4, 5}), 3),
    std::make_tuple((std::vector<int>{4, 2, 3, 1, 5}), 4),
    std::make_tuple((std::vector<int>{5, 2, 3, 4, 1}), 5)
));