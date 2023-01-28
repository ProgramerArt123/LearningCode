#ifndef __CODE_LEARNING_ALGORITHM_SET_H__
#define __CODE_LEARNING_ALGORITHM_SET_H__

#include <set>

namespace code_learning {

	namespace algorithm {

		class Range {
		public:
			Range(uint64_t from, uint64_t to){
				m_limits.first = from < to ? from : to;
				m_limits.second = from > to ? from : to;
			}

			bool operator<(const Range &other) const{
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
		
			std::pair<uint64_t, uint64_t> m_limits;
		};

		class Set {
		public:
			Set() {
				
			}

			explicit Set(uint64_t max){
				m_ranges.insert(Range(1, max));
			}

			template<typename T>
			void AddSingles(T element) {
				m_singles.insert(element);
			}

			template<typename T, typename ...Ts>
			void AddSingles(T element, Ts ...elements) {
				m_singles.insert(element);
				AddSingles(elements...);
			}

			uint64_t GetSize() const{
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
		private:
			std::set<uint64_t> m_singles;
			std::set<Range> m_ranges;
		};
	}

}

#endif