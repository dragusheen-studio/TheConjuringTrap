/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Node.hpp"

/* ----- CLASS ----- */
namespace yaml
{
    /* ----- GETTERs ----- */
    bool Node::has(const std::string &key) const
    {
        return children.find(key) != children.end();
    }

    std::shared_ptr<Node> Node::get(const std::string &key) const
    {
        if (has(key)) return children.at(key);
        throw std::runtime_error("Config key not found: " + key);
    }

    std::string Node::asString() const
    {
        std::string val = value;
        if (val.size() >= 2 && val.front() == '"' && val.back() == '"')
            val = val.substr(1, val.size() - 2);
        return val;
    }

    int Node::asInt() const
    {
        return std::stoi(asString());
    }

    double Node::asDouble() const
    {
        return std::stod(asString());
    }

}; // namespace yaml
