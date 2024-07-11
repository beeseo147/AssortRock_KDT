#include "Reflection/Reflection.h"
#include "Windows/WindowsPlatform.h"

namespace meta
{
	namespace internal
	{
		struct type_node;

		std::unordered_map<std::type_index, meta::internal::type_node*>& GetReflectionMap()
		{
			static std::unordered_map<std::type_index, meta::internal::type_node*> MapReflection;
			return MapReflection;
		}
		meta::internal::type_node** GetLastNode()
		{
			static meta::internal::type_node* Node;
			return &Node;
		}
	}
}