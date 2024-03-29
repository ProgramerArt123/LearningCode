#include "Set.hpp"

namespace code_learning {

	namespace algorithm {
		Range::Range(uint64_t from, uint64_t to) {
			m_limits.first = from < to ? from : to;
			m_limits.second = from > to ? from : to;
		}

		uint64_t Range::GetSize() const {
			return m_limits.second - m_limits.first + 1;
		}

		bool Range::operator<(const Range &other) const {
			return m_limits.second - m_limits.first <
				other.m_limits.second - other.m_limits.first;
		}

		bool Range::operator==(const Range &other) const {
			return m_limits.first == other.m_limits.first &&
				m_limits.second == other.m_limits.second;
		}

		bool Range::operator<=(const Range &other) const {
			return *this < other || *this == other;
		}

		bool Range::IsSub(const Range &super) const {
			return (m_limits.first >= super.m_limits.first &&
				m_limits.second <= super.m_limits.second);
		}

		bool Range::IsIntersection(const Range &other) const {
			return !(m_limits.second < other.m_limits.first ||
				other.m_limits.second < m_limits.first);
		}

		Set::Set(uint64_t max) {
			if (max) {
				AddRanges(Range(1, max));
			}
		}

		void Set::AddSingles(uint64_t element) {
			AddRanges(Range(element, element));
		}
		
		void Set::AddRanges(const Range &range) {
			for (auto &existed : m_ranges) {
				if (range.IsSub(existed)) {
					return;
				}
				if (range.IsIntersection(existed)) {
					uint64_t lower = range.m_limits.first < existed.m_limits.first ?
						range.m_limits.first : existed.m_limits.first;
					uint64_t upper = range.m_limits.second > existed.m_limits.second ?
						range.m_limits.second : existed.m_limits.second;
					m_ranges.erase(existed);
					m_ranges.insert(Range(lower, upper));
					return;
				}
			}
			m_ranges.insert(range);
		}

		uint64_t Set::GetCardinality() const {
			uint64_t cardinality = 0;
			for (const auto &range : m_ranges) {
				cardinality += range.GetSize();
			}
			return cardinality;
		}

		bool Set::IsSub(const Set &super) const {
			for (const auto &range : m_ranges) {
				if (!super.IsSuper(range)) {
					return false;
				}
			}
			return true;
		}

		bool Set::IsSuper(const Range &sub)const {
			for (const auto &range : m_ranges) {
				if (sub <= range) {
					return true;
				}
			}
			return false;
		}

		Set Set::operator-(const Set &other)const {
			Set difference(*this);
			for (const auto &range : other.m_ranges) {
				for (const auto &existed : difference.m_ranges) {
					if (range.IsIntersection(existed)) {
						if (existed.m_limits.first < range.m_limits.first) {
							difference.m_ranges.insert(Range(existed.m_limits.first,
								range.m_limits.first - 1));
						}
						if (existed.m_limits.second > range.m_limits.second) {
							difference.m_ranges.insert(Range(range.m_limits.second + 1,
								existed.m_limits.second));
						}
						difference.m_ranges.erase(existed);
						break;
					}
				}
			}
			return difference;
		}

		Set &Set::operator-=(const Set &other) {
			return *this = *this - other;
		}

		Set Set::operator+(const Set &other)const {
			Set unions(*this);
			for (const auto &range : other.m_ranges) {
				unions.AddRanges(range);
			}
			return unions;
		}

		Set &Set::operator+=(const Set &other) {
			return *this = *this + other;
		}
	}

}
