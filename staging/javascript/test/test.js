const wrap = require('../src/wrap.js')

const matrix = [
  [11, 12, 0, 14, 0, 0],
  [-12, 22, 23, 0, 0, 0],
  [0, -23, 33, 0, 0, 0],
  [-14, 0, 0, 44, 0, 46],
  [0, 0, 0, 0, 55, 0],
  [0, 0, 0, -46, 0, 66]
]
const n = matrix.length

const envelope = wrap.generateEnvelope(matrix)
console.log(envelope)

const regen = new Array(n)
for (let i = 0; i < n; i++) {
  regen[i] = new Array(n).fill(0)
}

wrap.unwrapEnvelope(envelope, regen)
console.log(regen)
