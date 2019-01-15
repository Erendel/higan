#pragma once

namespace nall {

template<int Requested> struct Real {
  enum : uint { Precision = Requested <= 32 ? 32 : 64 };
  static inline constexpr auto bits() -> uint { return Precision; }
  using type =
    typename conditional<bits() == 32, float32_t,
    typename conditional<bits() == 64, float64_t,
    void>::type>::type;

  inline Real() : data(0.0) {}
  template<typename T> inline Real(const T& value) : data((type)value) {}

  inline operator type() const { return data; }

  inline auto operator++(int) { auto value = *this; ++data; return value; }
  inline auto operator--(int) { auto value = *this; --data; return value; }

  inline auto& operator++() { data++; return *this; }
  inline auto& operator--() { data--; return *this; }

  template<typename T> inline auto& operator =(const T& value) { data =        value; return *this; }
  template<typename T> inline auto& operator*=(const T& value) { data = data * value; return *this; }
  template<typename T> inline auto& operator/=(const T& value) { data = data / value; return *this; }
  template<typename T> inline auto& operator%=(const T& value) { data = data % value; return *this; }
  template<typename T> inline auto& operator+=(const T& value) { data = data + value; return *this; }
  template<typename T> inline auto& operator-=(const T& value) { data = data - value; return *this; }

  inline auto serialize(serializer& s) { s(data); }

private:
  type data;
};

#define lhs (long double)(typename Real<LHS>::type)l
#define rhs (typename Real<RHS>::type)r
template<int LHS, int RHS> inline auto operator*(Real<LHS> l, Real<RHS> r) { return Real<64>{lhs * rhs}; }
template<int LHS, int RHS> inline auto operator/(Real<LHS> l, Real<RHS> r) { return Real<64>{lhs / rhs}; }
template<int LHS, int RHS> inline auto operator%(Real<LHS> l, Real<RHS> r) { return Real<64>{lhs % rhs}; }
template<int LHS, int RHS> inline auto operator+(Real<LHS> l, Real<RHS> r) { return Real<64>{lhs + rhs}; }
template<int LHS, int RHS> inline auto operator-(Real<LHS> l, Real<RHS> r) { return Real<64>{lhs - rhs}; }
#undef lhs
#undef rhs

}