# Anti Code Decompile
It confuses the decompiler by inserting fake instructions that cannot be executed in opaque predicates.

This is the original code.
```
int main()
{
    if (rand() == 100)
    {
        printf("hello");
    }
    puts("world!");
}
```

This is the IR of the original code.
```
> BasicBlock size : 3
 - Inst :  %1 = call i32 @rand()
 - Inst :  %2 = icmp eq i32 %1, 100
 - Inst :  br i1 %2, label %3, label %5
> BasicBlock size : 2
 - Inst :  %4 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i64 0, i64 0))
 - Inst :  br label %5
> BasicBlock size : 2
 - Inst :  %6 = call i32 @puts(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i64 0, i64 0))
 - Inst :  ret i32 0
```

This is IR after obfuscation pass.
```
> BasicBlock size : 4
 - Inst :  %1 = call i32 asm sideeffect “cmp x29, 0x109\0Abne 0x8\0A.long 0xdeadbeef\0A”, “”()
 - Inst :  %2 = call i32 @rand()
 - Inst :  %3 = icmp eq i32 %2, 100
 - Inst :  br i1 %3, label %4, label %7
> BasicBlock size : 3
 - Inst :  %5 = call i32 asm sideeffect “cmp x29, 0x109\0Abne 0x8\0A.long 0xdeadbeef\0A”, “”()
 - Inst :  %6 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i64 0, i64 0))
 - Inst :  br label %7
> BasicBlock size : 3
 - Inst :  %8 = call i32 asm sideeffect “cmp x29, 0x109\0Abne 0x8\0A.long 0xdeadbeef\0A”, “”()
 - Inst :  %9 = call i32 @puts(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i64 0, i64 0))
 - Inst :  ret i32 0
```

This is the obfuscated binary.
![image](https://github.com/codetronik/CodetronikPass/blob/main/img/AntiFunctionDecompile.png?raw=true)
