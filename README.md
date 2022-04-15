# x64dbg-yaraScan
x64dbg-plugin  Yara  (VS2022 c++\clr)
GUI (wait for design)

## Use
![image](https://github.com/nblog/x64dbg-yaraScan/blob/main/screenshots/memory-menu.png)


## Command
find within module:

```yarascan module, ntdll.dll, crypto_signatures.yar```


find within memory region:

```yarascan range, 0, crypto_signatures.yar```


find within memory length:

```yarascan memory, 0x401000, 0x1000, crypto_signatures.yar```


## Credits
- from [retdec yaracpp](https://github.com/avast/retdec/tree/v4.0/src/yaracpp)
- from [fmt](https://github.com/fmtlib/fmt/releases/tag/8.1.1)
- from [glob](https://github.com/p-ranav/glob)
- from [strutil](https://github.com/Shot511/strutil)


## License
x64dbg-yaraScan is licensed under the WTFPL License. Dependencies are under their respective licenses.