// Copyright 2025 atikdd.t.me

// Copyright 2025 atikdd.t.me

#pragma once

template <typename TKey, typename TVal>
class ITable {
 public:
    virtual ~ITable() = default;

    // Добавляет запись в таблицу. Если запись с таким ключом уже существует,
    virtual bool Insert(const TKey& key, const TVal& val) = 0;

    // Находит запись по ключу и возвращает значение
    virtual TVal Find(const TKey& key) const = 0;

    // Проверяет, есть ли запись с данным ключом
    virtual bool IsExists(const TKey& key) const = 0;

    // Удаляет запись по ключу. Если запись удалена, возвращает true,
    virtual bool Delete(const TKey& key) = 0;

    // Возвращает количество записей в таблице
    virtual size_t GetSize() const = 0;

    // Очищает таблицу
    virtual void Clear() = 0;
};
