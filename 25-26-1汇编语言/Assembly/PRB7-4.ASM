assume cs:codesg
codesg segment
start:  mov ax,2000h
        mov ds,ax
        mov bx,1000h
        mov si,0
        mov ax,[bx+si]
        inc si
        mov cx,[bx+si]
        inc si
        mov di,si
        add cx,[bx+di]
        mov ax,4c00h
        int 21h
codesg ends
end start
