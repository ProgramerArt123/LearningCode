#ifndef __CODE_LEARNING_STATISTICS_LIST_MAP_HPP__
#define __CODE_LEARNING_STATISTICS_LIST_MAP_HPP__

#include <memory>
#include <map>
#include <list>
#include <string>

#include "Adjacency.hpp"

namespace code_learning {

	class Glob;

		class ListMap {
		public:
			explicit ListMap(Glob &glob) :
				m_glob(glob) {

			}
			std::list<std::shared_ptr<AdjacencyBase>>::const_iterator begin() const {
				return m_list.begin();
			}
			std::list<std::shared_ptr<AdjacencyBase>>::const_iterator end() const {
				return m_list.end();
			}
			void Sort() {
				m_list.sort(compare);
				for (const auto &element : m_list) {
					element->Sort();
				}
			}
			static bool compare(const std::shared_ptr<AdjacencyBase> &one, const std::shared_ptr<AdjacencyBase> &other) {
				return one->GetCount() > other->GetCount();
			}

			template<typename Child>
			Child &Get(const std::string &key) {
				if (m_map.end() == m_map.find(key)) {
					std::shared_ptr<AdjacencyBase> lexis(new Child(key, m_glob));
					m_map.insert(std::make_pair(key, lexis));
					m_list.push_back(lexis);
				}
				return static_cast<Child&>(*m_map[key]);
			}

			template<typename Child>
			Child &Get(const std::string &key, const std::string &content) {
				if (m_map.end() == m_map.find(key)) {
					std::shared_ptr<AdjacencyBase> lexis(new Child(content, m_glob));
					m_map.insert(std::make_pair(key, lexis));
					m_list.push_back(lexis);
				}
				return static_cast<Child&>(*m_map[key]);
			}
			std::map<std::string, std::shared_ptr<AdjacencyBase>> m_map;
			std::list<std::shared_ptr<AdjacencyBase>> m_list;
		protected:
			Glob &m_glob;
		};


}

#endif