/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- YAML_NODE_HPP_ ----- */
#ifndef YAML_NODE_HPP_
#define YAML_NODE_HPP_

/* ----- INCLUDEs ----- */
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

/* ----- CLASS ----- */
namespace yaml
{
    class Node
    {
        public:
            std::string value;
            std::unordered_map<std::string, std::shared_ptr<Node>> children;
            std::vector<std::string> keys;

            bool has(const std::string &key) const;
            std::shared_ptr<Node> get(const std::string &key) const;

            std::string asString() const;
            int asInt() const;
            double asDouble() const;
            bool asBool() const;
    };
}; // namespace yaml

/* ----- YAML_NODE_HPP_ ----- */
#endif
