#ifndef NETSIM_FACTORY_HPP
#define NETSIM_FACTORY_HPP


template <class Worker>
class NodeCollection {
public:
    void add(Node &&node);
    void remove_by_id(ElementID id)
    NodeCollection<Node>::iterator find_by_id(ElementID id)
    NodeCollection<Node>::const_iterator {query} find_by_id(ElementID id)
private:

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
