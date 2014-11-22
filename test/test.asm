  .comment ';'
 ; A comment is now      											 ;
							              ; 16 bits. ... 
    .bits16       
   ; 32 bits.  
    .bits32   
   ; 64 bits.										
   .bits64     
   ; A comment is now ;
   .comment '!'    
				.org 31744     
	.include "bpb.inc"    
  .insert _bpb   
   ! A comment is now ;
  ! Ascii.   
   .ascii "Hello world!" 
      mov eax, 0   
	  ret 
		.comment '%'
					% lol
		.asciz "Hello world 2!"
        % A comment is now ;
   .hex   0x0A
   % A comment is now ;
   .dec  0
   % A comment is now ;
   .fill    510 0
  % A comment is now ;
 cli
					sti
														cld   std   		int 128
