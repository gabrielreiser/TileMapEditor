//
//  ResourceHolder.hpp
//  Noise2
//
//  Created by Gabriel Reiser on 5/6/18.
//  Copyright © 2018 Gabriel Reiser. All rights reserved.
//

#ifndef ResourceHolder_hpp
#define ResourceHolder_hpp

#include <map>
#include <memory>
#include <string>
#include <assert.h>
#include <SFML/Graphics.hpp>
#include "ResourceIdentifiers.hpp"


template<typename Resource, typename Identifier>
class ResourceHolder{
public:
	void load(Identifier, const std::string& filename);
    void remove(Identifier id);
    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;
    void clear(){mResourceMap.clear();}
private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};
#include "ResourceHolder.inl"

#endif /* ResourceHolder_hpp */

