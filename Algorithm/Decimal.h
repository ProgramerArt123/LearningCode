#ifndef __CODE_LEARNING_ALGORITHM_DECIMAL_H__
#define __CODE_LEARNING_ALGORITHM_DECIMAL_H__

#include <cstdint>
#include <vector>
#include "Number.h"

namespace code_learning {

	namespace algorithm {

		class Fraction;

		class Decimal : public Number {
		public :
			Decimal();
			Decimal(double value);
			Decimal(const Fraction &fraction);
			const std::string GetString() override;
			Decimal operator+(const Decimal &addition) const;
			Decimal &operator+=(const Decimal &addition);
		private:
			double m_value = 0.0;
		};

	}

}

#endif