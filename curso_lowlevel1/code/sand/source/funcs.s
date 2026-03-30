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
   
    mov r4, r0
    mov r5, r1
    mov r6, r2

bucle:

    ldrb r0, [r4, #2]           @r4 = alive
    cmp r0, #0                  @if alive = 0
    beq siguiente               

    ldrb r7, [r4, #0]           @r7 = x
    ldrb r8, [r4, #1]           @r8 = y

    mov r0, r8, lsl #4          @r0 = y * 16
    rsb r0, r0, r8, lsl #8      @r0 = y * 240

    add r0, r0, r7              @r0 = x + y * 240
    mov r0, r0, lsl #1          @r0 = r0 * 2

    add r0, r0, r6              @r0 = r0 + screen
    mov r9, r0                  @r9 = r0

    add r10, r9, #480         @r10 = r9 + 480 

    ldrh r0, [r10, #0]          @r0 = down[0]

    cmp r0, #0                  @if r0 = 0
    moveq r11, #0               @new_x = 0
    beq mover

    ldrh r0, [r10, #-2]         @r0 = down[-1]
    cmp r0, #0                  @if r0 = 0
    mvneq r11, #0               @new_x = -1
    beq mover

    ldrh r0, [r10, #2]          @r0 = down[1]
    cmp r0, #0                  @if r0 = 0

    moveq r11, #1               @new_x = 1
    beq mover

    b matar


mover: 
    
    mov r0, #0                  @r0 = BLACK (0)
    strh r0, [r9, #0]           @*current = BLACK
    mov r1, r11, lsl #1         @r1 = new_x * 2 

    add r1, r1, r10             @r1 = down + new_x * 2
    mov r0, #0x7F00             @r0 = 0x7F00
    orr r0, r0, #0xFF           @r0 = 0x7FFF = WHITE

    strh r0, [r1]               @down[new_x] = WHITE

    add r0, r7, r11             @r0 = x + new_x
    strb r0, [r4, #0]           @particles->x = x + new_x

    add r0, r8, #1              @r0 = y + 1
    strb r0, [r4, #1]           @particles->y = y + 1
    b siguiente


matar:

    mov r0, #0                  @r0 = 0
    strb r0, [r4, #2]           @particles->alive = 0

siguiente:

    add r4, r4, #4              @r4 = siguiente particula
    subs r5, r5, #1             @nparticles-- y actualizar flags
    bne bucle

fin:
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
