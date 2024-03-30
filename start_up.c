
//  
//�@�X�^�[�g�A�b�v����  (�C�����C���A�Z���u��)
//
//   1) �X�^�b�N�|�C���^�̐ݒ�
//   2) �g�p����RAM�̈� __RAM_ADDR_START(0xFF700)�`__STACK_ADDR_START(0xFFE20)�� 0�N���A 
//       (.bss (�����l�Ȃ��ϐ�)�̈�A�X�^�b�N�̈���܂�)�܂�)
//   3)  .data�̈�(ROM�� �ϐ��̏����l)��.dataR(RAM�� �����l�t���ϐ�)�փR�s�[ 
//        (saddr�̈�(0xFFE20�`0xFFF1F)�͖��g�p)
//   4) main()�̌Ăяo��
//


#pragma inline_asm  start_up

void start_up(void)
{
	MOVW	SP,#LOWW(__STACK_ADDR_START)    ; �X�^�b�N�|�C���^�̐ݒ�
	
	                                        ;__RAM_ADDR_START(0xFF700)�`__STACK_ADDR_START(0xFFE20)�� 0�N���A
						;
	MOVW	AX,#LOWW(__STACK_ADDR_START - __RAM_ADDR_START) ; AX = �N���A��
	MOVW	HL,#LOWW(__RAM_ADDR_START)                      ; HL = �N���A����A�h���X
	
	
CLR_LOOP:	
	MOV	[HL],#0x00	;�w��A�h���X��0�N���A
	INCW	HL              ;�A�h���X�C���N�������g
	SUBW    AX,#0x0001      ;�N���A���̃f�N�������g
	
	SKZ			; AX=0(Z=1)�Ȃ�΁A���̖��߂��X�L�b�v, AX>0�Ȃ�΁ABR��
	BR       $CLR_LOOP     ; 
	
				; .data�̈�(ROM�� �ϐ��̏����l)��.dataR(RAM�� �����l�t���ϐ�)�փR�s�[ 
	                        ;
	MOV	ES,#0x00	;  ES = 00

	MOVW	BC,#LOWW(SIZEOF(.data))    ; �R�s�[����o�C�g��
	MOVW    AX,BC		; AX �� BC
	CMPW    AX,#0x0000	; AX=0�Ȃ�� Z=1�@

	SKNZ			; AX>0(Z=0)�Ȃ�΁A���̖��߂��X�L�b�v, AX = 0�Ȃ�΁ABR��
	BR       $START_MAIN    ; 

	
	MOVW	HL,#LOWW(STARTOF(.data))   ; HL = �R�s�[���̃A�h���X ����16�r�b�g
	MOVW    DE,#LOWW(STARTOF(.dataR))  ; DE = �R�s�[��̃A�h���X ����16�r�b�g
	
COPY_LOOP:		
	MOV	A,ES:[HL]	; ROM�̈悩��̃f�[�^�ǂݏo���@
	MOV	[DE],A		; RAM�̈�֊i�[
	
	INCW	HL		; �R�s�[���̃A�h���X �C���N�������g
	INCW	DE		; �R�s�[��̃A�h���X �C���N�������g
		
	DECW	BC		; �R�s�[����o�C�g�� �f�N�������g
	MOVW    AX,BC		; AX �� BC
	CMPW    AX,#0x0000	;�@AX=0�Ȃ�� Z=1�@
	
	SKZ			; AX=0(Z=1)�Ȃ�΁A���̖��߂��X�L�b�v, AX>0�Ȃ�΁ABR��
	BR       $COPY_LOOP     ; 
	
	
START_MAIN:	
	CALL	!!_main		;���C�� main() �Ăяo��
	
	
EXIT:
	BR	$EXIT		; �������[�v

}




