#include <catch2/catch.hpp>
#include "matrix.hpp"
#include <sstream>

TEST_CASE("istream test") {
  Matrix<double> matrix(2, 3);

  std::istringstream s("[[1 2 3]\n[4 5 6]]");
  s >> matrix;

  CHECK( matrix(0, 0) == 1 );
  CHECK( matrix(0, 1) == 2 );
  CHECK( matrix(0, 2) == 3 );
  CHECK( matrix(1, 0) == 4 );
  CHECK( matrix(1, 1) == 5 );
  CHECK( matrix(1, 2) == 6 );

  CHECK( matrix.rows() == 2 );
  CHECK( matrix.columns() == 3 );
}

TEST_CASE("Constructors") {
  /* Default constructor */
  Matrix<double> empty;

  CHECK( empty.rows() == 0 );
  CHECK( empty.columns() == 0 );
  CHECK_THROWS_AS( empty(0,0), std::out_of_range );

  std::ostringstream out;
  out << empty;
  CHECK( out.str() == "[]" );


  /* Implicit constructor */
  Matrix<double> implicit(2);
	 
  CHECK( implicit.rows() == 2 );
  CHECK( implicit.columns() == 2 );
  CHECK( implicit(0,0) == 0 );
  CHECK( implicit(0,1) == 0 );
  CHECK( implicit(1,0) == 0 );
  CHECK( implicit(1,1) == 0 );
  CHECK_THROWS_AS( implicit(2, 0), std::out_of_range );
  CHECK_THROWS_AS( implicit(0, 2), std::out_of_range );

  /* Explicit constructor */
  Matrix<double> expl(2, 3);
  CHECK( expl.rows() == 2 );
  CHECK( expl.columns() == 3 );
  CHECK( expl(0,0) == 0 );
  CHECK( expl(0,1) == 0 );
  CHECK( expl(0,2) == 0 );
  CHECK( expl(1,0) == 0 );
  CHECK( expl(1,1) == 0 );
  CHECK( expl(1,2) == 0 );
  CHECK_THROWS_AS( expl(2, 2), std::out_of_range );
  CHECK_THROWS_AS( expl(1, 3), std::out_of_range );

  /* Initializer list */
  Matrix<int> initialiser = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  CHECK( initialiser.rows() == 3 );
  CHECK( initialiser.columns() == 3 );
  CHECK( initialiser(0, 0) == 1 );
  CHECK( initialiser(0, 1) == 2 );
  CHECK( initialiser(0, 2) == 3 );
  CHECK( initialiser(1, 0) == 4 );
  CHECK( initialiser(1, 1) == 5 );
  CHECK( initialiser(1, 2) == 6 );
  CHECK( initialiser(2, 0) == 7 );
  CHECK( initialiser(2, 1) == 8 );
  CHECK( initialiser(2, 2) == 9 );

}

TEST_CASE("Addition") {
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

  CHECK( sum == res );

  one += two;
  CHECK( one == res );

  CHECK_THROWS_AS( one + three, std::out_of_range );
  CHECK_THROWS_AS( one += three, std::out_of_range );
}

TEST_CASE("Scalar addition") {
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

  CHECK( rsum == rres );
  CHECK( lsum == lres );
}

TEST_CASE("Subtraction") {
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

  CHECK( diff == res );

  one -= two;
  CHECK( one == res );
}

TEST_CASE("Scalar subtraction") {
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

  CHECK( rdiff == rres );
  CHECK( ldiff == lres );
}

TEST_CASE("Multiplication") {
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

  CHECK( prod == res );

  Matrix<double> one_orig = one;
  one *= two;
  CHECK( one == res );

  CHECK_THROWS_AS( one_orig * three, std::out_of_range );
  CHECK_THROWS_AS( one_orig *= three, std::out_of_range );
}

TEST_CASE("Scalar multiplication") {
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

  CHECK( rprod == rres );
  CHECK( lprod == lres );
}

TEST_CASE("Pointwise multiplication") {
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

  CHECK( prod == res );
}

TEST_CASE("stdout") {
  Matrix<int> mtx = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  std::cout << mtx << std::endl;
}

TEST_CASE("Access operator") {
  Matrix<int> mtx = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  mtx(1, 2) = 10;

  CHECK( mtx(1, 2) == 10 );
}

TEST_CASE("Reset operation") {
  Matrix<int> mtx = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  mtx.reset();

  CHECK( mtx == Matrix<int>(3, 3) );
}
  
TEST_CASE("Copy operator") {
  Matrix<int> mtx = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  Matrix<int> copy = mtx;

  CHECK( copy == mtx );

  /* Make modifications in the copy */
  copy(1, 1) = 99;
  CHECK( copy != mtx );
}

TEST_CASE("Move operator") {
  Matrix<int> mtx = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  Matrix<int> move = std::move(mtx);

  CHECK_THROWS_AS( move == mtx, std::out_of_range );
}

TEST_CASE("Insert row 1") {
  Matrix<double> test(2, 3);
  Matrix<double> res(3, 3);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1 2 3][0 0 0][4 5 6]]");
  end >> res;

  test.insert_row(1);

  CHECK( test == res );
}

TEST_CASE("Insert row 2") {
  Matrix<double> test(2, 3);
  Matrix<double> res(3, 3);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[0 0 0][1 2 3][4 5 6]]");
  end >> res;

  test.insert_row(0);

  CHECK( test == res );
}

TEST_CASE("Append row 1") {
  Matrix<double> test(2, 3);
  Matrix<double> res(3, 3);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1 2 3][0 0 0][4 5 6]]");
  end >> res;

  test.append_row(0);

  CHECK( test == res );
}

TEST_CASE("Append row 2") {
  Matrix<double> test(2, 3);
  Matrix<double> res(3, 3);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1 2 3][4 5 6][0 0 0]]");
  end >> res;

  test.append_row(1);

  CHECK( test == res );
}

TEST_CASE("Remove row 1") {
  Matrix<double> test(2, 3);
  Matrix<double> res(1, 3);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1 2 3]]");
  end >> res;

  test.remove_row(1);

  CHECK( test == res );
}

TEST_CASE("Remove row 2") {
  Matrix<double> test(2, 3);
  Matrix<double> res(1, 3);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[4 5 6]]");
  end >> res;

  test.remove_row(0);

  CHECK( test == res );
}

TEST_CASE("Insert column 1") {
  Matrix<double> test(2, 3);
  Matrix<double> res(2, 4);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1 2 0 3][4 5 0 6]]");
  end >> res;

  test.insert_column(2);

  CHECK( test == res );
}

TEST_CASE("Insert column 2") {
  Matrix<double> test(2, 3);
  Matrix<double> res(2, 4);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[0 1 2 3][0 4 5 6]]");
  end >> res;

  test.insert_column(0);

  CHECK( test == res );
}

TEST_CASE("Append column 1") {
  Matrix<double> test(2, 3);
  Matrix<double> res(2, 4);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1 0 2 3][4 0 5 6]]");
  end >> res;

  test.append_column(0);

  CHECK( test == res );
}

TEST_CASE("Append column 2") {
  Matrix<double> test(2, 3);
  Matrix<double> res(2, 4);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1 2 3 0][4 5 6 0]]");
  end >> res;

  test.append_column(2);

  CHECK( test == res );
}

TEST_CASE("Remove column 1") {
  Matrix<double> test(2, 3);
  Matrix<double> res(2, 2);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[2 3][5 6]]");
  end >> res;

  test.remove_column(0);

  CHECK( test == res );
}

TEST_CASE("Remove column 2") {
  Matrix<double> test(2, 3);
  Matrix<double> res(2, 2);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1 2][4 5]]");
  end >> res;

  test.remove_column(2);

  CHECK( test == res );
}

TEST_CASE("Get column") {
  Matrix<double> test(2, 3);
  Matrix<double> res(2, 1);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1][4]]");
  end >> res;

  Matrix<double> column = test.getColumn(0);

  CHECK( column == res );
}

TEST_CASE("Get row") {
  Matrix<double> test(2, 3);
  Matrix<double> res(1, 3);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> test;

  std::istringstream end("[[1 2 3]]");
  end >> res;

  Matrix<double> row = test.getRow(0);

  CHECK( row == res );
}

TEST_CASE("Identity matrix") {
  Matrix<double> eye = Matrix<double>::eye(3);

  Matrix<double> reference = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  CHECK( eye == reference );
}

TEST_CASE("Transpose non-square") {
  Matrix<double> normal(2, 3);
  Matrix<double> transposed(3, 2);

  std::istringstream begin("[[1 2 3][4 5 6]]");
  begin >> normal;

  std::istringstream end("[[1 4][2 5][3 6]]");
  end >> transposed;

  CHECK( normal.transpose() == transposed );
  CHECK( normal.rows() == 3 );
  CHECK( normal.columns() == 2 );
}

TEST_CASE("Transpose square") {
  Matrix<double> normal(3, 3);
  Matrix<double> transposed(3, 3);

  std::istringstream begin("[[1 2 3][4 5 6][7 8 9]]");
  begin >> normal;

  std::istringstream end("[[1 4 7][2 5 8][3 6 9]]");
  end >> transposed;

  CHECK( normal.transpose() == transposed );
  CHECK( normal.rows() == 3 );
  CHECK( normal.columns() == 3 );
}

TEST_CASE("Iterators") {
  Matrix<double> normal(2, 3);

  std::istringstream s("[[1 2 3][4 5 6]]");
  s >> normal;

  double i = 0;
  for (auto k = normal.begin(); k != normal.end(); k++)
    CHECK( *k == ++i );

  CHECK( i == 6.0 );
}


