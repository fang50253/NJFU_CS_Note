assume cs:codesg,ds:datasg
datasg segment
        db 'ibm             '
        db 'dec             '
        db 'dos             '
        db 'vax             '
datasg ends
codesg segment
start:  mov ax,datasg
        mov ds,ax
        mov bx,0
        mov cx,4
s1:     mov si,0
        mov dx,cx
        mov cx,3
s2:     mov al,[bx+si]
        and al,11011111B
        mov [bx+si],al
        inc si
        loop s2
        mov cx,dx
        add bx,16
        loop s1
        mov ax,4c00h
        int 21h
codesg ends
end start
