#include <napi.h>
#include <string>
#include <vector>
#include "bot.h"

/*
Napi::String greetHello(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string result = helloUser("mike");

  return Napi::String::New(env, result);
}*/

Napi::Object moveBot1(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Array arr = info[0].As<Napi::Array>();
  int boardLength = (int)info[1].As<Napi::Number>();

  std::vector<std::vector<int>> boardState;

  
  for (int i = 0; i < arr.Length(); i++) {
    Napi::Value rowVal = arr[i];
    if (rowVal.IsArray()) {
      Napi::Array row = rowVal.As<Napi::Array>();
      std::vector<int> vec;
      for (int j=0; j<row.Length(); j++) {
        Napi::Value v = row[j];
        if (v.IsNumber())
        {
          int value = (int)v.As<Napi::Number>();
          vec.push_back(value);
        }
      }
      boardState.push_back(vec);
    }
  }
  std::vector<int> result = moveBot(boardState, 2);

  Napi::Object ret = Napi::Object::New(env);
  ret.Set("i", result[1]);
  ret.Set("j", result[2]);
  ret.Set("i2", result[3]);
  ret.Set("j2", result[4]);

  return ret;
  
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(
    Napi::String::New(env, "moveBot1"),
    Napi::Function::New(env, moveBot1)
  );
  return exports;
}

NODE_API_MODULE(bot, Init)

