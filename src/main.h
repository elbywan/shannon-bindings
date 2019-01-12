#include <napi.h>

namespace shannon {
  Napi::Object shnKey(const Napi::CallbackInfo& info);
  Napi::Object shnNonce(const Napi::CallbackInfo& info);
  Napi::Object shnStream(const Napi::CallbackInfo& info);
  Napi::Object shnMacOnly(const Napi::CallbackInfo& info);
  Napi::Object shnEncrypt(const Napi::CallbackInfo& info);
  Napi::Object shnDecrypt(const Napi::CallbackInfo& info);
  Napi::Object shnFinish(const Napi::CallbackInfo& info);
}