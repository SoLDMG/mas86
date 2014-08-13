mas86
=====

Maza Assembler for x86

WHAT IS MAZA?
  The Maza project is an effort to write a complete (probably self-proclaimed)
  UNIX-like operating system completely from scratch. No Linux-kernel, or GNU
  coreutils/compilers or BSD code. Everything from scratch. From the assembler
  (this) to the "pwd" program to the microkernel with reincarnation server.

WHEN WILL IT BE RELEASED?
  The first release is coming sometime soon. So far the work has been focused on
  the back-end, the part that actually generates the binary output, since it's 
  the most work.

WHY SHOULD I USE IT (WHEN IT COMES OUT)?
  mas86 has outperformed NASM and YASM (although mas86 does not yet support
  full-on assembly language) on assembling about half a million instructions
  (cli & sti). It did however use it's own input language while doing this,
  but the output is exactly the same. Although it doesn't say anything about
  the final product, this may be an indicator that it's really fast compared to
  NASM and YASM respectively.

HOW CAN I CONTRIBUTE?
  A preprocessor would be nice :). But no, I'm not yet accepting any
  contributions at this stage. Once the back-end is complete work will start
  on a preprocessor and then I'll be accepting contributions. Be patient,
  young paladin!
