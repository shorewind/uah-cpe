;
;	CPE 221 ARM Basics Question 7
;	
;	This program adds a scalar value to all the elements in one
;      array and stores that in another array.
;
;int main()
;{
;  const int size = 10;
;  int x[size] = {8, 2, 9, 6, 7, 0, 1, 3, 5, 4 };
;  int y[size];
;  int i;
;  for (i = 0; i < size; i++)
;    y[i] = x[i] + i;
;}
;
        AREA ARRAY_PLUS_SCALAR, CODE, READWRITE
        ENTRY
  	    ADR   r0, x        ; pointer to first element of x             (0)
        ADR   r1, y        ; pointer to first element of y             (4)
        LDR   r2, size     ; holds size of arrays                      (8)
        LDR   r3, i        ; holds loop counter                       (12)
loop    SUBS  r4, r3, r2   ; compute i - size                         (16)
        BPL   done         ; if i - size >= 0, done                   (20)
        LDR   r4, [r0]     ; r4 = x[i]                                (24)
        ADD   r4, r4, r3   ; r4 = x[i] + i                            (28)
        STR   r4, [r1]     ; y[i] = x[i] + i                          (32)
        ADD   r0, r0, #4   ; update r0 to point to next element of x  (36)
        ADD   r1, r1, #4   ; update r1 to point to next element of y  (40)
        ADD   r3, r3, #1   ; i++                                      (44)
        B     loop         ;                                          (48)
done    B     done         ;                                          (52)
size    DCD   10           ;                                          (56)
                           ; x has addresses                       (60-99)
x       DCD   8, 2, 9, 6, 7, 0, 1, 3, 5, 4 
                           ; y has addresses                     (100-143)
y       SPACE 40
i       DCD   0            ; (144)
	END
