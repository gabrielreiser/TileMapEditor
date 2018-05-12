//
//  ResourceIdentifiers.hpp
//  Noise2
//
//  Created by Gabriel Reiser on 5/7/18.
//  Copyright © 2018 Gabriel Reiser. All rights reserved.
//

#ifndef ResourceIdentifiers_hpp
#define ResourceIdentifiers_hpp


//Enumerations for different types of resources
namespace Texture{
    enum ID{Character, Pokemon, Zelda, Grass};
}
namespace SoundAffects{
    enum ID{};
}
namespace Fonts{
    enum ID{GeorgiaBold, Sansation};
}

//Forward declarator of ResourceHolder Class
template<typename Resouces, typename Identifier>
class ResourceHolder;

//Typedefs
typedef ResourceHolder<sf::Texture, Texture::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif /* ResourceIdentifiers_hpp */
