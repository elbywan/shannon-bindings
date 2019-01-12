#include <napi.h>
#include "main.h"
#include "../lib/Shannon.h"

shn_ctx contextToStruct(Napi::Object object) {
    Napi::Uint32Array R = object.Get("R").As<Napi::Uint32Array>();
    Napi::Uint32Array CRC = object.Get("CRC").As<Napi::Uint32Array>();
    Napi::Uint32Array initR = object.Get("initR").As<Napi::Uint32Array>();

    shn_ctx context = {
        {
            R[0], R[1], R[2], R[3], R[4], R[5], R[6], R[7],R[8], R[9], R[10], R[11], R[12], R[13], R[14], R[15]
        },
        {
            CRC[0], CRC[1], CRC[2], CRC[3], CRC[4], CRC[5], CRC[6], CRC[7],CRC[8], CRC[9], CRC[10], CRC[11], CRC[12], CRC[13], CRC[14], CRC[15]
        },
        {
            initR[0], initR[1], initR[2], initR[3], initR[4], initR[5], initR[6], initR[7],initR[8], initR[9], initR[10], initR[11], initR[12], initR[13], initR[14], initR[15]
        },
        object.Get("konst").As<Napi::Number>(),
        object.Get("sbuf").As<Napi::Number>(),
        object.Get("mbuf").As<Napi::Number>(),
        object.Get("nbuf").As<Napi::Number>()
    };
    return context;
}

Napi::Object structToContext(shn_ctx ctxStruct, Napi::Env env) {
    Napi::Object result = Napi::Object::New(env);

    Napi::Uint32Array R = Napi::Uint32Array::New(env, SHANNON_N);
    Napi::Uint32Array CRC = Napi::Uint32Array::New(env, SHANNON_N);
    Napi::Uint32Array initR = Napi::Uint32Array::New(env, SHANNON_N);

    for (int i = 0; i < SHANNON_N; i++) {
        R[i] = ctxStruct.R[i];
        CRC[i] = ctxStruct.CRC[i];
        initR[i] = ctxStruct.initR[i];
    }

    result.Set("R", R);
    result.Set("CRC", CRC);
    result.Set("initR", initR);
    result.Set("konst", ctxStruct.konst);
    result.Set("sbuf", ctxStruct.sbuf);
    result.Set("mbuf", ctxStruct.mbuf);
    result.Set("nbuf", ctxStruct.nbuf);

    return result;
}

Napi::Object shannon::shnKey(const Napi::CallbackInfo& info) {
    Napi::Uint8Array key = info[0].As<Napi::Uint8Array>();

    shn_ctx shnContext = { 0 };
    shn_key(&shnContext, key.Data(), key.ByteLength());
    return structToContext(shnContext, info.Env());
}

Napi::Object shannon::shnNonce(const Napi::CallbackInfo& info) {
    Napi::Object context = info[0].As<Napi::Object>();
    Napi::Uint8Array nonce = info[1].As<Napi::Uint8Array>();

    shn_ctx shnContext = contextToStruct(context);
    shn_nonce(&shnContext, nonce.Data(), nonce.ByteLength());
    return structToContext(shnContext, info.Env());
}

Napi::Object shannon::shnStream(const Napi::CallbackInfo& info) {
    Napi::Object context = info[0].As<Napi::Object>();
    Napi::Uint8Array buf = info[1].As<Napi::Uint8Array>();

    shn_ctx shnContext = contextToStruct(context);
    shn_stream(&shnContext, buf.Data(), buf.ByteLength());
    return structToContext(shnContext, info.Env());
}

Napi::Object shannon::shnMacOnly(const Napi::CallbackInfo& info) {
    Napi::Object context = info[0].As<Napi::Object>();
    Napi::Uint8Array buf = info[1].As<Napi::Uint8Array>();

    shn_ctx shnContext = contextToStruct(context);
    shn_maconly(&shnContext, buf.Data(), buf.ByteLength());
    return structToContext(shnContext, info.Env());
}

Napi::Object shannon::shnEncrypt(const Napi::CallbackInfo& info) {
    Napi::Object context = info[0].As<Napi::Object>();
    Napi::Uint8Array buf = info[1].As<Napi::Uint8Array>();

    shn_ctx shnContext = contextToStruct(context);
    shn_encrypt(&shnContext, buf.Data(), buf.ByteLength());
    return structToContext(shnContext, info.Env());
}

Napi::Object shannon::shnDecrypt(const Napi::CallbackInfo& info) {
    Napi::Object context = info[0].As<Napi::Object>();
    Napi::Uint8Array buf = info[1].As<Napi::Uint8Array>();

    shn_ctx shnContext = contextToStruct(context);
    shn_decrypt(&shnContext, buf.Data(), buf.ByteLength());
    return structToContext(shnContext, info.Env());
}

Napi::Object shannon::shnFinish(const Napi::CallbackInfo& info) {
    Napi::Object context = info[0].As<Napi::Object>();
    Napi::Uint8Array buf = info[1].As<Napi::Uint8Array>();

    shn_ctx shnContext = contextToStruct(context);
    shn_finish(&shnContext, buf.Data(), buf.ByteLength());
    return structToContext(shnContext, info.Env());
}


Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    exports.Set("shnKey", Napi::Function::New(env, shannon::shnKey));
    exports.Set("shnNonce", Napi::Function::New(env, shannon::shnNonce));
    exports.Set("shnStream", Napi::Function::New(env, shannon::shnStream));
    exports.Set("shnMacOnly", Napi::Function::New(env, shannon::shnMacOnly));
    exports.Set("shnEncrypt", Napi::Function::New(env, shannon::shnEncrypt));
    exports.Set("shnDecrypt", Napi::Function::New(env, shannon::shnDecrypt));
    exports.Set("shnFinish", Napi::Function::New(env, shannon::shnFinish));
    return exports;
}

NODE_API_MODULE(testaddon, InitAll)