template<typename T>
std::shared_ptr<T> Resources::get(const std::string& path) {
    std::shared_ptr<T> data;
    std::unordered_map<std::string, std::shared_ptr<void> >::iterator it;
    it = contents.find(path);
    if (it == contents.end()) {
        data = loadResource<T>(path);
        contents[path] = std::static_pointer_cast<void>(data);
    } else {
        data = std::static_pointer_cast<T>(it->second);
    }
    return data;
}

template<>
inline std::shared_ptr<sf::Texture> loadResource(const std::string& path) {
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(path)) {
        std::cout << "failed to load texture " << path << std::endl;
        abort();
    }
    std::cout << "loaded texture " << path << std::endl;
    return texture;
}