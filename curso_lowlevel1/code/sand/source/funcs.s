@typedef struct {
@  unsigned char  x, y; offsets 0, 1
@  unsigned char  alive;        2
@  char           PADDING; // Just to be sure sizeof(Particle) is a factor of 4
@} Particle;      sizeof == 4

@typedef struct
@{
@  unsigned short x, y;
@} Source;

@ void SeedParticles (const Source* sources, Particle* particles, int nparticles, unsigned short* screen)
@ r0 -> sources
@ r1 -> particles
@ r2 -> nparticles
@ r3 -> screen

  @.global SeedParticles
  @.global UpdateParticles

SeedParticles:

    stmdb   sp!,{r4,r5,r6,r7}

    mov r7,#8             @ int nsources = 8  

seed_loop:

    ldrb r4,[r1, #2]
    cmp r4, #0
    bne skip_seed         @ if (!particles->alive)



      ldrh r4,[r0, #0]      @ int x = sources->x; offset 0
      ldrh r5,[r0, #2]      @ int y = sources->y; offset 2 ->sizeof 4
      mov r6, #240          @ (int)unsigned short pixel = screen[x + y * SCREEN_W];
      mul r6, r5, r6        @ 
      add r6, r6, r4        @ + x
      mov r6, r6, lsl #1    @ <<1 -> 2 -> Isizeof(short)
      ldrh r6,[r3,r6]

      cmp r6, #0            @if pixel == black
      streqb r4, [r1, #0]   @particles->x = x;
      streqb r5, [r1, #1]   @particles->y = y;
      moveq r6, #1
      streqb r6,[r1, #2]

      add r0,r0,#4          @ sources++
      sub r7,r7,#1          @ nsources--

skip_seed:

      add r1,r1,#4          @ particles++
      sub r2,r2,#1          @ nparticles--

      cmp r2,#0
      beq seed_done
      cmp r7,#0
      bne   seed_loop

seed_done:

    ldmia   sp!,{r4,r5,r6,r7}
    bx      lr


UpdateParticles:

@typedef struct {
@  unsigned char  x, y; offsets 0, 1
@  unsigned char  alive;        2
@  char           PADDING; // Just to be sure sizeof(Particle) is a factor of 4
@} Particle;      sizeof == 4

@typedef struct
@{
@  unsigned short x, y;
@} Source;

@void UpdateParticles (Particle* particles, int nparticles, unsigned short* screen)

@ r0 -> particles
@ r1 -> nparticles
@ r2 -> screen

    stmdb   sp!,{r4,r5,r6,r7,r8,r9,r10,r11,r12,r14}
   
    ldrb    r3,[r1,#2]
    cmp     r3,#0          @ if (particles->alive)

    beq     skip_update
    
    ldrh    r3,[r0,#0]     @ int x = particles->x;
    ldrh    r4,[r0,#2]     @ int y = particles->y; 
    mov     r5,#240        @ SCREEN_W   

    cmp     r4,#33
    beq     NO_SLOT    


    ldmia   sp!,{r4,r5,r6,r7,r8,r9,r10,r11,r12,r14}
    bx      lr

/*
void UpdateParticles (Particle* particles, int nparticles, unsigned short* screen)
{
  //do {
    if (particles->alive) {
      // Mirar si hay sitio debajo
      int x = particles->x;
      int y = particles->y;
      unsigned short* current = &screen [x + SCREEN_W * y];
      unsigned short* down = current + SCREEN_W;
      int new_x = NO_SLOT;
      if (down[0] == BLACK)
        new_x = 0;      // There is room just down the current position
      else if (down[-1] == BLACK)
         // new_x = -1;      // There is room letf-down 
        else if (down[1] == BLACK)
            new_x = 1;      // There is room right-down 

      if (new_x != NO_SLOT) {
        *current = BLACK; // Clean the old position
        down[new_x] = WHITE; // Ocuppy the new position, color white
        particles->x = x + new_x;
        particles->y = y + 1;
      }
      else
        particles->alive = 0;

    }

    //particles++;
    //nparticles--;

  //} while (nparticles != 0);  // Do while there is particles left
}
*/
