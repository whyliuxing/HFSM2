namespace hfsm2 {
namespace detail {

////////////////////////////////////////////////////////////////////////////////

template <typename T, LongIndex NCapacity>
class StaticArray {
public:
	static constexpr LongIndex CAPACITY = NCapacity;
	static constexpr LongIndex DUMMY	= INVALID_LONG_INDEX;

	using Item  = T;
	using Index = UnsignedCapacity<CAPACITY>;

public:
	HFSM2_INLINE StaticArray() = default;
	HFSM2_INLINE StaticArray(const Item filler);

	template <typename N>
	HFSM2_INLINE	   Item& operator[] (const N i);

	template <typename N>
	HFSM2_INLINE const Item& operator[] (const N i) const;

	HFSM2_INLINE LongIndex count() const					{ return CAPACITY;									}

	HFSM2_INLINE void fill(const Item filler);
	HFSM2_INLINE void clear()								{ fill(INVALID_SHORT_INDEX);						}

	HFSM2_INLINE Iterator<      StaticArray>  begin()		{ return Iterator<      StaticArray>(*this,     0); }
	HFSM2_INLINE Iterator<const	StaticArray>  begin() const	{ return Iterator<const StaticArray>(*this,     0); }
	HFSM2_INLINE Iterator<const	StaticArray> cbegin() const	{ return Iterator<const StaticArray>(*this,     0); }

	HFSM2_INLINE Iterator<      StaticArray>    end()		{ return Iterator<      StaticArray>(*this, DUMMY);	}
	HFSM2_INLINE Iterator<const	StaticArray>    end() const	{ return Iterator<const StaticArray>(*this, DUMMY);	}
	HFSM2_INLINE Iterator<const	StaticArray>   cend() const	{ return Iterator<const StaticArray>(*this, DUMMY);	}

private:
	Item _items[CAPACITY];
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename T>
struct StaticArray<T, 0> {
	using Item  = T;

	HFSM2_INLINE StaticArray() = default;
	HFSM2_INLINE StaticArray(const Item)											{}
};

//------------------------------------------------------------------------------

template <typename T, LongIndex NCapacity>
class Array {
	template <typename>
	friend class Iterator;

public:
	static constexpr LongIndex CAPACITY = NCapacity;
	static constexpr LongIndex DUMMY	= INVALID_LONG_INDEX;

	using Item = T;
	using Index = UnsignedCapacity<CAPACITY>;

public:
	HFSM2_INLINE void clear()														{ _count = 0;		}

	template <typename TValue>
	HFSM2_INLINE LongIndex append(TValue&& value);

	template <typename N>
	HFSM2_INLINE		  Item& operator[] (const N i);

	template <typename N>
	HFSM2_INLINE const Item& operator[] (const N i) const;

	HFSM2_INLINE LongIndex count() const											{ return _count;	}

	HFSM2_INLINE Iterator<      Array>  begin()			{ return Iterator<		Array>(*this,     0);	}
	HFSM2_INLINE Iterator<const Array>  begin() const	{ return Iterator<const Array>(*this,     0);	}
	HFSM2_INLINE Iterator<const Array> cbegin() const	{ return Iterator<const Array>(*this,     0);	}

	HFSM2_INLINE Iterator<      Array>	  end()			{ return Iterator<		Array>(*this, DUMMY);	}
	HFSM2_INLINE Iterator<const Array>	  end() const	{ return Iterator<const Array>(*this, DUMMY);	}
	HFSM2_INLINE Iterator<const Array>   cend() const	{ return Iterator<const Array>(*this, DUMMY);	}

private:
	HFSM2_INLINE LongIndex next(const LongIndex i) const							{ return i + 1;		}
	HFSM2_INLINE LongIndex limit() const											{ return _count;	}

private:
	LongIndex _count = 0;

#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable: 4324) // structure was padded due to alignment specifier
#endif

	Item _items[CAPACITY]; // warning 4324 triggers for 'StructureStateInfo'

#ifdef _MSC_VER
	#pragma warning(pop)
#endif
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename T>
class Array<T, 0> {};

////////////////////////////////////////////////////////////////////////////////

}
}

#include "array.inl"
