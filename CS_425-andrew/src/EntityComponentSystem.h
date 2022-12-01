#pragma once

#include <vector>
#include <unordered_map>

#include "Component.h"

using namespace std;

namespace engine {

	typedef function<void(EntityID)> ForEachCallback;


	class EntityComponentSystem {

		public:
		
			EntityID entity = 0;
			vector< unique_ptr< SparseSetHolder > > m_components;

			template< typename T>
			ComponentIndex GetComponentIndex() {
				static ComponentIndex index = GetNextIndex(); // Only calls GetNextIndex() the first time this function is called.
				return index;
			}

			ComponentIndex GetNextIndex() {
				static ComponentIndex index = -1; // Returns the sequence 0, 1, 2, … every time this is called.
				index += 1;
				return index;
			}

			template< typename T >
			unordered_map< EntityID, T >& GetAppropriateSparseSet() {
				// Get the index for T’s SparseSet
				const ComponentIndex index = GetComponentIndex<T>();
				// If we haven’t seen it yet, it must be past the end.
				// Since component indices are shared by all ECS instances,
				// it could happen that index is more than one past the end.
				if (index >= m_components.size()) { m_components.resize(index + 1); }
				assert(index < m_components.size());

				// Create the actual sparse set if needed.
				if (m_components[index] == nullptr) m_components[index] = make_unique< SparseSet<T> >();
				// It’s safe to cast the SparseSetHolder to its subclass and return the std::unordered_map< EntityID, T > inside.
				return static_cast<SparseSet<T>&>(*m_components[index]).data;
			}

			template< typename T >
			T& Get(EntityID entity) {
				return GetAppropriateSparseSet<T>()[entity];
			}

			template< typename T, typename ... Types >
			EntityID Create(const T& t, const Types&... types) {

				Get<T>(entity + 1) = t;
				if constexpr (sizeof...(Types) > 0) { return Create<Types...>(types...); }

				return ++entity;
			}

			// Destroy the entity by removing all components.
			void Destroy(EntityID e) {
				for (const auto& comps : m_components) { comps->Drop(e); }
			}

			// Returns true if the entity has all types.
			template < typename T, typename... Types >
			bool HasAll(EntityID entity) {
				bool result = true;
				// https://stackoverflow.com/questions/48405482/variadic-template-no-matching-function-for-call/48405556#48405556
				if constexpr (sizeof...(Types) > 0) { result = HasAll<Types...>(entity); }
				return result && GetAppropriateSparseSet<T>().count(entity) > 0;
			}

			template<typename EntitiesThatHaveThisComponent, typename... AndAlsoTheseComponents>
			void ForEach(const function<void(EntityID)>& callback) {
				// Iterate over elements of the first container.

				auto& container = GetAppropriateSparseSet<EntitiesThatHaveThisComponent>();
				for (const auto& [entity, value] : container) {
					// We know it has the first component.
					// Skip the entity if it doesn't have the remaining components.
					// This `if constexpr` is evaluated at compile time. It is needed when AndAlsoTheseComponents is empty.
					// https://stackoverflow.com/questions/48405482/variadic-template-no-matching-function-for-call/48405556#48405556
					if constexpr (sizeof...(AndAlsoTheseComponents) > 0) {
						if (!HasAll<AndAlsoTheseComponents...>(entity)) {
							continue;
						}
					}
					callback(entity);
				}
			}
	};
}