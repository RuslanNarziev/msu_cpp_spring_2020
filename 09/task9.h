#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <pthread.h>
#include <thread>
#include <algorithm>
#include <functional>
#include "task8.h"

constexpr size_t MAX_MEMORY = 7 * 128 * 1024; // 7/8 of MAX_MEMORY_AVAILABLE, 1MB for all other stuff
constexpr size_t MAX_ELEMS = size_t(float(MAX_MEMORY) / sizeof(uint64_t));

class ThreadSort{
    uint64_t* buf;
    std::ifstream input;
    std::string output;
    ThreadPool pool{2};
private:
    std::vector<std::string> split(){
        input.seekg(0, input.end);
        size_t len = input.tellg() / sizeof(uint64_t);
        input.seekg(0, input.beg);
        size_t count = 2 * std::ceil(float(len) / MAX_ELEMS);
        std::vector<std::string> names(count);
        for (size_t i = 0; i < count; ++i){
            names[i] = std::string("Batch#") + std::to_string(i);
        }
        size_t id = 0;
        while (!input.eof()){
            input.read(reinterpret_cast<char*>(buf), MAX_ELEMS * sizeof(uint64_t));
            size_t read_count = input.gcount() / sizeof(uint64_t);

            auto a = pool.exec([this, read_count](){
                std::sort(buf, buf + read_count / 2);
            });
            a.get();
            auto b = pool.exec([this, read_count](){
                std::sort(buf + read_count / 2, buf + read_count);
            });
            b.get();
            std::ofstream batch(names[id], std::ios::binary);
            std::ofstream batch_2(names[id + 1], std::ios::binary);
            batch.write(reinterpret_cast<const char*>(buf), sizeof(uint64_t) * read_count / 2);
            batch_2.write(reinterpret_cast<const char*>(buf + read_count / 2), sizeof(uint64_t) * read_count / 2);
            batch.close();
            batch_2.close();
            id += 2;
        }

        return names;
    } 

    void merge(std::vector<std::string>& names){
        for (size_t i = 0; i < names.size() - 1; ++i){
            size_t pos = 0;
            uint64_t cur;
            std::ifstream batch(names[i], std::ios::binary);
            std::ifstream batch_2(names[i + 1], std::ios::binary);
            batch_2.seekg(0, batch_2.end);
            size_t len = batch_2.tellg() / sizeof(uint64_t);
            batch_2.seekg(0, batch_2.beg);
            batch_2.read(reinterpret_cast<char*>(buf), len * sizeof(uint64_t));
            batch_2.close();
            batch.read(reinterpret_cast<char*>(&cur), sizeof(uint64_t));
            std::ofstream out(names[i + 1], std::ios::binary);
            while (pos < len && !batch.eof()){
                if (cur > buf[pos]){
                    out.write(reinterpret_cast<const char*>(&buf[pos]), sizeof(uint64_t));
                    ++pos;
                } else if (cur < buf[pos]){
                    out.write(reinterpret_cast<const char*>(&cur), sizeof(uint64_t));
                    batch.read(reinterpret_cast<char*>(&cur), sizeof(uint64_t));
                } else {
                    out.write(reinterpret_cast<const char*>(&cur), sizeof(uint64_t));
                    out.write(reinterpret_cast<const char*>(&buf[pos]), sizeof(uint64_t));
                    batch.read(reinterpret_cast<char*>(&cur), sizeof(uint64_t));
                    ++pos;
                }
            }

            if (pos >= len){
                while (!batch.eof()){
                    out.write(reinterpret_cast<const char*>(&cur), sizeof(uint64_t));
                    batch.read(reinterpret_cast<char*>(&cur), sizeof(uint64_t));
                }
            } else if (batch.eof()){
                out.write(reinterpret_cast<const char*>(&buf[pos]), sizeof(uint64_t) * (len - pos));
            }
            batch.close();
            out.close();
        }
    } 

    void clear(std::vector<std::string>& names){
        for (size_t i = 0; i < names.size(); ++i){
            std::remove(names[i].c_str());
        }
    }

public:
    ThreadSort(const std::string& inp, const std::string& out) : input(inp, std::ios::binary){
        if (!input){
            throw std::runtime_error("input file error");
        }
        buf = new uint64_t [MAX_MEMORY];
        output = out;
    }

    ~ThreadSort(){
        delete [] buf;
        input.close();
    }

    void sort(){
        std::vector<std::string> names = split();
        merge(names);
        std::rename(names.back().c_str(), output.c_str());
        names.pop_back();
        clear(names);
    }
};
