// Copyright 2021 by Mark Melton
//

#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include "core/cache/all.h"

namespace fs = std::filesystem;

class Environment : public ::testing::Environment {
public:

    Environment()
	: cache_root_(fs::temp_directory_path()) {
	cache_root_ += fmt::format("/cache.{}", getpid());
	fs::remove_all(cache_root_);
    }
    
    ~Environment() override {
    }

    void SetUp() override {
	setenv("CACHE_ROOT", cache_root_.c_str(), true);
    }

    void TearDown() override {
	unsetenv("CACHE_ROOT");
	fs::remove_all(cache_root_);
    }
    
private:
    string cache_root_;
};

TEST(Cache, UniqueName)
{
    core::Cache a{1, 1};
    core::Cache b{1, 2};
    EXPECT_NE(a.name(), b.name());
}

TEST(Cache, Exists)
{
    core::Cache a{"Exists", 1, 2, 3};
    EXPECT_FALSE(a.exists());
    EXPECT_FALSE(a.exists("foobar"));

    a.get();
    EXPECT_TRUE(a.exists());
    EXPECT_FALSE(a.exists("foobar"));
}

TEST(Cache, Get)
{
    core::Cache a{"Get", 1, 2, 3};
    EXPECT_FALSE(a.exists());
    EXPECT_FALSE(a.exists("foobar"));

    auto [exists, path] = a.get("foobar");
    EXPECT_FALSE(exists);
    EXPECT_FALSE(a.exists());
    EXPECT_FALSE(a.exists("foobar"));

    a.prepare();
    EXPECT_TRUE(a.exists());
    EXPECT_FALSE(a.exists("foobar"));

    {
	std::ofstream ofs{path};
	ofs.write("hello", 6);
	ofs.close();
    }

    auto [exists_now, path_now] = a.get("foobar");
    EXPECT_TRUE(exists_now);
    EXPECT_TRUE(a.exists("foobar"));
    EXPECT_EQ(path, path_now);
}

TEST(Cache, GetOrThrow)
{
    core::Cache a{"GetOrThrow", 1, 2, 3};
    EXPECT_THROW(a.get_or_throw("foobar"), core::runtime_error);

    auto [exists, path] = a.get("foobar");
    {
	a.prepare();
	std::ofstream ofs{path};
	ASSERT_TRUE(ofs.good());
	ofs.write("hello", 6);
	ofs.close();
    }
    auto path_now = a.get_or_throw("foobar");
    EXPECT_EQ(path, path_now);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    AddGlobalTestEnvironment(new Environment);
    return RUN_ALL_TESTS();
}
