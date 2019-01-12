# shannon-bindings
#### Node.js bindings for the Shannon cipher

Check the [reference implementation repository mirror](https://github.com/timniederhausen/shannon) for more details.

## Setup

`npm i shannon-bindings`

## Usage

```js
const Shannon = require('shannon-bindings')

const shannon = new Shannon(key /* Buffer */)

shannon.nonce(nonce /* Buffer */)
shannon.decrypt(encryptedBuffer /* Buffer, decrypted in place */)
shannon.encrypt(buffer /* Buffer, encrypted in place */)

/* mac is calculated in-place */
const mac = Buffer.alloc(N)
shannon.mac(mac)
```
