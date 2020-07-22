#pragma once
#include <type_traits>
#include <typeindex>
#include <cassert>
#include <memory>

namespace beleg
{
	class beleg_any
	{
		struct internal
		{
			std::type_index data_type;
			internal(std::type_index type) : data_type(type)
			{};
		};
		template<typename T>
		struct internal_type : internal
		{
			T _data;
			internal_type(T data) : internal(typeid(data)), _data(data)
			{ }
		};
		std::shared_ptr<internal> data;
	public:
		beleg_any()
		{}
		template <typename T, std::enable_if_t<!std::is_same<T, beleg_any>::value>* = nullptr>
		beleg_any(T _data)
		{
			this->data = std::make_shared<internal_type<T>>(_data);
		}
		template <typename T, std::enable_if_t<!std::is_same<T, beleg_any>::value>* = nullptr>
		beleg_any& operator=(T _data)
		{
			this->data = std::make_shared<internal_type<T>>(_data);
			return *this;
		}
		template <typename T>
		T& get()
		{
			auto res = std::static_pointer_cast<internal_type<T>>(this->data);
			return res->_data;
		}
		template <typename T>
		T& safeGet()
		{
			if (this->data->data_type != typeid(T))
			{
				throw std::exception("Invalid conversion");
			}
			return get<T>();
		}
		template <typename T>
		bool is()
		{
			return data->data_type == typeid(T);
		}
		bool empty()
		{
			return (bool)this->data;
		}
		template <typename T>
		operator T()
		{
			return get<T>();
		}
	};
}