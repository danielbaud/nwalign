# Sequence Aligner

## Generation

### Dependencies

There are no dependencies
The project is made with c++17 with STL data types

### Compilation

To produce the _nwalign_ binary, do the following:
```bash
$ make
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
$ example1
example1 out
```

```bash
$ example2
example2 out
```
