#include "Set.hpp"

namespace code_learning {

	namespace algorithm {
		Range::Range(uint64_t from, uint64_t to) {
			m_limits.first = from < to ? from : to;
			m_limits.second = from > to ? from : to;
		}

		bool Range::operator<(const Range &other) const {
			if (m_limits.first >= other.m_limits.first &&
				m_limits.second < other.m_limits.second) {
				return true;
			}
			if (m_limits.first > other.m_limits.first &&
				m_limits.second <= other.m_limits.second) {
				return true;
			}
			return false;
		}


		bool Range::IsSub(const std::set<Range> &super) const {
			for (const auto &range : super) {
				if (range.m_limits.first <= m_limits.first &&
					m_limits.second <= range.m_limits.second) {
					return true;
				}
			}
			return false;
		}

		bool Range::IsSub(const std::set<uint64_t> &super) const {
			for (uint64_t element = m_limits.first;
				element <= m_limits.second; element++) {
				if (super.find(element) == super.end()) {
					return false;
				}
			}
			return true;
		}

		Set::Set(uint64_t max) {
			m_ranges.insert(Range(1, max));
		}

		void Set::AddSingles(uint64_t element) {
			m_singles.insert(element);
		}
		

		void Set::AddRanges(const Range &range) {
			m_ranges.insert(range);
		}

		

		uint64_t Set::GetSize() const {
			uint64_t size = 0;

			uint64_t from = UINT64_MAX;
			uint64_t to = 0;
			for (const auto &range : m_ranges) {
				from = range.m_limits.first < from ? range.m_limits.first : from;
				to = range.m_limits.second > to ? range.m_limits.second : to;
			}
			size = to - from + 1;

			for (const auto &single : m_singles) {
				if (!(from <= single && single <= to)) {
					size++;
				}
			}

			return size;
		}

		bool Set::IsSub(const Set &super) const {
			return RangesIsSub(super) &&
				SinglesIsSub(super);
		}

		bool Set::RangesIsSub(const Set &super) const {
			for (const auto &range : m_ranges) {
				if (!range.IsSub(super.m_ranges) &&
					!range.IsSub(super.m_singles)) {
					return false;
				}
			}
			return true;
		}

		bool Set::SinglesIsSub(const Set &super) const {
			for (const auto &single : m_singles) {
				if (!IsSubSingle(single, super.m_ranges) &&
					!IsSubSingle(single, super.m_singles)) {
					return false;
				}
			}
			return true;
		}

		bool Set::IsSubSingle(uint64_t single, const std::set<Range> &super) const {
			for (const auto &range : super) {
				if (range.m_limits.first <= single &&
					single <= range.m_limits.second) {
					return true;
				}
			}
			return false;
		}

		bool Set::IsSubSingle(uint64_t single, const std::set<uint64_t> &super) const {
			return super.find(single) != super.end();
		}


	}

}
