const shannon = require('../build/Release/shannon.node');

class Shannon {
    constructor (key) {
        this.context = shannon.shnKey(key)
    }

    nonce (buffer) {
        this.context = shannon.shnNonce(this.context, buffer)
    }

    stream (buffer) {
        this.context = shannon.shnStream(this.context, buffer)
    }

    macOnly (buffer) {
        this.context = shannon.shnMacOnly(this.context, buffer)
    }

    encrypt (buffer) {
        this.context = shannon.shnEncrypt(this.context, buffer)
        return buffer
    }

    decrypt (buffer) {
        this.context = shannon.shnDecrypt(this.context, buffer)
        return buffer
    }

    finish (buffer) {
        this.context = shannon.shnFinish(this.context, buffer)
        return buffer
    }
}

module.exports = Shannon