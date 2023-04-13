#include <stdio.h>
#include <iostream>
#include <list>
#include <unordered_map>

#define KEY_TYPE int
#define VAL_TYPE int

class LRUCache
{
public:
    LRUCache(int capacity) : capacity_(capacity) {}

    VAL_TYPE get(KEY_TYPE key)
    {
        if (map_.find(key) == map_.end())
            return -1;

        set(key, map_[key]->second);
        return map_[key]->second;
    }



    void set(KEY_TYPE key, VAL_TYPE val)
    {
        if (map_.find(key) != map_.end())
        {
            nodes_.erase(map_[key]);
            --size_;
        }
        else
        {
            if (size_ >= capacity_ && size_ != 0)
            {
                map_.erase(nodes_.rbegin()->first);
                nodes_.pop_back();
                --size_;
            }
        }

        nodes_.emplace_front(std::make_pair(key, val));
        map_[key] = nodes_.begin();
        ++size_;
    }
    void print_all()
    {
        for (auto &it : nodes_)
        {
            std::cout << "(" << it.first << ", " << it.second << ")  ";
        }
        std::cout << std::endl;
    }

private:   


    int capacity_ = 0;
    int size_ = 0;

    std::list<std::pair<KEY_TYPE, VAL_TYPE>> nodes_;
    std::unordered_map<KEY_TYPE, std::list<std::pair<KEY_TYPE, VAL_TYPE>>::iterator> map_;
};

int main()
{
    LRUCache lru(2);
    lru.set(1.0, 1);
    lru.print_all();
    lru.set(2, 2);
    lru.print_all();
    int v = lru.get(1);
    lru.print_all();
    lru.set(3, 3);
    lru.print_all();
    lru.set(4, 4);
    lru.print_all();
    lru.set(3, 33);
    lru.print_all();
    return 0;
}