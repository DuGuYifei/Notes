# CString写入文件(有中文)

[读写文件](读写文件.md)

## 带中文
```cpp
	//写入位置
	//CString temp;
	FILE* fp = NULL;
	errno_t error;
	CT2A ascii(temp, CP_UTF8);
	error = fopen_s(&fp, (ss + "\\address.txt").c_str(), "w+"); //第一个逗号前是文件位置。逗号之后是打开文件方式
	fprintf(fp, ascii);  //逗号之前是一个指针，表明往里面输入。逗号之后fprintf是往文件里面输入
	fclose(fp);  //记得用完关闭文件
```