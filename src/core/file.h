/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#pragma once

#include <cstdio>

template<typename IoPolicy>
class File
{
  public:
    File() {}

    File(const char* fileName) { Open(fileName); }

    ~File()
    {
        if (m_file.m_file != nullptr) {
            Close();
        }
    }

    int Open(const char* fileName) { return m_file.Open(fileName); }

    size_t Size() { return m_file.Size(); }

    int Read(char* buf, size_t n) { return m_file.Read(buf, n); }

    int Write(const char* line) { return m_file.Write(line); }

    int Flush() { return m_file.Flush(); }

    int Close() { return m_file.Close(); }

  private:
    IoPolicy m_file;
};

struct DefaultReadPolicy
{
    int Open(const char* fileName)
    {
        m_file = fopen(fileName, "rb");
        if (m_file == nullptr) {
            return -1;
        }

        return 0;
    }

    size_t Size()
    {
        fseek(m_file, 0, SEEK_END);
        auto ret = ftell(m_file);
        fseek(m_file, 0, SEEK_SET);
        return ret;
    }

    int Read(char* buf, size_t n) { return fread(buf, 1, n, m_file); }

    int Close() { return fclose(m_file); }

    FILE* m_file;
};

struct DefaultWritePolicy
{
    int Open(const char* fileName)
    {
        m_file = fopen(fileName, "wb");
        if (m_file == nullptr) {
            return -1;
        }

        return 0;
    }

    int Write(const char* line) { return fprintf(m_file, line); }

    int Flush() { return fflush(m_file); }

    int Close() { return fclose(m_file); }

    FILE* m_file;
};

using DefaultWriteFile = File<DefaultWritePolicy>;
using DefaultReadFile = File<DefaultReadPolicy>;