/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Parser.hpp"

/* ----- CLASS ----- */
namespace yaml
{
    /* ----- DEFAULTs ----- */
    Parser::Parser(const std::string &content)
    {
        _root = std::make_shared<Node>();
        _parse(content);
    }

    /* ----- STATICs ----- */
    Parser Parser::load(const std::string &filepath)
    {
        std::ifstream file(filepath);
        if (!file.is_open()) throw std::runtime_error("Could not open config file: " + filepath);

        std::stringstream buffer;
        buffer << file.rdbuf();
        return Parser(buffer.str());
    }

    /* ----- GETTERs ----- */
    std::shared_ptr<Node> Parser::getRoot() const
    {
        return _root;
    }

    std::shared_ptr<Node> Parser::get(const std::string &key) const
    {
        return _root->get(key);
    }

    /* ----- PRIVATE FUNCTIONs ----- */
    void Parser::_parse(const std::string &content)
    {
        std::istringstream stream(content);
        std::string line;

        std::vector<std::pair<int, std::shared_ptr<Node>>> stack;
        stack.push_back({-1, _root});

        while (std::getline(stream, line)) {
            std::string trimmed = _trim(line);
            if (trimmed.empty() || trimmed[0] == '#') continue;

            int indent = 0;
            while (indent < line.size() && line[indent] == ' ')
                indent++;

            size_t colonPos = line.find(':');
            if (colonPos == std::string::npos) continue;

            std::string key = _trim(line.substr(indent, colonPos - indent));
            std::string val = _trim(line.substr(colonPos + 1));

            while (stack.size() > 1 && stack.back().first >= indent)
                stack.pop_back();

            auto newNode = std::make_shared<Node>();
            newNode->value = val;
            stack.back().second->children[key] = newNode;

            if (val.empty())
                stack.push_back({indent, newNode});
        }
    }

    std::string Parser::_trim(const std::string &str)
    {
        std::string s = str;
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
        return s;
    }

}; // namespace yaml
