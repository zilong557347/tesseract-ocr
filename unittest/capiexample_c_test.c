///////////////////////////////////////////////////////////////////////
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

// Verifies that C is able to include capi header.
#include <tesseract/capi.h>


#if defined(BUILD_MONOLITHIC)
#define main      tesseract_capi_test_main
#endif

// Verifies that the libtesseract library has C API symbols.
int main() {
  printf("%s\n", TessVersion());
  return 0;
}
