#include <gtest/gtest.h>
#include "matrix.hpp"
#include <sstream>

TEST(istream_test, 1) {
  Matrix<double> matrix(2, 3);

  std::istringstream s("[[1 2 3]\n[4 5 6]]");
  s >> matrix;

  EXPECT_EQ( matrix(0, 0) ,  1 );
  EXPECT_EQ( matrix(0, 1) ,  2 );
  EXPECT_EQ( matrix(0, 2) ,  3 );
  EXPECT_EQ( matrix(1, 0) ,  4 );
  EXPECT_EQ( matrix(1, 1) ,  5 );
  EXPECT_EQ( matrix(1, 2) ,  6 );

  EXPECT_EQ( matrix.rows() ,  2 );
  EXPECT_EQ( matrix.columns() ,  3 );
}

TEST(constructors, 1) {
  /* Default constructor */
  Matrix<double> empty;

  EXPECT_EQ( empty.rows() ,  0 );
  EXPECT_EQ( empty.columns() ,  0 );
  EXPECT_THROW( empty(0,0), std::out_of_range );

  std::ostringstream out;
  out << empty;
  EXPECT_EQ( out.str() ,  "[]" );


  /* default constructor */
  Matrix<double> sing_constr(2);
	 
  EXPECT_EQ(sing_constr.rows() , 2 );
  EXPECT_EQ(sing_constr.columns() , 2 );
  EXPECT_EQ(sing_constr(0, 0) , 0 );
  EXPECT_EQ(sing_constr(0, 1) , 0 );
  EXPECT_EQ(sing_constr(1, 0) , 0 );
  EXPECT_EQ(sing_constr(1, 1) , 0 );
  EXPECT_THROW(sing_constr(2, 0), std::out_of_range );
  EXPECT_THROW(sing_constr(0, 2), std::out_of_range );

  /* Explicit constructor */
  Matrix<double> expl(2, 3);
  EXPECT_EQ( expl.rows() ,  2 );
  EXPECT_EQ( expl.columns() ,  3 );
  EXPECT_EQ( expl(0,0) ,  0 );
  EXPECT_EQ( expl(0,1) ,  0 );
  EXPECT_EQ( expl(0,2) ,  0 );
  EXPECT_EQ( expl(1,0) ,  0 );
  EXPECT_EQ( expl(1,1) ,  0 );
  EXPECT_EQ( expl(1,2) ,  0 );
  EXPECT_THROW( expl(2, 2), std::out_of_range );
  EXPECT_THROW( expl(1, 3), std::out_of_range );

  /* Initializer list */
  Matrix<int> initialiser = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  EXPECT_EQ( initialiser.rows() ,  3 );
  EXPECT_EQ( initialiser.columns() ,  3 );
  EXPECT_EQ( initialiser(0, 0) ,  1 );
  EXPECT_EQ( initialiser(0, 1) ,  2 );
  EXPECT_EQ( initialiser(0, 2) ,  3 );
  EXPECT_EQ( initialiser(1, 0) ,  4 );
  EXPECT_EQ( initialiser(1, 1) ,  5 );
  EXPECT_EQ( initialiser(1, 2) ,  6 );
  EXPECT_EQ( initialiser(2, 0) ,  7 );
  EXPECT_EQ( initialiser(2, 1) ,  8 );
  EXPECT_EQ( initialiser(2, 2) ,  9 );

}

TEST(addition, 1) {
  Matrix<double> one(2, 3);
  Matrix<double> two(2, 3);
  Matrix<double> three(2, 2);

  std::istringstream first("[[1 2 3]\n[4 5 6]]");
  std::istringstream second("[[7 5 4]\n[8 5 3]]");
  first >> one;
  second >> two;

  Matrix<double> sum = one + two;

  Matrix<double> res(2, 3);
  std::istringstream res_num("[[8 7 7]\n[12 10 9]]");
  res_num >> res;

  EXPECT_EQ( sum ,  res );

  one += two;
  EXPECT_EQ( one ,  res );

  EXPECT_THROW( one + three, std::out_of_range );
  EXPECT_THROW( one += three, std::out_of_range );
}

TEST(scalar_addition, 1) {
  Matrix<double> one(2, 3);

  std::istringstream first("[[1 2 3]\n[4 5 6]]");
  first >> one;

  Matrix<double> rsum = one + 3;
  Matrix<double> lsum = 7 + one;

  Matrix<double> rres(2, 3);
  Matrix<double> lres(2, 3);
  std::istringstream rres_num("[[4 5 6][7 8 9]]");
  std::istringstream lres_num("[[8 9 10][11 12 13]]");
  rres_num >> rres;
  lres_num >> lres;

  EXPECT_EQ( rsum ,  rres );
  EXPECT_EQ( lsum ,  lres );
}

TEST(subtraction, 1) {
  Matrix<double> one(2, 3);
  Matrix<double> two(2, 3);

  std::istringstream first("[[1 2 3]\n[4 5 6]]");
  std::istringstream second("[[7 5 4]\n[8 5 3]]");
  first >> one;
  second >> two;

  Matrix<double> diff = one - two;

  Matrix<double> res(2, 3);
  std::istringstream res_num("[[-6 -3 -1]\n[-4 0 3]]");
  res_num >> res;

  EXPECT_EQ( diff ,  res );

  one -= two;
  EXPECT_EQ( one ,  res );
}

TEST(Scalar_subtraction, 1) {
  Matrix<double> one(2, 3);

  std::istringstream first("[[1 2 3]\n[4 5 6]]");
  first >> one;

  Matrix<double> rdiff = one - 3;
  Matrix<double> ldiff = 7 - one;

  Matrix<double> rres(2, 3);
  Matrix<double> lres(2, 3);
  std::istringstream rres_num("[[-2 -1 0][1 2 3]]");
  std::istringstream lres_num("[[6 5 4][3 2 1]]");
  rres_num >> rres;
  lres_num >> lres;

  EXPECT_EQ( rdiff ,  rres );
  EXPECT_EQ( ldiff ,  lres );
}

TEST(Multiplication, 1) {
  Matrix<double> one(2, 3);
  Matrix<double> two(3, 2);
  Matrix<double> three(2, 2);

  std::istringstream first("[[1 2 3]\n[4 5 6]]");
  std::istringstream second("[[7 5]\n[4 8]\n[5 3]]");
  first >> one;
  second >> two;

  Matrix<double> prod = one * two;

  Matrix<double> res(2, 2);
  std::istringstream res_num("[[30 30]\n[78 78]]");
  res_num >> res;

  EXPECT_EQ( prod ,  res );

  Matrix<double> one_orig = one;
  one *= two;
  EXPECT_EQ( one ,  res );

  EXPECT_THROW( one_orig * three, std::out_of_range );
  EXPECT_THROW( one_orig *= three, std::out_of_range );
}

TEST(scalar_multiplication, 1) {
  Matrix<double> one(2, 3);

  std::istringstream first("[[1 2 3]\n[4 5 6]]");
  first >> one;

  Matrix<double> rprod = one * 3;
  Matrix<double> lprod = 7 * one;

  Matrix<double> rres(2, 3);
  Matrix<double> lres(2, 3);
  std::istringstream rres_num("[[3 6 9][12 15 18]]");
  std::istringstream lres_num("[[7 14 21][28 35 42]]");
  rres_num >> rres;
  lres_num >> lres;

  EXPECT_EQ( rprod ,  rres );
  EXPECT_EQ( lprod ,  lres );
}

TEST(pointwise_multiplication, 1) {
  Matrix<double> one(2, 3);
  Matrix<double> two(2, 3);

  std::istringstream first("[[1 2 3]\n[4 5 6]]");
  first >> one;

  std::istringstream second("[[1 8 5]\n[4 3 17]]");
  second >> two;

  Matrix<double> prod = one.pointwiseMult(two);

  Matrix<double> res(2, 3);
  std::istringstream res_num("[[1 16 15][16 15 102]]");
  res_num >> res;

  EXPECT_EQ( prod ,  res );
}

TEST(stdout, 1) {
  Matrix<int> mtx = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  std::cout << mtx << std::endl;
}

TEST(access_operator, 1) {
  Matrix<int> mtx = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  mtx(1, 2) = 10;

  EXPECT_EQ( mtx(1, 2) ,  10 );
}

TEST(reset_operation, 1) {
  Matrix<int> mtx = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  mtx.reset();

  EXPECT_EQ( mtx ,  Matrix<int>(3, 3) );
}
  
TEST(copy_operator, 1) {
  Matrix<int> mtx = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  Matrix<int> copy = mtx;

  EXPECT_EQ( copy ,  mtx );

  /* Make modifications in the copy */
  copy(1, 1) = 99;
  EXPECT_NE( copy, mtx );
}

TEST(move_operator, 1) {
  Matrix<int> mtx = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  Matrix<int> move = std::move(mtx);

  EXPECT_THROW( move == mtx, std::out_of_range );
}

TEST(insert_row, 1) {
  Matrix<double> test(2, 3);
  Matrix<double> res(3, 3);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1 2 3][0 0 0][4 5 6]]");
  end >> res;

  test.insert_row(1);

  EXPECT_EQ( test ,  res );
}

TEST(insert_row, 2) {
  Matrix<double> test(2, 3);
  Matrix<double> res(3, 3);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[0 0 0][1 2 3][4 5 6]]");
  end >> res;

  test.insert_row(0);

  EXPECT_EQ( test ,  res );
}

TEST(append_row, 1) {
  Matrix<double> test(2, 3);
  Matrix<double> res(3, 3);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1 2 3][0 0 0][4 5 6]]");
  end >> res;

  test.append_row(0);

  EXPECT_EQ( test ,  res );
}

TEST(append_row, 2) {
  Matrix<double> test(2, 3);
  Matrix<double> res(3, 3);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1 2 3][4 5 6][0 0 0]]");
  end >> res;

  test.append_row(1);

  EXPECT_EQ( test ,  res );
}

TEST(remove_row, 1) {
  Matrix<double> test(2, 3);
  Matrix<double> res(1, 3);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1 2 3]]");
  end >> res;

  test.remove_row(1);

  EXPECT_EQ( test ,  res );
}

TEST(remove_row, 2) {
  Matrix<double> test(2, 3);
  Matrix<double> res(1, 3);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[4 5 6]]");
  end >> res;

  test.remove_row(0);

  EXPECT_EQ( test ,  res );
}

TEST(insert_column, 1) {
  Matrix<double> test(2, 3);
  Matrix<double> res(2, 4);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1 2 0 3][4 5 0 6]]");
  end >> res;

  test.insert_column(2);

  EXPECT_EQ( test ,  res );
}

TEST(insert_column, 2) {
  Matrix<double> test(2, 3);
  Matrix<double> res(2, 4);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[0 1 2 3][0 4 5 6]]");
  end >> res;

  test.insert_column(0);

  EXPECT_EQ( test ,  res );
}

TEST(append_column, 1) {
  Matrix<double> test(2, 3);
  Matrix<double> res(2, 4);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1 0 2 3][4 0 5 6]]");
  end >> res;

  test.append_column(0);

  EXPECT_EQ( test ,  res );
}

TEST(append_column, 2) {
  Matrix<double> test(2, 3);
  Matrix<double> res(2, 4);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1 2 3 0][4 5 6 0]]");
  end >> res;

  test.append_column(2);

  EXPECT_EQ( test ,  res );
}

TEST(remove_column, 1) {
  Matrix<double> test(2, 3);
  Matrix<double> res(2, 2);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[2 3][5 6]]");
  end >> res;

  test.remove_column(0);

  EXPECT_EQ( test ,  res );
}

TEST(remove_column, 2) {
  Matrix<double> test(2, 3);
  Matrix<double> res(2, 2);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1 2][4 5]]");
  end >> res;

  test.remove_column(2);

  EXPECT_EQ( test ,  res );
}

TEST(get_column, 1) {
  Matrix<double> test(2, 3);
  Matrix<double> res(2, 1);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1][4]]");
  end >> res;

  Matrix<double> column = test.getColumn(0);

  EXPECT_EQ( column ,  res );
}

TEST(get_row, 1) {
  Matrix<double> test(2, 3);
  Matrix<double> res(1, 3);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1 2 3]]");
  end >> res;

  Matrix<double> row = test.getRow(0);

  EXPECT_EQ( row ,  res );
}

TEST(identity_matrix, 1) {
  Matrix<double> eye = Matrix<double>::eye(3);

  Matrix<double> reference = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  EXPECT_EQ( eye ,  reference );
}

TEST(transpose, 1) {
  Matrix<double> normal(2, 3);
  Matrix<double> transposed(3, 2);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> normal;

  std::istringstream end("[[1 4][2 5][3 6]]");
  end >> transposed;

  EXPECT_EQ( normal.transpose() ,  transposed );
  EXPECT_EQ( normal.rows() ,  3 );
  EXPECT_EQ( normal.columns() ,  2 );
}

TEST(transpose_square, 1) {
  Matrix<double> normal(3, 3);
  Matrix<double> transposed(3, 3);

  std::istringstream begin("[[1 2 3][4 5 6][7 8 9]]");
  begin >> normal;

  std::istringstream end("[[1 4 7][2 5 8][3 6 9]]");
  end >> transposed;

  EXPECT_EQ( normal.transpose() ,  transposed );
  EXPECT_EQ( normal.rows() ,  3 );
  EXPECT_EQ( normal.columns() ,  3 );
}

TEST(iterators, 1) {
  Matrix<double> normal(2, 3);

  std::istringstream s("[[1 2 3][4 5 6]]");
  s >> normal;

  double i = 0;
  for (auto k = normal.begin(); k != normal.end(); k++)
    EXPECT_EQ( *k ,  ++i );

  EXPECT_EQ( i ,  6.0 );
}

int main(int argc, char ** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
