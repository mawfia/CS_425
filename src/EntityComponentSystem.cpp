#pragma once

#include <thread>
#include <chrono>
#include <iostream>
#include <functional>
#include <vector>
#include <assert.h>


#include "EntityComponentSystem.h"

using namespace std;

namespace engine {
	

	template< typename T> 
	ComponentIndex EntityComponentSystem::GetComponentIndex() {
		static ComponentIndex index = GetNextIndex(); // Only calls GetNextIndex() the first time this function is called.
		return index;
	}
	
	ComponentIndex EntityComponentSystem::GetNextIndex() {
		static ComponentIndex index = -1; // Returns the sequence 0, 1, 2, … every time this is called.
		index += 1;
		return index;
	}

	
	template< typename T >
	unordered_map< EntityID, T >& EntityComponentSystem::GetAppropriateSparseSet() {
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
	T& EntityComponentSystem::Get(EntityID entity) {
		return GetAppropriateSparseSet<T>()[entity];
	}
	

	template< typename T, typename ... Types >
	EntityID EntityComponentSystem::Create(const T& t, const Types&... types ) {

		Get<T>(entity+1) = t;
		if constexpr (sizeof...(Types) > 0) { return Create<Types...>(types...); }

		return ++entity;
	}



	// Destroy the entity by removing all components.
	void EntityComponentSystem::Destroy(EntityID e) {
		for (const auto& comps : m_components) { comps->Drop(e); }
	}

	// Returns true if the entity has all types.
	template < typename T, typename... Types >
	bool EntityComponentSystem::HasAll(EntityID entity) {
		bool result = true;
		// https://stackoverflow.com/questions/48405482/variadic-template-no-matching-function-for-call/48405556#48405556
		if constexpr (sizeof...(Types) > 0) { result = HasAll<Types...>(entity); }
		return result && GetAppropriateSparseSet<T>().count(entity) > 0;
	}

	template<typename EntitiesThatHaveThisComponent, typename... AndAlsoTheseComponents>
	void EntityComponentSystem::ForEach(const function<void(EntityID)>& callback) {
		// Iterate over elements of the first container.

		auto& container = GetAppropriateSparseSet<EntitiesThatHaveThisComponent>();
		for ( const auto& [entity, value] : container) {
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
}