// Copyright 2010-2021, Google Inc.
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

#include "gui/dictionary_tool/zero_width_splitter.h"

#include <QtGui/QtGui>
#include <QtWidgets/QSplitter>

void ZeroWidthSplitterHandle::paintEvent(QPaintEvent *event) {
#ifdef __APPLE__
  QPainter painter(this);
  QColor topColor(145, 145, 145);
  painter.setPen(topColor);
  painter.drawLine(0, 0, 0, height());
#endif  // __APPLE__
}

QSize ZeroWidthSplitterHandle::sizeHint() const {
  QSize parent = QSplitterHandle::sizeHint();
  return QSize(1, parent.height());
}

ZeroWidthSplitterHandle::ZeroWidthSplitterHandle(Qt::Orientation orientation,
                                                 QSplitter *parent)
    : QSplitterHandle(orientation, parent) {}

ZeroWidthSplitterHandle::~ZeroWidthSplitterHandle() {}

ZeroWidthSplitter::ZeroWidthSplitter(QWidget *parent) : QSplitter(parent) {}

QSplitterHandle *ZeroWidthSplitter::createHandle() {
  return new ZeroWidthSplitterHandle(orientation(), this);
}
