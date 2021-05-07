# Envelope Matrix
[![License](https://img.shields.io/github/license/guimspace/envelope-matrix)](https://github.com/guimspace/envelope-matrix/blob/main/LICENSE) [![Release](https://img.shields.io/github/v/release/guimspace/envelope-matrix)](https://github.com/guimspace/envelope-matrix/releases)

> Methods to generate and work with envelopes of matrices.

**Notice** Use _envelope-matrix_ methods for educational purposes only. The methods are NOT suitable for professional application as it is not meant to be the most efficient, optimized, correct and secure implementation.

> The _envelope_ of a symmetric or upper-triangular matrix _A_ is a set of ordered pais _(i, j)_, _i < j_, representing element locations in the upper triangle of _A_, defined as follows:
>   _(i, j)_ is in the envelope of _A_ if and only if _a\_kj != 0_ for some _k <= i_. Thus, if the first nonzero entry of the _j_ th column is _a\_mj_ and _m < j_, then _(m, j)_, _(m + 1, j)_, ..., _(j - 1, j)_ are the members of the envelope of _A_ from the _j_ th column. [1]


## About

A basic data structure of four arrays is one way to store the envelope a matrix _A_.

Array | Description
---|---
**DIAG** | Stores the elements from the diagonal of _A_.
**ENV** | Stores the envelope of _A_.
**ENVcol** | Points to elements of **ENV**. **ENVcol(j)** points to position in **ENV** that stores the first non-zero element of the _j_ th column. If the _j_ th column is "empty", then **ENVcol(j)** points to **ENVcol(j + 1)**.
**ENVlin** | Stores the line index of each element from **ENV**.

#### Example

    A = [
      11  12  0   14  0   0;
      0   22  23  0   0   0;
      0   0   33  0   0   0;
      0   0   0   44  0   46;
      0   0   0   0   55  0;
      0   0   0   0   0   66
    ]
    
    DIAG = [11   22   33   44   55   66];
    ENV = [12   23   14    0    0   46    0    null];
    ENVcol = [1   1   2   3   6   6   8];
    ENVlin = [1   2   1   2   3   4   5   null];

To retrieve an element _a\_ij_ from an envelope:
1. If **i == j**, return **DIAG(i)**.
2. Get **pos = ENVcol(j)**.
3. If **pos == ENVcol(j + 1)**, then the _j_ th column is empty: return 0.
4. If **ENVlin(pos) > i**, then the column has 0's up to the **ENVlin(pos)** th line.
5. Get **pos = pos + i - ENVlin(pos)**.
6. Return **ENV(pos)**.


## Contribute code and ideas

Contributors *sign-off* that they adhere to the [Developer Certificate of Origin (DCO)](https://developercertificate.org/) by adding a `Signed-off-by` line to commit messages.

```
$ git commit -s -m 'This is my commit message'
```

For straight forward patches and minor changes, [create a pull request](https://help.github.com/en/articles/creating-a-pull-request).

For larger changes and feature ideas, please open an issue first for a discussion before implementation.


## Reference
1. Watkins, David S. (2010), _Fundamentals of matrix computations_ (Third ed.), New York: John Wiley & Sons, Inc., ISBN 0-470-52833-4
