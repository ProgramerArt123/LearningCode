#ifndef __CODE_LEARNING_ALGORITHM_SERIES_HPP__
#define __CODE_LEARNING_ALGORITHM_SERIES_HPP__

#include <vector>
#include <functional>
#include "Number.h"

namespace code_learning {

	namespace algorithm {

		template<typename Monomial>
		class Series : public Number {
			static_assert(std::is_base_of_v<Number, Monomial>, "Monomial invalid");
		public:
			Series(std::function<Monomial(const uint64_t index)> monomial):
				m_monomial(monomial){

			}
			Series<Monomial> &Summation(uint64_t length) {
				if (m_polynomial.size() < length) {
					for (int index = m_polynomial.size() + 1; index <= length; index ++) {
						m_polynomial.push_back(m_monomial(index));
					}
				}
				else if (m_polynomial.size() > length) {
					m_polynomial.resize(length);
				}
				return *this;
			}
			Monomial GetMonomial() {
				Monomial summation;
				for (const auto &monomial : m_polynomial) {
					summation += monomial;
				}
				return summation;
			}
			const std::string GetString() override {
				return GetMonomial().GetString();
			}
		private:
			std::vector<Monomial> m_polynomial;
			std::function<Monomial(const uint64_t index)> m_monomial;
		};

	}

}

#endif