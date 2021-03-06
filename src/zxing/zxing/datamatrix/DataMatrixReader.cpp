// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
/*
 *  DataMatrixReader.cpp
 *  zxing
 *
 *  Created by Luiz Silva on 09/02/2010.
 *  Copyright 2010 ZXing authors All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <zxing/datamatrix/DataMatrixReader.h>
#include <zxing/datamatrix/detector/Detector.h>
#include <iostream>

namespace zxing {
namespace datamatrix {

using namespace std;

DataMatrixReader::DataMatrixReader() :
    decoder_() {
}

QSharedPointer<Result> DataMatrixReader::decode(QSharedPointer<BinaryBitmap> image, DecodeHints hints) {
  (void)hints;
  Detector detector(image->getBlackMatrix());
  QSharedPointer<DetectorResult> detectorResult(detector.detect());
  QSharedPointer<std::vector<QSharedPointer<ResultPoint>> > points(detectorResult->getPoints());


  QSharedPointer<DecoderResult> decoderResult(decoder_.decode(detectorResult->getBits()));

  QSharedPointer<Result> result(
    new Result(decoderResult->getText(), decoderResult->getRawBytes(), points, BarcodeFormat::DATA_MATRIX));

  return result;
}

DataMatrixReader::~DataMatrixReader() {
}

}
}
