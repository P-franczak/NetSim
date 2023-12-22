#ifndef NETSIM_FACTORY_HPP
#define NETSIM_FACTORY_HPP

#include "nodes.hpp"
#include <vector>

template <class Node>
class NodeCollection {
public:
    using container_t = typename std::list<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    void add(Node&& node) { collection_.emplace_back(std::move(node)); }

    iterator begin() { return collection_.begin(); }
    iterator end() { return collection_.end(); }

    const_iterator begin() const { return collection_.begin(); }
    const_iterator end() const { return collection_.end(); }

    const_iterator cbegin() const { return collection_.begin(); }
    const_iterator cend() const { return collection_.end(); }

    iterator find_by_id(ElementID id) { return std::find_if(begin(), end(), [id](auto node){ return node.get_id() == id; } ); }
    const_iterator find_by_id(ElementID id) const { return std::find_if(cbegin(), cend(), [id](Node node){ return node.get_id() == id; }); }

    void remove_by_id(ElementID id) { auto foundID = find_by_id(id); if(foundID != end()) collection_.erase(foundID); }
private:
    container_t collection_;
};



class Factory{
public:
    void add_ramp(&&Ramp)
    void remove_ramp(ElementID id)
    NodeCollection<Node>::iterator find_by_id(ElementID id)
    NodeCollection<Node>::const_iterator {query} find_by_id(ElementID id)
    NodeCollection<Ramp>::const_iterator {query} ramp_cbegin()
    NodeCollection<Ramp>::const_iterator {query} ramp_cend()
    NodeCollection<Workers>::const_iterator {query} ramp_cbegin()
    NodeCollection<Workers>::const_iterator {query} ramp_cend()
    NodeCollection<Storehouse>::const_iterator {query} ramp_cbegin()
    NodeCollection<Sotrehouse>::const_iterator {query} ramp_cend()
private:

};

#endif //NETSIM_FACTORY_HPP
