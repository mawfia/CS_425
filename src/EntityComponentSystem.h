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

			template< typename T> ComponentIndex GetComponentIndex();
			ComponentIndex GetNextIndex();
			template< typename T > unordered_map< EntityID, T >& GetAppropriateSparseSet();
			template< typename T > T& Get(EntityID);
			template< typename T, typename... Types > EntityID Create(const T&, const Types& ... );
			void Destroy(EntityID);
			template< typename T, typename... Types > bool HasAll(EntityID);
			template< typename T, typename... Types > void ForEach(const function<void(EntityID)>& );
	};
}