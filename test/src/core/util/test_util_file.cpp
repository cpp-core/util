// Copyright 2021, 2022 by Mark Melton
//

#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include "core/util/file.h"

namespace fs = std::filesystem;

class Environment : public ::testing::Environment {
public:
    Environment()
	: dir_(fs::temp_directory_path()) {
	if (not dir_.ends_with("/"))
	    dir_ += "/";
	dir_ += fmt::format("root.{}/", getpid());
	fs::remove_all(dir_);
	fs::create_directories(dir_);
    }
    
    ~Environment() override { }
    
    void SetUp() override {
    }
    
    void TearDown() override {
	fs::remove_all(dir_);
    }

    string filename(const string& name) const {
	return fmt::format("{}/{}", dir(), name);
    }
    
    void create_file(const string& file) const {
	std::ofstream ofs{file};
	assert(ofs.good());
	ofs.close();
    }
    
    const string& dir() const {	return dir_; }
private:
    string dir_;
    string existing_env_;
};

Environment *env{nullptr};

using core::File;

TEST(File, Create)
{
    auto file = env->filename("foo");
    File f{file};
    EXPECT_EQ(f, file);
    EXPECT_FALSE(f.exists());
    
    env->create_file(f);
    EXPECT_TRUE(f.exists());
}

TEST(File, Fstream)
{
    auto file = env->filename("fstream");
    File f{file};
    EXPECT_FALSE(f.exists());

    auto ofs = f.as_ofstream();
    ofs << "abc" << endl;
    ofs.close();

    string line;
    auto ifs = f.as_ifstream();
    ASSERT_TRUE(std::getline(ifs, line));
    EXPECT_EQ(line, "abc"s);
}

TEST(File, ZstdCompressor)
{
    auto file = env->filename("decompressor");
    File f{file};
    EXPECT_FALSE(f.exists());

    int expected{42};
    auto zofs = f.as_zstd_compressor();
    zofs.write_pod(expected);
    zofs.close();

    int actual{0};
    auto zifs = f.as_zstd_decompressor();
    zifs.read_pod(actual);
    EXPECT_EQ(expected, actual);
}

TEST(File, Json)
{
    auto file = env->filename("json");
    File f{file};
    EXPECT_EQ(f, file);
    EXPECT_FALSE(f.exists());

    auto actual_nil = f.as_json();
    EXPECT_FALSE(actual_nil);

    json expected = {{"pi", 3.14}};
    auto ofs = f.as_ofstream();
    ofs << expected;
    ofs.close();
    
    auto actual = f.as_json();
    EXPECT_TRUE(actual);
    EXPECT_EQ(expected, actual);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    env = new Environment;
    AddGlobalTestEnvironment(env);
    return RUN_ALL_TESTS();
}
