#pragma once
#include <utility>
#include <vector>
#include <optional>

class IAccessor
{
public:
	virtual ~IAccessor() = default;
	virtual int size() const = 0;
	virtual int columns() const = 0;
	virtual bool hasElement(int index) const = 0;
	virtual void clearElement(int index) = 0;
	virtual void insertToEnd(int count) = 0;
	virtual void removeFromEnd(int count) = 0;
};

/*template<typename T>
concept HasCount = requires()
{
	T::COUNT;
};*/

template<typename T>
class Accessor: public IAccessor
{
public:
	/*Accessor()
	{
		this->storage = &Database::Get()->getStorage<T>();
	}*/

	Accessor() = default;

	Accessor(std::vector<std::optional<T>> *storage)
	{
		this->storage = storage;
	}

	T *value(int id)
	{
		return const_cast<T *>(std::as_const(*this).value(id));
	}

	const T *value(int index) const
	{
		if (index < 0 || index >= size())
			return nullptr;

		if (!storage->at(index).has_value())
			return nullptr;

		return &storage->at(index).value();
	}

	int size() const override
	{
		return storage->size();
	}

	int columns() const override
	{
		return T::COUNT;
	}

	bool hasElement(int index) const override
	{
		return value(index) != nullptr;
	}

	void clearElement(int index) override
	{
		int prevId = value(index)->id;
		*value(index) = { .id = prevId };
	}

	void insertToEnd(int count) override
	{
		int nextId = storage->back().value().id + 1;
		for (int i = 0; i < count; i++)
			storage->emplace_back( T { .id = nextId++ } );
	}

	void removeFromEnd(int count) override
	{
		storage->erase(storage->end() - count, storage->end());
	}

private:
	std::vector<std::optional<T>> *storage;
};
