#include "factory.hpp"


bool Factory::has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors){
    if(node_colors[sender] == NodeColor::VERIFIED){
        return true;
    }
    node_colors[sender] = NodeColor::VISITED;
    if (sender->receiver_preferences_.get_preferences().empty()){
        throw std::logic_error("No defined receivers.");
    }
    bool hasOtherReceiver = false;
    for (auto receiver : sender->receiver_preferences_.get_preferences()){
        if (receiver.first->get_receiver_type() == STOREHOUSE){
            hasOtherReceiver = true;
        }
        else if(receiver.first->get_receiver_type() == WORKER){
            IPackageReceiver* receiver_ptr = receiver.first;
            auto worker_ptr = dynamic_cast<Worker*>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);
            if(sendrecv_ptr == sender){
                continue;
            }
            hasOtherReceiver = true;
            if (node_colors[sendrecv_ptr] == NodeColor::UNVISITED){
                has_reachable_storehouse(sendrecv_ptr, node_colors);
            }
        }
    }
    node_colors[sender] = NodeColor::VERIFIED;
    if(hasOtherReceiver){
        return true;
    }
    else{
        throw std::logic_error("No reachable storehouse.");
    }
}


bool Factory::is_consistent(){
    std::map<const PackageSender*, NodeColor> node_colors;
    for(auto node : ramps_){
        node_colors[&node] = NodeColor::UNVISITED;
    }
    for(auto node : workers_){
        node_colors[&node] = NodeColor::UNVISITED;
    }
    try{
        for (auto node : ramps_){
            has_reachable_storehouse(&node, node_colors);
        }
        return true;
    }
    catch(std::logic_error &error){
        return false;
    }
}


void Factory::do_deliveries(Time time){
    for (auto& ramp : ramps_){
        ramp.deliver_goods(time);
    }
}

void Factory::do_package_passing(){
    for (auto& ramp : ramps_){
        ramp.send_package();
    }
    for (auto& worker : workers_){
        worker.send_package();
    }
}

void Factory::do_work(Time time){
    for (auto& worker : workers_){
        worker.do_work(time);
    }
}

void Factory::remove_receiver(NodeCollection<Worker>& collection, ElementID id) {
    Worker& receiver = *collection.find_by_id(id);
    for (auto &ramp : ramps_){
        ramp.receiver_preferences_.remove_receiver(&receiver);
    }
}

void Factory::remove_receiver(NodeCollection<Storehouse>& collection, ElementID id) {
    Storehouse& receiver = *collection.find_by_id(id);
    for (auto &worker : workers_){
        worker.receiver_preferences_.remove_receiver(&receiver);
    }
}

void Factory::remove_storehouse(ElementID id){
    remove_receiver(storehouses_, id);
    storehouses_.remove_by_id(id);
}

void Factory::remove_worker(ElementID id){
    remove_receiver(workers_, id);
    workers_.remove_by_id(id);
}
