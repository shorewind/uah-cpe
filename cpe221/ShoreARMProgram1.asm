;
;	CPE 221 ARM Assignment 1
;	
;      This program examines two arrays, element by element and copies the
;      largest number of each pair into a third array.
;
; const int size = 10;
; int x[size] = {100, 3, -1, 2, 4, 4, 2, -1, 3, 100};
; int y[size] = {-53, 247, 95, -7, 481, 91, -33, 1500, 29, -83};
; int z[size], i;
; for (i = 0; i < size; i++)
;   if (x[i] > y[i])
;     z[i] = x[i];
;   else
;     z[i] = y[i];
;
       AREA   PROB_11, CODE, READONLY
       ENTRY
       ADR r0, x					; points to first element of x	(0)
       ADR r1, y					; points to first element of y	(4)
       ADR r2, z					; points to first element of z	(8)
       LDR r3, i					; holds loop counter			(12)
       LDR r4, size					; holds size of arrays			(16)
loop   CMP r3, r4					; compare i and size			(20)
	   BGE done						; if i >= size, done			(24)
	   LDR r5, [r0, r3, LSL #2]		; r5 = x[i]						(28)
	   LDR r6, [r1, r3, LSL #2]		; r6 = y[i]						(32)
	   CMP r5, r6					; compare x[i] and y[i]			(36)
	   STRGT r5, [r2, r3, LSL #2]	; if x[i] > y[i], z[i] = x[i]	(40)
	   STRLE r6, [r2, r3, LSL #2]	; else, z[i] = y[i]				(44)
	   ADD r3, r3, #1				; i++							(48)
	   B loop						;								(52)
done   B	  done					;								(56)
									; x has addresses			 (60-99)
x      DCD    100, 3, -1, 2, 4, 4, 2, -1, 3, 100 
									; y has addresses		   (100-139)
y      DCD    -53, 247, 95, -7, 481, 91, -33, 1500, 29, -83
z      SPACE  40					; z has addresses		   (140-179)
i      DCD    0						;							   (180)
size   DCD    10					;							   (184)
       END