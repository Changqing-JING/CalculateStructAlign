#include <stdalign.h>
struct ST {
  ST() {
  }
  int aa{};
  char bb{};
  long long cc{};
};

int main() {
  ST st;

  return st.aa;
}