# CITS5507 Project
_Jared Healy, 23398223_

# Building
To build the project, simply run the `make` command in the root directory, which will compile all the files into an 
executable called `CITS`.

# Executing
To execute the project, run the command`./CITS` with arguments 
```yaml
f: Filepath to the feature map.  
    If -H & -W are specified, the feature map will be written here. Otherwise it will be
    loaded from this location based on the format specified below.
g: Filepath to the kernel.
    If -x & -y are specified, the kernel will be written here. Otherwise it will be
    loaded from this location based on the format specified below.
o: Filepath to the output.
    Location for the output to be written to.
H: Height of Feature Map to randomly generate.
W: Width of Feature Map to randomly generate.
    If one is specified, the other MUST be specified!
    If specified, the width and height provided will be used to generate a random feature map.
x: Height of Kernel to randomly generate.
y: Width of Kernel to randomly generate.
    If one is specified, the other MUST be specified!
    If specified, the width and height provided will be used to generate a random kernel.
a: Selects the algorithm to use while running the program
    1) Static
    2) Dynamic
    3) Guided
    4) Collapse Static
    5) Linear
```

# Matrix save format
When a matrix is saved or loaded, it will be loaded in the following format:

```
H W
V_00 V_01 ... V_0W
V_10 V_11
...       ...
V_H0          V_HW
```

For example, a 3x4 matrix would be stored like so:

```
3 4
0.884 0.915 0.259 0.937
0.189 0.448 0.337 0.033
0.122 0.169 0.316 0.111
```