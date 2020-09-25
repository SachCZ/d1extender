# d1extender

This is a source of two programs. `pos2mesh` and `fun2gfun`. The first one takes a simple
txt or csv file containing the list of positions of nodes, eg:
```
0.0
0.1
0.2
0.3
...
1.0
```
and creates a 2D [MFEM mesh](https://mfem.org/mesh-formats/) from it.

Second one takes also a file with a list of values and returns an
[MFEM grid function](http://mfem.github.io/doxygen/html/classmfem_1_1GridFunction.html)
extended to similarly generated mesh.

## Installing

Classic `cmake`, `make`, `make install` is supported. You can provide a prefix of the install location.

## Executing program

Execute the programs in the following way:

### pos2mesh
```
pos2mesh -i <input_filename> -o <output_filename> -c <cell_count> -f <from> -t <to>
```
eg.:
```
pos2mesh -i positions.csv -o mesh.mfem -c 200 -f 0.0 -t 130.0
```

### fun2gfun
```
pos2mesh -i <input_filename> -o <output_filename> -c <cell_count>
```
eg.:
```
pos2mesh -i density.csv -o density.gf -c 200
```