/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include <gtest/gtest.h>
#include "Yaml/Node/Node.hpp"

/* ----- TESTs ----- */
TEST(YamlNodeTest, HasExistingKey)
{
    yaml::Node n;
    n.children["test"] = std::make_shared<yaml::Node>();
    EXPECT_TRUE(n.has("test"));
}

TEST(YamlNodeTest, HasMissingKey)
{
    yaml::Node n;
    EXPECT_FALSE(n.has("missing"));
}

TEST(YamlNodeTest, GetExistingKey)
{
    yaml::Node n;
    auto child = std::make_shared<yaml::Node>();
    child->value = "data";
    n.children["test"] = child;

    EXPECT_EQ(n.get("test")->value, "data");
}

TEST(YamlNodeTest, GetMissingKeyThrows)
{
    yaml::Node n;
    EXPECT_THROW(n.get("missing"), std::runtime_error);
}

TEST(YamlNodeTest, AsStringRaw)
{
    yaml::Node n;
    n.value = "hello world";
    EXPECT_EQ(n.asString(), "hello world");
}

TEST(YamlNodeTest, AsStringStripsQuotes)
{
    yaml::Node n;
    n.value = "\"hello\"";
    EXPECT_EQ(n.asString(), "hello");
}

TEST(YamlNodeTest, AsStringEmpty)
{
    yaml::Node n;
    n.value = "";
    EXPECT_EQ(n.asString(), "");
}

TEST(YamlNodeTest, AsStringOnlyOneQuote)
{
    yaml::Node n;
    n.value = "\"broken";
    EXPECT_EQ(n.asString(), "\"broken");
}

TEST(YamlNodeTest, AsIntPositive)
{
    yaml::Node n;
    n.value = "42";
    EXPECT_EQ(n.asInt(), 42);
}

TEST(YamlNodeTest, AsIntNegative)
{
    yaml::Node n;
    n.value = "-15";
    EXPECT_EQ(n.asInt(), -15);
}

TEST(YamlNodeTest, AsIntZero)
{
    yaml::Node n;
    n.value = "0";
    EXPECT_EQ(n.asInt(), 0);
}

TEST(YamlNodeTest, AsIntThrowsOnInvalid)
{
    yaml::Node n;
    n.value = "not_a_number";
    EXPECT_THROW(n.asInt(), std::invalid_argument);
}

TEST(YamlNodeTest, AsDoublePositive)
{
    yaml::Node n;
    n.value = "3.14159";
    EXPECT_DOUBLE_EQ(n.asDouble(), 3.14159);
}

TEST(YamlNodeTest, AsDoubleNegative)
{
    yaml::Node n;
    n.value = "-0.5";
    EXPECT_DOUBLE_EQ(n.asDouble(), -0.5);
}

TEST(YamlNodeTest, AsDoubleWholeNumber)
{
    yaml::Node n;
    n.value = "42";
    EXPECT_DOUBLE_EQ(n.asDouble(), 42.0);
}

TEST(YamlNodeTest, AsDoubleThrowsOnInvalid)
{
    yaml::Node n;
    n.value = "invalid";
    EXPECT_THROW(n.asDouble(), std::invalid_argument);
}

TEST(YamlNodeTest, AsBoolTrueString)
{
    yaml::Node n;
    n.value = "true";
    EXPECT_TRUE(n.asBool());
}

TEST(YamlNodeTest, AsBoolTrueUppercase)
{
    yaml::Node n;
    n.value = "TRUE";
    EXPECT_TRUE(n.asBool());
}

TEST(YamlNodeTest, AsBoolTrueMixedCase)
{
    yaml::Node n;
    n.value = "TrUe";
    EXPECT_TRUE(n.asBool());
}

TEST(YamlNodeTest, AsBoolTrueNumber)
{
    yaml::Node n;
    n.value = "1";
    EXPECT_TRUE(n.asBool());
}

TEST(YamlNodeTest, AsBoolTrueYes)
{
    yaml::Node n;
    n.value = "yes";
    EXPECT_TRUE(n.asBool());
}

TEST(YamlNodeTest, AsBoolFalseString)
{
    yaml::Node n;
    n.value = "false";
    EXPECT_FALSE(n.asBool());
}

TEST(YamlNodeTest, AsBoolFalseNumber)
{
    yaml::Node n;
    n.value = "0";
    EXPECT_FALSE(n.asBool());
}

TEST(YamlNodeTest, AsBoolInvalidIsFalse)
{
    yaml::Node n;
    n.value = "random_garbage";
    EXPECT_FALSE(n.asBool());
}
