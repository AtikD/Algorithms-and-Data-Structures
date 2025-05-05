// Copyright 2025 atikdd.t.me
#include <gtest/gtest.h>
#include <dsu.h>

TEST(DSUTest, Constructor) {
    ASSERT_NO_THROW(DSU dsu);

    ASSERT_NO_THROW(DSU dsu(5));

    ASSERT_THROW(DSU dsu(-1), std::invalid_argument);
}

TEST(DSUTest, MakeSet) {
    DSU dsu;

    ASSERT_NO_THROW(dsu.make_set(1));

    ASSERT_NO_THROW(dsu.make_set(2));
    ASSERT_NO_THROW(dsu.make_set(3));

    ASSERT_THROW(dsu.make_set(3), std::invalid_argument);

    ASSERT_THROW(dsu.make_set(0), std::invalid_argument);
    ASSERT_THROW(dsu.make_set(-1), std::invalid_argument);
}

TEST(DSUTest, Find) {
    DSU dsu(5);

    ASSERT_EQ(dsu.find(1), 1);
    ASSERT_EQ(dsu.find(2), 2);
    ASSERT_EQ(dsu.find(3), 3);
    ASSERT_EQ(dsu.find(4), 4);
    ASSERT_EQ(dsu.find(5), 5);

    ASSERT_THROW(dsu.find(0), std::logic_error);
    ASSERT_THROW(dsu.find(-1), std::logic_error);
    ASSERT_THROW(dsu.find(6), std::logic_error);
}

TEST(DSUTest, UnionTrivial) {
    DSU dsu(5);

    // Объединение двух множеств
    dsu.union_trivial(1, 2);
    ASSERT_EQ(dsu.find(1), dsu.find(2));

    // Объединение еще двух множеств
    dsu.union_trivial(3, 4);
    ASSERT_EQ(dsu.find(3), dsu.find(4));

    // Проверка, что элементы из разных множеств не связаны
    ASSERT_NE(dsu.find(1), dsu.find(3));

    // Объединение уже объединенных множеств
    dsu.union_trivial(2, 1);
    ASSERT_EQ(dsu.find(1), dsu.find(2));

    // Объединение множеств из разных компонент
    dsu.union_trivial(2, 3);
    ASSERT_EQ(dsu.find(1), dsu.find(3));
    ASSERT_EQ(dsu.find(1), dsu.find(4));
}

TEST(DSUTest, UnionByRank) {
    DSU dsu(7);

    // Создаем дерево с корнем 1 и высотой 1
    dsu.union_by_rank(1, 2);
    dsu.union_by_rank(1, 3);

    // Создаем дерево с корнем 4 и высотой 2
    dsu.union_by_rank(4, 5);
    dsu.union_by_rank(4, 6);
    dsu.union_by_rank(6, 7);

    // После объединения дерево с корнем 1 должно стать подмножеством
    // дерева с корнем 4
    dsu.union_by_rank(1, 4);

    // Проверяем, что все элементы находятся в одном множестве
    ASSERT_EQ(dsu.find(1), dsu.find(4));
    ASSERT_EQ(dsu.find(2), dsu.find(4));
    ASSERT_EQ(dsu.find(3), dsu.find(4));
    ASSERT_EQ(dsu.find(5), dsu.find(4));
    ASSERT_EQ(dsu.find(6), dsu.find(4));
    ASSERT_EQ(dsu.find(7), dsu.find(4));
}


TEST(DSUTest, Clear) {
    DSU dsu(5);

    dsu.union_trivial(1, 2);
    dsu.union_trivial(3, 4);

    dsu.clear();

    // После очистки размер должен быть 0
    // и добавление нового элемента должно работать
    ASSERT_NO_THROW(dsu.make_set(1));
    ASSERT_EQ(dsu.find(1), 1);
}
