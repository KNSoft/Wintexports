# Wintexports
Wintexports (Windows INTernal EXPORTS) supplements missing symbols in LIBs from `Windows SDK` but exported from corresponding system DLLs. And exports some essential CRT symbols additionally, to make some simple C programs can be run without `Microsoft CRT`. Using by [KNSoft.org](https://knsoft.org) ourselves.

>Wintexports（Windows INTernal EXPORTS）补充了`Windows SDK`里LIB缺失但对应系统DLL导出了的符号。还额外地导出一些必需的CRT符号，可以让一些简单的C程序运行无需`Microsoft CRT`。由[KNSoft.org](https://knsoft.org)自用。

<br>

## Features
Wintexports currently exports:

>Wintexports当前导出了：

<table>
<tr>
<th>System DLL</th>
<th>Category</th>
<th>Symbol</th>
</tr>
<tr>
<td rowspan="2">MSVCRT</td>
<td>CRT</td>
<td>_fltused</td>
</tr>
<tr>
<td>CRT (x86 only)</td>
<td>__isa_available, _(d/f)to(l/ui/ul)3[_legacy], _[u]ltod3</td>
</tr>
<tr>
<td rowspan="2">NTDLL.dll</td>
<td>CRT</td>
<td>
    (wcs/str)(len/cmp/str), vs[w]printf_s<br>
    mem(set/chr/cmp), mem(cpy/move)[_s]
</td>
</tr>
<tr>
<td>CRT (x86 only)</td>
<td>_a[u]ll(div/dvrm/mul/rem)</td>
</tr>
<tr>
<td>Kernel32.dll</td>
<td>API</td>
<td>CreateProcessInternalW</td>
</tr>
</table>
<br>
IDE: Visual Studio 2019 and above, with corresponding SDK

>IDE：Visual Studio 2019及以上，与对应的SDK

<br>

## Caution
In alpha stage, do not use on production environment.
> 处于Alpha阶段，不应在生产环境中使用。

<br>

## To do
+ Exports more missing symbols
+ More CRT features and functions
> + 导出更多缺少的符号
> + 更多CRT功能和函数
