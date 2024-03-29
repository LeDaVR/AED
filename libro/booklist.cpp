#include <iostream>

template <typename Object>
class List
{
private:
    struct Node
{
    Object data;
    Node *prev;
    Node *next;

    Node(const Object &d = Object{}, Node *p = nullptr,
         Node *n = nullptr)
        : data{d}, prev{p}, next{n} {}

    Node(Object &&d, Node *p = nullptr, Node *n = nullptr)
        : data{std::move(d)}, prev{p}, next{n} {}
};

public:
    class const_iterator
    { /* See Figure 3.14 */
    };

    class iterator : public const_iterator
    { /* See Figure 3.15 */
    };

public:
    List()
    { /* See Figure 3.16 */
    }
    List(const List &rhs)
    { /* See Figure 3.16 */
    }
    ~List()
    { /* See Figure 3.16 */
    }
    List &operator=(const List &rhs)
    { /* See Figure 3.16 */
    }
    List(List &&rhs)
    { /* See Figure 3.16 */
    }
    List &operator=(List &&rhs)
    { /* See Figure 3.16 */
    }

    iterator begin()
    {
        return {head->next};
    }
    const_iterator begin() const
    {
        return {head->next};
    }
    iterator end()
    {
        return {tail};
    }
    const_iterator end() const
    {
        return {tail};
    }

    int size() const
    {
        return theSize;
    }
    bool empty() const
    {
        return size() == 0;
    }

    void clear()
    {
        while (!empty())
            pop_front();
    }
    Object &front()
    {
        return *begin();
    }
    const Object &front() const
    {
        return *begin();
    }
    Object &back()
    {
        return *--end();
    }
    const Object &back() const
    {
        return *--end();
    }
    void push_front(const Object &x)
    {
        insert(begin(), x);
    }
    void push_front(Object &&x)
    {
        insert(begin(), std::move(x));
    }
    void push_back(const Object &x)
    {
        insert(end(), x);
    }
    void push_back(Object &&x)
    {
        insert(end(), std::move(x));
    }
    void pop_front()
    {
        erase(begin());
    }
    void pop_back()
    {
        erase(--end());
    }

    iterator insert(iterator itr, const Object &x)
    { /* See Figure 3.18 */
    }
    iterator insert(iterator itr, Object &&x)
    { /* See Figure 3.18 */
    }

    iterator erase(iterator itr)
    { /* See Figure 3.20 */
    }
    iterator erase(iterator from, iterator to)
    { /* See Figure 3.20 */
    }

private:
    int theSize;
    Node *head;
    Node *tail;

    void init()
    { /* See Figure 3.16 */
    }
};


int main(){
    return 0;
}