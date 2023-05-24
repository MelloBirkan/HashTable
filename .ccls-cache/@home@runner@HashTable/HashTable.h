#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <string>
#include "LinkedList.h"

class HashTable
{
private:
	static const int DEFAULT_SIZE = 31;

	int m_Size;
	LinkedList* m_Table;

	int HashFunction(int key) const;
public:
	enum class InsertResult
	{
		WithCollision,
		WithoutCollision,
		Updated,
	};

	HashTable();
	HashTable(int size);
	~HashTable();

	std::string Search(int key) const;
	InsertResult Insert(int key, const std::string& value);
	bool Remove(int key);
  std::string Extrair(int key) const;

	bool IsEmpty() const;

	std::string ToString() const;
};

#endif
