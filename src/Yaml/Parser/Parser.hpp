/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- YAML_PARSER_HPP_ ----- */
#ifndef YAML_PARSER_HPP_
#define YAML_PARSER_HPP_

/* ----- INCLUDEs ----- */
#include <algorithm>
#include <fstream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include "Yaml/Node/Node.hpp"

/* ----- CLASS ----- */
namespace yaml
{
    class Parser
    {
        public:
            Parser(const std::string &content);
            ~Parser() = default;

            static Parser load(const std::string &filepath);

            std::shared_ptr<Node> getRoot() const;
            std::shared_ptr<Node> get(const std::string &key) const;

        private:
            std::shared_ptr<Node> _root;

            void _parse(const std::string &content);
            std::string _trim(const std::string &str);
    };
}; // namespace yaml

/* ----- YAML_PARSER_HPP_ ----- */
#endif
