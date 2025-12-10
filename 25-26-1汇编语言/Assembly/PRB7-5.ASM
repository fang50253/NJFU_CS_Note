assume cs:codesg
codesg segment
start:  mov ax,2000h
        mov ds,ax
        mov bx,1000h
        mov si,0
        mov ax,[bx+2+si]
        inc si
        mov cx,[bx+2+si]
        inc si
        mov di,si
        mov bx,[bx+2+di]
        mov ax,4c00h
        int 21h
codesg ends
end start
