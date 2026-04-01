/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include <fstream>
#include <gtest/gtest.h>
#include "Yaml/Parser/Parser.hpp"

/* ----- CLASS ----- */
class YamlFileTestFixture : public ::testing::Test
{
    protected:
        const char *validFilePath = "test_valid.yaml";

        void SetUp() override
        {
            std::ofstream file(validFilePath);
            file << "game: TheConjuringTrap\n";
            file << "version: 1.0\n";
            file.close();
        }

        void TearDown() override
        {
            remove(validFilePath);
        }
};

/* ----- TESTs ----- */
TEST(YamlParserTest, ParseSingleKeyValue)
{
    yaml::Parser p("key: value");
    EXPECT_EQ(p.get("key")->asString(), "value");
}

TEST(YamlParserTest, ParseMultipleKeys)
{
    yaml::Parser p("key1: 10\nkey2: 20");
    EXPECT_EQ(p.get("key1")->asInt(), 10);
    EXPECT_EQ(p.get("key2")->asInt(), 20);
}

TEST(YamlParserTest, TrimSpacesAroundKey)
{
    yaml::Parser p("  key  : value");
    EXPECT_TRUE(p.getRoot()->has("key"));
}

TEST(YamlParserTest, TrimSpacesAroundValue)
{
    yaml::Parser p("key:    value   ");
    EXPECT_EQ(p.get("key")->asString(), "value");
}

TEST(YamlParserTest, IgnoreEmptyLines)
{
    yaml::Parser p("\n\nkey: value\n\n");
    EXPECT_TRUE(p.getRoot()->has("key"));
    EXPECT_EQ(p.get("key")->asString(), "value");
}

TEST(YamlParserTest, IgnoreComments)
{
    yaml::Parser p("# This is a comment\nkey: value");
    EXPECT_TRUE(p.getRoot()->has("key"));
    EXPECT_FALSE(p.getRoot()->has("#"));
}

TEST(YamlParserTest, NestedOneLevel)
{
    std::string content =
        "parent:\n"
        "  child: value\n";
    yaml::Parser p(content);
    EXPECT_TRUE(p.get("parent")->has("child"));
    EXPECT_EQ(p.get("parent")->get("child")->asString(), "value");
}

TEST(YamlParserTest, NestedMultipleChildren)
{
    std::string content =
        "parent:\n"
        "  child1: 1\n"
        "  child2: 2\n";
    yaml::Parser p(content);
    auto parent = p.get("parent");
    EXPECT_EQ(parent->get("child1")->asInt(), 1);
    EXPECT_EQ(parent->get("child2")->asInt(), 2);
}

TEST(YamlParserTest, NestedDeep)
{
    std::string content =
        "level1:\n"
        "  level2:\n"
        "    level3: secret\n";
    yaml::Parser p(content);
    EXPECT_EQ(p.get("level1")->get("level2")->get("level3")->asString(), "secret");
}

TEST(YamlParserTest, ReturnToRootLevel)
{
    std::string content =
        "parent:\n"
        "  child: 1\n"
        "sibling: 2\n";
    yaml::Parser p(content);
    EXPECT_TRUE(p.getRoot()->has("sibling"));
    EXPECT_EQ(p.get("sibling")->asInt(), 2);
}

TEST(YamlParserTest, ReturnToIntermediateLevel)
{
    std::string content =
        "level1:\n"
        "  level2:\n"
        "    child: 1\n"
        "  sibling2: 2\n";
    yaml::Parser p(content);
    EXPECT_TRUE(p.get("level1")->has("sibling2"));
    EXPECT_EQ(p.get("level1")->get("sibling2")->asInt(), 2);
}

TEST_F(YamlFileTestFixture, LoadValidFile)
{
    yaml::Parser p = yaml::Parser::load(validFilePath);
    EXPECT_EQ(p.get("game")->asString(), "TheConjuringTrap");
    EXPECT_DOUBLE_EQ(p.get("version")->asDouble(), 1.0);
}

TEST_F(YamlFileTestFixture, LoadInvalidFileThrows)
{
    EXPECT_THROW(yaml::Parser::load("non_existent_file_12345.yaml"), std::runtime_error);
}
