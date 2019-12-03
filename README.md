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
$ example1
example1 out
```

```bash
$ example2
example2 out
```
