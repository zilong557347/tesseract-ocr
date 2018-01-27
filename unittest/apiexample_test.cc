///////////////////////////////////////////////////////////////////////
// File:        apiexample_test.cc
// Description: Api Test for Tesseract using text fixtures and parameters.
// Author:      ShreeDevi Kumar
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
///////////////////////////////////////////////////////////////////////
#include "log.h"
#include "include_gunit.h"
#include "baseapi.h"
#include "leptonica/allheaders.h"
#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <limits.h>
#include <time.h>

namespace {

class QuickTest : public testing::Test {
 protected:
  virtual void SetUp() {
    start_time_ = time(NULL);
  }
  virtual void TearDown() {
    const time_t end_time = time(NULL);
    EXPECT_TRUE(end_time - start_time_ <=25) << "The test took too long - " << ::testing::PrintToString(end_time - start_time_);
  }
  time_t start_time_;
  };

  void OCRTester(const char* imgname, const char* groundtruth, const char* tessdatadir, const char* lang) {
    log.info() << tessdatadir << " for language: " << lang << std::endl;
    char *outText;
    std::locale loc("C"); // You can also use "" for the default system locale
    std::ifstream file(groundtruth);
    file.imbue(loc); // Use it for file input
    std::string gtText((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    ASSERT_FALSE(api->Init(tessdatadir, lang)) << "Could not initialize tesseract.";
    Pix *image = pixRead(imgname);
    ASSERT_TRUE(image != nullptr) << "Failed to read test image.";
    api->SetImage(image);
    outText = api->GetUTF8Text();
    EXPECT_EQ(gtText,outText) << "Phototest.tif OCR does not match ground truth for " << ::testing::PrintToString(lang);
    api->End();
    delete [] outText;
    pixDestroy(&image);
  }

  class PhotoTest : public QuickTest ,
      public ::testing::WithParamInterface<const char*> {
  };
  
  TEST_P(PhotoTest, FastOCR) {
  OCRTester("../testing/phototest.tif" ,"../testing/phototest.txt" , "../../tessdata_fast/", GetParam());
  }
  
  TEST_P(PhotoTest, BestOCR) {
  OCRTester("../testing/phototest.tif" ,"../testing/phototest.txt" , "../../tessdata_best/", GetParam());
  }
  
  INSTANTIATE_TEST_CASE_P( APILanguageTest, PhotoTest, 
                        ::testing::Values("eng", "Latin", "Devanagari", "Arabic") );

  class EuroTest : public QuickTest {
  };
  
  TEST_F(EuroTest, FastOCR) {
  OCRTester("../testing/eurotext.tif" ,"../testing/eurotext.txt" , "../../tessdata_fast/", "Latin");
  }

  TEST_F(EuroTest, BestOCR) {
  OCRTester("../testing/eurotext.tif" ,"../testing/eurotext.txt" , "../../tessdata_best/", "Latin");
  }
  
}  // namespace
