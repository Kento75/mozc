// Copyright 2010-2016, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "data_manager/oss/oss_user_pos_manager.h"

#include "base/embedded_file.h"
#include "base/logging.h"
#include "base/singleton.h"
#include "dictionary/pos_group.h"
#include "dictionary/pos_matcher.h"

namespace mozc {
namespace oss {

OssUserPosManager *OssUserPosManager::GetUserPosManager() {
  return Singleton<OssUserPosManager>::get();
}

namespace {

// Embedded file kUserPosManagerData is defined in this header file.
#include "data_manager/oss/user_pos_manager_data.h"

}  // namespace

OssUserPosManager::OssUserPosManager() {
  const StringPiece data = LoadEmbeddedFile(kUserPosManagerData);
  const char *kMagicNumber = "";  // Magic number is not present.
  CHECK(manager_.InitUserPosManagerDataFromArray(data, kMagicNumber))
      << "Embedded user_pos_manager_data.h is broken";
}

OssUserPosManager::~OssUserPosManager() = default;

void OssUserPosManager::GetUserPOSData(
    StringPiece *token_array_data, StringPiece *string_array_data) const {
  manager_.GetUserPOSData(token_array_data, string_array_data);
}

namespace {
// This header file is autogenerated by gen_pos_matcher_code.py and contains
// kRuleIdTable[] and kRangeTable[].
#include "data_manager/oss/pos_matcher_data.h"

class OssPOSMatcher : public dictionary::POSMatcher {
 public:
  OssPOSMatcher() : POSMatcher(kRuleIdTable, kRangeTables) {}
};
}  // namespace

const dictionary::POSMatcher *OssUserPosManager::GetPOSMatcher() const {
  return Singleton<OssPOSMatcher>::get();
}

}  // namespace oss
}  // namespace mozc
