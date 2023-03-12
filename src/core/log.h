/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#pragma once

#include <core/file.h>

#include <cstdio>

namespace cv {
class Log
{
  public:
    Log(const char* fileName);
    ~Log();

    int Write(const char* line);

  private:
    DefaultWriteFile m_file;
};
}