/**
 *   MIT License
 *
 *   Copyright (c) 2021 Guilherme Tadashi Maeoka
 *   https://github.com/guimspace/envelope-matrix
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *   SOFTWARE.
 */

module.exports = {
  generateEnvelope, unwrapEnvelope
}

function unwrapEnvelope (envelope, matrix, isLine = false) {
  const n = envelope.diagg.length

  let p = 0

  for (let i = 0; i < n; i++) {
    matrix[i][i] = envelope.diagg[i]

    const d = envelope.enveLin[i] - p
    const top = envelope.enveCol[i + 1]

    while (p < top) {
      if (isLine) matrix[i][d + p] = envelope.enve[p]
      else matrix[d + p][i] = envelope.enve[p]

      p++
    }
  }
}

function generateEnvelope (matrix, isLine = false) {
  const diagg = []
  const enve = []
  const enveCol = []
  const enveLin = []

  const n = matrix.length

  let p = 0
  let j = 0

  while (j < n) {
    diagg[j] = matrix[j][j]

    let i = 0
    if (isLine) {
      while (i < j && matrix[j][i] === 0) { i++ }
    } else {
      while (i < j && matrix[i][j] === 0) { i++ }
    }

    enveCol[j] = p
    enveLin[j] = i

    p += j - i

    while (i < j) {
      isLine ? enve.push(matrix[j][i]) : enve.push(matrix[i][j])
      i++
    }

    j++
  }

  enve.push(null)
  enveCol[j] = p

  return {
    diagg: diagg,
    enve: enve,
    enveCol: enveCol,
    enveLin: enveLin
  }
}
