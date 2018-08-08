read_time:
	jsr $FFDE
	sta last_time
	stx last_time+1
	;sty last_time+2
	rts
