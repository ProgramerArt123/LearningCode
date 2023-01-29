#ifndef __CODE_LEARNING_ALGORITHM_SET_H__
#define __CODE_LEARNING_ALGORITHM_SET_H__

#include <set>

namespace code_learning {

	namespace algorithm {

		class Range {
		public:
			Range(uint64_t from, uint64_t to);

			bool operator<(const Range &other) const;
			bool operator==(const Range &other) const;
			bool operator<=(const Range &other) const;

			bool IsSub(const Range &super) const;
			bool IsIntersection(const Range &other) const;

			std::pair<uint64_t, uint64_t> m_limits;
		};

		class Set {
		public:
			
			explicit Set(uint64_t max = 0);

			void AddSingles(uint64_t element);

			template<typename ...Elements>
			void AddSingles(uint64_t element, Elements ...elements) {
				AddRanges(Range(element, element));
				AddSingles(elements...);
			}

			void AddRanges(const Range &range);

			template<typename ...Ranges>
			void AddRanges(const Range &range, const Ranges ...ranges) {
				m_ranges.insert(range);
				AddRanges(ranges...);
			}

			uint64_t GetSize() const;

			bool IsSub(const Set &super) const;

			bool IsSuper(const Range &sub)const;

		public:
			std::set<Range> m_ranges;
		};
	}

}

#endif