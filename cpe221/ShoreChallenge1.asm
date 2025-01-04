;
;	CPE 221 ARM Challenge 1
;	
;      This program copies the elements of one array at the
;	   indexes determined by another array into a third array.
;
; const int size = 10;
; int x[size] = {0, 1, 3, 6, 2, 5, 8, 7, 4, 9};
; int y[size] = {-53, 247, 95, -7, 481, 91, -33, 1500, 29, -83};
; int z[size], i;
; for (i = 0; i < size; i++)
;  z[i] = y[x[i]];
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
	   LDR r6, [r1, r5, LSL #2]		; r6 = y[x[i]]					(32)
	   STR r6, [r2, r3, LSL #2]     ; z[i] = y[x[i]]				(36)
	   ADD r3, r3, #1				; i++							(40)
	   B loop						;								(44)
done   B	  done					;								(48)
									; x has addresses			 (52-91)
x      DCD    0, 1, 3, 6, 2, 5, 8, 7, 4, 9
									; y has addresses		    (92-131)
y      DCD    -53, 247, 95, -7, 481, 91, -33, 1500, 29, -83
z      SPACE  40					; z has addresses		   (132-171)
i      DCD    0						;							   (172)
size   DCD    10					;							   (176)
       END