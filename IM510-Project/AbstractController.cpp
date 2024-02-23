#include <algorithm>
#include <cctype>
#include <locale>
#include <sstream>

#include "AbstractController.h"

AbstractController::AbstractController() {}

// Extracts query/post parameter value from request by given key.
std::string
AbstractController::getParam(const std::shared_ptr<express::Request> req,
                             const std::string &key) {
  std::string result;

  // Check if query param
  result = req->query(key);

  if (result != "") {
    return result;
  }

  // Transform body
  std::string body = "";
  body.assign(req->body.begin(), req->body.end());
  std::istringstream iss(body);

  bool found = false;
  int index = 0;

  // Search for param in body
  for (std::string line; std::getline(iss, line);) {
    if (line.find("name=\"" + key + "\"") != std::string::npos) {
      found = true;
    }

    if (found) {
      index++;
    }

    if (found && index == 3) {
      result = line;
      break;
    }
  }

  // Trim front of string
  result.erase(result.begin(),
               std::find_if(result.begin(), result.end(), [](unsigned char ch) {
                 return !std::isspace(ch);
               }));

  // Trim end of string
  result.erase(std::find_if(result.rbegin(), result.rend(),
                            [](unsigned char ch) { return !std::isspace(ch); })
                   .base(),
               result.end());

  return result;
}
