/* Copyright (c) 2016 Baidu, Inc. All Rights Reserved.
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
==============================================================================*/

#pragma once

#include "framework.pb.h"

namespace paddle_mobile {
namespace framework {

//    inline proto::VarType::Type ToDataType(std::type_index type) {
//        using namespace paddle_mobile::framework::proto;
//        if (typeid(float).hash_code() == type.hash_code()) {
//            return proto::VarType::FP32;
//        } else if (typeid(double).hash_code() == type.hash_code()) {
//            return proto::VarType::FP64;
//        } else if (typeid(int).hash_code() == type.hash_code()) {
//            return proto::VarType::INT32;
//        } else if (typeid(int64_t).hash_code() == type.hash_code()) {
//            return proto::VarType::INT64;
//        } else if (typeid(bool).hash_code() == type.hash_code()) {
//            return proto::VarType::BOOL;
//        } else {
////            PADDLE_THROW("Not supported");
//        }
//    }
}
}  // namespace paddle_mobile
