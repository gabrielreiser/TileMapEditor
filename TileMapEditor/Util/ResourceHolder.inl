//Inline funciton definitions for Resource holder class template

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id){
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());    //The given resource is not loaded
    //returns the adress of the second value(the resource we are storing)
    return *found->second;
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const {
    auto found = mResourceMap.find(id);
    //assert if the resource is not found
    assert(found != mResourceMap.end());    //The given resource is not loaded
    //returns the adress of the second value(the resource we are storing)
    return *found->second;
}

//Function to load the resource and store it in a unique pointer
template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename){
    std::unique_ptr<Resource> resource(new Resource());
    if(!resource->loadFromFile(filename)){
        throw std::runtime_error("ResourceHolder::load - Failed to Load " + filename);
    }
    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);    //Cannot input since the pair already exists.
}

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::remove(Identifier id){
    auto remove = mResourceMap.find(id);
    assert(remove != mResourceMap.end());   //The desired resource to remove does not exist
    mResourceMap.erase(remove);
}
