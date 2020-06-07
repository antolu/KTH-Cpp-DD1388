#define CATCH_CONFIG_MAIN
#include <gtest/gtest.h>

#include "Complex.hpp"
#include <cmath>

TEST(complex_numbers, complex_numers) {
  Complex x;
  EXPECT_EQ( x, Complex(0, 0));
  
  Complex x2 = 5;
  EXPECT_EQ( x2, Complex(5.0, 0));
  
  Complex y(6,2);
  EXPECT_EQ( y, Complex(6.0, 2.0));
  
  Complex z = x + y;
  EXPECT_EQ( z, Complex(6.0, 2.0));

  Complex w(5, -3);

  Complex u = y - w;
  EXPECT_EQ( u, Complex(1, 5));

  Complex t = y * w;
  EXPECT_EQ( t,  Complex(36, -8));

  Complex s = y / w;
  EXPECT_EQ( s, Complex(36.0/34, -8.0/34));
  
  Complex k = 3 + 5.0_i;
  EXPECT_EQ( k, Complex(3.0, 5.0));

  k -= 5 + ( 1.0_i * Complex(5,3) );
  EXPECT_EQ( k, 1 );

  EXPECT_EQ( abs(w), std::sqrt(34) );
  EXPECT_EQ( real(y), 6.0 );
  EXPECT_EQ( imag(y), 2.0 );
  EXPECT_EQ( y.real(), 6.0 );
  EXPECT_EQ( y.imag(), 2.0 );

  std::cout << "w != y:" << ( w != y ) << std::endl;
  std::cout << "w != w:" << ( w != w ) << std::endl;

  std::cout << Complex(6, 6) / 6 << std::endl;
  std::cout << Complex(6, -6) / 6 << std::endl;
  std::cout << Complex(-6, -6) / 6 << std::endl;
  std::cout << Complex(-6, 6) / 6 << std::endl;
}


int main(int argc, char ** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
