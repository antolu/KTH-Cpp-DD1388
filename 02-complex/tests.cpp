#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "Complex.hpp"
#include <cmath>

TEST_CASE("Complex numbers") {
  Complex x;
  REQUIRE( x == Complex(0, 0));
  
  Complex x2 = 5;
  REQUIRE( x2 == Complex(5.0, 0));
  
  Complex y(6,2);
  REQUIRE( y == Complex(6.0, 2.0));
  
  Complex z = x + y;
  REQUIRE( z == Complex(6.0, 2.0));

  Complex w(5, -3);

  Complex u = y - w;
  REQUIRE( u == Complex(1, 5));

  Complex t = y * w;
  REQUIRE( t == Complex(36, -8));

  Complex s = y / w;
  REQUIRE( s == Complex(36.0/34, -8.0/34));
  
  Complex k = 3 + 5.0_i;
  REQUIRE( k == Complex(3.0, 5.0));

  k -= 5 + ( 1.0_i * Complex(5,3) );
  REQUIRE( k == 1 );

  REQUIRE( abs(w) == std::sqrt(34) );
  REQUIRE( real(y) == 6.0 );
  REQUIRE( imag(y) == -3.0 );
  REQUIRE( y.real() == 6.0 );
  REQUIRE( y.imag() == -3.0 );

  std::cout << "w != y:" << ( w != y ) << std::endl;
  std::cout << "w != w:" << ( w != w ) << std::endl;

  std::cout << Complex(6, 6) / 6 << std::endl;
  std::cout << Complex(6, -6) / 6 << std::endl;
  std::cout << Complex(-6, -6) / 6 << std::endl;
  std::cout << Complex(-6, 6) / 6 << std::endl;
}
