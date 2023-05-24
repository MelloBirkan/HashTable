#include "HashTable.h"
#include <cmath>
#include <sstream>
#include <string>

HashTable::HashTable() : HashTable(DEFAULT_SIZE) {}

HashTable::HashTable(int size) : m_Size(size) {
  m_Table = new LinkedList[m_Size];
}

HashTable::~HashTable() {
  delete[] m_Table;
  m_Table = nullptr;
}

std::string HashTable::Search(int key) const {
  int hashKey = HashFunction(key);

  const Node *node = m_Table[hashKey].GetNode(key);
  if (node)
    return node->GetValue();

  return "";
}

HashTable::InsertResult HashTable::Insert(int key, const std::string &value) {
  int hashKey = HashFunction(key);
  InsertResult result = m_Table[hashKey].IsEmpty()
                            ? InsertResult::WithoutCollision
                            : InsertResult::WithCollision;

  Node *node = m_Table[hashKey].GetNode(key);
  if (node) {
    node->SetValue(value);
    result = InsertResult::Updated;
  } else {
    m_Table[hashKey].Append(key, value);
  }

  return result;
}

bool HashTable::Remove(int key) {
  int hashKey = HashFunction(key);

  Node *node = m_Table[hashKey].RemoveNode(key);
  if (node) {
    delete node;
    node = nullptr;

    return true;
  }

  return false;
}

bool HashTable::IsEmpty() const {
  bool isEmpty = true;

  for (int i = 0; i < m_Size; ++i) {
    isEmpty &= m_Table[i].IsEmpty();
  }

  return isEmpty;
}

std::string HashTable::ToString() const {
  std::ostringstream oss;

  for (int i = 0; i < m_Size; ++i)
    oss << "[" << i << "] " << m_Table[i].ToString() << '\n';

  return oss.str();
}

int HashTable::HashFunction(int key) const {
  // Converter a chave de entrada para uma string
  std::string str_chave = std::to_string(key);

  // Verificar se temos ao menos 5 dígitos
  if (str_chave.length() < 5) {
    return -1; // retorna -1 se a chave for inválida
  }

  // Manter apenas o 1º, 3º e 5º dígitos
  std::string str_resultado = "";
  str_resultado += str_chave[0]; // Adiciona o 1º dígito ao resultado
  str_resultado += str_chave[2]; // Adiciona o 3º dígito ao resultado
  str_resultado += str_chave[4]; // Adiciona o 5º dígito ao resultado

  // Converter a string resultante de volta para um inteiro
  int resultado = std::stoi(str_resultado);

  // Aplicar o método quadrático ao resultado
  resultado = std::pow(resultado, 2);

  // Realizar a divisão inteira do resultado por 11
  resultado = resultado % 11;

  return resultado;
}
