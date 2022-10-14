#include "tmatrix.h"

#include "gtest/gtest.h"

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m(5);
    auto copy = TDynamicMatrix<int>(m);
    ASSERT_EQ(m,copy);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m(5);
    auto copy = TDynamicMatrix<int>(m);
    m[0][1] = 2;
    ASSERT_NE(m[0][1],copy[0][1]);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(10);
    ASSERT_NO_THROW(m[0].size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(10);
    m[0][2] = -3;
    ASSERT_EQ(m[0][2],-3);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(10);
    ASSERT_ANY_THROW(m[-5][0]=3);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(10);
    ASSERT_ANY_THROW(m[6][MAX_MATRIX_SIZE+10]=3);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(10);
    m[0][1] = 2;
    ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m1(10);
    m1[1][3] = -1;
    TDynamicMatrix<int> m2(10);
    m2[9][3] = 31;
    ASSERT_NO_THROW(m2 = m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m1(10);
    m1[1][3] = -1;
    TDynamicMatrix<int> m2(20);
    m2[9][3] = 31;
    m1 = m2;
    ASSERT_EQ(m1[0].size(),20);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m1(10);
    m1[1][3] = -1;
    TDynamicMatrix<int> m2(20);
    m2[9][3] = 31; m2[0][1] = 5;
    ASSERT_NO_THROW(m2 = m1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m1(10);
    m1[1][3] = -1;
    TDynamicMatrix<int> m2(10);
    m2[9][3] = 31;
    m2 = m1;
    ASSERT_EQ(m1,m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m1(10);
    m1[5][3] = 71; m1[6][8] = -19;
    ASSERT_EQ(m1,m1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m1(10);
    m1[5][3] = 71; m1[6][8] = -19;
    TDynamicMatrix<int> m2(20);
    m2[5][3] = 71; m2[6][8] = -19;
    ASSERT_NE(m1,m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(10);
    m1[5][3] = 71; m1[6][8] = -19;
    TDynamicMatrix<int> m2(10);
    m2[5][3] = -61; m2[5][8] = 29;
    ASSERT_NO_THROW(m1+m2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(10);
    m1[5][3] = 71; m1[6][8] = -19;
    TDynamicMatrix<int> m2(13);
    m2[5][3] = -61; m2[5][8] = 29;
    ASSERT_ANY_THROW(m1+m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(10);
    m1[5][2] = 31; m1[6][8] = -19;
    TDynamicMatrix<int> m2(10);
    m2[5][3] = -91; m2[4][9] = 29;
    ASSERT_NO_THROW(m1-m2);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m1(10);
    m1[5][2] = 31; m1[6][8] = -19;
    TDynamicMatrix<int> m2(16);
    m2[5][3] = -91; m2[4][9] = 29;
    ASSERT_ANY_THROW(m1-m2);
}

