.class public Output 
.super java/lang/Object

.method public <init>()V
 aload_0
 invokenonvirtual java/lang/Object/<init>()V
 return
.end method

.method public static print(I)V
 .limit stack 2
 getstatic java/lang/System/out Ljava/io/PrintStream;
 iload_0 
 invokestatic java/lang/Integer/toString(I)Ljava/lang/String;
 invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
 return
.end method

.method public static read()I
 .limit stack 3
 new java/util/Scanner
 dup
 getstatic java/lang/System/in Ljava/io/InputStream;
 invokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V
 invokevirtual java/util/Scanner/next()Ljava/lang/String;
 invokestatic java/lang/Integer.parseInt(Ljava/lang/String;)I
 ireturn
.end method

.method public static run()V
 .limit stack 1024
 .limit locals 256
 ldc 1000
 ldc 2000
 ldc 3000
 invokestatic Output/print(I)V
 invokestatic Output/print(I)V
 invokestatic Output/print(I)V
 ldc 42
 istore 0
 ldc 3
 istore 1
 ldc 9999
 invokestatic Output/print(I)V
 invokestatic Output/read()I
 istore 2
L0:
 iload 1
 ldc 0
 if_icmpgt L1
 goto L2
L1:
 iload 2
 iload 0
 if_icmpeq L3
 goto L4
L3:
 ldc 8888
 invokestatic Output/print(I)V
 ldc 0
 istore 1
 goto L5
L4:
 iload 2
 iload 0
 if_icmplt L6
 goto L7
L6:
 ldc 1111
 invokestatic Output/print(I)V
 goto L8
L7:
 ldc 2222
 invokestatic Output/print(I)V
L8:
 iload 1
 ldc 1
 isub 
 istore 1
 iload 1
 ldc 0
 if_icmpgt L9
 goto L10
L9:
 iload 1
 invokestatic Output/print(I)V
 invokestatic Output/read()I
 istore 2
 goto L11
L10:
L11:
L5:
 goto L0
L2:
 iload 2
 iload 0
 if_icmpeq L12
 goto L13
L12:
 ldc 9000
 invokestatic Output/print(I)V
 goto L14
L13:
 ldc 9001
 invokestatic Output/print(I)V
 iload 0
 invokestatic Output/print(I)V
L14:
 ldc 10
 dup
 istore 3
 dup
 istore 4
 istore 5
 iload 3
 iload 4
 iload 5
 iadd 
 iadd 
 istore 6
 iload 6
 invokestatic Output/print(I)V
 ldc 200
 ldc 4
 idiv 
 istore 7
 ldc 2
 ldc 3
 ldc 4
 imul 
 imul 
 ldc 100
 iload 7
 isub 
 ldc 7
 iadd 
 iadd 
 istore 8
 iload 8
 invokestatic Output/print(I)V
 ldc 1
 istore 9
 ldc 2
 istore 10
 iload 9
 iload 10
 iadd 
 istore 11
 iload 11
 invokestatic Output/print(I)V
 iload 10
 invokestatic Output/print(I)V
 iload 9
 invokestatic Output/print(I)V
 return
.end method

.method public static main([Ljava/lang/String;)V
 invokestatic Output/run()V
 return
.end method

