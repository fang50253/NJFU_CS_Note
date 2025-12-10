assume cs:code
code segment
        mov ax,0
        mov ds,ax
        mov al,0
        mov bx,200h
        mov cx,64
s:      mov [bx],al
        inc al
        inc bx
        loop s
        mov ax,4c00h
        int 21h
code ends
end
