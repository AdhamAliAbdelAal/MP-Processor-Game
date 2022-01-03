#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

Q::
send,MOV AX,
return
^W::
send,ADD BX,
return
^E::
send,INC CX
return
^R::
send,MOV AX,
return
^T::
send,SUB AX,
return
^Y::
send,MUL DX
return
^U::
send,DIV DX
return
^I::
send,SHL CX,
return
^O::
send,ROR AX,
return
^P::
send,MOV DX,
return
^L::
send,MOV AX,BX
return
^K::
send,MOV AX,DX
return
^J::
send,MOV AX,BX
return
^H::
send,MOV AX,CX
return
^G::
send,MOV AX,[BX+3]
return
^A::
send,MOV AX,[5]
return
^B::
send,MOV SI,FFA2
return
^D::
send,MOV [BX+3],DX
return
^F::
send,MOV [6],DI
return
^M::
send,P1
return
^N::
send,P2
return




