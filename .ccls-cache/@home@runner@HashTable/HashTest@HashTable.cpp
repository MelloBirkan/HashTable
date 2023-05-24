#include "HashTable.h"
#include <sstream>

HashTable::HashTable()
	: HashTable(DEFAULT_SIZE)
{
}

HashTable::HashTable(int size)
	: m_Size(size)
{
	m_Table = new LinkedList[m_Size];
}

HashTable::~HashTable()
{
	delete[] m_Table;
	m_Table = nullptr;
}

std::string HashTable::Search(int key) const
{
	int hashKey = HashFunction(key);

	const Node* node = m_Table[hashKey].GetNode(key);
	if (node)
		return node->GetValue();

	return "";
}

HashTable::InsertResult HashTable::Insert(int key, const std::string& value)
{
	int hashKey = HashFunction(key);
	InsertResult result = m_Table[hashKey].IsEmpty() ? InsertResult::WithoutCollision : InsertResult::WithCollision;

	Node* node = m_Table[hashKey].GetNode(key);
	if (node)
	{
		node->SetValue(value);
		result = InsertResult::Updated;
	}
	else
	{
		m_Table[hashKey].Append(key, value);
	}

	return result;
}

bool HashTable::Remove(int key)
{
	int hashKey = HashFunction(key);

	Node* node = m_Table[hashKey].RemoveNode(key);
	if (node)
	{
		delete node;
		node = nullptr;

		return true;
	}

	return false;
}

bool HashTable::IsEmpty() const
{
	bool isEmpty = true;

	for (int i = 0; i < m_Size; ++i)
	{
		isEmpty &= m_Table[i].IsEmpty();
	}

	return isEmpty;
}

std::string HashTable::ToString() const
{
	std::ostringstream oss;

	for (int i = 0; i < m_Size; ++i)
		oss << "[" << i << "] " << m_Table[i].ToString() << '\n';

	return oss.str();
}

int HashTable::HashFunction(int key) const
{
	return key % m_Size;
}