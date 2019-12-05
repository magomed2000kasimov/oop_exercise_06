#pragma once

#include <iterator>
#include <memory>

namespace cntr {

    template<class T>
    class List {
    private:
        class ListNode;

    public:
        class ForwardIterator {
        public:
            using value_type = T;
            using reference = T &;
            using pointer = T *;
            using difference_type = ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

            ForwardIterator(ListNode *node) : Ptr(node) {};

            T &operator*();

            ForwardIterator &operator++();

            ForwardIterator operator++(int);

            bool operator==(const ForwardIterator &it) const;

            bool operator!=(const ForwardIterator &it) const;

        private:
            ListNode *Ptr;

            friend class List;
        };

        ForwardIterator begin();

        ForwardIterator end();

        T& Top();

        void Insert(size_t & index,const T &value );

        void InsertHelp(const ForwardIterator &it, const T &value);

        void Erase(const ForwardIterator &it);

        bool Empty() {
            return Size == 0;
        }

        void Pop();

        void Push_back(const T &value);

        void Push(const T &value);

        List() = default;

        List(const List &) = delete;

        List &operator=(const List &) = delete;

        size_t Size = 0;
    private:
        class ListNode {
        public:
            T Value;
            std::unique_ptr<ListNode> NextNode = nullptr;

            ForwardIterator next();

            ListNode(const T &value, std::unique_ptr<ListNode> next) : Value(value), NextNode(std::move(next)) {};
        };

        std::unique_ptr<ListNode> Head = nullptr;


    };


    template<class T>
    typename List<T>::ForwardIterator List<T>::ListNode::next() {
        return {NextNode.get()};
    }

    template<class T>
    T &List<T>::ForwardIterator::operator*() {
        return Ptr->Value;
    }

    template<class T>
    typename List<T>::ForwardIterator &List<T>::ForwardIterator::operator++() {
        *this = Ptr->next();
        return *this;
    }

    template<class T>
    typename List<T>::ForwardIterator List<T>::ForwardIterator::operator++(int) {
        ForwardIterator prev = *this;
        ++(*this);
        return prev;
    }

    template<class T>
    bool List<T>::ForwardIterator::operator!=(const ForwardIterator &other) const {
        return Ptr != other.Ptr;
    }

    template<class T>
    bool List<T>::ForwardIterator::operator==(const ForwardIterator &other) const {
        return Ptr == other.Ptr;
    }

    template<class T>
    typename List<T>::ForwardIterator List<T>::begin() {
        return Head.get();
    }

    template<class T>
    typename List<T>::ForwardIterator List<T>::end() {
        return nullptr;
    }


    template<class T>
    void List<T>::Insert(size_t &index, const T &value) {
        int id = index - 1;
        if (index > this->Size) {
            throw std::logic_error("Out of bounds\n");
        }
        if (id == -1) {
            this->Push(value);
        }
        else {
            auto it = this->begin();
            for (int i = 0; i < id; ++i) {
                ++it;
            }
            this->InsertHelp(it,value);
        }
    }


    template<class T>
    void List<T>::InsertHelp(const ForwardIterator &it, const T &value) {
        std::unique_ptr<ListNode> newNode(new ListNode(value, nullptr));
        if (it.Ptr == nullptr && Size != 0) {
            throw std::logic_error("Out of bounds");
        }
        if (Size == 0) {
            Head = std::move(newNode);
            ++Size;
        } else {
            newNode->NextNode = std::move(it.Ptr->NextNode);
            it.Ptr->NextNode = std::move(newNode);
            ++Size;
        }
    }

    template<class T>
    void List<T>::Push(const T &value) {
        std::unique_ptr<ListNode> newNode(new ListNode(value, nullptr));
        newNode->NextNode = std::move(Head);
        Head = std::move(newNode);
        ++Size;
    }

    template<class T>
    void List<T>::Push_back(const T &value) {
        size_t index =  Size;
        this->Insert(index,value);
    }
    template<class T>
    T& List<T>::Top() {
        if (Head.get()) {
            return Head->Value;
        } else {
            throw std::logic_error("List is empty");
        }
    }

    template<class T>
    void List<T>::Pop() {
        if (Head.get() == nullptr) {
            throw std::logic_error("List is empty");
        }
        Head = std::move(Head->NextNode);
        --Size;
    }

    template<class T>
    void List<T>::Erase(const List<T>::ForwardIterator &it) {
        if (it.Ptr == nullptr) {
            throw std::logic_error("Invalid iterator");
        }
        --Size;
        if (it == this->begin()) {
            Head = std::move(Head->NextNode);

        } else {
            auto tmp = this->begin();
            while (tmp.Ptr->next() != it.Ptr) {
                ++tmp;
            }
            tmp.Ptr->NextNode = std::move(it.Ptr->NextNode);
        }
    }

}


