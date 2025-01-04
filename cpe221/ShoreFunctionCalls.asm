;
;	This program uses Euclid’s algorithm to find the greatest common divisor of two
; 	numbers. Because Euclid’s algorithm only works on positive numbers, first take
; 	the absolute values of both numbers.
;
; void euclid (int*, int*, int*)
; int main()
; {
; 	int x0 = -8;
; 	int y0 = 9;
; 	int x1 = -295;
; 	int y1 = -45;
; 	int x2 = 280;
; 	int y2 = 8;
; 	int x3 = 81;
; 	int y3 = -243;
; 	int e0, e1, e2, e3;
; 	euclid(x0, y0, &e0);
; 	euclid(x1, y1, &e1);
; 	euclid(x2, y2, &e2);
; 	euclid(x3, y3, &e3);
; }
; void euclid(int x, int y, int *result)
; {
; 	if x < 0
; 		x = -x;
; 	if y < 0
; 		y = -y;
; 	while (x != y)
; 		if (x < y)
; 			y = y – x;
; 		else
; 			x = x – y;
;	 *result = x;
; 	return;
; }

		AREA EUCLID, CODE, READONLY
		ENTRY
		LDR		R0, x0		; define arugments
		LDR		R1, y0
		ADR		R2, e0		
		BL		Euclid		; call subroutine
		LDR		R0, x1
		LDR		R1, y1
		ADR		R2, e1
		BL		Euclid
		LDR		R0, x2
		LDR		R1, y2
		ADR		R2, e2
		BL		Euclid
		LDR		R0, x3
		LDR		R1, y3
		ADR		R2, e3
		BL		Euclid
done 	B		done

Euclid	CMP 	R0, #0		; x - 0 and set flags
		RSBLT	R0, R0, #0	; if x < 0, x = -x
		CMP 	R1, #0		; y - 0 and set flags
		RSBLT	R1, R1, #0	; if y < 0, y = -y
loop	CMP		R0, R1		; x - y and set flags
		STREQ	R0, [R2]	; if x == y, e = x  (greatest common divisor)
		BXEQ	LR			; if x == y, return from subroutine
		SUBLT	R1, R1, R0	; if x < y, y = y - x
		SUBGE	R0, R0, R1	; if x >= y, x = x - y
		B		loop		; loop while x != y
		BX		LR			; return from subroutine

x0		DCD		-8			; declare values for x and y
y0		DCD		9
x1		DCD		-295
y1		DCD		-45
x2		DCD		280
y2		DCD		8
x3		DCD		81
y3		DCD		-243		   	
e0     	SPACE	4			; allocate memory for values of e
e1     	SPACE	4			
e2     	SPACE	4			
e3     	SPACE	4			; addresses 144 - 159
		END
