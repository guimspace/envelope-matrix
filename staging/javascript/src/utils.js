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
  initEnvelope, getElement
}

function getElement (envelope, i, j) {
  if (i === j) return envelope.diagg[i]
  else if (envelope.enveCol[j] === envelope.enveCol[j + 1]) return 0

  let p = envelope.enveCol[j]
  const l = envelope.enveLin[p]

  if (l > i) return 0

  p = p + i - l

  return envelope.enve[p]
}

function initEnvelope () {
  return {
    diagg: [],
    enve: [],
    enveCol: [],
    enveLin: []
  }
}
