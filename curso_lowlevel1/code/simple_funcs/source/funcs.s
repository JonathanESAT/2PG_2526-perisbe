@ int Biggest (int a, int b)
@ r0 -> a
@ r1 -> b
@ return in r0


  .global Biggest
  .global Smallest
  .global TotalOfArray
  .global BiggestOfArray
  .global SmallestOfArray

Biggest:
  cmp r1,r0
  movgt r0,r1

  bx lr


Smallest:
  cmp r1,r0
  movlt r0,r1

  bx lr


TotalOfArray:
  ldr r2,[r0],#4
  sub r1,r1,#1
while_total_loop:
  ldr r3,[r0],#4
  add r2,r2,r3
  sub r1,r1,#1
  cmp r1,#0
  bne while_total_loop
  mov r0,r2

  bx lr


BiggestOfArray:
  ldr r2,[r0],#4
  sub r1,r1,#1
while_biggest_loop:
  ldr r3,[r0],#4
  cmp r3,r2
  movgt r2,r3
  sub r1,r1,#1
  cmp r1,#0
  bne while_biggest_loop
  mov r0,r2

  bx lr


SmallestOfArray:
  ldr r2,[r0],#4
  sub r1,r1,#1
while_smallest_loop:
  ldr r3,[r0],#4
  cmp r3,r2
  movlt r2,r3
  sub r1,r1,#1
  cmp r1,#0
  bne while_smallest_loop
  mov r0,r2

  bx lr
@ int Biggest (int a, int b)
@ r0 -> a
@ r1 -> b
@ return in r0


  .global Biggest
  .global Smallest
  .global TotalOfArray
  .global BiggestOfArray
  .global SmallestOfArray

Biggest:
  cmp r1,r0
  movgt r0,r1

  bx lr


Smallest:
  cmp r1,r0
  movlt r0,r1

  bx lr


TotalOfArray:
  ldr r2,[r0],#4
  sub r1,r1,#1
  cmp r1,#0
  ble exit_total
while_total_loop:
  ldr r3,[r0],#4
  add r2,r2,r3
  sub r1,r1,#1
  cmp r1,#0
  bne while_total_loop
exit_total:
  mov r0,r2

  bx lr


BiggestOfArray:
  ldr r2,[r0],#4
  sub r1,r1,#1
  cmp r1,#0
  ble exit_biggest
while_biggest_loop:
  ldr r3,[r0],#4
  cmp r3,r2
  movgt r2,r3
  sub r1,r1,#1
  cmp r1,#0
  bne while_biggest_loop
exit_biggest:
  mov r0,r2

  bx lr


SmallestOfArray:
  ldr r2,[r0],#4
  sub r1,r1,#1
  cmp r1,#0
  ble exit_smallest
while_smallest_loop:
  ldr r3,[r0],#4
  cmp r3,r2
  movlt r2,r3
  sub r1,r1,#1
  cmp r1,#0
  bne while_smallest_loop
exit_smallest:
  mov r0,r2

  bx lr
