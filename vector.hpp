#pragma once

#include <functional>
#include <iostream>
#include <iterator>
#include <memory>

namespace usu
{

    template <typename T>
    class vector
    {

      public:
        using size_type = std::size_t;
        using reference = T&;
        using pointer = std::shared_ptr<T[]>;
        using resize_type = std::function<size_type(size_type)>;

        pointer m_data;
        size_type m_capacity;
        resize_type func = [](size_type currentCapacity) -> size_type
        {
            return currentCapacity * 2;
        };
        
        int m_size;

        // Iterator
        class iterator
        {
          public:
            using iterator_category = std::forward_iterator_tag;

            size_type m_pos;
            pointer m_data;
            iterator() :
                iterator(nullptr) // DefaultConstructable
            {
            }
            iterator(pointer ptr) :
                m_data(ptr),
                m_pos(0)
            {
            }
            iterator(size_type pos, pointer ptr) :
                m_pos(pos),
                m_data(ptr)
            {
            }
            iterator(const iterator& obj)
            {
                this->m_pos = obj.m_pos;
                this->m_data = obj.m_data;
            } // CopyConstructable
            iterator(iterator&& obj) noexcept
            {
                this->m_pos = obj.m_pos;
                this->m_data = obj.m_data;
                obj.m_pos = 0;
                obj.m_data = nullptr;
            } // MoveConstructable
            iterator operator++()
            {
                m_pos++;
                return *this;
            } // incrementable e.g., ++r
            iterator operator++(int)
            {
                iterator i = *this;
                m_pos++;
                return i;
            } // incrementable e.g., r++

            iterator operator--()
            {
                m_pos--;
                return *this;
            } // incrementable e.g., --r
            iterator operator--(int)
            {
                iterator i = *this;
                m_pos--;
                return i;
            } // incrementable e.g., r--

            T* operator->()
            {

                return &m_data[m_pos];
            }

            iterator& operator=(const iterator& rhs)
            {
                this->m_pos = rhs.m_pos;
                this->m_data = rhs.m_data;
                return *this;
            } // CopyAssignable
            iterator& operator=(iterator&& rhs)
            {
                if (this != &rhs)
                {
                    std::swap(this->m_pos, rhs.m_pos);
                    std::swap(this->m_data, rhs.m_data);
                }
                return *this;
            } // MoveAssignable

            reference operator*() // Derefrenceable
            {
                return m_data[m_pos];
            }

            bool operator==(const iterator& rhs) { return m_pos == rhs.m_pos; }
            bool operator!=(const iterator& rhs) { return m_pos != rhs.m_pos; }
        };

        // Constructors

        vector()
        {
            m_capacity = 10;
            m_size = 0;
            m_data.reset(new T[10]);
        }

        vector(size_type size)
        {
            
            if (size < 10)
            {
                m_capacity = 10;
                m_size = size;
                m_data.reset(new T[10]);
            }
            else
            {
                m_capacity = size * 2;
                m_size = size;
                m_data.reset(new T[m_capacity]);
            };
        }

        vector(resize_type resize)
        {
       
            func = resize;
            m_size = 0;
            m_capacity = 10;   
            m_data.reset(new T[10]);
        }
        vector(size_type size, resize_type resize)
        {
            
            m_size = size;
            
            func = resize;
            if(m_size <= 10){
                m_capacity = 10;
                
            }
            else
            {
                m_capacity = resize(m_size);
            }
                
            m_data.reset(new T[m_capacity]);
        }
        vector(std::initializer_list<T> list)
        {
            m_capacity = 10;
            m_size = 0;

            m_data.reset(new T[m_capacity]);
            for (T item : list)
            {
                add(item);
            }
        }
        vector(std::initializer_list<T> list, resize_type resize)
        {
            m_capacity = 10;
            m_size = 0;
            func = resize;
            m_data.reset(new T[m_capacity]);
            for (T item : list)
            {
                add(item);
            }
        }

        // Methods & Operators
        reference operator[](size_type index)
        {
            if (index >= m_size) {
                throw std::range_error("");
        }
            return m_data[index];
        }

        void add(T value)
        {
            if (m_size < m_capacity)
            {
                m_data[m_size] = value;
                m_size += 1;
            }
            else
            {
                m_capacity = func(m_capacity);

                pointer newData;
                newData.reset(new T[m_capacity]);
                for (int i = 0; i < m_size; i++)
                {
                    newData[i] = m_data[i];
                }
                m_data = newData;
                m_data[m_size] = value;
                m_size += 1;
            }
            

        }

        void insert(size_type index, T value) 
        {
            if (index <= m_size)
            {
                m_size += 1;
                pointer newData;
                if (m_size >= m_capacity)
                {
                    m_capacity = func(m_capacity);
                    newData.reset(new T[m_capacity * 2]);
                }
                else
                {
                    newData.reset(new T[m_capacity]);
                }
                for (int i = 0; i < m_size; i++)
                {
                    if (i < index)
                    {
                        newData[i] = m_data[i];
                    }
                    else if (i > index)
                    {
                        newData[i] = m_data[i - 1];
                    }
                    else
                    {
                        newData[i] = value;
                    }
                }
                m_data = newData;
            }
            else
            {
                throw std::range_error("");
            }
        }

        void remove(size_type index)
        {
            if (index < m_size)
            {
                m_size -= 1;
                pointer newData;
                newData.reset(new T[m_capacity]);

                for (int i = 0; i <= m_size; i++)
                {
                    if (i < index)
                    {
                        newData[i] = m_data[i];
                    }
                    else
                    {

                        newData[i] = m_data[i + 1];
                    }
                }
                m_data = newData;
            }
            else
            {
                throw std::range_error("");
            }
        }

        void clear()
        {
            pointer newData;
            newData.reset(new T[m_capacity]);

            m_data = newData;
            m_size = 0;
        }
        size_type size()
        {
            return m_size;
        }
        size_type capacity()
        {
            return m_capacity;
        }

        iterator begin()
        {
            return iterator(m_data);
        }

        iterator end()
        {
            return iterator(m_size, m_data);
        }
    };

} // namespace usu