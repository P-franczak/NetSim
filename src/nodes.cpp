#include "nodes.hpp"

void ReceiverPreferences::add_receiver(IPackageReceiver *r) {
    double num_of_receivers_begin = double(preferences_.size());
    if (num_of_receivers_begin == 0) {
        preferences_[r] = 1.0;
    }
    else {
        for (auto &rec: preferences_) {
            rec.second = 1 / (num_of_receivers_begin + 1);
        }
        preferences_[r] = 1 / (num_of_receivers_begin + 1);
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver *r) {
    double num_of_receivers_begin = double(preferences_.size());
    if (num_of_receivers_begin > 1) {
        for (auto &rec: preferences_) {
            if (rec.first != r) {
                rec.second = 1 / (num_of_receivers_begin - 1);
            }
        }
    }
    preferences_.erase(r);
}

IPackageReceiver *ReceiverPreferences::choose_receiver() {
    auto prob = pg_();
    if (prob >= 0 && prob <= 1) {
        double distribution = 0.0;
        for (auto &rec: preferences_) {
            distribution = distribution + rec.second;
            if (distribution < 0 || distribution > 1) {
                return nullptr;
            }
            if (prob <= distribution) {
                return rec.first;
            }
        }
        return nullptr;
    }
    return nullptr;
}

void PackageSender::send_package() {
    IPackageReceiver *receiver;
    if (bufor_) {
        receiver = receiver_preferences_.choose_receiver();
        receiver->receive_package(std::move(*bufor_));
        bufor_.reset();
    }
}

void PackageSender::push_package(Package&& package){
    if (!bufor_.has_value()) {
        bufor_.emplace(std::move(package));
    }
}

Worker::Worker(const Worker &worker){
    id_ = worker.get_id();
    pd_ = worker.get_processing_duration();
    receiver_preferences_ = worker.receiver_preferences_;
    q_ = std::make_unique<PackageQueue>(worker.get_queue()->get_queue_type());
}

Worker& Worker::operator=(const Worker &worker) noexcept {
    id_ = worker.get_id();
    pd_ = worker.get_processing_duration();
    receiver_preferences_ = worker.receiver_preferences_;
    q_ = std::make_unique<PackageQueue>(worker.get_queue()->get_queue_type());
    return *this;
}

void Worker::do_work(Time t) {
    if(!bufor_.has_value()){
        bufor_.emplace(q_->pop());
        t_ = t;
    }
    else if(t - t_ + 1 == pd_){
        push_package(std::move(*bufor_));
        bufor_.reset();
    }
}

void Worker::receive_package(Package &&p) {
    q_->push(std::move(p));
}

void Storehouse::receive_package(Package &&p) {
    d_->push(std::move(p));
}

Ramp::Ramp(const Ramp &ramp) {
    id_ = ramp.get_id();
    di_ = ramp.get_delivery_interval();
    receiver_preferences_ = ramp.receiver_preferences_;
}

Ramp& Ramp::operator=(const Ramp &ramp) noexcept{
    id_ = ramp.get_id();
    di_ = ramp.get_delivery_interval();
    receiver_preferences_ = ramp.receiver_preferences_;
    return *this;
}

void Ramp::deliver_goods(Time t) {
    if (t % di_ == 1){
        Package package = Package();
        push_package(std::move(package));
    }
}
