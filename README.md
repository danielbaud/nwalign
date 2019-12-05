# Sequence Aligner

## Generation

### Dependencies

There are no dependencies
The project is made with c++17 with STL data types

### Compilation



There are two ways to produce the _nwalign_ binary. To produce the binary with the first implementation (ignoring _o_), do:
```bash
$ make nwalign_simple
```
To produce the binary with the second implementation (that is a bit slower but takes _o_ into account), do:
```bash
$ make nwalign
```
By default, the second version is made doing
```bash
$ make
```
The second version being the most complete, it will be the one used in the usage and example parts. We just made possible to compile a faster version, since it is possible to prefer it to the second one in a realistic context.

Since the substitution matrices are stored in files in the project (in _matrices/_), the project folder **must not** be moved after compiling, since the absolute path of the matrices folder is given at compile time.
However, the _nwalign_ binary can be executed from anywhere.

To remove the produced files, just do:
```bash
$ make clean
```
## Usage

To compute the alignment score of two sequences, do:
```bash
$ ./nwalign score <seq1> <seq2>
```

To get the alignment of two sequences, do:
```bash
$ ./nwalign align <seq1> <seq2>
```

You can also set the values $e$ and $o$ of $\gamma(x) = ex + o$
To do so, do:
```bash
./nwalign --gamma=<e>,<o> <cmd> <seq1> <seq2>
```

## Examples

Here are some example of usage:

```bash
$ ./nwalign score TTAATCGGATCGGATC GAAATCGCTAA
-2.0
```

```bash
$ ./nwalign align TTAATCGGATCGGATC GAAATCGCTAA
TTAATCGGATCGGATC
GAAATC-G--C-TA-A
```

```bash
$ ./nwalign score HDGDYSCDKSLZIKZDYHQNNS FEZFKEILPMMSCGTDTGZ
8.0
```

```bash
$ ./nwalign align HDGDYSCDKSLZIKZDYHQNNS FEZFKEILPMMSCGTDTGZ
HDGDYSCDKS-L-ZIK--ZDYHQNNS
FE-ZF---KEILPMMSCGTD---TGZ
```

```bash
$ ./nwalign --gamma=-2,-2 score GCTDHFYEHDYZHDTCGZTDFZDTLM DZGDYGCCZPIKZASKDDY
-3.0
```

```bash
$ ./nwalign --gamma=-2,-2 align GCTDHFYEHDYZHDTCGZTDFZDTLM DZGDYGCCZPIKZASKDDY
GCTDHFYEHDYZHDTC---GZTDFZDTLM
---D---ZGDY--GCCZPIKZAS-KDD-Y
```
