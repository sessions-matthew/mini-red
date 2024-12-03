# MINI-RED

Intended as a smaller and more embeddable nodered replacement for simpler systems. Includes two executables, one for defining the program and the other for running it.

# Building

Edit meson.build with the file path to extracted boost library files

Commands to build are as follows:

```
meson builddir
cd builddir
ninja 
```

File paths are currently hard-coded and executables are meant to be run from the project directory. Ex: ```./builddir/my_executable```.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.