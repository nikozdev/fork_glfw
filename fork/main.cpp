#include <iostream>

int main(int vArgC, const char **vArgV)
{
  std::copy(
    &vArgV[0],
    &vArgV[vArgC],
    std::ostream_iterator<const char*>(std::cout, "\n")
  );
  return 0;
}
