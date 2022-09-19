// Copyright 2021, 2022 by Mark Melton
//

#include <filesystem>
#include <fmt/format.h>
#include <fstream>
#include <gtest/gtest.h>
#include "core/util/hash/path.h"
#include "core/util/exception.h"

namespace fs = std::filesystem;

class Environment : public ::testing::Environment {
public:
    Environment()
	: root_(fs::temp_directory_path()) {
	root_ += fmt::format("/path.{}", getpid());
	fs::remove_all(root_);
    }
    
    ~Environment() override {
    }

    void SetUp() override {
	fs::create_directories(root_);
    }

    void TearDown() override {
	fs::remove_all(root_);
    }

    const std::string root() const {
	return root_;
    }
    
private:
    std::string root_;
};

Environment *env{nullptr};

void write_to_file(const std::string& file) {
    std::ofstream ofs{file, std::ios::app};
    ASSERT_TRUE(ofs.good());

    ofs.write("abc", 3);
    ofs.close();
}

TEST(Hash, File)
{
    std::string dir = env->root();
    std::string foo_file = fmt::format("{}/foo", dir);
    std::string bar_file = fmt::format("{}/bar", dir);
    write_to_file(foo_file);
    write_to_file(bar_file);
    
    fs::path foo_path{foo_file};
    fs::path bar_path{bar_file};
    auto foo_hid = core::hash(foo_path);
    auto bar_hid = core::hash(bar_path);
    EXPECT_NE(foo_hid, bar_hid);

    EXPECT_EQ(foo_hid, core::hash(foo_path));
    EXPECT_EQ(bar_hid, core::hash(bar_path));

    write_to_file(foo_path);
    EXPECT_NE(foo_hid, core::hash(foo_path));
    EXPECT_EQ(bar_hid, core::hash(bar_path));
}

TEST(Hash, Dir)
{
    std::string dir = env->root();
    std::string new_dir = fmt::format("{}/duh", dir);
    fs::create_directory(new_dir);
    
    std::string foo_file = fmt::format("{}/foo", new_dir);
    write_to_file(foo_file);

    fs::path dir_path{new_dir};
    auto hid = core::hash(dir_path);
    EXPECT_EQ(hid, core::hash(dir_path));

    write_to_file(foo_file);
    EXPECT_NE(hid, core::hash(dir_path));
}

TEST(Hash, PathException)
{
    std::string dir = env->root();
    std::string file = fmt::format("{}/nothere", dir);
    fs::path nonexistent_path = fs::path{file};
    EXPECT_THROW(core::hash(nonexistent_path), core::runtime_error);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    env = new Environment{};
    AddGlobalTestEnvironment(env);
    return RUN_ALL_TESTS();
}
