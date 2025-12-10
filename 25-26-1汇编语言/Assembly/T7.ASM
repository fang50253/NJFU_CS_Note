assume cs:codesg

data segment
        db '1975','1976','1977','1978','1979','1980','1981','1982','1983'
        db '1984','1985','1986','1987','1988','1989','1990','1991','1992'
        db '1993','1994','1995'
        dd 16,22,382,1356,2390,8000,16000,24486,50065,97479
        dd 140417,197514,345980,590827,803530,1183000,1843000
        dd 2759000,3753000,4649000,5937000
        dw 3,7,9,13,28,38,130,220,476,778,1001,1442,2258
        dw 2793,4037,5635,8226,11542,14430,15257,17800
data ends

table segment
        db 21 dup('year summ ne ?? ')
table ends

codesg segment
start:
        mov     ax, data
        mov     ds, ax
        mov     ax, table
        mov     es, ax
        mov     bx, 0
        mov     di, 21*4*2
        mov     bp, 0
        mov     cx, 21

s:
        mov     ax, [bx]
        mov     es:[bp], ax
        mov     ax, [bx+2]
        mov     es:[bp+2], ax
        mov     ax, [bx+21*4]
        mov     es:[bp+5], ax
        mov     dx, [bx+21*4+2]
        mov     es:[bp+7], dx
        div     word ptr [di]
        mov     dx, [di]
        mov     es:[bp+0Ah], dx
        mov     es:[bp+0Dh], ax
        add     bx, 4
        add     di, 2
        add     bp, 16
        loop    s

        mov     ax, 4C00h
        int     21h
codesg ends
end start