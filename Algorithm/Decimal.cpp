#include <cassert>
#include "Fraction.h"
#include "Decimal.h"
namespace code_learning {

	namespace algorithm {
		Decimal::Decimal() {

		}
		Decimal::Decimal(double value):m_value(value) {

		}
		Decimal::Decimal(const Fraction &fraction) {
			if(fraction.IsPositive()){
				m_value = (double)fraction.m_numerator.m_value / fraction.m_denominator.m_value;
			}
			else {
				m_value = -(double)fraction.m_numerator.m_value / fraction.m_denominator.m_value;
			}
		}
		const std::string Decimal::GetString() {
			return std::to_string(m_value);
		}
		Decimal Decimal::operator+(const Decimal &addition) const {
			return Decimal(m_value + addition.m_value);
		}
		Decimal &Decimal::operator+=(const Decimal &addition) {
			*this = *this + addition;
			return *this;
		}
	}

}