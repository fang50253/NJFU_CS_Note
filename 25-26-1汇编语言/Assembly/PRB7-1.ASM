assume cs:codesg
codesg segment
start:
        mov ax,2000h
        mov ds,ax
        mov bx,1000h
        mov ax,[bx]
        mov cx,[bx+1]
        mov cx,[bx+2]
        mov ax,4c00h
        int 21h
codesg ends
end start
