// * License: Apache 2.0
// * File: error_base.h
// * Author: Mai Tianle
// * Date: 2024-08-05
// * Description: Declare common errors to be called in catch(...).
#ifndef LMS_BASE_ERROR_BASE_H_
#define LMS_BASE_ERROR_BASE_H_
namespace library_management_sys {
// Tag types of errors to benefit debugging.
// Example:
//    try throw kNullPointer;
//    catch (BasicError& err_num) std::wcerr << err_num << std::endl;
enum BasicError {
  // throw when SetConsoleTextAttribute() fails.
  kColor = 1,

  // throw when SetConsoleCursorPosition() fails.
  kCoord,

  // throw when functions find any pointer is NULL.
  kNullPointer
};
}  // namespace library_management_sys
#endif  // LMS_BASE_ERROR_BASE_H_